/* ------------------------------------------------------------
name: "tailwind_reverb"
Code generated with Faust 2.79.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn TailwindDSP -scn  -es 1 -mcd 0 -mdd 1024 -mdy 33 -uim -single -ftz 0 -vec -lv 1 -vs 32
------------------------------------------------------------ */

#ifndef  __TailwindDSP_H__
#define  __TailwindDSP_H__

#include "FaustDefs.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS TailwindDSP
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

struct TailwindDSPSIG0 {
	int IOTA0;
	int iVec1[2];
	int iRec40[2];
	
	int getNumInputsTailwindDSPSIG0() {
		return 0;
	}
	int getNumOutputsTailwindDSPSIG0() {
		return 1;
	}
	
	void instanceInitTailwindDSPSIG0(int sample_rate) {
		(void)sample_rate;
		IOTA0 = 0;
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			iVec1[l30] = 0;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			iRec40[l31] = 0;
		}
	}
	
	void fillTailwindDSPSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec1[IOTA0 & 1] = 1;
			iRec40[IOTA0 & 1] = (iVec1[(IOTA0 - 1) & 1] + iRec40[(IOTA0 - 1) & 1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec40[IOTA0 & 1]));
			IOTA0 = IOTA0 + 1;
		}
	}

};

static TailwindDSPSIG0* newTailwindDSPSIG0() { return (TailwindDSPSIG0*)new TailwindDSPSIG0(); }
static void deleteTailwindDSPSIG0(TailwindDSPSIG0* dsp) { delete dsp; }

struct TailwindDSPSIG1 {
	int IOTA1;
	int iVec2[2];
	int iRec45[2];
	
	int getNumInputsTailwindDSPSIG1() {
		return 0;
	}
	int getNumOutputsTailwindDSPSIG1() {
		return 1;
	}
	
	void instanceInitTailwindDSPSIG1(int sample_rate) {
		(void)sample_rate;
		IOTA1 = 0;
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			iVec2[l39] = 0;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			iRec45[l40] = 0;
		}
	}
	
	void fillTailwindDSPSIG1(int count, float* table) {
		for (int i2 = 0; i2 < count; i2 = i2 + 1) {
			iVec2[IOTA1 & 1] = 1;
			iRec45[IOTA1 & 1] = (iVec2[(IOTA1 - 1) & 1] + iRec45[(IOTA1 - 1) & 1]) % 65536;
			table[i2] = std::cos(9.58738e-05f * float(iRec45[IOTA1 & 1]));
			IOTA1 = IOTA1 + 1;
		}
	}

};

static TailwindDSPSIG1* newTailwindDSPSIG1() { return (TailwindDSPSIG1*)new TailwindDSPSIG1(); }
static void deleteTailwindDSPSIG1(TailwindDSPSIG1* dsp) { delete dsp; }

static float ftbl0TailwindDSPSIG0[65536];
static float TailwindDSP_faustpower2_f(float value) {
	return value * value;
}
static float ftbl1TailwindDSPSIG1[65536];

struct TailwindDSP {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec0[64];
	int fRec0_idx;
	int fRec0_idx_save;
	FAUSTFLOAT fHslider1;
	float fRec1[64];
	int fRec1_idx;
	int fRec1_idx_save;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fCheckbox0;
	float fRec15[64];
	int fRec15_idx;
	int fRec15_idx_save;
	FAUSTFLOAT fHslider3;
	float fRec16[64];
	int fRec16_idx;
	int fRec16_idx_save;
	FAUSTFLOAT fHslider4;
	float fRec17[64];
	int fRec17_idx;
	int fRec17_idx_save;
	FAUSTFLOAT fHslider5;
	float fRec26[64];
	int fRec26_idx;
	int fRec26_idx_save;
	FAUSTFLOAT fHslider6;
	float fRec27[64];
	int fRec27_idx;
	int fRec27_idx_save;
	float fYec0[32768];
	int fYec0_idx;
	int fYec0_idx_save;
	float fConst3;
	int iVec0[64];
	int iVec0_idx;
	int iVec0_idx_save;
	float fYec1[256];
	int fYec1_idx;
	int fYec1_idx_save;
	float fRec24[64];
	int fRec24_idx;
	int fRec24_idx_save;
	float fYec2[256];
	int fYec2_idx;
	int fYec2_idx_save;
	float fRec22[64];
	int fRec22_idx;
	int fRec22_idx_save;
	float fYec3[512];
	int fYec3_idx;
	int fYec3_idx_save;
	float fRec20[64];
	int fRec20_idx;
	int fRec20_idx_save;
	float fYec4[512];
	int fYec4_idx;
	int fYec4_idx_save;
	float fRec18[64];
	int fRec18_idx;
	int fRec18_idx_save;
	float fYec5[32768];
	int fYec5_idx;
	int fYec5_idx_save;
	float fYec6[256];
	int fYec6_idx;
	int fYec6_idx_save;
	float fRec34[64];
	int fRec34_idx;
	int fRec34_idx_save;
	float fYec7[256];
	int fYec7_idx;
	int fYec7_idx_save;
	float fRec32[64];
	int fRec32_idx;
	int fRec32_idx_save;
	float fYec8[512];
	int fYec8_idx;
	int fYec8_idx_save;
	float fRec30[64];
	int fRec30_idx;
	int fRec30_idx_save;
	float fYec9[512];
	int fYec9_idx;
	int fYec9_idx_save;
	float fRec28[64];
	int fRec28_idx;
	int fRec28_idx_save;
	FAUSTFLOAT fHslider7;
	float fRec36[64];
	int fRec36_idx;
	int fRec36_idx_save;
	FAUSTFLOAT fHslider8;
	float fRec38[64];
	int fRec38_idx;
	int fRec38_idx_save;
	float fConst4;
	float fRec37[64];
	int fRec37_idx;
	int fRec37_idx_save;
	float fConst5;
	float fConst6;
	float fConst7;
	float fYec10[8192];
	int fYec10_idx;
	int fYec10_idx_save;
	float fYec11[64];
	int fYec11_idx;
	int fYec11_idx_save;
	float fRec39[64];
	int fRec39_idx;
	int fRec39_idx_save;
	FAUSTFLOAT fHslider9;
	float fRec41[64];
	int fRec41_idx;
	int fRec41_idx_save;
	float fConst8;
	float fConst9;
	float fRec14[64];
	int fRec14_idx;
	int fRec14_idx_save;
	float fRec4[64];
	int fRec4_idx;
	int fRec4_idx_save;
	float fConst10;
	float fRec43[64];
	int fRec43_idx;
	int fRec43_idx_save;
	float fYec12[8192];
	int fYec12_idx;
	int fYec12_idx_save;
	float fYec13[64];
	int fYec13_idx;
	int fYec13_idx_save;
	float fRec44[64];
	int fRec44_idx;
	int fRec44_idx_save;
	float fConst11;
	float fRec42[64];
	int fRec42_idx;
	int fRec42_idx_save;
	float fRec5[64];
	int fRec5_idx;
	int fRec5_idx_save;
	float fConst12;
	float fRec47[64];
	int fRec47_idx;
	int fRec47_idx_save;
	float fYec14[8192];
	int fYec14_idx;
	int fYec14_idx_save;
	float fYec15[64];
	int fYec15_idx;
	int fYec15_idx_save;
	float fRec48[64];
	int fRec48_idx;
	int fRec48_idx_save;
	float fConst13;
	float fRec46[64];
	int fRec46_idx;
	int fRec46_idx_save;
	float fRec6[64];
	int fRec6_idx;
	int fRec6_idx_save;
	float fConst14;
	float fRec50[64];
	int fRec50_idx;
	int fRec50_idx_save;
	float fYec16[8192];
	int fYec16_idx;
	int fYec16_idx_save;
	float fYec17[64];
	int fYec17_idx;
	int fYec17_idx_save;
	float fRec51[64];
	int fRec51_idx;
	int fRec51_idx_save;
	float fConst15;
	float fRec49[64];
	int fRec49_idx;
	int fRec49_idx_save;
	float fRec7[64];
	int fRec7_idx;
	int fRec7_idx_save;
	float fConst16;
	float fRec53[64];
	int fRec53_idx;
	int fRec53_idx_save;
	float fYec18[8192];
	int fYec18_idx;
	int fYec18_idx_save;
	float fYec19[64];
	int fYec19_idx;
	int fYec19_idx_save;
	float fRec54[64];
	int fRec54_idx;
	int fRec54_idx_save;
	float fConst17;
	float fRec52[64];
	int fRec52_idx;
	int fRec52_idx_save;
	float fRec8[64];
	int fRec8_idx;
	int fRec8_idx_save;
	float fConst18;
	float fRec56[64];
	int fRec56_idx;
	int fRec56_idx_save;
	float fYec20[8192];
	int fYec20_idx;
	int fYec20_idx_save;
	float fYec21[64];
	int fYec21_idx;
	int fYec21_idx_save;
	float fRec57[64];
	int fRec57_idx;
	int fRec57_idx_save;
	float fConst19;
	float fRec55[64];
	int fRec55_idx;
	int fRec55_idx_save;
	float fRec9[64];
	int fRec9_idx;
	int fRec9_idx_save;
	float fConst20;
	float fRec59[64];
	int fRec59_idx;
	int fRec59_idx_save;
	float fYec22[8192];
	int fYec22_idx;
	int fYec22_idx_save;
	float fYec23[64];
	int fYec23_idx;
	int fYec23_idx_save;
	float fRec60[64];
	int fRec60_idx;
	int fRec60_idx_save;
	float fConst21;
	float fRec58[64];
	int fRec58_idx;
	int fRec58_idx_save;
	float fRec10[64];
	int fRec10_idx;
	int fRec10_idx_save;
	float fConst22;
	float fRec62[64];
	int fRec62_idx;
	int fRec62_idx_save;
	float fYec24[8192];
	int fYec24_idx;
	int fYec24_idx_save;
	float fYec25[64];
	int fYec25_idx;
	int fYec25_idx_save;
	float fRec63[64];
	int fRec63_idx;
	int fRec63_idx_save;
	float fConst23;
	float fRec61[64];
	int fRec61_idx;
	int fRec61_idx_save;
	float fRec11[64];
	int fRec11_idx;
	int fRec11_idx_save;
	FAUSTFLOAT fHslider10;
	float fRec64[64];
	int fRec64_idx;
	int fRec64_idx_save;
	float fConst24;
	float fRec3[64];
	int fRec3_idx;
	int fRec3_idx_save;
	FAUSTFLOAT fHslider11;
	float fRec65[64];
	int fRec65_idx;
	int fRec65_idx_save;
	float fRec2[64];
	int fRec2_idx;
	int fRec2_idx_save;
	FAUSTFLOAT fHslider12;
	float fRec66[64];
	int fRec66_idx;
	int fRec66_idx_save;
	FAUSTFLOAT fHslider13;
	float fRec67[64];
	int fRec67_idx;
	int fRec67_idx_save;
	float fRec69[64];
	int fRec69_idx;
	int fRec69_idx_save;
	float fRec68[64];
	int fRec68_idx;
	int fRec68_idx_save;
	
