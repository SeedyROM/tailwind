// ============================================================================
// TAILWIND REVERB — BigSky-inspired Long Tail Reverb
// Faust DSP — Paste into https://faustide.grame.fr/
// ============================================================================
//
// Features:
//   - 8x8 FDN reverb with Hadamard mixing matrix
//   - Shimmer (octave up) and mutter (octave down) via granular pitch shift
//   - LFO modulation on tank delay lines
//   - Zita-Rev1-style frequency-dependent damping
//   - Full parameter control (12 params)
//
// ============================================================================

import("stdfaust.lib");

// ============================================================================
// PARAMETERS
// ============================================================================

mix          = hslider("[01] Mix", 0.5, 0.0, 1.0, 0.01) : si.smoo;
decay        = hslider("[02] Decay", 0.85, 0.1, 0.99, 0.001) : si.smoo;
predelay_ms  = hslider("[03] Pre-Delay (ms)", 20, 0, 500, 1) : si.smoo;
diffusion    = hslider("[04] Diffusion", 0.7, 0.0, 1.0, 0.01) : si.smoo;
hf_damp      = hslider("[05] Damping", 0.5, 0.0, 1.0, 0.01) : si.smoo;
lf_damp      = hslider("[06] Low Damp", 0.2, 0.0, 1.0, 0.01) : si.smoo;
mod_rate     = hslider("[07] Mod Rate (Hz)", 0.8, 0.1, 5.0, 0.01) : si.smoo;
mod_depth    = hslider("[08] Mod Depth", 0.3, 0.0, 1.0, 0.01) : si.smoo;
shimmer_pitch= hslider("[09] Shimmer Pitch", 0.0, -1.0, 1.0, 0.01) : si.smoo;
shimmer_amt  = hslider("[10] Shimmer Amount", 0.0, 0.0, 1.0, 0.01) : si.smoo;
low_cut_freq = hslider("[11] Low Cut (Hz)", 80, 20, 500, 1) : si.smoo;
high_cut_freq= hslider("[12] High Cut (Hz)", 12000, 1000, 20000, 100) : si.smoo;
freeze       = checkbox("[13] Freeze");

// ============================================================================
// UTILITIES
// ============================================================================

MAX_PRE_DELAY = 24000;
ms2samp(ms) = ms * ma.SR / 1000.0;

// Equal-power crossfade
xfade(m, dry, wet) = dry * cos(m * ma.PI/2) + wet * sin(m * ma.PI/2);

// Soft saturation
soft_clip = ma.tanh;

// Freeze-aware input gain (zero input when frozen)
in_gain = select2(freeze, 1.0, 0.0);

// ============================================================================
// DAMPING FILTERS (Zita-Rev1 / Jot-style)
// ============================================================================
//
// Low-shelf filter for LF damping + tuned one-pole lowpass for HF damping.
// Per-delay-line gain derived from desired T60 decay time.
// Gain is always <= 1.0 at every frequency — guaranteed stable.

// Map decay (0.1..0.99) to T60 in seconds (0.2s .. 30s, exponential)
t60_mid = 0.2 * (30.0/0.2) ^ decay;

// LF T60: lf_damp=0 -> same as mid, lf_damp=1 -> LF decays 4x faster
t60_dc = t60_mid * (1.0 - lf_damp * 0.75);

// HF damping frequency: hf_damp=0 -> 20kHz, hf_damp=1 -> 1kHz
hf_freq = 20000.0 * (1000.0/20000.0) ^ hf_damp;

// LF shelf crossover
lf_freq = 200.0;

// Per-delay-line gain: g = exp(-6.908 * delay_sec / t60)
line_gain_t60(delay_samps, t60) = exp(-6.908 * delay_samps / (t60 * ma.SR));

// Zita-style tuned one-pole lowpass (gain exactly g_target at f_target)
special_lp(g_target, f_target) = si.smooth(p)
with {
    gs = g_target * g_target;
    c = cos(2.0 * ma.PI * f_target / ma.SR);
    mbo2 = (1.0 - gs * c) / max(1e-6, 1.0 - gs);
    p = mbo2 - sqrt(max(0, mbo2 * mbo2 - 1.0));
};

