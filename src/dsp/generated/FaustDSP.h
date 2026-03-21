/* ------------------------------------------------------------
name: "tailwind_reverb"
Code generated with Faust 2.79.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn TailwindDSP -scn  -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  __TailwindDSP_H__
#define  __TailwindDSP_H__

#include "FaustDefs.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
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
	int iVec12[2];
	int iRec36[2];
	
	int getNumInputsTailwindDSPSIG0() {
		return 0;
	}
	int getNumOutputsTailwindDSPSIG0() {
		return 1;
	}
	
	void instanceInitTailwindDSPSIG0(int sample_rate) {
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			iVec12[l27] = 0;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			iRec36[l28] = 0;
		}
	}
	
	void fillTailwindDSPSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec12[0] = 1;
			iRec36[0] = (iVec12[1] + iRec36[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec36[0]));
			iVec12[1] = iVec12[0];
			iRec36[1] = iRec36[0];
		}
	}

};

static TailwindDSPSIG0* newTailwindDSPSIG0() { return (TailwindDSPSIG0*)new TailwindDSPSIG0(); }
static void deleteTailwindDSPSIG0(TailwindDSPSIG0* dsp) { delete dsp; }

struct TailwindDSPSIG1 {
	int iVec15[2];
	int iRec43[2];
	
	int getNumInputsTailwindDSPSIG1() {
		return 0;
	}
	int getNumOutputsTailwindDSPSIG1() {
		return 1;
	}
	
	void instanceInitTailwindDSPSIG1(int sample_rate) {
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			iVec15[l38] = 0;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			iRec43[l39] = 0;
		}
	}
	
	void fillTailwindDSPSIG1(int count, float* table) {
		for (int i2 = 0; i2 < count; i2 = i2 + 1) {
			iVec15[0] = 1;
			iRec43[0] = (iVec15[1] + iRec43[1]) % 65536;
			table[i2] = std::cos(9.58738e-05f * float(iRec43[0]));
			iVec15[1] = iVec15[0];
			iRec43[1] = iRec43[0];
		}
	}

};

static TailwindDSPSIG1* newTailwindDSPSIG1() { return (TailwindDSPSIG1*)new TailwindDSPSIG1(); }
static void deleteTailwindDSPSIG1(TailwindDSPSIG1* dsp) { delete dsp; }

static float TailwindDSP_faustpower2_f(float value) {
	return value * value;
}
static float ftbl0TailwindDSPSIG0[65536];
static float ftbl1TailwindDSPSIG1[65536];

struct TailwindDSP {
	
	int IOTA0;
	float fVec0[32768];
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	int iVec1[2];
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fCheckbox0;
	float fRec14[2];
	float fConst3;
	FAUSTFLOAT fHslider2;
	float fRec15[2];
	float fConst4;
	FAUSTFLOAT fHslider3;
	float fRec16[2];
	float fConst5;
	FAUSTFLOAT fHslider4;
	float fRec25[2];
	FAUSTFLOAT fHslider5;
	float fRec26[2];
	float fVec2[256];
	float fRec23[2];
	float fVec3[128];
	float fRec21[2];
	float fVec4[512];
	float fRec19[2];
	float fVec5[512];
	float fRec17[2];
	float fVec6[32768];
	float fVec7[256];
	float fRec33[2];
	float fVec8[128];
	float fRec31[2];
	float fVec9[512];
	float fRec29[2];
	float fVec10[512];
	float fRec27[2];
	float fVec11[8192];
	FAUSTFLOAT fHslider6;
	float fRec35[2];
	float fConst6;
	FAUSTFLOAT fHslider7;
	float fRec38[2];
	float fRec37[2];
	float fVec13[2];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec39[2];
	FAUSTFLOAT fHslider8;
	float fRec40[2];
	float fRec13[2];
	float fRec3[2];
	float fConst10;
	float fVec14[8192];
	float fConst11;
	float fRec42[2];
	float fVec16[2];
	float fRec44[2];
	float fRec41[2];
	float fRec4[2];
	float fConst12;
	float fVec17[8192];
	float fConst13;
	float fRec46[2];
	float fVec18[2];
	float fRec47[2];
	float fRec45[2];
	float fRec5[2];
	float fConst14;
	float fVec19[8192];
	float fConst15;
	float fRec49[2];
	float fVec20[2];
	float fRec50[2];
	float fRec48[2];
	float fRec6[2];
	float fConst16;
	float fVec21[8192];
	float fConst17;
	float fRec52[2];
	float fVec22[2];
	float fRec53[2];
	float fRec51[2];
	float fRec7[2];
	float fConst18;
	float fVec23[8192];
	float fConst19;
	float fRec55[2];
	float fVec24[2];
	float fRec56[2];
	float fRec54[2];
	float fRec8[2];
	float fConst20;
	float fVec25[8192];
	float fConst21;
	float fRec58[2];
	float fVec26[2];
	float fRec59[2];
	float fRec57[2];
	float fRec9[2];
	float fConst22;
	float fVec27[8192];
	float fConst23;
	float fRec61[2];
	float fVec28[2];
	float fRec62[2];
	float fRec60[2];
	float fRec10[2];
	float fConst24;
	FAUSTFLOAT fHslider9;
	float fRec63[2];
	float fRec2[3];
	FAUSTFLOAT fHslider10;
	float fRec64[2];
	float fRec1[3];
	FAUSTFLOAT fHslider11;
	float fRec65[2];
	float fRec67[3];
	float fRec66[3];
	
	TailwindDSP() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -cn TailwindDSP -scn  -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
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
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
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
		fConst3 = 9830.084f / fConst0;
		fConst4 = 125663.7f / fConst0;
		fConst5 = 0.001f * fConst0;
		fConst6 = 1.0f / fConst0;
		fConst7 = 1.0f / std::tan(628.31854f / fConst0);
		fConst8 = 1.0f / (fConst7 + 1.0f);
		fConst9 = 1.0f - fConst7;
		fConst10 = 11308.396f / fConst0;
		fConst11 = 1.013f / fConst0;
		fConst12 = 12510.388f / fConst0;
		fConst13 = 1.026f / fConst0;
		fConst14 = 13836.724f / fConst0;
		fConst15 = 1.039f / fConst0;
		fConst16 = 15052.532f / fConst0;
		fConst17 = 1.052f / fConst0;
		fConst18 = 16447.947f / fConst0;
		fConst19 = 1.065f / fConst0;
		fConst20 = 17898.629f / fConst0;
		fConst21 = 1.078f / fConst0;
		fConst22 = 19321.676f / fConst0;
		fConst23 = 1.091f / fConst0;
		fConst24 = 3.1415927f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.85f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(2e+01f);
		fHslider5 = FAUSTFLOAT(0.7f);
		fHslider6 = FAUSTFLOAT(0.3f);
		fHslider7 = FAUSTFLOAT(0.8f);
		fHslider8 = FAUSTFLOAT(0.2f);
		fHslider9 = FAUSTFLOAT(8e+01f);
		fHslider10 = FAUSTFLOAT(1.2e+04f);
		fHslider11 = FAUSTFLOAT(0.125f);
	}
	
	virtual void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 32768; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iVec1[l1] = 0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec14[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec15[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec16[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec25[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec26[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 256; l8 = l8 + 1) {
			fVec2[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec23[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 128; l10 = l10 + 1) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec21[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 512; l12 = l12 + 1) {
			fVec4[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec19[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 512; l14 = l14 + 1) {
			fVec5[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec17[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 32768; l16 = l16 + 1) {
			fVec6[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 256; l17 = l17 + 1) {
			fVec7[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec33[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 128; l19 = l19 + 1) {
			fVec8[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec31[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 512; l21 = l21 + 1) {
			fVec9[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec29[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 512; l23 = l23 + 1) {
			fVec10[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec27[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 8192; l25 = l25 + 1) {
			fVec11[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec35[l26] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec38[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec37[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fVec13[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec39[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec40[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec13[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec3[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 8192; l36 = l36 + 1) {
			fVec14[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec42[l37] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fVec16[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec44[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec41[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec4[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 8192; l44 = l44 + 1) {
			fVec17[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec46[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fVec18[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec47[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fRec45[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec5[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 8192; l50 = l50 + 1) {
			fVec19[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec49[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fVec20[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec50[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec48[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec6[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 8192; l56 = l56 + 1) {
			fVec21[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec52[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fVec22[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec53[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 2; l60 = l60 + 1) {
			fRec51[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec7[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 8192; l62 = l62 + 1) {
			fVec23[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec55[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fVec24[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec56[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fRec54[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fRec8[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 8192; l68 = l68 + 1) {
			fVec25[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 2; l69 = l69 + 1) {
			fRec58[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fVec26[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fRec59[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 2; l72 = l72 + 1) {
			fRec57[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 2; l73 = l73 + 1) {
			fRec9[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 8192; l74 = l74 + 1) {
			fVec27[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fRec61[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fVec28[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 2; l77 = l77 + 1) {
			fRec62[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fRec60[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fRec10[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			fRec63[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec2[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec64[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 3; l83 = l83 + 1) {
			fRec1[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 2; l84 = l84 + 1) {
			fRec65[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 3; l85 = l85 + 1) {
			fRec67[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 3; l86 = l86 + 1) {
			fRec66[l86] = 0.0f;
		}
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
		ui_interface->declare(&fHslider0, "01", "");
		ui_interface->addHorizontalSlider("Mix", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider2, "02", "");
		ui_interface->addHorizontalSlider("Decay", &fHslider2, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.99f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider4, "03", "");
		ui_interface->addHorizontalSlider("Pre-Delay (ms)", &fHslider4, FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "04", "");
		ui_interface->addHorizontalSlider("Diffusion", &fHslider5, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider3, "05", "");
		ui_interface->addHorizontalSlider("Damping", &fHslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider8, "06", "");
		ui_interface->addHorizontalSlider("Low Damp", &fHslider8, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider7, "07", "");
		ui_interface->addHorizontalSlider("Mod Rate (Hz)", &fHslider7, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.1f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider6, "08", "");
		ui_interface->addHorizontalSlider("Mod Depth", &fHslider6, FAUSTFLOAT(0.3f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider9, "09", "");
		ui_interface->addHorizontalSlider("Low Cut (Hz)", &fHslider9, FAUSTFLOAT(8e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(5e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider10, "10", "");
		ui_interface->addHorizontalSlider("High Cut (Hz)", &fHslider10, FAUSTFLOAT(1.2e+04f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1e+02f));
		ui_interface->declare(&fHslider1, "11", "");
		ui_interface->addHorizontalSlider("Freeze", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.6f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fCheckbox0, "12", "");
		ui_interface->addCheckButton("Freeze On", &fCheckbox0);
		ui_interface->declare(&fHslider11, "13", "");
		ui_interface->addHorizontalSlider("Saturation", &fHslider11, FAUSTFLOAT(0.125f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = fConst1 * float(fHslider1) * float(fCheckbox0);
		float fSlow2 = fConst1 * float(fHslider2);
		float fSlow3 = fConst1 * float(fHslider3);
		float fSlow4 = fConst1 * float(fHslider4);
		float fSlow5 = fConst1 * float(fHslider5);
		float fSlow6 = fConst1 * float(fHslider6);
		float fSlow7 = fConst1 * float(fHslider7);
		float fSlow8 = fConst1 * float(fHslider8);
		float fSlow9 = fConst1 * float(fHslider9);
		float fSlow10 = fConst1 * float(fHslider10);
		float fSlow11 = fConst1 * float(fHslider11);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			fVec0[IOTA0 & 32767] = fTemp0;
			iVec1[0] = 1;
			fRec0[0] = fSlow0 + fConst2 * fRec0[1];
			float fTemp1 = 1.5707964f * fRec0[0];
			float fTemp2 = std::cos(fTemp1);
			fRec14[0] = fSlow1 + fConst2 * fRec14[1];
			float fTemp3 = 1.0f - fRec14[0];
			fRec15[0] = fSlow2 + fConst2 * fRec15[1];
			float fTemp4 = std::pow(1.5e+02f, fRec15[0]);
			float fTemp5 = std::max<float>(0.01f, 0.2f * fTemp4);
			float fTemp6 = fRec14[0] + fTemp3 * std::exp(-(fConst3 / fTemp5));
			float fTemp7 = TailwindDSP_faustpower2_f(fTemp6);
			fRec16[0] = fSlow3 + fConst2 * fRec16[1];
			float fTemp8 = std::cos(fConst4 * std::pow(0.05f, fRec16[0]));
			float fTemp9 = 1.0f - fTemp7 * fTemp8;
			float fTemp10 = std::max<float>(1e-06f, 1.0f - fTemp7);
			float fTemp11 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp9) / TailwindDSP_faustpower2_f(fTemp10) + -1.0f));
			float fTemp12 = fTemp9 / fTemp10;
			float fTemp13 = fRec3[1] + fRec7[1];
			float fTemp14 = fRec9[1] + fRec5[1] + fTemp13;
			fRec25[0] = fSlow4 + fConst2 * fRec25[1];
			float fTemp15 = fConst5 * fRec25[0];
			int iTemp16 = int(fTemp15);
			int iTemp17 = std::min<int>(24001, std::max<int>(0, iTemp16));
			float fTemp18 = std::floor(fTemp15);
			float fTemp19 = fTemp18 + (1.0f - fTemp15);
			float fTemp20 = fTemp15 - fTemp18;
			int iTemp21 = std::min<int>(24001, std::max<int>(0, iTemp16 + 1));
			fRec26[0] = fSlow5 + fConst2 * fRec26[1];
			float fTemp22 = fVec0[(IOTA0 - iTemp17) & 32767] * fTemp19 + fTemp20 * fVec0[(IOTA0 - iTemp21) & 32767] - 0.75f * fRec26[0] * fRec23[1];
			fVec2[IOTA0 & 255] = fTemp22;
			fRec23[0] = fVec2[(IOTA0 - 141) & 255];
			float fRec24 = 0.75f * fRec26[0] * fTemp22;
			float fTemp23 = fRec24 + fRec23[1] - 0.75f * fRec26[0] * fRec21[1];
			fVec3[IOTA0 & 127] = fTemp23;
			fRec21[0] = fVec3[(IOTA0 - 106) & 127];
			float fRec22 = 0.75f * fRec26[0] * fTemp23;
			float fTemp24 = fRec22 + fRec21[1] - 0.75f * fRec26[0] * fRec19[1];
			fVec4[IOTA0 & 511] = fTemp24;
			fRec19[0] = fVec4[(IOTA0 - 378) & 511];
			float fRec20 = 0.75f * fRec26[0] * fTemp24;
			float fTemp25 = fRec20 + fRec19[1] - 0.75f * fRec26[0] * fRec17[1];
			fVec5[IOTA0 & 511] = fTemp25;
			fRec17[0] = fVec5[(IOTA0 - 276) & 511];
			float fRec18 = 0.75f * fRec26[0] * fTemp25;
			float fTemp26 = fRec18 + fRec17[1];
			float fTemp27 = float(input1[i0]);
			fVec6[IOTA0 & 32767] = fTemp27;
			float fTemp28 = fTemp19 * fVec6[(IOTA0 - iTemp17) & 32767] + fTemp20 * fVec6[(IOTA0 - iTemp21) & 32767] - 0.75f * fRec26[0] * fRec33[1];
			fVec7[IOTA0 & 255] = fTemp28;
			fRec33[0] = fVec7[(IOTA0 - 150) & 255];
			float fRec34 = 0.75f * fRec26[0] * fTemp28;
			float fTemp29 = fRec34 + fRec33[1] - 0.75f * fRec26[0] * fRec31[1];
			fVec8[IOTA0 & 127] = fTemp29;
			fRec31[0] = fVec8[(IOTA0 - 112) & 127];
			float fRec32 = 0.75f * fRec26[0] * fTemp29;
			float fTemp30 = fRec32 + fRec31[1] - 0.75f * fRec26[0] * fRec29[1];
			fVec9[IOTA0 & 511] = fTemp30;
			fRec29[0] = fVec9[(IOTA0 - 388) & 511];
			float fRec30 = 0.75f * fRec26[0] * fTemp30;
			float fTemp31 = fRec30 + fRec29[1] - 0.75f * fRec26[0] * fRec27[1];
			fVec10[IOTA0 & 511] = fTemp31;
			fRec27[0] = fVec10[(IOTA0 - 282) & 511];
			float fRec28 = 0.75f * fRec26[0] * fTemp31;
			float fTemp32 = fRec28 + fRec27[1];
			float fTemp33 = fRec10[1] + fRec6[1] + fRec8[1] + fRec4[1] + fTemp14 + 2.0f * fTemp3 * (fTemp26 + fTemp32);
			fVec11[IOTA0 & 8191] = fTemp33;
			fRec35[0] = fSlow6 + fConst2 * fRec35[1];
			int iTemp34 = 1 - iVec1[1];
			fRec38[0] = fSlow7 + fConst2 * fRec38[1];
			float fTemp35 = ((iTemp34) ? 0.0f : fRec37[1] + fConst6 * fRec38[0]);
			fRec37[0] = fTemp35 - std::floor(fTemp35);
			float fTemp36 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (ftbl0TailwindDSPSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec37[0]), 65535))] + 1.0f) + 1423.0f));
			int iTemp37 = int(fTemp36);
			float fTemp38 = std::floor(fTemp36);
			float fTemp39 = fVec11[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp37))) & 8191] * (fTemp38 + (1.0f - fTemp36)) + (fTemp36 - fTemp38) * fVec11[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp37 + 1))) & 8191];
			fVec13[0] = fTemp39;
			fRec39[0] = -(fConst8 * (fConst9 * fRec39[1] - (fTemp39 + fVec13[1])));
			fRec40[0] = fSlow8 + fConst2 * fRec40[1];
			float fTemp40 = std::max<float>(0.01f, 0.2f * fTemp4 * (1.0f - 0.75f * fRec40[0]));
			fRec13[0] = fTemp6 * (fTemp11 + (1.0f - fTemp12)) * (fTemp39 + fRec39[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst3 / fTemp40))) / std::max<float>(1e-06f, fTemp6) + -1.0f)) + (fTemp12 - fTemp11) * fRec13[1];
			float fTemp41 = tanhf(0.35355338f * (fRec13[0] + 1e-20f));
			fRec3[0] = fTemp41;
			float fTemp42 = fRec14[0] + fTemp3 * std::exp(-(fConst10 / fTemp5));
			float fTemp43 = TailwindDSP_faustpower2_f(fTemp42);
			float fTemp44 = 1.0f - fTemp8 * fTemp43;
			float fTemp45 = std::max<float>(1e-06f, 1.0f - fTemp43);
			float fTemp46 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp44) / TailwindDSP_faustpower2_f(fTemp45) + -1.0f));
			float fTemp47 = fTemp44 / fTemp45;
			float fTemp48 = fTemp14 + 2.0f * fTemp3 * (fTemp26 - fTemp32) - (fRec10[1] + fRec6[1] + fRec4[1] + fRec8[1]);
			fVec14[IOTA0 & 8191] = fTemp48;
			float fTemp49 = ((iTemp34) ? 0.0f : fRec42[1] + fConst11 * fRec38[0]);
			fRec42[0] = fTemp49 - std::floor(fTemp49);
			int iTemp50 = std::max<int>(0, std::min<int>(int(65536.0f * fRec42[0]), 65535));
			float fTemp51 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (0.70710677f * ftbl0TailwindDSPSIG0[iTemp50] + 0.70710677f * ftbl1TailwindDSPSIG1[iTemp50] + 1.0f) + 1637.0f));
			int iTemp52 = int(fTemp51);
			float fTemp53 = std::floor(fTemp51);
			float fTemp54 = fVec14[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp52))) & 8191] * (fTemp53 + (1.0f - fTemp51)) + (fTemp51 - fTemp53) * fVec14[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp52 + 1))) & 8191];
			fVec16[0] = fTemp54;
			fRec44[0] = -(fConst8 * (fConst9 * fRec44[1] - (fTemp54 + fVec16[1])));
			fRec41[0] = fTemp42 * (fTemp46 + (1.0f - fTemp47)) * (fTemp54 + fRec44[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst10 / fTemp40))) / std::max<float>(1e-06f, fTemp42) + -1.0f)) + (fTemp47 - fTemp46) * fRec41[1];
			float fTemp55 = tanhf(0.35355338f * (fRec41[0] + 1e-20f));
			fRec4[0] = fTemp55;
			float fTemp56 = fRec14[0] + fTemp3 * std::exp(-(fConst12 / fTemp5));
			float fTemp57 = TailwindDSP_faustpower2_f(fTemp56);
			float fTemp58 = 1.0f - fTemp8 * fTemp57;
			float fTemp59 = std::max<float>(1e-06f, 1.0f - fTemp57);
			float fTemp60 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp58) / TailwindDSP_faustpower2_f(fTemp59) + -1.0f));
			float fTemp61 = fTemp58 / fTemp59;
			float fTemp62 = fRec5[1] + fRec9[1];
			float fTemp63 = fRec8[1] + fRec4[1] + fTemp13 - (fRec10[1] + fRec6[1] + fTemp62);
			fVec17[IOTA0 & 8191] = fTemp63;
			float fTemp64 = ((iTemp34) ? 0.0f : fRec46[1] + fConst13 * fRec38[0]);
			fRec46[0] = fTemp64 - std::floor(fTemp64);
			float fTemp65 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (ftbl1TailwindDSPSIG1[std::max<int>(0, std::min<int>(int(65536.0f * fRec46[0]), 65535))] + 1.0f) + 1811.0f));
			int iTemp66 = int(fTemp65);
			float fTemp67 = std::floor(fTemp65);
			float fTemp68 = fVec17[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp66))) & 8191] * (fTemp67 + (1.0f - fTemp65)) + (fTemp65 - fTemp67) * fVec17[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp66 + 1))) & 8191];
			fVec18[0] = fTemp68;
			fRec47[0] = -(fConst8 * (fConst9 * fRec47[1] - (fTemp68 + fVec18[1])));
			fRec45[0] = fTemp56 * (fTemp60 + (1.0f - fTemp61)) * (fTemp68 + fRec47[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst12 / fTemp40))) / std::max<float>(1e-06f, fTemp56) + -1.0f)) + (fTemp61 - fTemp60) * fRec45[1];
			float fTemp69 = tanhf(0.35355338f * (fRec45[0] + 1e-20f));
			fRec5[0] = fTemp69;
			float fTemp70 = fRec14[0] + fTemp3 * std::exp(-(fConst14 / fTemp5));
			float fTemp71 = TailwindDSP_faustpower2_f(fTemp70);
			float fTemp72 = 1.0f - fTemp8 * fTemp71;
			float fTemp73 = std::max<float>(1e-06f, 1.0f - fTemp71);
			float fTemp74 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp72) / TailwindDSP_faustpower2_f(fTemp73) + -1.0f));
			float fTemp75 = fTemp72 / fTemp73;
			float fTemp76 = fRec10[1] + fRec6[1] + fTemp13 - (fRec8[1] + fRec4[1] + fTemp62);
			fVec19[IOTA0 & 8191] = fTemp76;
			float fTemp77 = ((iTemp34) ? 0.0f : fRec49[1] + fConst15 * fRec38[0]);
			fRec49[0] = fTemp77 - std::floor(fTemp77);
			int iTemp78 = std::max<int>(0, std::min<int>(int(65536.0f * fRec49[0]), 65535));
			float fTemp79 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (0.70710677f * ftbl1TailwindDSPSIG1[iTemp78] - 0.70710677f * ftbl0TailwindDSPSIG0[iTemp78] + 1.0f) + 2003.0f));
			int iTemp80 = int(fTemp79);
			float fTemp81 = std::floor(fTemp79);
			float fTemp82 = fVec19[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp80))) & 8191] * (fTemp81 + (1.0f - fTemp79)) + (fTemp79 - fTemp81) * fVec19[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp80 + 1))) & 8191];
			fVec20[0] = fTemp82;
			fRec50[0] = -(fConst8 * (fConst9 * fRec50[1] - (fTemp82 + fVec20[1])));
			fRec48[0] = fTemp70 * (fTemp74 + (1.0f - fTemp75)) * (fTemp82 + fRec50[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst14 / fTemp40))) / std::max<float>(1e-06f, fTemp70) + -1.0f)) + (fTemp75 - fTemp74) * fRec48[1];
			float fTemp83 = tanhf(0.35355338f * (fRec48[0] + 1e-20f));
			fRec6[0] = fTemp83;
			float fTemp84 = fRec14[0] + fTemp3 * std::exp(-(fConst16 / fTemp5));
			float fTemp85 = TailwindDSP_faustpower2_f(fTemp84);
			float fTemp86 = 1.0f - fTemp8 * fTemp85;
			float fTemp87 = std::max<float>(1e-06f, 1.0f - fTemp85);
			float fTemp88 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp86) / TailwindDSP_faustpower2_f(fTemp87) + -1.0f));
			float fTemp89 = fTemp86 / fTemp87;
			float fTemp90 = fRec3[1] + fRec5[1];
			float fTemp91 = fRec7[1] + fRec9[1];
			float fTemp92 = fRec6[1] + fRec4[1] + fTemp90 - (fRec10[1] + fRec8[1] + fTemp91);
			fVec21[IOTA0 & 8191] = fTemp92;
			float fTemp93 = ((iTemp34) ? 0.0f : fRec52[1] + fConst17 * fRec38[0]);
			fRec52[0] = fTemp93 - std::floor(fTemp93);
			float fTemp94 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (1.0f - ftbl0TailwindDSPSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec52[0]), 65535))]) + 2179.0f));
			int iTemp95 = int(fTemp94);
			float fTemp96 = std::floor(fTemp94);
			float fTemp97 = fVec21[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp95))) & 8191] * (fTemp96 + (1.0f - fTemp94)) + (fTemp94 - fTemp96) * fVec21[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp95 + 1))) & 8191];
			fVec22[0] = fTemp97;
			fRec53[0] = -(fConst8 * (fConst9 * fRec53[1] - (fTemp97 + fVec22[1])));
			fRec51[0] = fTemp84 * (fTemp88 + (1.0f - fTemp89)) * (fTemp97 + fRec53[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst16 / fTemp40))) / std::max<float>(1e-06f, fTemp84) + -1.0f)) + (fTemp89 - fTemp88) * fRec51[1];
			float fTemp98 = tanhf(0.35355338f * (fRec51[0] + 1e-20f));
			fRec7[0] = fTemp98;
			float fTemp99 = fRec14[0] + fTemp3 * std::exp(-(fConst18 / fTemp5));
			float fTemp100 = TailwindDSP_faustpower2_f(fTemp99);
			float fTemp101 = 1.0f - fTemp8 * fTemp100;
			float fTemp102 = std::max<float>(1e-06f, 1.0f - fTemp100);
			float fTemp103 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp101) / TailwindDSP_faustpower2_f(fTemp102) + -1.0f));
			float fTemp104 = fTemp101 / fTemp102;
			float fTemp105 = fRec10[1] + fRec8[1] + fTemp90 - (fRec6[1] + fRec4[1] + fTemp91);
			fVec23[IOTA0 & 8191] = fTemp105;
			float fTemp106 = ((iTemp34) ? 0.0f : fRec55[1] + fConst19 * fRec38[0]);
			fRec55[0] = fTemp106 - std::floor(fTemp106);
			int iTemp107 = std::max<int>(0, std::min<int>(int(65536.0f * fRec55[0]), 65535));
			float fTemp108 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (1.0f - (0.70710677f * ftbl0TailwindDSPSIG0[iTemp107] + 0.70710677f * ftbl1TailwindDSPSIG1[iTemp107])) + 2381.0f));
			int iTemp109 = int(fTemp108);
			float fTemp110 = std::floor(fTemp108);
			float fTemp111 = fVec23[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp109))) & 8191] * (fTemp110 + (1.0f - fTemp108)) + (fTemp108 - fTemp110) * fVec23[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp109 + 1))) & 8191];
			fVec24[0] = fTemp111;
			fRec56[0] = -(fConst8 * (fConst9 * fRec56[1] - (fTemp111 + fVec24[1])));
			fRec54[0] = fTemp99 * (fTemp103 + (1.0f - fTemp104)) * (fTemp111 + fRec56[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst18 / fTemp40))) / std::max<float>(1e-06f, fTemp99) + -1.0f)) + (fTemp104 - fTemp103) * fRec54[1];
			float fTemp112 = tanhf(0.35355338f * (fRec54[0] + 1e-20f));
			fRec8[0] = fTemp112;
			float fTemp113 = fRec14[0] + fTemp3 * std::exp(-(fConst20 / fTemp5));
			float fTemp114 = TailwindDSP_faustpower2_f(fTemp113);
			float fTemp115 = 1.0f - fTemp8 * fTemp114;
			float fTemp116 = std::max<float>(1e-06f, 1.0f - fTemp114);
			float fTemp117 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp115) / TailwindDSP_faustpower2_f(fTemp116) + -1.0f));
			float fTemp118 = fTemp115 / fTemp116;
			float fTemp119 = fRec3[1] + fRec9[1];
			float fTemp120 = fRec7[1] + fRec5[1];
			float fTemp121 = fRec10[1] + fRec4[1] + fTemp119 - (fRec6[1] + fRec8[1] + fTemp120);
			fVec25[IOTA0 & 8191] = fTemp121;
			float fTemp122 = ((iTemp34) ? 0.0f : fRec58[1] + fConst21 * fRec38[0]);
			fRec58[0] = fTemp122 - std::floor(fTemp122);
			float fTemp123 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (1.0f - ftbl1TailwindDSPSIG1[std::max<int>(0, std::min<int>(int(65536.0f * fRec58[0]), 65535))]) + 2591.0f));
			int iTemp124 = int(fTemp123);
			float fTemp125 = std::floor(fTemp123);
			float fTemp126 = fVec25[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp124))) & 8191] * (fTemp125 + (1.0f - fTemp123)) + (fTemp123 - fTemp125) * fVec25[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp124 + 1))) & 8191];
			fVec26[0] = fTemp126;
			fRec59[0] = -(fConst8 * (fConst9 * fRec59[1] - (fTemp126 + fVec26[1])));
			fRec57[0] = fTemp113 * (fTemp117 + (1.0f - fTemp118)) * (fTemp126 + fRec59[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst20 / fTemp40))) / std::max<float>(1e-06f, fTemp113) + -1.0f)) + (fTemp118 - fTemp117) * fRec57[1];
			float fTemp127 = tanhf(0.35355338f * (fRec57[0] + 1e-20f));
			fRec9[0] = fTemp127;
			float fTemp128 = fRec14[0] + fTemp3 * std::exp(-(fConst22 / fTemp5));
			float fTemp129 = TailwindDSP_faustpower2_f(fTemp128);
			float fTemp130 = 1.0f - fTemp8 * fTemp129;
			float fTemp131 = std::max<float>(1e-06f, 1.0f - fTemp129);
			float fTemp132 = std::sqrt(std::max<float>(0.0f, TailwindDSP_faustpower2_f(fTemp130) / TailwindDSP_faustpower2_f(fTemp131) + -1.0f));
			float fTemp133 = fTemp130 / fTemp131;
			float fTemp134 = fRec6[1] + fRec8[1] + fTemp119 - (fRec10[1] + fRec4[1] + fTemp120);
			fVec27[IOTA0 & 8191] = fTemp134;
			float fTemp135 = ((iTemp34) ? 0.0f : fRec61[1] + fConst23 * fRec38[0]);
			fRec61[0] = fTemp135 - std::floor(fTemp135);
			int iTemp136 = std::max<int>(0, std::min<int>(int(65536.0f * fRec61[0]), 65535));
			float fTemp137 = std::min<float>(4095.0f, std::max<float>(1.0f, 24.0f * fRec35[0] * (0.70710677f * ftbl0TailwindDSPSIG0[iTemp136] - 0.70710677f * ftbl1TailwindDSPSIG1[iTemp136] + 1.0f) + 2797.0f));
			int iTemp138 = int(fTemp137);
			float fTemp139 = std::floor(fTemp137);
			float fTemp140 = fVec27[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp138))) & 8191] * (fTemp139 + (1.0f - fTemp137)) + (fTemp137 - fTemp139) * fVec27[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp138 + 1))) & 8191];
			fVec28[0] = fTemp140;
			fRec62[0] = -(fConst8 * (fConst9 * fRec62[1] - (fTemp140 + fVec28[1])));
			fRec60[0] = fTemp128 * (fTemp132 + (1.0f - fTemp133)) * (fTemp140 + fRec62[0] * ((fRec14[0] + fTemp3 * std::exp(-(fConst22 / fTemp40))) / std::max<float>(1e-06f, fTemp128) + -1.0f)) + (fTemp133 - fTemp132) * fRec60[1];
			float fTemp141 = tanhf(0.35355338f * (fRec60[0] + 1e-20f));
			fRec10[0] = fTemp141;
			float fRec11 = 0.2f * (fTemp127 + fTemp98 + fTemp41 + fTemp69);
			float fRec12 = 0.2f * (fTemp141 + fTemp112 + fTemp55 + fTemp83);
			fRec63[0] = fSlow9 + fConst2 * fRec63[1];
			float fTemp142 = std::tan(fConst24 * fRec63[0]);
			float fTemp143 = 1.0f / fTemp142;
			float fTemp144 = (fTemp143 + -1.4142135f) / fTemp142 + 1.0f;
			float fTemp145 = TailwindDSP_faustpower2_f(fTemp142);
			float fTemp146 = 1.0f - 1.0f / fTemp145;
			float fTemp147 = (fTemp143 + 1.4142135f) / fTemp142 + 1.0f;
			fRec2[0] = fRec11 - (fRec2[2] * fTemp144 + 2.0f * fRec2[1] * fTemp146) / fTemp147;
			float fTemp148 = fTemp145 * fTemp147;
			fRec64[0] = fSlow10 + fConst2 * fRec64[1];
			float fTemp149 = std::tan(fConst24 * fRec64[0]);
			float fTemp150 = 1.0f / fTemp149;
			float fTemp151 = (fTemp150 + -1.4142135f) / fTemp149 + 1.0f;
			float fTemp152 = 1.0f - 1.0f / TailwindDSP_faustpower2_f(fTemp149);
			float fTemp153 = (fTemp150 + 1.4142135f) / fTemp149 + 1.0f;
			fRec1[0] = (fRec2[2] + (fRec2[0] - 2.0f * fRec2[1])) / fTemp148 - (fRec1[2] * fTemp151 + 2.0f * fRec1[1] * fTemp152) / fTemp153;
			fRec65[0] = fSlow11 + fConst2 * fRec65[1];
			float fTemp154 = 7.0f * fRec65[0] + 1.0f;
			float fTemp155 = std::sin(fTemp1);
			float fTemp156 = tanhf(fTemp154);
			output0[i0] = FAUSTFLOAT(fTemp0 * fTemp2 + tanhf((fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) * fTemp154 / fTemp153) * fTemp155 / fTemp156);
			fRec67[0] = fRec12 - (fTemp144 * fRec67[2] + 2.0f * fTemp146 * fRec67[1]) / fTemp147;
			fRec66[0] = (fRec67[2] + (fRec67[0] - 2.0f * fRec67[1])) / fTemp148 - (fTemp151 * fRec66[2] + 2.0f * fTemp152 * fRec66[1]) / fTemp153;
			output1[i0] = FAUSTFLOAT(fTemp27 * fTemp2 + fTemp155 * tanhf(fTemp154 * (fRec66[2] + fRec66[0] + 2.0f * fRec66[1]) / fTemp153) / fTemp156);
			IOTA0 = IOTA0 + 1;
			iVec1[1] = iVec1[0];
			fRec0[1] = fRec0[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec23[1] = fRec23[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			fRec17[1] = fRec17[0];
			fRec33[1] = fRec33[0];
			fRec31[1] = fRec31[0];
			fRec29[1] = fRec29[0];
			fRec27[1] = fRec27[0];
			fRec35[1] = fRec35[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fVec13[1] = fVec13[0];
			fRec39[1] = fRec39[0];
			fRec40[1] = fRec40[0];
			fRec13[1] = fRec13[0];
			fRec3[1] = fRec3[0];
			fRec42[1] = fRec42[0];
			fVec16[1] = fVec16[0];
			fRec44[1] = fRec44[0];
			fRec41[1] = fRec41[0];
			fRec4[1] = fRec4[0];
			fRec46[1] = fRec46[0];
			fVec18[1] = fVec18[0];
			fRec47[1] = fRec47[0];
			fRec45[1] = fRec45[0];
			fRec5[1] = fRec5[0];
			fRec49[1] = fRec49[0];
			fVec20[1] = fVec20[0];
			fRec50[1] = fRec50[0];
			fRec48[1] = fRec48[0];
			fRec6[1] = fRec6[0];
			fRec52[1] = fRec52[0];
			fVec22[1] = fVec22[0];
			fRec53[1] = fRec53[0];
			fRec51[1] = fRec51[0];
			fRec7[1] = fRec7[0];
			fRec55[1] = fRec55[0];
			fVec24[1] = fVec24[0];
			fRec56[1] = fRec56[0];
			fRec54[1] = fRec54[0];
			fRec8[1] = fRec8[0];
			fRec58[1] = fRec58[0];
			fVec26[1] = fVec26[0];
			fRec59[1] = fRec59[0];
			fRec57[1] = fRec57[0];
			fRec9[1] = fRec9[0];
			fRec61[1] = fRec61[0];
			fVec28[1] = fVec28[0];
			fRec62[1] = fRec62[0];
			fRec60[1] = fRec60[0];
			fRec10[1] = fRec10[0];
			fRec63[1] = fRec63[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec64[1] = fRec64[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec65[1] = fRec65[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "tailwind_reverb.dsp"
	#define FAUST_CLASS_NAME "TailwindDSP"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -ct 1 -cn TailwindDSP -scn  -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 13
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Mix", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Decay", fHslider2, 0.85f, 0.1f, 0.99f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Pre-Delay (ms)", fHslider4, 2e+01f, 0.0f, 5e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Diffusion", fHslider5, 0.7f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Damping", fHslider3, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Low Damp", fHslider8, 0.2f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Mod Rate (Hz)", fHslider7, 0.8f, 0.1f, 5.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Mod Depth", fHslider6, 0.3f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Low Cut (Hz)", fHslider9, 8e+01f, 2e+01f, 5e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("High Cut (Hz)", fHslider10, 1.2e+04f, 1e+03f, 2e+04f, 1e+02f);
	FAUST_ADDHORIZONTALSLIDER("Freeze", fHslider1, 1.0f, 0.6f, 1.0f, 0.01f);
	FAUST_ADDCHECKBOX("Freeze On", fCheckbox0);
	FAUST_ADDHORIZONTALSLIDER("Saturation", fHslider11, 0.125f, 0.0f, 0.25f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Mix, "Mix", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Decay, "Decay", fHslider2, 0.85f, 0.1f, 0.99f, 0.001f) \
		p(HORIZONTALSLIDER, Pre-Delay_(ms), "Pre-Delay (ms)", fHslider4, 2e+01f, 0.0f, 5e+02f, 1.0f) \
		p(HORIZONTALSLIDER, Diffusion, "Diffusion", fHslider5, 0.7f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Damping, "Damping", fHslider3, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Low_Damp, "Low Damp", fHslider8, 0.2f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Mod_Rate_(Hz), "Mod Rate (Hz)", fHslider7, 0.8f, 0.1f, 5.0f, 0.01f) \
		p(HORIZONTALSLIDER, Mod_Depth, "Mod Depth", fHslider6, 0.3f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Low_Cut_(Hz), "Low Cut (Hz)", fHslider9, 8e+01f, 2e+01f, 5e+02f, 1.0f) \
		p(HORIZONTALSLIDER, High_Cut_(Hz), "High Cut (Hz)", fHslider10, 1.2e+04f, 1e+03f, 2e+04f, 1e+02f) \
		p(HORIZONTALSLIDER, Freeze, "Freeze", fHslider1, 1.0f, 0.6f, 1.0f, 0.01f) \
		p(CHECKBOX, Freeze_On, "Freeze On", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Saturation, "Saturation", fHslider11, 0.125f, 0.0f, 0.25f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
