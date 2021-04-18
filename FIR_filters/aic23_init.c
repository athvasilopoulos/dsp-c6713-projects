/*
 * aic23_init.c
 */
//*
#include "dsk6713.h"
#include "dsk6713_aic23.h"
#include "stdlib.h"
#include "math.h"
//*/
// Codec configuration settings
DSK6713_AIC23_Config config = { \
    0x0017,  /* 0 DSK6713_AIC23_LEFTINVOL  Left line input channel volume */ \
    0x0017,  /* 1 DSK6713_AIC23_RIGHTINVOL Right line input channel volume */\
    0x01f9,  /* 2 DSK6713_AIC23_LEFTHPVOL  Left channel headphone volume */  \
    0x01f9,  /* 3 DSK6713_AIC23_RIGHTHPVOL Right channel headphone volume */ \
    0x0011,  /* 4 DSK6713_AIC23_ANAPATH    Analog audio path control */      \
    0x0000,  /* 5 DSK6713_AIC23_DIGPATH    Digital audio path control */     \
    0x0000,  /* 6 DSK6713_AIC23_POWERDOWN  Power down control */             \
    0x0043,  /* 7 DSK6713_AIC23_DIGIF      Digital audio interface format */ \
    0x0001,  /* 8 DSK6713_AIC23_SAMPLERATE Sample rate control */            \
    0x0001   /* 9 DSK6713_AIC23_DIGACT     Digital interface activation */   \
};

void main()
{
	DSK6713_AIC23_CodecHandle hCodec;
	Int16 OUT_L, OUT_R;
	Uint32 IN_L;
	// Initialize BSL
	DSK6713_init();

	//Start codec
	hCodec = DSK6713_AIC23_openCodec(0, &config);

	// Set  frequency to 48KHz
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_48KHZ);
	entry();
}