// Low shelf: unity at mid/HF, gain G0 at DC
low_shelf1(G0, fx) = _ <: _, fi.lowpass(1, fx) : _, *(G0 - 1.0) : +;

// Combined damping filter for a given delay length
staynormal = 10.0^(-20);

damping_filter(delay_samps) = gM * low_shelf1(g0 / max(1e-6, gM), lf_freq)
                            : special_lp(gM, hf_freq) : +(staynormal)
with {
    g0 = select2(freeze, line_gain_t60(delay_samps, max(0.01, t60_dc)), 1.0);
    gM = select2(freeze, line_gain_t60(delay_samps, max(0.01, t60_mid)), 1.0);
};

// ============================================================================
// PRE-DELAY
// ============================================================================

predelay = de.fdelay(MAX_PRE_DELAY, ms2samp(predelay_ms));

// ============================================================================
// INPUT DIFFUSERS
// ============================================================================

diff_g = diffusion * 0.75;

diffuser_L = fi.allpass_comb(142, 142, diff_g)
           : fi.allpass_comb(107, 107, diff_g)
           : fi.allpass_comb(379, 379, diff_g)
           : fi.allpass_comb(277, 277, diff_g);

diffuser_R = fi.allpass_comb(151, 151, diff_g)
           : fi.allpass_comb(113, 113, diff_g)
           : fi.allpass_comb(389, 389, diff_g)
           : fi.allpass_comb(283, 283, diff_g);

// ============================================================================
// MODULATION LFOs
// ============================================================================

// max excursion in samples — 48 samples ≈ 1ms @ 48kHz for deep chorus
max_mod_exc = 48;

lfo(freq, phase) = os.oscp(freq, phase) * 0.5 + 0.5 : *(max_mod_exc * mod_depth);

// ============================================================================
// SHIMMER / MUTTER — Granular Pitch Shifter
// ============================================================================
//
// Two overlapping grains reading from a delay buffer. Each grain's read
// pointer advances at (1 - ratio) samples/sample relative to real time.
// For octave up (ratio=2): read pointer moves backward 1 sample/sample
//   → delay decreases over the grain → pitch goes UP
// For octave down (ratio=0.5): read pointer moves forward 0.5 sample/sample extra
//   → delay increases over the grain → pitch goes DOWN
//
// The key: delay_offset = phase * (1.0 - ratio), NO abs().
// Positive offset = read behind (pitch down), negative = read ahead (pitch up).
// We handle the sign by biasing into the valid delay range.

pitch_ratio = 2.0 ^ shimmer_pitch;  // -1→0.5, 0→1.0, +1→2.0
grain_size = 2048;                   // ~42ms @ 48kHz
grain_max_del = 8192;                // must fit the largest offset

// Base delay to keep read pointer always positive.
// Worst case offset: grain_size * |1 - ratio|. At ratio=2, offset = -2048.
// We add a base delay so the read pointer is always > 0.
grain_base_del = 4096;

pitch_shifter(x) = g1 + g2
with {
    // Two ramp phasors offset by half a grain
    ramp1 = +(1) ~ %(grain_size);
    ramp2 = (ramp1 + grain_size/2) % grain_size;

    // Hann window envelope per grain
    hann(p) = sin(ma.PI * float(p) / float(grain_size)) ^ 2.0;

    // Delay offset: how far from the base delay the read pointer is.
    // Positive = further behind (pitch down), negative = closer (pitch up).
    // For ratio=2 (octave up): (1-2) = -1, so offset sweeps from 0 to -grain_size
    //   → total delay decreases → reading "faster" → pitch UP ✓
    // For ratio=0.5 (octave down): (1-0.5) = 0.5, offset sweeps 0 to +grain_size/2
    //   → total delay increases → reading "slower" → pitch DOWN ✓
    del(p) = grain_base_del + float(p) * (1.0 - pitch_ratio)
           : max(1) : min(grain_max_del - 1);

    g1 = de.fdelay(grain_max_del, del(ramp1), x) * hann(ramp1);
    g2 = de.fdelay(grain_max_del, del(ramp2), x) * hann(ramp2);
};

