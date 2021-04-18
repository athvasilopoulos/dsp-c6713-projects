#include <stdio.h>
#include <c6x.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_irq.h>
#include "dsk6713.h"
#include "dsk6713_aic23.h"
#include "C6xdsk.h"
#include "coefs.h"

#define N 256

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

// Variables to handle the IIR calculations
short a11 = a1_1, a21 = a2_1, a12 = a1_2, a22 = a2_2;
short b11 = b1_1, b21 = b2_1, b12 = b1_2, b22 = b2_2;
short G1 = G1_c, G2 = G2_c;
short input[N] = {0}, output[N] = {0};
short memory1[2] = {0}, memory2[2] = {0};
int i = 0;

// Function to handle the multiplication on Q15 format
short int multQ15(int a, int b){
	short int Q;
	int temp;
	temp = a * b;
	Q=(short)(temp >> 14);
	return Q;
}

void main()
{

	DSK6713_init();		// Initialize the board support library, must be called first
	hCodec = DSK6713_AIC23_openCodec(0, &config);	// open codec and get handle
	// set codec sampling frequency 48kHz
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_48KHZ);
	*(unsigned volatile int *)McBSP1_RCR = 0x00A0;
	*(unsigned volatile int *)McBSP1_XCR = 0x00A0;
	init_hw_interrupts();
	while(1);  // wait for interrupts

}

// interrupt service routine
void init_hw_interrupts(void)
{

	IRQ_globalDisable();			// Globally disables interrupts
	IRQ_nmiEnable();				// Enables the NMI interrupt

	// Maps an event to a physical interrupt
	IRQ_map(IRQ_EVT_RINT1, 11);
	IRQ_enable(IRQ_EVT_RINT1);		// Enables the event
	IRQ_globalEnable();				// Globally enables interrupts

}

// interrupt service routine
interrupt void serial_port_rcv_isr(void)
{

	short int y1 = 0, w1 = 0, w2 = 0, y2 = 0, x;
	int data = input_leftright_sample();

	// "data" contains both audio channels
	// I keep only the right channel
	x = (short)data;
	input[i] = x;

	// Calculations for the 4th order filter, split into 2 2nd order filters
	// using the output of the first as input for the second.
	w1 = multQ15(G1, x) - multQ15(a11, memory1[0]) - multQ15(a21, memory1[1]);
	y1 = w1 + multQ15(b11, memory1[0]) + multQ15(b21, memory1[1]);
	memory1[1] = memory1[0];
	memory1[0] = w1;

	w2 = multQ15(G2, y1) - multQ15(a12, memory2[0]) - multQ15(a22, memory2[1]);
	y2 = w2 + multQ15(b12, memory2[0]) + multQ15(b22, memory2[1]);
	memory2[1] = memory2[0];
	memory2[0] = w2;

	output[i] = y2;
	i++;
	i=i % N;
	data = y2;

	output_leftright_sample(data);
	return;
}
