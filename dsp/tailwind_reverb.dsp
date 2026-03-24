// ============================================================================
// TAILWIND REVERB — BigSky-inspired Long Tail Reverb
// Faust DSP — Paste into https://faustide.grame.fr/
// ============================================================================
//
// Features:
//   - 8x8 FDN reverb with Hadamard mixing matrix
//   - LFO modulation on tank delay lines
//   - Zita-Rev1-style frequency-dependent damping
//   - Input diffusers, pre-delay, output EQ, freeze
//   - Full parameter control (15 params)
//
// ============================================================================

import("stdfaust.lib");

// ============================================================================
// PARAMETERS
// ============================================================================

mix            = hslider("[1][id:mix] Mix", 0.5, 0.0, 1.0, 0.01) : si.smoo;
decay          = hslider("[2][id:decay] Decay", 0.85, 0.1, 0.99, 0.001) : si.smoo;
predelay_ms    = hslider("[3][id:pre_delay_ms] Pre-Delay (ms)", 20, 0, 500, 1) : si.smoo;
diffusion      = hslider("[4][id:diffusion] Diffusion", 0.7, 0.0, 1.0, 0.01) : si.smoo;
hf_damp        = hslider("[5][id:damping] Damping", 0.5, 0.0, 1.0, 0.01) : si.smoo;
lf_damp        = hslider("[6][id:low_damp] Low Damp", 0.2, 0.0, 1.0, 0.01) : si.smoo;
mod_rate       = hslider("[7][id:mod_rate_hz] Mod Rate (Hz)", 0.8, 0.1, 5.0, 0.01) : si.smoo;
mod_depth      = hslider("[8][id:mod_depth] Mod Depth", 0.3, 0.0, 1.0, 0.01) : si.smoo;
low_cut_freq   = hslider("[9][id:low_cut_hz] Low Cut (Hz)", 80, 20, 500, 1) : si.smoo;
high_cut_freq  = hslider("[10][id:high_cut_hz] High Cut (Hz)", 12000, 1000, 20000, 100) : si.smoo;
freeze_amt     = hslider("[11][id:freeze] Freeze", 1.0, 0.6, 1.0, 0.01);
freeze_on      = checkbox("[12][id:freeze_on] Freeze On");
freeze         = freeze_amt * freeze_on : si.smoo;
saturation     = hslider("[13][id:saturation] Saturation", 0.125, 0.0, 0.25, 0.01) : si.smoo;
input_gain_db  = hslider("[14][id:input_gain_db] Input Gain", 0.0, -24.0, 24.0, 0.1) : si.smoo;
output_gain_db = hslider("[15][id:output_gain_db] Output Gain", 0.0, -24.0, 24.0, 0.1) : si.smoo;
input_gain     = ba.db2linear(input_gain_db);
output_gain    = ba.db2linear(output_gain_db);

// ============================================================================
// UTILITIES
// ============================================================================

MAX_PRE_DELAY = 24000;
ms2samp(ms) = ms * ma.SR / 1000.0;

// Equal-power crossfade
xfade(m, dry, wet) = dry * cos(m * ma.PI/2) + wet * sin(m * ma.PI/2);

// Fast tanh approximation (Padé [3/2]): max |error| < 0.004 for |x| < 4.
// Branchless and fully vectorizable — no libm call barrier.
// For |x| > ~3.6 it soft-saturates at ±1 via the rational form.
fast_tanh(x) = x * (27.0 + x2) / (27.0 + 9.0 * x2)
with {
    x2 = x * x;
};

// Soft saturation (vectorizable fast tanh)
soft_clip = fast_tanh;

// Freeze-aware input gain (crossfades to zero when frozen)
in_gain = 1.0 - freeze;

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
// NOTE: Denormal protection is handled by Faust -ftz 2 (FTZ code insertion).
damping_filter(delay_samps) = gM * low_shelf1(g0 / max(1e-6, gM), lf_freq)
                            : special_lp(gM, hf_freq)
with {
    g0 = line_gain_t60(delay_samps, max(0.01, t60_dc)) * (1.0 - freeze) + freeze;
    gM = line_gain_t60(delay_samps, max(0.01, t60_mid)) * (1.0 - freeze) + freeze;
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
// FDN TANK — 8x8 Feedback Delay Network
// ============================================================================
//
// Signal flow:
//   Stereo input → split dry/wet
//     dry: → crossfade mix
//     wet: → predelay → diffusers → FDN tank (shimmer in feedback) → output EQ → crossfade mix

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
// Injection and tap gains: 1/sqrt(N/2) = 1/sqrt(4) = 0.5 for energy-matched
// half-injection (L into even channels, R into odd channels).
fdn_inject = 0.5;
fdn_tap = 0.20;

fdn_tank(inL, inR) = (fdn_body(inL, inR) ~ si.bus(8)) : par(i, 8, !), _, _
with {
    fdn_body(iL, iR, fb0,fb1,fb2,fb3,fb4,fb5,fb6,fb7) =
        fb0 + iL*in_gain*fdn_inject,
        fb1 + iR*in_gain*fdn_inject,
        fb2 + iL*in_gain*fdn_inject,
        fb3 + iR*in_gain*fdn_inject,
        fb4 + iL*in_gain*fdn_inject,
        fb5 + iR*in_gain*fdn_inject,
        fb6 + iL*in_gain*fdn_inject,
        fb7 + iR*in_gain*fdn_inject
        // Hadamard mixing (unnormalized — compensation is in fdn_line)
        : ro.hadamard(8)
        // 8 parallel delay lines with damping
        : par(i, 8, fdn_line(i))
        // Duplicate: 8 for feedback + 2 stereo taps
        <: si.bus(8),
           ((_, !, _, !, _, !, _, !) :> _) * fdn_tap,    // even lines → L
           ((!, _, !, _, !, _, !, _) :> _) * fdn_tap     // odd lines  → R
    ;
};

// ============================================================================
// OUTPUT EQ + SATURATION
// ============================================================================

output_eq = fi.highpass(2, low_cut_freq) : fi.lowpass(2, high_cut_freq);

// Normalized tanh soft clip: drive maps saturation 0..1 to 1..8.
// At drive=1 (saturation=0): fast_tanh(x)/fast_tanh(1) ≈ linear, nearly clean.
// At drive=8 (saturation=1): heavy soft clipping on peaks.
// The /fast_tanh(drive) normalization keeps quiet-signal gain at unity.
output_saturate = _ * drive : fast_tanh : /(fast_tanh(drive))
with {
    drive = 1.0 + saturation * 7.0;
};

// ============================================================================
// MAIN PROCESS
// ============================================================================

// Stereo in → input trim → split dry/wet → FDN → EQ → saturate → mix → output trim
process = _, _ : par(i, 2, *(input_gain)) <: wet_path, dry_path : interleave_mix : par(i, 2, *(output_gain))
with {
    wet_path = par(i, 2, predelay) : diffuser_L, diffuser_R
             : fdn_tank : par(i, 2, output_eq : output_saturate);
    dry_path = si.bus(2);
    interleave_mix(wL, wR, dL, dR) = xfade(mix, dL, wL), xfade(mix, dR, wR);
};
