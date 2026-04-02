# Echo / Delay Effect — Implementation Plan

## Overview

Add a stereo ping-pong echo module to the Tailwind reverb as an optionally-toggled section.
The echo can be placed **pre-FDN** (echo → reverb, default) or **post-FDN** (reverb → echo)
via a runtime toggle, and offers a **tape color** parameter that blends in HF rolloff and
soft saturation on the feedback path, emulating Echoplex-style character.

BPM sync is deferred to a future iteration.

---

## Design Summary

### Signal Flow

**Pre-FDN (default)**
```
Input → Pre-Delay → [Echo Loop] → Diffusers → FDN → Output EQ → Saturation → Dry/Wet → Out
```

**Post-FDN**
```
Input → Pre-Delay → Diffusers → FDN → [Echo Loop] → Output EQ → Saturation → Dry/Wet → Out
```

The echo module always reads from the **post-predelay signal** as its input source. Its output
is then injected into the signal chain at whichever position the toggle selects. This means
echo is computed once regardless of position.

### Stereo Ping-Pong Structure

```
inL + fb_R*feedback → delay(time) → outL
inR + fb_L*feedback → delay(time) → outR
```

L and R delay outputs cross-feed into each other's inputs each cycle. This creates the classic
L→R→L ping-pong bounce. The FDN then decorrelates and diffuses this further.

### Tape Color

A single `echo_color` knob (0 = clean, 1 = full tape) applies two things **inside the feedback
loop**, so they accumulate with each repeat:

| `echo_color` | HF Rolloff frequency | Drive into fast_tanh |
|---|---|---|
| 0.0 | 20 kHz (flat) | 1.0 (linear) |
| 0.5 | ~4.5 kHz | ~2.5× |
| 1.0 | ~1 kHz | 4.0× |

The saturation is normalized (`tanh(drive·x) / tanh(drive)`) so unity-gain behavior is
preserved at quiet levels — only peaks get compressed on successive repeats.

---

## Step 1 — Faust DSP

### New Parameters (IDs 16–21)

```faust
echo_on       = checkbox("[16][id:echo_on] Echo On");
echo_pre_fdn  = checkbox("[17][id:echo_pre_fdn] Echo Pre-FDN");
echo_time_ms  = hslider("[18][id:echo_time_ms] Echo Time (ms)", 250, 1, 1000, 1) : si.smoo;
echo_feedback = hslider("[19][id:echo_feedback] Echo Feedback", 0.4, 0.0, 0.95, 0.01) : si.smoo;
echo_color    = hslider("[20][id:echo_color] Echo Color", 0.0, 0.0, 1.0, 0.01) : si.smoo;
echo_mix      = hslider("[21][id:echo_mix] Echo Mix", 0.5, 0.0, 1.0, 0.01) : si.smoo;
```

### Max Delay Buffer

```faust
MAX_ECHO_DELAY = 48000;   // 1000 ms @ 48 kHz
```

### Tape Color Chain (runs inside feedback path)

```faust
// HF cutoff: 20 kHz at color=0, ~1 kHz at color=1
echo_hf_freq = 20000.0 * (1000.0/20000.0) ^ echo_color;

// One-pole LP tuned to echo_hf_freq (reuses existing special_lp)
echo_tape_lp = special_lp(0.707, echo_hf_freq);

// Soft saturation: drive 1.0→4.0 across color range, normalized
echo_tape_sat(x) = x * drive : fast_tanh : /(fast_tanh(drive))
with { drive = 1.0 + echo_color * 3.0; };

// Combined: apply both in sequence inside feedback loop
echo_fb_color = echo_tape_lp : echo_tape_sat;
```

### Echo Module (stereo ping-pong, returns wet L/R)

```faust
echo_module(inL, inR) = (body ~ si.bus(2)) : par(i, 2, !), _, _
with {
    body(fbL, fbR) = outL, outR, outL, outR
    with {
        dt   = ms2samp(echo_time_ms) : max(1) : min(MAX_ECHO_DELAY - 1);
        fb   = echo_feedback;
        outL = de.fdelay(MAX_ECHO_DELAY, dt, (inL + fbR*fb) : echo_fb_color);
        outR = de.fdelay(MAX_ECHO_DELAY, dt, (inR + fbL*fb) : echo_fb_color);
    };
};
```

### Routing into Wet Path

Replace the existing `wet_path` in `process` with:

```faust
wet_path(inL, inR) = post_mix
with {
    // Post-predelay signals
    pdL = inL : predelay;
    pdR = inR : predelay;

    // Echo wet output (always computed from post-predelay source)
    (echoL, echoR) = echo_module(pdL, pdR);
    eff_echo_gain  = echo_mix * echo_on;

    // Pre-FDN injection: echo added before diffusers
    pre_fdn_L = pdL + echoL * eff_echo_gain * echo_pre_fdn;
    pre_fdn_R = pdR + echoR * eff_echo_gain * echo_pre_fdn;

    // FDN path
    (fdnL, fdnR) = (pre_fdn_L, pre_fdn_R) : diffuser_L, diffuser_R : fdn_tank;

    // Post-FDN injection: echo added after FDN
    post_fdn_L = fdnL + echoL * eff_echo_gain * (1 - echo_pre_fdn);
    post_fdn_R = fdnR + echoR * eff_echo_gain * (1 - echo_pre_fdn);

    post_mix = (post_fdn_L, post_fdn_R) : par(i, 2, output_eq : output_saturate);
};
```