// Shimmer blend: dry/wet mix of original and pitch-shifted signal
shimmer_process = _ <: *(1.0 - shimmer_amt), (pitch_shifter : *(shimmer_amt)) :> _;

// ============================================================================
// FDN TANK — 8x8 Feedback Delay Network
// ============================================================================
//
// Signal flow:
//   Stereo input → shimmer → inject into 8 channels
//   → [add feedback] → Hadamard(8) → 8 delay lines → damping → feedback
//                                                              → stereo taps
//
// Shimmer is BEFORE the tank so the FDN reverberates the pitch-shifted signal.
// This creates the classic BigSky shimmer buildup effect.

// Delay lengths (mutually prime, ~30-58ms @ 48kHz)
fdn_dt(0) = 1423; fdn_dt(1) = 1637; fdn_dt(2) = 1811; fdn_dt(3) = 2003;
fdn_dt(4) = 2179; fdn_dt(5) = 2381; fdn_dt(6) = 2591; fdn_dt(7) = 2797;
fdn_max = 4096;

// Single FDN delay line: delay → damping → normalize
// The / sqrt(8.0) compensates for ro.hadamard(8) being unnormalized.
fdn_line(i) = de.fdelay(fdn_max, dt)
            : damping_filter(fdn_dt(i)) / sqrt(8.0)
            : soft_clip
with {
    dt = fdn_dt(i)
       + lfo(mod_rate * (1.0 + float(i)*0.013), float(i) * ma.PI/4.0)
       : max(1) : min(fdn_max - 1);
};

// FDN tank: stereo in → stereo out
// Shimmer is applied to the input BEFORE entering the tank.
fdn_tank(inL, inR) = (fdn_body(shimL, shimR) ~ si.bus(8)) : par(i, 8, !), _, _
with {
    // Apply shimmer to input — the FDN then reverberates the shifted signal,
    // building up the classic octave-up/down shimmer effect over time
    shimL = inL : shimmer_process;
    shimR = inR : shimmer_process;

    fdn_body(iL, iR, fb0,fb1,fb2,fb3,fb4,fb5,fb6,fb7) =
        fb0 + iL*in_gain*0.25,
        fb1 + iR*in_gain*0.25,
        fb2 + iL*in_gain*0.25,
        fb3 + iR*in_gain*0.25,
        fb4 + iL*in_gain*0.25,
        fb5 + iR*in_gain*0.25,
        fb6 + iL*in_gain*0.25,
        fb7 + iR*in_gain*0.25
        // Hadamard mixing (unnormalized — compensation is in fdn_line)
        : ro.hadamard(8)
        // 8 parallel delay lines with damping
        : par(i, 8, fdn_line(i))
        // Duplicate: 8 for feedback + 2 stereo taps
        <: si.bus(8),
           ((_, !, _, !, _, !, _, !) :> _) * 0.25,    // even lines → L
           ((!, _, !, _, !, _, !, _) :> _) * 0.25     // odd lines  → R
    ;
};

// ============================================================================
// OUTPUT EQ
// ============================================================================

output_eq = fi.highpass(2, low_cut_freq) : fi.lowpass(2, high_cut_freq);

// ============================================================================
// MAIN PROCESS
// ============================================================================

// Stereo in → split dry/wet → FDN reverb → EQ → mix → stereo out
process = _, _ <: wet_path, dry_path : interleave_mix
with {
    wet_path = par(i, 2, predelay) : diffuser_L, diffuser_R
             : fdn_tank : par(i, 2, output_eq);
    dry_path = si.bus(2);
    interleave_mix(wL, wR, dL, dR) = xfade(mix, dL, wL), xfade(mix, dR, wR);
};