	TailwindDSP() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -cn TailwindDSP -scn  -es 1 -mcd 0 -mdd 1024 -mdy 33 -uim -single -ftz 0 -vec -lv 1 -vs 32");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("filename", "tailwind_reverb.dsp");
		m->declare("filters.lib/allpass_comb:author", "Julius O. Smith III");
		m->declare("filters.lib/allpass_comb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpass_comb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "tailwind_reverb");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/hadamard:author", "Remy Muller, revised by Romain Michon");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		TailwindDSPSIG0* sig0 = newTailwindDSPSIG0();
		sig0->instanceInitTailwindDSPSIG0(sample_rate);
		sig0->fillTailwindDSPSIG0(65536, ftbl0TailwindDSPSIG0);
		TailwindDSPSIG1* sig1 = newTailwindDSPSIG1();
		sig1->instanceInitTailwindDSPSIG1(sample_rate);
		sig1->fillTailwindDSPSIG1(65536, ftbl1TailwindDSPSIG1);
		deleteTailwindDSPSIG0(sig0);
		deleteTailwindDSPSIG1(sig1);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 0.001f * fConst0;
		fConst4 = 1.0f / fConst0;
		fConst5 = 1.0f / std::tan(628.31854f / fConst0);
		fConst6 = 1.0f / (fConst5 + 1.0f);
		fConst7 = 1.0f - fConst5;
		fConst8 = 9830.084f / fConst0;
		fConst9 = 125663.7f / fConst0;
		fConst10 = 1.013f / fConst0;
		fConst11 = 11308.396f / fConst0;
		fConst12 = 1.026f / fConst0;
		fConst13 = 12510.388f / fConst0;
		fConst14 = 1.039f / fConst0;
		fConst15 = 13836.724f / fConst0;
		fConst16 = 1.052f / fConst0;
		fConst17 = 15052.532f / fConst0;
		fConst18 = 1.065f / fConst0;
		fConst19 = 16447.947f / fConst0;
		fConst20 = 1.078f / fConst0;
		fConst21 = 17898.629f / fConst0;
		fConst22 = 1.091f / fConst0;
		fConst23 = 19321.676f / fConst0;
		fConst24 = 3.1415927f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.85f);
		fHslider4 = FAUSTFLOAT(0.5f);
		fHslider5 = FAUSTFLOAT(2e+01f);
		fHslider6 = FAUSTFLOAT(0.7f);
		fHslider7 = FAUSTFLOAT(0.3f);
		fHslider8 = FAUSTFLOAT(0.8f);
		fHslider9 = FAUSTFLOAT(0.2f);
		fHslider10 = FAUSTFLOAT(8e+01f);
		fHslider11 = FAUSTFLOAT(1.2e+04f);
		fHslider12 = FAUSTFLOAT(0.125f);
		fHslider13 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 64; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		fRec0_idx = 0;
		fRec0_idx_save = 0;
		for (int l1 = 0; l1 < 64; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		fRec1_idx = 0;
		fRec1_idx_save = 0;
		for (int l2 = 0; l2 < 64; l2 = l2 + 1) {
			fRec15[l2] = 0.0f;
		}
		fRec15_idx = 0;
		fRec15_idx_save = 0;
		for (int l3 = 0; l3 < 64; l3 = l3 + 1) {
			fRec16[l3] = 0.0f;
		}
		fRec16_idx = 0;
		fRec16_idx_save = 0;
		for (int l4 = 0; l4 < 64; l4 = l4 + 1) {
			fRec17[l4] = 0.0f;
		}
		fRec17_idx = 0;
		fRec17_idx_save = 0;
		for (int l5 = 0; l5 < 64; l5 = l5 + 1) {
			fRec26[l5] = 0.0f;
		}
		fRec26_idx = 0;
		fRec26_idx_save = 0;
		for (int l6 = 0; l6 < 64; l6 = l6 + 1) {
			fRec27[l6] = 0.0f;
		}
		fRec27_idx = 0;
		fRec27_idx_save = 0;
		for (int l7 = 0; l7 < 32768; l7 = l7 + 1) {
			fYec0[l7] = 0.0f;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l8 = 0; l8 < 64; l8 = l8 + 1) {
			iVec0[l8] = 0;
		}
		iVec0_idx = 0;
		iVec0_idx_save = 0;
		for (int l9 = 0; l9 < 256; l9 = l9 + 1) {
			fYec1[l9] = 0.0f;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l10 = 0; l10 < 64; l10 = l10 + 1) {
			fRec24[l10] = 0.0f;
		}
		fRec24_idx = 0;
		fRec24_idx_save = 0;
		for (int l11 = 0; l11 < 256; l11 = l11 + 1) {
			fYec2[l11] = 0.0f;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l12 = 0; l12 < 64; l12 = l12 + 1) {
			fRec22[l12] = 0.0f;
		}
		fRec22_idx = 0;
		fRec22_idx_save = 0;
		for (int l13 = 0; l13 < 512; l13 = l13 + 1) {
			fYec3[l13] = 0.0f;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l14 = 0; l14 < 64; l14 = l14 + 1) {
			fRec20[l14] = 0.0f;
		}
		fRec20_idx = 0;
		fRec20_idx_save = 0;
		for (int l15 = 0; l15 < 512; l15 = l15 + 1) {
			fYec4[l15] = 0.0f;
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l16 = 0; l16 < 64; l16 = l16 + 1) {
			fRec18[l16] = 0.0f;
		}
		fRec18_idx = 0;
		fRec18_idx_save = 0;
		for (int l17 = 0; l17 < 32768; l17 = l17 + 1) {
			fYec5[l17] = 0.0f;
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l18 = 0; l18 < 256; l18 = l18 + 1) {
			fYec6[l18] = 0.0f;
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
		for (int l19 = 0; l19 < 64; l19 = l19 + 1) {
			fRec34[l19] = 0.0f;
		}
		fRec34_idx = 0;
		fRec34_idx_save = 0;
		for (int l20 = 0; l20 < 256; l20 = l20 + 1) {
			fYec7[l20] = 0.0f;
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l21 = 0; l21 < 64; l21 = l21 + 1) {
			fRec32[l21] = 0.0f;
		}
		fRec32_idx = 0;
		fRec32_idx_save = 0;
		for (int l22 = 0; l22 < 512; l22 = l22 + 1) {
			fYec8[l22] = 0.0f;
		}
		fYec8_idx = 0;
		fYec8_idx_save = 0;
		for (int l23 = 0; l23 < 64; l23 = l23 + 1) {
			fRec30[l23] = 0.0f;
		}
		fRec30_idx = 0;
		fRec30_idx_save = 0;
		for (int l24 = 0; l24 < 512; l24 = l24 + 1) {
			fYec9[l24] = 0.0f;
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l25 = 0; l25 < 64; l25 = l25 + 1) {
			fRec28[l25] = 0.0f;
		}
		fRec28_idx = 0;
		fRec28_idx_save = 0;
		for (int l26 = 0; l26 < 64; l26 = l26 + 1) {
			fRec36[l26] = 0.0f;
		}
		fRec36_idx = 0;
		fRec36_idx_save = 0;
		for (int l27 = 0; l27 < 64; l27 = l27 + 1) {
			fRec38[l27] = 0.0f;
		}
		fRec38_idx = 0;
		fRec38_idx_save = 0;
		for (int l28 = 0; l28 < 64; l28 = l28 + 1) {
			fRec37[l28] = 0.0f;
		}
		fRec37_idx = 0;
		fRec37_idx_save = 0;
		for (int l29 = 0; l29 < 8192; l29 = l29 + 1) {
			fYec10[l29] = 0.0f;
		}
		fYec10_idx = 0;
		fYec10_idx_save = 0;
		for (int l32 = 0; l32 < 64; l32 = l32 + 1) {
			fYec11[l32] = 0.0f;
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l33 = 0; l33 < 64; l33 = l33 + 1) {
			fRec39[l33] = 0.0f;
		}
		fRec39_idx = 0;
		fRec39_idx_save = 0;
		for (int l34 = 0; l34 < 64; l34 = l34 + 1) {
			fRec41[l34] = 0.0f;
		}
		fRec41_idx = 0;
		fRec41_idx_save = 0;
		for (int l35 = 0; l35 < 64; l35 = l35 + 1) {
			fRec14[l35] = 0.0f;
		}
		fRec14_idx = 0;
		fRec14_idx_save = 0;
		for (int l36 = 0; l36 < 64; l36 = l36 + 1) {
			fRec4[l36] = 0.0f;
		}
		fRec4_idx = 0;
		fRec4_idx_save = 0;
		for (int l37 = 0; l37 < 64; l37 = l37 + 1) {
			fRec43[l37] = 0.0f;
		}
		fRec43_idx = 0;
		fRec43_idx_save = 0;
		for (int l38 = 0; l38 < 8192; l38 = l38 + 1) {
			fYec12[l38] = 0.0f;
		}
		fYec12_idx = 0;
		fYec12_idx_save = 0;
		for (int l41 = 0; l41 < 64; l41 = l41 + 1) {
			fYec13[l41] = 0.0f;
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l42 = 0; l42 < 64; l42 = l42 + 1) {
			fRec44[l42] = 0.0f;
		}
		fRec44_idx = 0;
		fRec44_idx_save = 0;
		for (int l43 = 0; l43 < 64; l43 = l43 + 1) {
			fRec42[l43] = 0.0f;
		}
		fRec42_idx = 0;
		fRec42_idx_save = 0;
		for (int l44 = 0; l44 < 64; l44 = l44 + 1) {
			fRec5[l44] = 0.0f;
		}
		fRec5_idx = 0;
		fRec5_idx_save = 0;
		for (int l45 = 0; l45 < 64; l45 = l45 + 1) {
			fRec47[l45] = 0.0f;
		}
		fRec47_idx = 0;
		fRec47_idx_save = 0;
		for (int l46 = 0; l46 < 8192; l46 = l46 + 1) {
			fYec14[l46] = 0.0f;
		}
		fYec14_idx = 0;
		fYec14_idx_save = 0;
		for (int l47 = 0; l47 < 64; l47 = l47 + 1) {
			fYec15[l47] = 0.0f;
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l48 = 0; l48 < 64; l48 = l48 + 1) {
			fRec48[l48] = 0.0f;
		}
		fRec48_idx = 0;
		fRec48_idx_save = 0;
		for (int l49 = 0; l49 < 64; l49 = l49 + 1) {
			fRec46[l49] = 0.0f;
		}
		fRec46_idx = 0;
		fRec46_idx_save = 0;
		for (int l50 = 0; l50 < 64; l50 = l50 + 1) {
			fRec6[l50] = 0.0f;
		}
		fRec6_idx = 0;
		fRec6_idx_save = 0;
		for (int l51 = 0; l51 < 64; l51 = l51 + 1) {
			fRec50[l51] = 0.0f;
		}
		fRec50_idx = 0;
		fRec50_idx_save = 0;
		for (int l52 = 0; l52 < 8192; l52 = l52 + 1) {
			fYec16[l52] = 0.0f;
		}
		fYec16_idx = 0;
		fYec16_idx_save = 0;
		for (int l53 = 0; l53 < 64; l53 = l53 + 1) {
			fYec17[l53] = 0.0f;
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l54 = 0; l54 < 64; l54 = l54 + 1) {
			fRec51[l54] = 0.0f;
		}
		fRec51_idx = 0;
		fRec51_idx_save = 0;
		for (int l55 = 0; l55 < 64; l55 = l55 + 1) {
			fRec49[l55] = 0.0f;
		}
		fRec49_idx = 0;
		fRec49_idx_save = 0;
		for (int l56 = 0; l56 < 64; l56 = l56 + 1) {
			fRec7[l56] = 0.0f;
		}
		fRec7_idx = 0;
		fRec7_idx_save = 0;
		for (int l57 = 0; l57 < 64; l57 = l57 + 1) {
			fRec53[l57] = 0.0f;
		}
		fRec53_idx = 0;
		fRec53_idx_save = 0;
		for (int l58 = 0; l58 < 8192; l58 = l58 + 1) {
			fYec18[l58] = 0.0f;
		}
		fYec18_idx = 0;
		fYec18_idx_save = 0;
		for (int l59 = 0; l59 < 64; l59 = l59 + 1) {
			fYec19[l59] = 0.0f;
		}
		fYec19_idx = 0;
		fYec19_idx_save = 0;
		for (int l60 = 0; l60 < 64; l60 = l60 + 1) {
			fRec54[l60] = 0.0f;
		}
		fRec54_idx = 0;
		fRec54_idx_save = 0;
		for (int l61 = 0; l61 < 64; l61 = l61 + 1) {
			fRec52[l61] = 0.0f;
		}
		fRec52_idx = 0;
		fRec52_idx_save = 0;
		for (int l62 = 0; l62 < 64; l62 = l62 + 1) {
			fRec8[l62] = 0.0f;
		}
		fRec8_idx = 0;
		fRec8_idx_save = 0;
		for (int l63 = 0; l63 < 64; l63 = l63 + 1) {
			fRec56[l63] = 0.0f;
		}
		fRec56_idx = 0;
		fRec56_idx_save = 0;
		for (int l64 = 0; l64 < 8192; l64 = l64 + 1) {
			fYec20[l64] = 0.0f;
		}
		fYec20_idx = 0;
		fYec20_idx_save = 0;
		for (int l65 = 0; l65 < 64; l65 = l65 + 1) {
			fYec21[l65] = 0.0f;
		}
		fYec21_idx = 0;
		fYec21_idx_save = 0;
		for (int l66 = 0; l66 < 64; l66 = l66 + 1) {
			fRec57[l66] = 0.0f;
		}
		fRec57_idx = 0;
		fRec57_idx_save = 0;
		for (int l67 = 0; l67 < 64; l67 = l67 + 1) {
			fRec55[l67] = 0.0f;
		}
		fRec55_idx = 0;
		fRec55_idx_save = 0;
		for (int l68 = 0; l68 < 64; l68 = l68 + 1) {
			fRec9[l68] = 0.0f;
		}
		fRec9_idx = 0;
		fRec9_idx_save = 0;
		for (int l69 = 0; l69 < 64; l69 = l69 + 1) {
			fRec59[l69] = 0.0f;
		}
		fRec59_idx = 0;
		fRec59_idx_save = 0;
		for (int l70 = 0; l70 < 8192; l70 = l70 + 1) {
			fYec22[l70] = 0.0f;
		}
		fYec22_idx = 0;
		fYec22_idx_save = 0;
		for (int l71 = 0; l71 < 64; l71 = l71 + 1) {
			fYec23[l71] = 0.0f;
		}
		fYec23_idx = 0;
		fYec23_idx_save = 0;
		for (int l72 = 0; l72 < 64; l72 = l72 + 1) {
			fRec60[l72] = 0.0f;
		}
		fRec60_idx = 0;
		fRec60_idx_save = 0;
		for (int l73 = 0; l73 < 64; l73 = l73 + 1) {
			fRec58[l73] = 0.0f;
		}
		fRec58_idx = 0;
		fRec58_idx_save = 0;
		for (int l74 = 0; l74 < 64; l74 = l74 + 1) {
			fRec10[l74] = 0.0f;
		}
		fRec10_idx = 0;
		fRec10_idx_save = 0;
		for (int l75 = 0; l75 < 64; l75 = l75 + 1) {
			fRec62[l75] = 0.0f;
		}
		fRec62_idx = 0;
		fRec62_idx_save = 0;
		for (int l76 = 0; l76 < 8192; l76 = l76 + 1) {
			fYec24[l76] = 0.0f;
		}
		fYec24_idx = 0;
		fYec24_idx_save = 0;
		for (int l77 = 0; l77 < 64; l77 = l77 + 1) {
			fYec25[l77] = 0.0f;
		}
		fYec25_idx = 0;
		fYec25_idx_save = 0;
		for (int l78 = 0; l78 < 64; l78 = l78 + 1) {
			fRec63[l78] = 0.0f;
		}
		fRec63_idx = 0;
		fRec63_idx_save = 0;
		for (int l79 = 0; l79 < 64; l79 = l79 + 1) {
			fRec61[l79] = 0.0f;
		}
		fRec61_idx = 0;
		fRec61_idx_save = 0;
		for (int l80 = 0; l80 < 64; l80 = l80 + 1) {
			fRec11[l80] = 0.0f;
		}
		fRec11_idx = 0;
		fRec11_idx_save = 0;
		for (int l81 = 0; l81 < 64; l81 = l81 + 1) {
			fRec64[l81] = 0.0f;
		}
		fRec64_idx = 0;
		fRec64_idx_save = 0;
		for (int l82 = 0; l82 < 64; l82 = l82 + 1) {
			fRec3[l82] = 0.0f;
		}
		fRec3_idx = 0;
		fRec3_idx_save = 0;
		for (int l83 = 0; l83 < 64; l83 = l83 + 1) {
			fRec65[l83] = 0.0f;
		}
		fRec65_idx = 0;
		fRec65_idx_save = 0;
		for (int l84 = 0; l84 < 64; l84 = l84 + 1) {
			fRec2[l84] = 0.0f;
		}
		fRec2_idx = 0;
		fRec2_idx_save = 0;
		for (int l85 = 0; l85 < 64; l85 = l85 + 1) {
			fRec66[l85] = 0.0f;
		}
		fRec66_idx = 0;
		fRec66_idx_save = 0;
		for (int l86 = 0; l86 < 64; l86 = l86 + 1) {
			fRec67[l86] = 0.0f;
		}
		fRec67_idx = 0;
		fRec67_idx_save = 0;
		for (int l87 = 0; l87 < 64; l87 = l87 + 1) {
			fRec69[l87] = 0.0f;
		}
		fRec69_idx = 0;
		fRec69_idx_save = 0;
		for (int l88 = 0; l88 < 64; l88 = l88 + 1) {
			fRec68[l88] = 0.0f;
		}
		fRec68_idx = 0;
		fRec68_idx_save = 0;
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual TailwindDSP* clone() {
		return new TailwindDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("tailwind_reverb");
		ui_interface->declare(&fHslider1, "01", "");
		ui_interface->declare(&fHslider1, "id", "mix");
		ui_interface->addHorizontalSlider("Mix", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider3, "02", "");
		ui_interface->declare(&fHslider3, "id", "decay");
		ui_interface->addHorizontalSlider("Decay", &fHslider3, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.99f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider5, "03", "");
		ui_interface->declare(&fHslider5, "id", "pre_delay_ms");
		ui_interface->addHorizontalSlider("Pre-Delay (ms)", &fHslider5, FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider6, "04", "");
		ui_interface->declare(&fHslider6, "id", "diffusion");
		ui_interface->addHorizontalSlider("Diffusion", &fHslider6, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider4, "05", "");
		ui_interface->declare(&fHslider4, "id", "damping");
		ui_interface->addHorizontalSlider("Damping", &fHslider4, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider9, "06", "");
		ui_interface->declare(&fHslider9, "id", "low_damp");
		ui_interface->addHorizontalSlider("Low Damp", &fHslider9, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider8, "07", "");
		ui_interface->declare(&fHslider8, "id", "mod_rate_hz");
		ui_interface->addHorizontalSlider("Mod Rate (Hz)", &fHslider8, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.1f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider7, "08", "");
		ui_interface->declare(&fHslider7, "id", "mod_depth");
		ui_interface->addHorizontalSlider("Mod Depth", &fHslider7, FAUSTFLOAT(0.3f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider10, "09", "");
		ui_interface->declare(&fHslider10, "id", "low_cut_hz");
		ui_interface->addHorizontalSlider("Low Cut (Hz)", &fHslider10, FAUSTFLOAT(8e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(5e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider11, "10", "");
		ui_interface->declare(&fHslider11, "id", "high_cut_hz");
		ui_interface->addHorizontalSlider("High Cut (Hz)", &fHslider11, FAUSTFLOAT(1.2e+04f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1e+02f));
		ui_interface->declare(&fHslider2, "11", "");
		ui_interface->declare(&fHslider2, "id", "freeze");
		ui_interface->addHorizontalSlider("Freeze", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.6f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fCheckbox0, "12", "");
		ui_interface->declare(&fCheckbox0, "id", "freeze_on");
		ui_interface->addCheckButton("Freeze On", &fCheckbox0);
		ui_interface->declare(&fHslider12, "13", "");
		ui_interface->declare(&fHslider12, "id", "saturation");
		ui_interface->addHorizontalSlider("Saturation", &fHslider12, FAUSTFLOAT(0.125f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "14", "");
		ui_interface->declare(&fHslider0, "id", "input_gain_db");
		ui_interface->addHorizontalSlider("Input Gain", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider13, "15", "");
		ui_interface->declare(&fHslider13, "id", "output_gain_db");
		ui_interface->addHorizontalSlider("Output Gain", &fHslider13, FAUSTFLOAT(0.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = fConst1 * float(fHslider1);
		float fSlow2 = fConst1 * float(fHslider2) * float(fCheckbox0);
		float fSlow3 = fConst1 * float(fHslider3);
		float fSlow4 = fConst1 * float(fHslider4);
		float fSlow5 = fConst1 * float(fHslider5);
		float fSlow6 = fConst1 * float(fHslider6);
		float fZec0[32];
		float fZec1[32];
		int iZec2[32];
		int iZec3[32];
		float fZec4[32];
		float fZec5[32];
		float fZec6[32];
		int iZec7[32];
		float fRec25[32];
		float fRec23[32];
		float fRec21[32];
		float fRec19[32];
		float fRec35[32];
		float fRec33[32];
		float fRec31[32];
		float fRec29[32];
		float fSlow7 = fConst1 * float(fHslider7);
		float fSlow8 = fConst1 * float(fHslider8);
		int iZec8[32];
		float fZec9[32];
		float fZec10[32];
		float fZec11[32];
		float fZec12[32];
		float fZec13[32];
		float fZec14[32];
		float fZec15[32];
		int iZec16[32];
		float fZec17[32];
		float fSlow9 = fConst1 * float(fHslider9);
		float fZec18[32];
		float fZec19[32];
		float fZec20[32];
		float fZec21[32];
		float fZec22[32];
		float fZec23[32];
		float fZec24[32];
		float fZec25[32];
		float fZec26[32];
		float fZec27[32];
		float fZec28[32];
		float fZec29[32];
		float fZec30[32];
		int iZec31[32];
		float fZec32[32];
		int iZec33[32];
		float fZec34[32];
		float fZec35[32];
		float fZec36[32];
		float fZec37[32];
		float fZec38[32];
		float fZec39[32];
		float fZec40[32];
		float fZec41[32];
		float fZec42[32];
		float fZec43[32];
		float fZec44[32];
		float fZec45[32];
		int iZec46[32];
		float fZec47[32];
		float fZec48[32];
		float fZec49[32];
		float fZec50[32];
		float fZec51[32];
		float fZec52[32];
		float fZec53[32];
		float fZec54[32];
		float fZec55[32];
		float fZec56[32];
		int iZec57[32];
		float fZec58[32];
		int iZec59[32];
		float fZec60[32];
		float fZec61[32];
		float fZec62[32];
		float fZec63[32];
		float fZec64[32];
		float fZec65[32];
		float fZec66[32];
		float fZec67[32];
		float fZec68[32];
		float fZec69[32];
		float fZec70[32];
		float fZec71[32];
		float fZec72[32];
		int iZec73[32];
		float fZec74[32];
		float fZec75[32];
		float fZec76[32];
		float fZec77[32];
		float fZec78[32];
		float fZec79[32];
		float fZec80[32];
		float fZec81[32];
		float fZec82[32];
		float fZec83[32];
		int iZec84[32];
		float fZec85[32];
		int iZec86[32];
		float fZec87[32];
		float fZec88[32];
		float fZec89[32];
		float fZec90[32];
		float fZec91[32];
		float fZec92[32];
		float fZec93[32];
		float fZec94[32];
		float fZec95[32];
		float fZec96[32];
		float fZec97[32];
		float fZec98[32];
		float fZec99[32];
		int iZec100[32];
		float fZec101[32];
		float fZec102[32];
		float fZec103[32];
		float fZec104[32];
		float fZec105[32];
		float fZec106[32];
		float fZec107[32];
		float fZec108[32];
		float fZec109[32];
		float fZec110[32];
		int iZec111[32];
		float fZec112[32];
		int iZec113[32];
		float fZec114[32];
		float fZec115[32];
		float fZec116[32];
		float fZec117[32];
		float fZec118[32];
		float fZec119[32];
		float fZec120[32];
		float fZec121[32];
		float fZec122[32];
		float fRec12[32];
		float fRec13[32];
		float fSlow10 = fConst1 * float(fHslider10);
		float fZec123[32];
		float fZec124[32];
		float fZec125[32];
		float fZec126[32];
		float fZec127[32];
		float fZec128[32];
		float fSlow11 = fConst1 * float(fHslider11);
		float fZec129[32];
		float fZec130[32];
		float fZec131[32];
		float fZec132[32];
		float fZec133[32];
		float fZec134[32];
		float fSlow12 = fConst1 * float(fHslider12);
		float fSlow13 = fConst1 * float(fHslider13);
		float fZec135[32];
		float fZec136[32];
		float fZec137[32];
		float fZec138[32];
		float fZec139[32];
		float fZec140[32];
		float fZec141[32];
		float fZec142[32];
		float fZec143[32];
		float fZec144[32];
		float fZec145[32];
		float fZec146[32];
		for (int vindex = 0; vindex < count; vindex = vindex + 32) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = std::min<int>(32, count - vindex);
			/* Recursive loop 0 */
			/* Pre code */
			fRec26_idx = (fRec26_idx + fRec26_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec26[(i + fRec26_idx) & 63] = fSlow5 + fConst2 * fRec26[(i + fRec26_idx - 1) & 63];
			}
			/* Post code */
			fRec26_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			fRec0_idx = (fRec0_idx + fRec0_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec0[(i + fRec0_idx) & 63] = fSlow0 + fConst2 * fRec0[(i + fRec0_idx - 1) & 63];
			}
			/* Post code */
			fRec0_idx_save = vsize;
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = fConst3 * fRec26[(i + fRec26_idx) & 63];
			}
			/* Recursive loop 3 */
			/* Pre code */
			fRec16_idx = (fRec16_idx + fRec16_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec16[(i + fRec16_idx) & 63] = fSlow3 + fConst2 * fRec16[(i + fRec16_idx - 1) & 63];
			}
			/* Post code */
			fRec16_idx_save = vsize;
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = std::pow(1e+01f, 0.05f * fRec0[(i + fRec0_idx) & 63]);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec2[i] = int(fZec1[i]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = std::floor(fZec1[i]);
			}
			/* Vectorizable loop 7 */
			/* Pre code */
			iVec0_idx = (iVec0_idx + iVec0_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iVec0[(i + iVec0_idx) & 63] = 1;
			}
			/* Post code */
			iVec0_idx_save = vsize;
			/* Recursive loop 8 */
			/* Pre code */
			fRec15_idx = (fRec15_idx + fRec15_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec15[(i + fRec15_idx) & 63] = fSlow2 + fConst2 * fRec15[(i + fRec15_idx - 1) & 63];
			}
			/* Post code */
			fRec15_idx_save = vsize;
			/* Recursive loop 9 */
			/* Pre code */
			fRec27_idx = (fRec27_idx + fRec27_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec27[(i + fRec27_idx) & 63] = fSlow6 + fConst2 * fRec27[(i + fRec27_idx - 1) & 63];
			}
			/* Post code */
			fRec27_idx_save = vsize;
			/* Vectorizable loop 10 */
			/* Pre code */
			fYec0_idx = (fYec0_idx + fYec0_idx_save) & 32767;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[(i + fYec0_idx) & 32767] = float(input0[i]) * fZec0[i];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec3[i] = std::min<int>(24001, std::max<int>(0, iZec2[i]));
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = fZec4[i] + (1.0f - fZec1[i]);
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = fZec1[i] - fZec4[i];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec7[i] = std::min<int>(24001, std::max<int>(0, iZec2[i] + 1));
			}
			/* Vectorizable loop 15 */
			/* Pre code */
			fYec5_idx = (fYec5_idx + fYec5_idx_save) & 32767;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec5[(i + fYec5_idx) & 32767] = float(input1[i]) * fZec0[i];
			}
			/* Post code */
			fYec5_idx_save = vsize;
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec18[i] = std::pow(1.5e+02f, fRec16[(i + fRec16_idx) & 63]);
			}
			/* Recursive loop 17 */
			/* Pre code */
			fYec1_idx = (fYec1_idx + fYec1_idx_save) & 255;
			fRec24_idx = (fRec24_idx + fRec24_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[(i + fYec1_idx) & 255] = fYec0[(i + fYec0_idx - iZec3[i]) & 32767] * fZec5[i] + fZec6[i] * fYec0[(i + fYec0_idx - iZec7[i]) & 32767] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec24[(i + fRec24_idx - 1) & 63];
				fRec24[(i + fRec24_idx) & 63] = fYec1[(i + fYec1_idx - 141) & 255];
				fRec25[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec1[(i + fYec1_idx) & 255];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			fRec24_idx_save = vsize;
			/* Recursive loop 18 */
			/* Pre code */
			fYec6_idx = (fYec6_idx + fYec6_idx_save) & 255;
			fRec34_idx = (fRec34_idx + fRec34_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec6[(i + fYec6_idx) & 255] = fZec5[i] * fYec5[(i + fYec5_idx - iZec3[i]) & 32767] + fZec6[i] * fYec5[(i + fYec5_idx - iZec7[i]) & 32767] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec34[(i + fRec34_idx - 1) & 63];
				fRec34[(i + fRec34_idx) & 63] = fYec6[(i + fYec6_idx - 150) & 255];
				fRec35[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec6[(i + fYec6_idx) & 255];
			}
			/* Post code */
			fYec6_idx_save = vsize;
			fRec34_idx_save = vsize;
			/* Recursive loop 19 */
			/* Pre code */
			fRec38_idx = (fRec38_idx + fRec38_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec38[(i + fRec38_idx) & 63] = fSlow8 + fConst2 * fRec38[(i + fRec38_idx - 1) & 63];
			}
			/* Post code */
			fRec38_idx_save = vsize;
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec8[i] = 1 - iVec0[(i + iVec0_idx - 1) & 63];
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec12[i] = 1.0f - fRec15[(i + fRec15_idx) & 63];
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec19[i] = std::max<float>(0.01f, 0.2f * fZec18[i]);
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec115[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst23 / fZec19[i]));
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec88[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst19 / fZec19[i]));
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec75[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst17 / fZec19[i]));
			}
			/* Recursive loop 26 */
			/* Pre code */
			fRec56_idx = (fRec56_idx + fRec56_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec83[i] = ((iZec8[i]) ? 0.0f : fRec56[(i + fRec56_idx - 1) & 63] + fConst18 * fRec38[(i + fRec38_idx) & 63]);
				fRec56[(i + fRec56_idx) & 63] = fZec83[i] - std::floor(fZec83[i]);
			}
			/* Post code */
			fRec56_idx_save = vsize;
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec102[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst21 / fZec19[i]));
			}
			/* Recursive loop 28 */
			/* Pre code */
			fRec62_idx = (fRec62_idx + fRec62_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec110[i] = ((iZec8[i]) ? 0.0f : fRec62[(i + fRec62_idx - 1) & 63] + fConst22 * fRec38[(i + fRec38_idx) & 63]);
				fRec62[(i + fRec62_idx) & 63] = fZec110[i] - std::floor(fZec110[i]);
			}
			/* Post code */
			fRec62_idx_save = vsize;
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec48[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst13 / fZec19[i]));
			}
			/* Recursive loop 30 */
			/* Pre code */
			fRec50_idx = (fRec50_idx + fRec50_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec56[i] = ((iZec8[i]) ? 0.0f : fRec50[(i + fRec50_idx - 1) & 63] + fConst14 * fRec38[(i + fRec38_idx) & 63]);
				fRec50[(i + fRec50_idx) & 63] = fZec56[i] - std::floor(fZec56[i]);
			}
			/* Post code */
			fRec50_idx_save = vsize;
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec61[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst15 / fZec19[i]));
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec35[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst11 / fZec19[i]));
			}
			/* Recursive loop 33 */
			/* Pre code */
			fRec17_idx = (fRec17_idx + fRec17_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec17[(i + fRec17_idx) & 63] = fSlow4 + fConst2 * fRec17[(i + fRec17_idx - 1) & 63];
			}
			/* Post code */
			fRec17_idx_save = vsize;
			/* Recursive loop 34 */
			/* Pre code */
			fYec2_idx = (fYec2_idx + fYec2_idx_save) & 255;
			fRec22_idx = (fRec22_idx + fRec22_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec2[(i + fYec2_idx) & 255] = fRec25[i] + fRec24[(i + fRec24_idx - 1) & 63] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec22[(i + fRec22_idx - 1) & 63];
				fRec22[(i + fRec22_idx) & 63] = fYec2[(i + fYec2_idx - 106) & 255];
				fRec23[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec2[(i + fYec2_idx) & 255];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			fRec22_idx_save = vsize;
			/* Recursive loop 35 */
			/* Pre code */
			fYec7_idx = (fYec7_idx + fYec7_idx_save) & 255;
			fRec32_idx = (fRec32_idx + fRec32_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec7[(i + fYec7_idx) & 255] = fRec35[i] + fRec34[(i + fRec34_idx - 1) & 63] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec32[(i + fRec32_idx - 1) & 63];
				fRec32[(i + fRec32_idx) & 63] = fYec7[(i + fYec7_idx - 112) & 255];
				fRec33[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec7[(i + fYec7_idx) & 255];
			}
			/* Post code */
			fYec7_idx_save = vsize;
			fRec32_idx_save = vsize;
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec20[i] = fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst8 / fZec19[i]));
			}
			/* Recursive loop 37 */
			/* Pre code */
			fRec43_idx = (fRec43_idx + fRec43_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec30[i] = ((iZec8[i]) ? 0.0f : fRec43[(i + fRec43_idx - 1) & 63] + fConst10 * fRec38[(i + fRec38_idx) & 63]);
				fRec43[(i + fRec43_idx) & 63] = fZec30[i] - std::floor(fZec30[i]);
			}
			/* Post code */
			fRec43_idx_save = vsize;
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec116[i] = TailwindDSP_faustpower2_f(fZec115[i]);
			}
			/* Recursive loop 39 */
			/* Pre code */
			fRec47_idx = (fRec47_idx + fRec47_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec43[i] = ((iZec8[i]) ? 0.0f : fRec47[(i + fRec47_idx - 1) & 63] + fConst12 * fRec38[(i + fRec38_idx) & 63]);
				fRec47[(i + fRec47_idx) & 63] = fZec43[i] - std::floor(fZec43[i]);
			}
			/* Post code */
			fRec47_idx_save = vsize;
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec84[i] = std::max<int>(0, std::min<int>(int(65536.0f * fRec56[(i + fRec56_idx) & 63]), 65535));
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec89[i] = TailwindDSP_faustpower2_f(fZec88[i]);
			}
			/* Recursive loop 42 */
			/* Pre code */
			fRec64_idx = (fRec64_idx + fRec64_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec64[(i + fRec64_idx) & 63] = fSlow10 + fConst2 * fRec64[(i + fRec64_idx - 1) & 63];
			}
			/* Post code */
			fRec64_idx_save = vsize;
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec76[i] = TailwindDSP_faustpower2_f(fZec75[i]);
			}
			/* Recursive loop 44 */
			/* Pre code */
			fRec59_idx = (fRec59_idx + fRec59_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec96[i] = ((iZec8[i]) ? 0.0f : fRec59[(i + fRec59_idx - 1) & 63] + fConst20 * fRec38[(i + fRec38_idx) & 63]);
				fRec59[(i + fRec59_idx) & 63] = fZec96[i] - std::floor(fZec96[i]);
			}
			/* Post code */
			fRec59_idx_save = vsize;
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec103[i] = TailwindDSP_faustpower2_f(fZec102[i]);
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec111[i] = std::max<int>(0, std::min<int>(int(65536.0f * fRec62[(i + fRec62_idx) & 63]), 65535));
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec22[i] = std::cos(fConst9 * std::pow(0.05f, fRec17[(i + fRec17_idx) & 63]));
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec49[i] = TailwindDSP_faustpower2_f(fZec48[i]);
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec57[i] = std::max<int>(0, std::min<int>(int(65536.0f * fRec50[(i + fRec50_idx) & 63]), 65535));
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec62[i] = TailwindDSP_faustpower2_f(fZec61[i]);
			}
			/* Recursive loop 51 */
			/* Pre code */
			fRec53_idx = (fRec53_idx + fRec53_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec69[i] = ((iZec8[i]) ? 0.0f : fRec53[(i + fRec53_idx - 1) & 63] + fConst16 * fRec38[(i + fRec38_idx) & 63]);
				fRec53[(i + fRec53_idx) & 63] = fZec69[i] - std::floor(fZec69[i]);
			}
			/* Post code */
			fRec53_idx_save = vsize;
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec36[i] = TailwindDSP_faustpower2_f(fZec35[i]);
			}
			/* Recursive loop 53 */
			/* Pre code */
			fYec3_idx = (fYec3_idx + fYec3_idx_save) & 511;
			fRec20_idx = (fRec20_idx + fRec20_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec3[(i + fYec3_idx) & 511] = fRec23[i] + fRec22[(i + fRec22_idx - 1) & 63] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec20[(i + fRec20_idx - 1) & 63];
				fRec20[(i + fRec20_idx) & 63] = fYec3[(i + fYec3_idx - 378) & 511];
				fRec21[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec3[(i + fYec3_idx) & 511];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			fRec20_idx_save = vsize;
			/* Recursive loop 54 */
			/* Pre code */
			fYec8_idx = (fYec8_idx + fYec8_idx_save) & 511;
			fRec30_idx = (fRec30_idx + fRec30_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec8[(i + fYec8_idx) & 511] = fRec33[i] + fRec32[(i + fRec32_idx - 1) & 63] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec30[(i + fRec30_idx - 1) & 63];
				fRec30[(i + fRec30_idx) & 63] = fYec8[(i + fYec8_idx - 388) & 511];
				fRec31[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec8[(i + fYec8_idx) & 511];
			}
			/* Post code */
			fYec8_idx_save = vsize;
			fRec30_idx_save = vsize;
			/* Recursive loop 55 */
			/* Pre code */
			fRec36_idx = (fRec36_idx + fRec36_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec36[(i + fRec36_idx) & 63] = fSlow7 + fConst2 * fRec36[(i + fRec36_idx - 1) & 63];
			}
			/* Post code */
			fRec36_idx_save = vsize;
			/* Recursive loop 56 */
			/* Pre code */
			fRec37_idx = (fRec37_idx + fRec37_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = ((iZec8[i]) ? 0.0f : fRec37[(i + fRec37_idx - 1) & 63] + fConst4 * fRec38[(i + fRec38_idx) & 63]);
				fRec37[(i + fRec37_idx) & 63] = fZec9[i] - std::floor(fZec9[i]);
			}
			/* Post code */
			fRec37_idx_save = vsize;
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec21[i] = TailwindDSP_faustpower2_f(fZec20[i]);
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec31[i] = std::max<int>(0, std::min<int>(int(65536.0f * fRec43[(i + fRec43_idx) & 63]), 65535));
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec117[i] = 1.0f - fZec22[i] * fZec116[i];
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec118[i] = std::max<float>(1e-06f, 1.0f - fZec116[i]);
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec85[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (1.0f - (0.70710677f * ftbl0TailwindDSPSIG0[iZec84[i]] + 0.70710677f * ftbl1TailwindDSPSIG1[iZec84[i]])) + 2381.0f));
			}
			/* Vectorizable loop 62 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec90[i] = 1.0f - fZec22[i] * fZec89[i];
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec91[i] = std::max<float>(1e-06f, 1.0f - fZec89[i]);
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec123[i] = std::tan(fConst24 * fRec64[(i + fRec64_idx) & 63]);
			}
			/* Recursive loop 65 */
			/* Pre code */
			fRec65_idx = (fRec65_idx + fRec65_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec65[(i + fRec65_idx) & 63] = fSlow11 + fConst2 * fRec65[(i + fRec65_idx - 1) & 63];
			}
			/* Post code */
			fRec65_idx_save = vsize;
			/* Vectorizable loop 66 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec72[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (1.0f - ftbl0TailwindDSPSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec53[(i + fRec53_idx) & 63]), 65535))]) + 2179.0f));
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec77[i] = 1.0f - fZec22[i] * fZec76[i];
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec78[i] = std::max<float>(1e-06f, 1.0f - fZec76[i]);
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec99[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (1.0f - ftbl1TailwindDSPSIG1[std::max<int>(0, std::min<int>(int(65536.0f * fRec59[(i + fRec59_idx) & 63]), 65535))]) + 2591.0f));
			}
			/* Vectorizable loop 70 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec104[i] = 1.0f - fZec22[i] * fZec103[i];
			}
			/* Vectorizable loop 71 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec105[i] = std::max<float>(1e-06f, 1.0f - fZec103[i]);
			}
			/* Vectorizable loop 72 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec112[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (0.70710677f * ftbl0TailwindDSPSIG0[iZec111[i]] - 0.70710677f * ftbl1TailwindDSPSIG1[iZec111[i]] + 1.0f) + 2797.0f));
			}
			/* Vectorizable loop 73 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec24[i] = std::max<float>(1e-06f, 1.0f - fZec21[i]);
			}
			/* Vectorizable loop 74 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec45[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (ftbl1TailwindDSPSIG1[std::max<int>(0, std::min<int>(int(65536.0f * fRec47[(i + fRec47_idx) & 63]), 65535))] + 1.0f) + 1811.0f));
			}
			/* Vectorizable loop 75 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec50[i] = 1.0f - fZec22[i] * fZec49[i];
			}
			/* Vectorizable loop 76 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec51[i] = std::max<float>(1e-06f, 1.0f - fZec49[i]);
			}
			/* Vectorizable loop 77 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec58[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (0.70710677f * ftbl1TailwindDSPSIG1[iZec57[i]] - 0.70710677f * ftbl0TailwindDSPSIG0[iZec57[i]] + 1.0f) + 2003.0f));
			}
			/* Vectorizable loop 78 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec63[i] = 1.0f - fZec22[i] * fZec62[i];
			}
			/* Vectorizable loop 79 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec64[i] = std::max<float>(1e-06f, 1.0f - fZec62[i]);
			}
			/* Vectorizable loop 80 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec37[i] = 1.0f - fZec22[i] * fZec36[i];
			}
			/* Vectorizable loop 81 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec38[i] = std::max<float>(1e-06f, 1.0f - fZec36[i]);
			}
			/* Recursive loop 82 */
			/* Pre code */
			fYec4_idx = (fYec4_idx + fYec4_idx_save) & 511;
			fRec18_idx = (fRec18_idx + fRec18_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec4[(i + fYec4_idx) & 511] = fRec21[i] + fRec20[(i + fRec20_idx - 1) & 63] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec18[(i + fRec18_idx - 1) & 63];
				fRec18[(i + fRec18_idx) & 63] = fYec4[(i + fYec4_idx - 276) & 511];
				fRec19[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec4[(i + fYec4_idx) & 511];
			}
			/* Post code */
			fYec4_idx_save = vsize;
			fRec18_idx_save = vsize;
			/* Recursive loop 83 */
			/* Pre code */
			fYec9_idx = (fYec9_idx + fYec9_idx_save) & 511;
			fRec28_idx = (fRec28_idx + fRec28_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec9[(i + fYec9_idx) & 511] = fRec31[i] + fRec30[(i + fRec30_idx - 1) & 63] - 0.75f * fRec27[(i + fRec27_idx) & 63] * fRec28[(i + fRec28_idx - 1) & 63];
				fRec28[(i + fRec28_idx) & 63] = fYec9[(i + fYec9_idx - 282) & 511];
				fRec29[i] = 0.75f * fRec27[(i + fRec27_idx) & 63] * fYec9[(i + fYec9_idx) & 511];
			}
			/* Post code */
			fYec9_idx_save = vsize;
			fRec28_idx_save = vsize;
			/* Vectorizable loop 84 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec15[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (ftbl0TailwindDSPSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec37[(i + fRec37_idx) & 63]), 65535))] + 1.0f) + 1423.0f));
			}
			/* Recursive loop 85 */
			/* Pre code */
			fRec41_idx = (fRec41_idx + fRec41_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec41[(i + fRec41_idx) & 63] = fSlow9 + fConst2 * fRec41[(i + fRec41_idx - 1) & 63];
			}
			/* Post code */
			fRec41_idx_save = vsize;
			/* Vectorizable loop 86 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec23[i] = 1.0f - fZec21[i] * fZec22[i];
			}
			/* Vectorizable loop 87 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec32[i] = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec36[(i + fRec36_idx) & 63] * (0.70710677f * ftbl0TailwindDSPSIG0[iZec31[i]] + 0.70710677f * ftbl1TailwindDSPSIG1[iZec31[i]] + 1.0f) + 1637.0f));
			}
			/* Vectorizable loop 88 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec119[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec117[i]) / TailwindDSP_faustpower2_f(fZec118[i]) + -1.0f));
			}
			/* Vectorizable loop 89 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec120[i] = fZec117[i] / fZec118[i];
			}
			/* Vectorizable loop 90 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec86[i] = int(fZec85[i]);
			}
			/* Vectorizable loop 91 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec87[i] = std::floor(fZec85[i]);
			}
			/* Vectorizable loop 92 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec92[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec90[i]) / TailwindDSP_faustpower2_f(fZec91[i]) + -1.0f));
			}
			/* Vectorizable loop 93 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec93[i] = fZec90[i] / fZec91[i];
			}
			/* Vectorizable loop 94 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec124[i] = 1.0f / fZec123[i];
			}
			/* Vectorizable loop 95 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec126[i] = TailwindDSP_faustpower2_f(fZec123[i]);
			}
			/* Vectorizable loop 96 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec130[i] = std::tan(fConst24 * fRec65[(i + fRec65_idx) & 63]);
			}
			/* Vectorizable loop 97 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec73[i] = int(fZec72[i]);
			}
			/* Vectorizable loop 98 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec74[i] = std::floor(fZec72[i]);
			}
			/* Vectorizable loop 99 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec79[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec77[i]) / TailwindDSP_faustpower2_f(fZec78[i]) + -1.0f));
			}
			/* Vectorizable loop 100 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec80[i] = fZec77[i] / fZec78[i];
			}
			/* Vectorizable loop 101 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec100[i] = int(fZec99[i]);
			}
			/* Vectorizable loop 102 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec101[i] = std::floor(fZec99[i]);
			}
			/* Vectorizable loop 103 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec106[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec104[i]) / TailwindDSP_faustpower2_f(fZec105[i]) + -1.0f));
			}
			/* Vectorizable loop 104 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec107[i] = fZec104[i] / fZec105[i];
			}
			/* Vectorizable loop 105 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec113[i] = int(fZec112[i]);
			}
			/* Vectorizable loop 106 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec114[i] = std::floor(fZec112[i]);
			}
			/* Vectorizable loop 107 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec26[i] = fZec23[i] / fZec24[i];
			}
			/* Vectorizable loop 108 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec27[i] = std::max<float>(0.01f, 0.2f * fZec18[i] * (1.0f - 0.75f * fRec41[(i + fRec41_idx) & 63]));
			}
			/* Vectorizable loop 109 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec46[i] = int(fZec45[i]);
			}
			/* Vectorizable loop 110 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec47[i] = std::floor(fZec45[i]);
			}
			/* Vectorizable loop 111 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec52[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec50[i]) / TailwindDSP_faustpower2_f(fZec51[i]) + -1.0f));
			}
			/* Vectorizable loop 112 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec53[i] = fZec50[i] / fZec51[i];
			}
			/* Vectorizable loop 113 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec59[i] = int(fZec58[i]);
			}
			/* Vectorizable loop 114 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec60[i] = std::floor(fZec58[i]);
			}
			/* Vectorizable loop 115 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec65[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec63[i]) / TailwindDSP_faustpower2_f(fZec64[i]) + -1.0f));
			}
			/* Vectorizable loop 116 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec66[i] = fZec63[i] / fZec64[i];
			}
			/* Vectorizable loop 117 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec34[i] = std::floor(fZec32[i]);
			}
			/* Vectorizable loop 118 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec39[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec37[i]) / TailwindDSP_faustpower2_f(fZec38[i]) + -1.0f));
			}
			/* Vectorizable loop 119 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec40[i] = fZec37[i] / fZec38[i];
			}
			/* Vectorizable loop 120 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec13[i] = fRec19[i] + fRec18[(i + fRec18_idx - 1) & 63];
			}
			/* Vectorizable loop 121 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec14[i] = fRec29[i] + fRec28[(i + fRec28_idx - 1) & 63];
			}
			/* Vectorizable loop 122 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec16[i] = int(fZec15[i]);
			}
			/* Vectorizable loop 123 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec17[i] = std::floor(fZec15[i]);
			}
			/* Vectorizable loop 124 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec25[i] = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fZec23[i]) / TailwindDSP_faustpower2_f(fZec24[i]) + -1.0f));
			}
			/* Vectorizable loop 125 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec33[i] = int(fZec32[i]);
			}
			/* Vectorizable loop 126 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec125[i] = (fZec124[i] + -1.4142135f) / fZec123[i] + 1.0f;
			}
			/* Vectorizable loop 127 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec127[i] = 1.0f - 1.0f / fZec126[i];
			}
			/* Vectorizable loop 128 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec128[i] = (fZec124[i] + 1.4142135f) / fZec123[i] + 1.0f;
			}
			/* Vectorizable loop 129 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec131[i] = 1.0f / fZec130[i];
			}
			/* Recursive loop 130 */
			/* Pre code */
			fYec10_idx = (fYec10_idx + fYec10_idx_save) & 8191;
			fYec11_idx = (fYec11_idx + fYec11_idx_save) & 63;
			fRec39_idx = (fRec39_idx + fRec39_idx_save) & 63;
			fRec14_idx = (fRec14_idx + fRec14_idx_save) & 63;
			fRec4_idx = (fRec4_idx + fRec4_idx_save) & 63;
			fYec12_idx = (fYec12_idx + fYec12_idx_save) & 8191;
			fYec13_idx = (fYec13_idx + fYec13_idx_save) & 63;
			fRec44_idx = (fRec44_idx + fRec44_idx_save) & 63;
			fRec42_idx = (fRec42_idx + fRec42_idx_save) & 63;
			fRec5_idx = (fRec5_idx + fRec5_idx_save) & 63;
			fYec14_idx = (fYec14_idx + fYec14_idx_save) & 8191;
			fYec15_idx = (fYec15_idx + fYec15_idx_save) & 63;
			fRec48_idx = (fRec48_idx + fRec48_idx_save) & 63;
			fRec46_idx = (fRec46_idx + fRec46_idx_save) & 63;
			fRec6_idx = (fRec6_idx + fRec6_idx_save) & 63;
			fYec16_idx = (fYec16_idx + fYec16_idx_save) & 8191;
			fYec17_idx = (fYec17_idx + fYec17_idx_save) & 63;
			fRec51_idx = (fRec51_idx + fRec51_idx_save) & 63;
			fRec49_idx = (fRec49_idx + fRec49_idx_save) & 63;
			fRec7_idx = (fRec7_idx + fRec7_idx_save) & 63;
			fYec18_idx = (fYec18_idx + fYec18_idx_save) & 8191;
			fYec19_idx = (fYec19_idx + fYec19_idx_save) & 63;
			fRec54_idx = (fRec54_idx + fRec54_idx_save) & 63;
			fRec52_idx = (fRec52_idx + fRec52_idx_save) & 63;
			fRec8_idx = (fRec8_idx + fRec8_idx_save) & 63;
			fYec20_idx = (fYec20_idx + fYec20_idx_save) & 8191;
			fYec21_idx = (fYec21_idx + fYec21_idx_save) & 63;
			fRec57_idx = (fRec57_idx + fRec57_idx_save) & 63;
			fRec55_idx = (fRec55_idx + fRec55_idx_save) & 63;
			fRec9_idx = (fRec9_idx + fRec9_idx_save) & 63;
			fYec22_idx = (fYec22_idx + fYec22_idx_save) & 8191;
			fYec23_idx = (fYec23_idx + fYec23_idx_save) & 63;
			fRec60_idx = (fRec60_idx + fRec60_idx_save) & 63;
			fRec58_idx = (fRec58_idx + fRec58_idx_save) & 63;
			fRec10_idx = (fRec10_idx + fRec10_idx_save) & 63;
			fYec24_idx = (fYec24_idx + fYec24_idx_save) & 8191;
			fYec25_idx = (fYec25_idx + fYec25_idx_save) & 63;
			fRec63_idx = (fRec63_idx + fRec63_idx_save) & 63;
			fRec61_idx = (fRec61_idx + fRec61_idx_save) & 63;
			fRec11_idx = (fRec11_idx + fRec11_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec10[i] = fRec4[(i + fRec4_idx - 1) & 63] + fRec8[(i + fRec8_idx - 1) & 63];
				fZec11[i] = fRec10[(i + fRec10_idx - 1) & 63] + fRec6[(i + fRec6_idx - 1) & 63] + fZec10[i];
				fYec10[(i + fYec10_idx) & 8191] = fRec11[(i + fRec11_idx - 1) & 63] + fRec7[(i + fRec7_idx - 1) & 63] + fRec9[(i + fRec9_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fZec11[i] + 2.0f * fZec12[i] * (fZec13[i] + fZec14[i]);
				fYec11[(i + fYec11_idx) & 63] = fYec10[(i + fYec10_idx - std::min<int>(4097, std::max<int>(0, iZec16[i]))) & 8191] * (fZec17[i] + (1.0f - fZec15[i])) + (fZec15[i] - fZec17[i]) * fYec10[(i + fYec10_idx - std::min<int>(4097, std::max<int>(0, iZec16[i] + 1))) & 8191];
				fRec39[(i + fRec39_idx) & 63] = -(fConst6 * (fConst7 * fRec39[(i + fRec39_idx - 1) & 63] - (fYec11[(i + fYec11_idx) & 63] + fYec11[(i + fYec11_idx - 1) & 63])));
				fRec14[(i + fRec14_idx) & 63] = fZec20[i] * (fZec25[i] + (1.0f - fZec26[i])) * (fYec11[(i + fYec11_idx) & 63] + fRec39[(i + fRec39_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst8 / fZec27[i]))) / std::max<float>(1e-06f, fZec20[i]) + -1.0f)) + (fZec26[i] - fZec25[i]) * fRec14[(i + fRec14_idx - 1) & 63];
				fZec28[i] = TailwindDSP_faustpower2_f(fRec14[(i + fRec14_idx) & 63]);
				fZec29[i] = fRec14[(i + fRec14_idx) & 63] * (0.125f * fZec28[i] + 27.0f) / (1.125f * fZec28[i] + 27.0f);
				fRec4[(i + fRec4_idx) & 63] = 0.35355338f * fZec29[i];
				fYec12[(i + fYec12_idx) & 8191] = fZec11[i] + 2.0f * fZec12[i] * (fZec13[i] - fZec14[i]) - (fRec11[(i + fRec11_idx - 1) & 63] + fRec7[(i + fRec7_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fRec9[(i + fRec9_idx - 1) & 63]);
				fYec13[(i + fYec13_idx) & 63] = fYec12[(i + fYec12_idx - std::min<int>(4097, std::max<int>(0, iZec33[i]))) & 8191] * (fZec34[i] + (1.0f - fZec32[i])) + (fZec32[i] - fZec34[i]) * fYec12[(i + fYec12_idx - std::min<int>(4097, std::max<int>(0, iZec33[i] + 1))) & 8191];
				fRec44[(i + fRec44_idx) & 63] = -(fConst6 * (fConst7 * fRec44[(i + fRec44_idx - 1) & 63] - (fYec13[(i + fYec13_idx) & 63] + fYec13[(i + fYec13_idx - 1) & 63])));
				fRec42[(i + fRec42_idx) & 63] = fZec35[i] * (fZec39[i] + (1.0f - fZec40[i])) * (fYec13[(i + fYec13_idx) & 63] + fRec44[(i + fRec44_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst11 / fZec27[i]))) / std::max<float>(1e-06f, fZec35[i]) + -1.0f)) + (fZec40[i] - fZec39[i]) * fRec42[(i + fRec42_idx - 1) & 63];
				fZec41[i] = TailwindDSP_faustpower2_f(fRec42[(i + fRec42_idx) & 63]);
				fZec42[i] = fRec42[(i + fRec42_idx) & 63] * (0.125f * fZec41[i] + 27.0f) / (1.125f * fZec41[i] + 27.0f);
				fRec5[(i + fRec5_idx) & 63] = 0.35355338f * fZec42[i];
				fZec44[i] = fRec6[(i + fRec6_idx - 1) & 63] + fRec10[(i + fRec10_idx - 1) & 63];
				fYec14[(i + fYec14_idx) & 8191] = fRec9[(i + fRec9_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fZec10[i] - (fRec11[(i + fRec11_idx - 1) & 63] + fRec7[(i + fRec7_idx - 1) & 63] + fZec44[i]);
				fYec15[(i + fYec15_idx) & 63] = fYec14[(i + fYec14_idx - std::min<int>(4097, std::max<int>(0, iZec46[i]))) & 8191] * (fZec47[i] + (1.0f - fZec45[i])) + (fZec45[i] - fZec47[i]) * fYec14[(i + fYec14_idx - std::min<int>(4097, std::max<int>(0, iZec46[i] + 1))) & 8191];
				fRec48[(i + fRec48_idx) & 63] = -(fConst6 * (fConst7 * fRec48[(i + fRec48_idx - 1) & 63] - (fYec15[(i + fYec15_idx) & 63] + fYec15[(i + fYec15_idx - 1) & 63])));
				fRec46[(i + fRec46_idx) & 63] = fZec48[i] * (fZec52[i] + (1.0f - fZec53[i])) * (fYec15[(i + fYec15_idx) & 63] + fRec48[(i + fRec48_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst13 / fZec27[i]))) / std::max<float>(1e-06f, fZec48[i]) + -1.0f)) + (fZec53[i] - fZec52[i]) * fRec46[(i + fRec46_idx - 1) & 63];
				fZec54[i] = TailwindDSP_faustpower2_f(fRec46[(i + fRec46_idx) & 63]);
				fZec55[i] = fRec46[(i + fRec46_idx) & 63] * (0.125f * fZec54[i] + 27.0f) / (1.125f * fZec54[i] + 27.0f);
				fRec6[(i + fRec6_idx) & 63] = 0.35355338f * fZec55[i];
				fYec16[(i + fYec16_idx) & 8191] = fRec11[(i + fRec11_idx - 1) & 63] + fRec7[(i + fRec7_idx - 1) & 63] + fZec10[i] - (fRec9[(i + fRec9_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fZec44[i]);
				fYec17[(i + fYec17_idx) & 63] = fYec16[(i + fYec16_idx - std::min<int>(4097, std::max<int>(0, iZec59[i]))) & 8191] * (fZec60[i] + (1.0f - fZec58[i])) + (fZec58[i] - fZec60[i]) * fYec16[(i + fYec16_idx - std::min<int>(4097, std::max<int>(0, iZec59[i] + 1))) & 8191];
				fRec51[(i + fRec51_idx) & 63] = -(fConst6 * (fConst7 * fRec51[(i + fRec51_idx - 1) & 63] - (fYec17[(i + fYec17_idx) & 63] + fYec17[(i + fYec17_idx - 1) & 63])));
				fRec49[(i + fRec49_idx) & 63] = fZec61[i] * (fZec65[i] + (1.0f - fZec66[i])) * (fYec17[(i + fYec17_idx) & 63] + fRec51[(i + fRec51_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst15 / fZec27[i]))) / std::max<float>(1e-06f, fZec61[i]) + -1.0f)) + (fZec66[i] - fZec65[i]) * fRec49[(i + fRec49_idx - 1) & 63];
				fZec67[i] = TailwindDSP_faustpower2_f(fRec49[(i + fRec49_idx) & 63]);
				fZec68[i] = fRec49[(i + fRec49_idx) & 63] * (0.125f * fZec67[i] + 27.0f) / (1.125f * fZec67[i] + 27.0f);
				fRec7[(i + fRec7_idx) & 63] = 0.35355338f * fZec68[i];
				fZec70[i] = fRec4[(i + fRec4_idx - 1) & 63] + fRec6[(i + fRec6_idx - 1) & 63];
				fZec71[i] = fRec8[(i + fRec8_idx - 1) & 63] + fRec10[(i + fRec10_idx - 1) & 63];
				fYec18[(i + fYec18_idx) & 8191] = fRec7[(i + fRec7_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fZec70[i] - (fRec11[(i + fRec11_idx - 1) & 63] + fRec9[(i + fRec9_idx - 1) & 63] + fZec71[i]);
				fYec19[(i + fYec19_idx) & 63] = fYec18[(i + fYec18_idx - std::min<int>(4097, std::max<int>(0, iZec73[i]))) & 8191] * (fZec74[i] + (1.0f - fZec72[i])) + (fZec72[i] - fZec74[i]) * fYec18[(i + fYec18_idx - std::min<int>(4097, std::max<int>(0, iZec73[i] + 1))) & 8191];
				fRec54[(i + fRec54_idx) & 63] = -(fConst6 * (fConst7 * fRec54[(i + fRec54_idx - 1) & 63] - (fYec19[(i + fYec19_idx) & 63] + fYec19[(i + fYec19_idx - 1) & 63])));
				fRec52[(i + fRec52_idx) & 63] = fZec75[i] * (fZec79[i] + (1.0f - fZec80[i])) * (fYec19[(i + fYec19_idx) & 63] + fRec54[(i + fRec54_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst17 / fZec27[i]))) / std::max<float>(1e-06f, fZec75[i]) + -1.0f)) + (fZec80[i] - fZec79[i]) * fRec52[(i + fRec52_idx - 1) & 63];
				fZec81[i] = TailwindDSP_faustpower2_f(fRec52[(i + fRec52_idx) & 63]);
				fZec82[i] = fRec52[(i + fRec52_idx) & 63] * (0.125f * fZec81[i] + 27.0f) / (1.125f * fZec81[i] + 27.0f);
				fRec8[(i + fRec8_idx) & 63] = 0.35355338f * fZec82[i];
				fYec20[(i + fYec20_idx) & 8191] = fRec11[(i + fRec11_idx - 1) & 63] + fRec9[(i + fRec9_idx - 1) & 63] + fZec70[i] - (fRec7[(i + fRec7_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fZec71[i]);
				fYec21[(i + fYec21_idx) & 63] = fYec20[(i + fYec20_idx - std::min<int>(4097, std::max<int>(0, iZec86[i]))) & 8191] * (fZec87[i] + (1.0f - fZec85[i])) + (fZec85[i] - fZec87[i]) * fYec20[(i + fYec20_idx - std::min<int>(4097, std::max<int>(0, iZec86[i] + 1))) & 8191];
				fRec57[(i + fRec57_idx) & 63] = -(fConst6 * (fConst7 * fRec57[(i + fRec57_idx - 1) & 63] - (fYec21[(i + fYec21_idx) & 63] + fYec21[(i + fYec21_idx - 1) & 63])));
				fRec55[(i + fRec55_idx) & 63] = fZec88[i] * (fZec92[i] + (1.0f - fZec93[i])) * (fYec21[(i + fYec21_idx) & 63] + fRec57[(i + fRec57_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst19 / fZec27[i]))) / std::max<float>(1e-06f, fZec88[i]) + -1.0f)) + (fZec93[i] - fZec92[i]) * fRec55[(i + fRec55_idx - 1) & 63];
				fZec94[i] = TailwindDSP_faustpower2_f(fRec55[(i + fRec55_idx) & 63]);
				fZec95[i] = fRec55[(i + fRec55_idx) & 63] * (0.125f * fZec94[i] + 27.0f) / (1.125f * fZec94[i] + 27.0f);
				fRec9[(i + fRec9_idx) & 63] = 0.35355338f * fZec95[i];
				fZec97[i] = fRec4[(i + fRec4_idx - 1) & 63] + fRec10[(i + fRec10_idx - 1) & 63];
				fZec98[i] = fRec8[(i + fRec8_idx - 1) & 63] + fRec6[(i + fRec6_idx - 1) & 63];
				fYec22[(i + fYec22_idx) & 8191] = fRec11[(i + fRec11_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fZec97[i] - (fRec7[(i + fRec7_idx - 1) & 63] + fRec9[(i + fRec9_idx - 1) & 63] + fZec98[i]);
				fYec23[(i + fYec23_idx) & 63] = fYec22[(i + fYec22_idx - std::min<int>(4097, std::max<int>(0, iZec100[i]))) & 8191] * (fZec101[i] + (1.0f - fZec99[i])) + (fZec99[i] - fZec101[i]) * fYec22[(i + fYec22_idx - std::min<int>(4097, std::max<int>(0, iZec100[i] + 1))) & 8191];
				fRec60[(i + fRec60_idx) & 63] = -(fConst6 * (fConst7 * fRec60[(i + fRec60_idx - 1) & 63] - (fYec23[(i + fYec23_idx) & 63] + fYec23[(i + fYec23_idx - 1) & 63])));
				fRec58[(i + fRec58_idx) & 63] = fZec102[i] * (fZec106[i] + (1.0f - fZec107[i])) * (fYec23[(i + fYec23_idx) & 63] + fRec60[(i + fRec60_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst21 / fZec27[i]))) / std::max<float>(1e-06f, fZec102[i]) + -1.0f)) + (fZec107[i] - fZec106[i]) * fRec58[(i + fRec58_idx - 1) & 63];
				fZec108[i] = TailwindDSP_faustpower2_f(fRec58[(i + fRec58_idx) & 63]);
				fZec109[i] = fRec58[(i + fRec58_idx) & 63] * (0.125f * fZec108[i] + 27.0f) / (1.125f * fZec108[i] + 27.0f);
				fRec10[(i + fRec10_idx) & 63] = 0.35355338f * fZec109[i];
				fYec24[(i + fYec24_idx) & 8191] = fRec7[(i + fRec7_idx - 1) & 63] + fRec9[(i + fRec9_idx - 1) & 63] + fZec97[i] - (fRec11[(i + fRec11_idx - 1) & 63] + fRec5[(i + fRec5_idx - 1) & 63] + fZec98[i]);
				fYec25[(i + fYec25_idx) & 63] = fYec24[(i + fYec24_idx - std::min<int>(4097, std::max<int>(0, iZec113[i]))) & 8191] * (fZec114[i] + (1.0f - fZec112[i])) + (fZec112[i] - fZec114[i]) * fYec24[(i + fYec24_idx - std::min<int>(4097, std::max<int>(0, iZec113[i] + 1))) & 8191];
				fRec63[(i + fRec63_idx) & 63] = -(fConst6 * (fConst7 * fRec63[(i + fRec63_idx - 1) & 63] - (fYec25[(i + fYec25_idx) & 63] + fYec25[(i + fYec25_idx - 1) & 63])));
				fRec61[(i + fRec61_idx) & 63] = fZec115[i] * (fZec119[i] + (1.0f - fZec120[i])) * (fYec25[(i + fYec25_idx) & 63] + fRec63[(i + fRec63_idx) & 63] * ((fRec15[(i + fRec15_idx) & 63] + fZec12[i] * std::exp(-(fConst23 / fZec27[i]))) / std::max<float>(1e-06f, fZec115[i]) + -1.0f)) + (fZec120[i] - fZec119[i]) * fRec61[(i + fRec61_idx - 1) & 63];
				fZec121[i] = TailwindDSP_faustpower2_f(fRec61[(i + fRec61_idx) & 63]);
				fZec122[i] = fRec61[(i + fRec61_idx) & 63] * (0.125f * fZec121[i] + 27.0f) / (1.125f * fZec121[i] + 27.0f);
				fRec11[(i + fRec11_idx) & 63] = 0.35355338f * fZec122[i];
				fRec12[i] = 0.07071068f * (fZec109[i] + fZec82[i] + fZec29[i] + fZec55[i]);
				fRec13[i] = 0.07071068f * (fZec122[i] + fZec95[i] + fZec42[i] + fZec68[i]);
			}
			/* Post code */
			fYec24_idx_save = vsize;
			fYec25_idx_save = vsize;
			fRec63_idx_save = vsize;
			fRec61_idx_save = vsize;
			fYec22_idx_save = vsize;
			fYec23_idx_save = vsize;
			fRec60_idx_save = vsize;
			fRec58_idx_save = vsize;
			fYec20_idx_save = vsize;
			fYec21_idx_save = vsize;
			fRec57_idx_save = vsize;
			fRec55_idx_save = vsize;
			fYec18_idx_save = vsize;
			fYec19_idx_save = vsize;
			fRec54_idx_save = vsize;
			fRec52_idx_save = vsize;
			fYec16_idx_save = vsize;
			fYec17_idx_save = vsize;
			fRec51_idx_save = vsize;
			fRec49_idx_save = vsize;
			fYec14_idx_save = vsize;
			fYec15_idx_save = vsize;
			fRec48_idx_save = vsize;
			fRec46_idx_save = vsize;
			fYec12_idx_save = vsize;
			fYec13_idx_save = vsize;
			fRec44_idx_save = vsize;
			fRec42_idx_save = vsize;
			fYec10_idx_save = vsize;
			fYec11_idx_save = vsize;
			fRec39_idx_save = vsize;
			fRec14_idx_save = vsize;
			fRec4_idx_save = vsize;
			fRec5_idx_save = vsize;
			fRec6_idx_save = vsize;
			fRec7_idx_save = vsize;
			fRec8_idx_save = vsize;
			fRec9_idx_save = vsize;
			fRec10_idx_save = vsize;
			fRec11_idx_save = vsize;
			/* Vectorizable loop 131 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec129[i] = fZec126[i] * fZec128[i];
			}
			/* Vectorizable loop 132 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec132[i] = (fZec131[i] + -1.4142135f) / fZec130[i] + 1.0f;
			}
			/* Vectorizable loop 133 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec133[i] = 1.0f - 1.0f / TailwindDSP_faustpower2_f(fZec130[i]);
			}
			/* Vectorizable loop 134 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec134[i] = (fZec131[i] + 1.4142135f) / fZec130[i] + 1.0f;
			}
			/* Recursive loop 135 */
			/* Pre code */
			fRec69_idx = (fRec69_idx + fRec69_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec69[(i + fRec69_idx) & 63] = fRec13[i] - (fZec125[i] * fRec69[(i + fRec69_idx - 2) & 63] + 2.0f * fZec127[i] * fRec69[(i + fRec69_idx - 1) & 63]) / fZec128[i];
			}
			/* Post code */
			fRec69_idx_save = vsize;
			/* Recursive loop 136 */
			/* Pre code */
			fRec3_idx = (fRec3_idx + fRec3_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec3[(i + fRec3_idx) & 63] = fRec12[i] - (fRec3[(i + fRec3_idx - 2) & 63] * fZec125[i] + 2.0f * fRec3[(i + fRec3_idx - 1) & 63] * fZec127[i]) / fZec128[i];
			}
			/* Post code */
			fRec3_idx_save = vsize;
			/* Recursive loop 137 */
			/* Pre code */
			fRec66_idx = (fRec66_idx + fRec66_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec66[(i + fRec66_idx) & 63] = fSlow12 + fConst2 * fRec66[(i + fRec66_idx - 1) & 63];
			}
			/* Post code */
			fRec66_idx_save = vsize;
			/* Recursive loop 138 */
			/* Pre code */
			fRec68_idx = (fRec68_idx + fRec68_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec68[(i + fRec68_idx) & 63] = (fRec69[(i + fRec69_idx - 2) & 63] + (fRec69[(i + fRec69_idx) & 63] - 2.0f * fRec69[(i + fRec69_idx - 1) & 63])) / fZec129[i] - (fZec132[i] * fRec68[(i + fRec68_idx - 2) & 63] + 2.0f * fZec133[i] * fRec68[(i + fRec68_idx - 1) & 63]) / fZec134[i];
			}
			/* Post code */
			fRec68_idx_save = vsize;
			/* Recursive loop 139 */
			/* Pre code */
			fRec1_idx = (fRec1_idx + fRec1_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec1[(i + fRec1_idx) & 63] = fSlow1 + fConst2 * fRec1[(i + fRec1_idx - 1) & 63];
			}
			/* Post code */
			fRec1_idx_save = vsize;
			/* Recursive loop 140 */
			/* Pre code */
			fRec2_idx = (fRec2_idx + fRec2_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec2[(i + fRec2_idx) & 63] = (fRec3[(i + fRec3_idx - 2) & 63] + (fRec3[(i + fRec3_idx) & 63] - 2.0f * fRec3[(i + fRec3_idx - 1) & 63])) / fZec129[i] - (fRec2[(i + fRec2_idx - 2) & 63] * fZec132[i] + 2.0f * fRec2[(i + fRec2_idx - 1) & 63] * fZec133[i]) / fZec134[i];
			}
			/* Post code */
			fRec2_idx_save = vsize;
			/* Vectorizable loop 141 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec145[i] = fRec68[(i + fRec68_idx - 2) & 63] + fRec68[(i + fRec68_idx) & 63] + 2.0f * fRec68[(i + fRec68_idx - 1) & 63];
			}
			/* Recursive loop 142 */
			/* Pre code */
			fRec67_idx = (fRec67_idx + fRec67_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec67[(i + fRec67_idx) & 63] = fSlow13 + fConst2 * fRec67[(i + fRec67_idx - 1) & 63];
			}
			/* Post code */
			fRec67_idx_save = vsize;
			/* Vectorizable loop 143 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec135[i] = 1.5707964f * fRec1[(i + fRec1_idx) & 63];
			}
			/* Vectorizable loop 144 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec137[i] = fRec2[(i + fRec2_idx - 2) & 63] + fRec2[(i + fRec2_idx) & 63] + 2.0f * fRec2[(i + fRec2_idx - 1) & 63];
			}
			/* Vectorizable loop 145 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec138[i] = TailwindDSP_faustpower2_f(7.0f * fRec66[(i + fRec66_idx) & 63] + 1.0f);
			}
			/* Vectorizable loop 146 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec139[i] = TailwindDSP_faustpower2_f(fZec134[i]);
			}
			/* Vectorizable loop 147 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec146[i] = fZec138[i] * TailwindDSP_faustpower2_f(fZec145[i]) / fZec139[i];
			}
			/* Vectorizable loop 148 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec136[i] = std::cos(fZec135[i]);
			}
			/* Vectorizable loop 149 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec140[i] = TailwindDSP_faustpower2_f(fZec137[i]) * fZec138[i] / fZec139[i];
			}
			/* Vectorizable loop 150 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec141[i] = 9.0f * fZec138[i] + 27.0f;
			}
			/* Vectorizable loop 151 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec142[i] = std::sin(fZec135[i]);
			}
			/* Vectorizable loop 152 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec143[i] = fZec138[i] + 27.0f;
			}
			/* Vectorizable loop 153 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec144[i] = std::pow(1e+01f, 0.05f * fRec67[(i + fRec67_idx) & 63]);
			}
			/* Vectorizable loop 154 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output1[i] = FAUSTFLOAT(fZec144[i] * (fYec5[(i + fYec5_idx) & 32767] * fZec136[i] + fZec141[i] * fZec142[i] * fZec145[i] * (fZec146[i] + 27.0f) / (fZec134[i] * fZec143[i] * (9.0f * fZec146[i] + 27.0f))));
			}
			/* Vectorizable loop 155 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = FAUSTFLOAT((fYec0[(i + fYec0_idx) & 32767] * fZec136[i] + fZec137[i] * (fZec140[i] + 27.0f) * fZec141[i] * fZec142[i] / (fZec134[i] * (9.0f * fZec140[i] + 27.0f) * fZec143[i])) * fZec144[i]);
			}
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "tailwind_reverb.dsp"
	#define FAUST_CLASS_NAME "TailwindDSP"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -ct 1 -cn TailwindDSP -scn  -es 1 -mcd 0 -mdd 1024 -mdy 33 -uim -single -ftz 0 -vec -lv 1 -vs 32"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 15
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Mix", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Decay", fHslider3, 0.85f, 0.1f, 0.99f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Pre-Delay (ms)", fHslider5, 2e+01f, 0.0f, 5e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Diffusion", fHslider6, 0.7f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Damping", fHslider4, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Low Damp", fHslider9, 0.2f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Mod Rate (Hz)", fHslider8, 0.8f, 0.1f, 5.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Mod Depth", fHslider7, 0.3f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Low Cut (Hz)", fHslider10, 8e+01f, 2e+01f, 5e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("High Cut (Hz)", fHslider11, 1.2e+04f, 1e+03f, 2e+04f, 1e+02f);
	FAUST_ADDHORIZONTALSLIDER("Freeze", fHslider2, 1.0f, 0.6f, 1.0f, 0.01f);
	FAUST_ADDCHECKBOX("Freeze On", fCheckbox0);
	FAUST_ADDHORIZONTALSLIDER("Saturation", fHslider12, 0.125f, 0.0f, 0.25f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Input Gain", fHslider0, 0.0f, -24.0f, 24.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Output Gain", fHslider13, 0.0f, -24.0f, 24.0f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Mix, "Mix", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Decay, "Decay", fHslider3, 0.85f, 0.1f, 0.99f, 0.001f) \
		p(HORIZONTALSLIDER, Pre-Delay_(ms), "Pre-Delay (ms)", fHslider5, 2e+01f, 0.0f, 5e+02f, 1.0f) \
		p(HORIZONTALSLIDER, Diffusion, "Diffusion", fHslider6, 0.7f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Damping, "Damping", fHslider4, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Low_Damp, "Low Damp", fHslider9, 0.2f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Mod_Rate_(Hz), "Mod Rate (Hz)", fHslider8, 0.8f, 0.1f, 5.0f, 0.01f) \
		p(HORIZONTALSLIDER, Mod_Depth, "Mod Depth", fHslider7, 0.3f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Low_Cut_(Hz), "Low Cut (Hz)", fHslider10, 8e+01f, 2e+01f, 5e+02f, 1.0f) \
		p(HORIZONTALSLIDER, High_Cut_(Hz), "High Cut (Hz)", fHslider11, 1.2e+04f, 1e+03f, 2e+04f, 1e+02f) \
		p(HORIZONTALSLIDER, Freeze, "Freeze", fHslider2, 1.0f, 0.6f, 1.0f, 0.01f) \
		p(CHECKBOX, Freeze_On, "Freeze On", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Saturation, "Saturation", fHslider12, 0.125f, 0.0f, 0.25f, 0.01f) \
		p(HORIZONTALSLIDER, Input_Gain, "Input Gain", fHslider0, 0.0f, -24.0f, 24.0f, 0.1f) \
		p(HORIZONTALSLIDER, Output_Gain, "Output Gain", fHslider13, 0.0f, -24.0f, 24.0f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