### Updated `process` Signature

```faust
process = _, _ : par(i, 2, *(input_gain))
        <: wet_path, si.bus(2)
         : interleave_mix
         : par(i, 2, *(output_gain));
with {
    interleave_mix(wL, wR, dL, dR) = xfade(mix, dL, wL), xfade(mix, dR, wR);
};
```

> **FaustIDE validation step**: paste into faustide.grame.fr, listen to the echo in isolation
> by setting `echo_mix = 1.0`, `mix = 0.0`, decay to a short value. Confirm ping-pong and
> tape color audibly degrades HF with increasing `echo_color`.

---

## Step 2 — Codegen

Run the normal codegen pipeline (cmake --build triggers it automatically):

```
cmake --build build --target tailwind_reverb_faust_codegen
```

This regenerates:
- `src/dsp/generated/FaustDSP.h`
- `src/dsp/generated/FaustBridge.h`
- `src/dsp/generated/FaustParams.h`

Verify 6 new parameter zones appear in `FaustParams.h`:
`echo_on`, `echo_pre_fdn`, `echo_time_ms`, `echo_feedback`, `echo_color`, `echo_mix`

---

## Step 3 — UI Section: ECHO

### Layout

A new collapsible row is added **below** the existing CHARACTER / GAIN STAGING row. It is
hidden by default and revealed by clicking a toggle in its section header (same pattern as the
other tool's collapsible section — user will supply that reference code).

```
┌─────────────────────────────────────────────────────────────────────────┐
│  ECHO  [on/off toggle]                            [PRE ↔ POST FDN btn]  │
│                                                                          │
│   TIME          FEEDBACK        COLOR           MIX                     │
│  [knob]         [knob]          [knob]         [knob]                   │
└─────────────────────────────────────────────────────────────────────────┘
```

**Controls:**

| Control | Type | Parameter | Notes |
|---|---|---|---|
| Section header toggle | Button | `echo_on` | Shows/hides body; glows when active |
| PRE / POST | TextButton toggle | `echo_pre_fdn` | Two-state label swap: "PRE" ↔ "POST" |
| Time | RotaryKnob | `echo_time_ms` | Suffix "ms", range 1–1000 |
| Feedback | RotaryKnob | `echo_feedback` | Suffix "%", display as 0–95% |
| Color | RotaryKnob | `echo_color` | No suffix, display 0–100% |
| Mix | RotaryKnob | `echo_mix` | Suffix "%", display 0–100% |

### Visual Style

- Section follows the same panel border + title bar treatment as CHARACTER / GAIN STAGING
- When `echo_on = false`: section header is muted, body collapses (height → 0 with animation)
- PRE/POST button: small pill-style toggle, warm amber when PRE (default), cool blue when POST
  to give a visual cue that the signal path has changed character
- No meters needed in this section

### JUCE Component Structure

```
EchoSection : public juce::Component
  ├── header (click to toggle)
  │     ├── title label ("ECHO")
  │     ├── EchoOnButton (FreezeButton-style toggle, reuses existing look-and-feel)
  │     └── PrePostButton (TextButton, "PRE" / "POST")
  └── body (shown/hidden)
        ├── RotaryKnob  timeKnob      ("TIME")
        ├── RotaryKnob  feedbackKnob  ("FEEDBACK")
        ├── RotaryKnob  colorKnob     ("COLOR")
        └── RotaryKnob  mixKnob       ("MIX")
```

`PluginEditor::resized()` allocates a fixed row height for the echo section when expanded
(same height as bottom row, ~34% of content area), 0 when collapsed.

---

## New Parameters Summary

| ID | Name | Type | Range | Default |
|----|------|------|-------|---------|
| 16 | `echo_on` | bool | — | false |
| 17 | `echo_pre_fdn` | bool | — | true (pre) |
| 18 | `echo_time_ms` | float | 1–1000 ms | 250 ms |
| 19 | `echo_feedback` | float | 0.0–0.95 | 0.4 |
| 20 | `echo_color` | float | 0.0–1.0 | 0.0 |
| 21 | `echo_mix` | float | 0.0–1.0 | 0.5 |

---

## Deferred

- **BPM sync**: note-division quantization of `echo_time_ms` to host tempo via JUCE
  `AudioPlayHead`. Requires host-tempo API exploration, smooth time-stretching on tap changes
  (interpolated delay line crossfade to avoid clicks).
- **Multi-tap**: additional fixed-ratio echo taps (e.g., dotted-eighth alongside quarter).
- **Ping-pong width**: separate L/R delay time offset for stereo spread control.
