#include <stdio.h>
#include <c6x.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_irq.h>
#include "dsk6713.h"
#include "dsk6713_aic23.h"
#include "C6xdsk.h"

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

int freqlow[4] = {697, 770, 852, 941}, n = 0;
int freqhigh[4] = {1209, 1336, 1477, 1633};
short int coefslow[4] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7};
short int coefshigh[4] = {0x4A70, 0x4090, 0x6521, 0x479C};
short int spec_high[4] = {0}, spec_low[4] = {0};
char button[4][4] = {
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'}
};
int poshigh, poslow;
char prevchar;
short buffer[205] = {0};

// Function to handle the Q15 format multiplication
short int multQ15(short int a, short int b, int flag){
	short int Q;
	int temp;
	temp = a * b;
	if(flag) Q = (short)(temp >> 14);
	else Q = (short)(temp >> 15);
	return Q;
}

// Goertzel algorithm to calculate the spectrum
short Goertzel(short int coef, short *buffer, int flag){
	short int memory[2]={0}, Q, Q1, Q2, Q3;
	short int spec;
	int i;
	for(i = 0;i < 205; i++){
		Q = buffer[i] + multQ15(coef, memory[0], flag) - memory[1];
		memory[1] = memory[0];
		memory[0] = Q;
	}
	Q1 = multQ15(Q, Q, 0);
	Q2 = multQ15(memory[1], memory[1], 0);
	Q3 = multQ15(Q, memory[1], 0);
	spec = Q1 + Q2 - multQ15(Q3, coef, flag);
	return spec;
}

// Find the maximum
int max_array(short *array){
	int j, max = 0, maxpos = 0;
	for(j = 0; j < 4; j++)
		if (array[j] > max){
			max = array[j];
			maxpos = j;
		}
	return maxpos;
}


void main()
{

	DSK6713_init();		// Initialize the board support library, must be called first
	hCodec = DSK6713_AIC23_openCodec(0, &config);	// open codec and get handle
	// set codec sampling frequency 48kHz
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_8KHZ);
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
	short x;
	int data = input_leftright_sample();
	int flag = 1, k, t;
	char output;
	x = 2 * (short)data;
	if (x < 75 && x > -75) return;
	if(n < 205){
		buffer[n] = x;
		n++;
	}
	else{
		for(k = 0; k < 4; k++){
			spec_low[k] = Goertzel(coefslow[k], buffer, flag);
			if (k > 1) flag = 0;
			spec_high[k] = Goertzel(coefshigh[k], buffer, flag);
		}
		poslow = max_array(spec_low);
		poshigh = max_array(spec_high);
		output = button[poslow][poshigh];
		if(prevchar != output){
			printf("pressed: %c   ",output);
			for(t = 0; t < 4; t++) printf("%d  ",spec_high[t]);
			for(t = 0; t < 4; t++) printf("%d  ",spec_low[t]);
			printf("\n");
		}
		n = 0;
		prevchar = output;
	}
}
