#include <stdio.h>
#include <c6x.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_irq.h>
#include "dsk6713.h"
#include "dsk6713_aic23.h"
#include "C6xdsk.h"
#include "ham64.h"
#include <math.h>

static DSK6713_AIC23_CodecHandle hCodec;							// Codec handle
static DSK6713_AIC23_Config config = { \
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
	};  // Codec configuration with default settings

interrupt void serial_port_rcv_isr(void);
void init_hw_interrupts(void);

short w[64] = {0}, input[64] = {0};
short index[64] = {0}, fft_input[128] = {0}, fft_output[64] = {0}, real, im;
int pointer = 0;

// Function to handle the multiplication of Q15 format, with additional scaling 1/nx (6 extra shifts)
short int multQ21(short int a, short int b){
	int temp;
	short int Q;
	temp = (int)a * (int)b;
	Q = (short)(temp >> 21);
	return Q;
}

// Function to handle the multiplication of Q15 format, without additional scaling
short multQ15(short a, short b){
	int temp;
	short int Q;
	temp = a * b;
	Q = (short)(temp >> 15);
	return Q;
}

void main()
{
	DSK6713_init();		// Initialize the board support library, must be called first
	hCodec = DSK6713_AIC23_openCodec(0, &config);	// open codec and get handle
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_48KHZ);
	*(unsigned volatile int *)McBSP1_RCR = 0x00A0;
	*(unsigned volatile int *)McBSP1_XCR = 0x00A0;

	init_hw_interrupts();
	int i, nx = 64;
	int real2, im2;
	for (i = 0; i < nx/2; i++){
		w[i*2] = 32767 * (-cos(i * 2 * PI / nx));
		w[i*2 + 1] = 32767 * (-sin(i * 2 * PI / nx));
	}
	bitrev_index(index,64);

	// Wait for a data block to be filled and then
	// perform the Complex Forward FFT algorithm
	while(1){
		if (!pointer){
			for(i = 0; i < nx; i++){
				fft_input[2*i] = multQ21(input[i],ham64[i]);
				fft_input[2*i+1] = 0;
			}
			DSP_radix2(64, fft_input, w);
			DSP_bitrev_cplx((int*)fft_input, index, 64);
			for(i = 0; i < nx; i++){
				real = (short)fft_input[2*i];
				im = (short)fft_input[2*i+1];
				real2 = real * real;
				real = (short)(real2 >> 15);
				im2 = im * im;
				im = (short)(im2 >> 15);
				fft_output[i] = real + im;
			}
		}
	}
}


void init_hw_interrupts(void)
{

	IRQ_globalDisable();
	IRQ_nmiEnable();

	IRQ_map(IRQ_EVT_RINT1, 11);
	IRQ_enable(IRQ_EVT_RINT1);
	IRQ_globalEnable();

}

// Create data blocks of size 64
interrupt void serial_port_rcv_isr(){
	int data;
	short in;
	data = input_leftright_sample();
	in = (short)(data);
	input[pointer] = in;
	pointer = (pointer + 1) % 64;
	return;
}
