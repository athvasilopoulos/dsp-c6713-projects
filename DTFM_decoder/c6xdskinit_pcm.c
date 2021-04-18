//C6xdskinit_pcm.c Includes functions provided by TI, init DSK, McBSP
//Contribution by Walter J. Gomes and Mike Morrow
//Compile with optimization level -o1 due to "bug" SDSsq21295 (OK with CCS V1.2)

#include <c6x.h>
#include "c6xdsk.h"
#include "c6xdskinit_pcm.h"
#include "c6xinterrupts.h"

#define LEFT  1
#define RIGHT 0

float Act_Fs = 0;
char polling = 0;
extern float Fs;

volatile union {
	unsigned int uint;
	short channel[2];
} mcbspData;

/* declare McBSP base addresses */
#define McBSP0_Base     ((McBSP *)0x18c0000)
#define McBSP1_Base     ((McBSP *)0x1900000)

/* declare McBSP data structure */
typedef volatile struct {
	unsigned int drr;   /* rx data reg */
	unsigned int dxr;   /* tx data reg */
	unsigned int spcr;  /* control reg */
	unsigned int rcr;   /* rx control reg */
	unsigned int xcr;   /* tx control reg */
	unsigned int srgr;  /* sample rate gen reg */
	unsigned int mcr;   /* multichannel reg */
	unsigned int rcer;  /* rx chan enable reg */
	unsigned int xcer;  /* tx chan enable reg */
	unsigned int pcr;   /* pin control reg */
} McBSP;


void mcbsp1_init(void)
{
	McBSP *port  = McBSP1_Base;

	port->spcr = 0;  		 /* reset serial port */
	port->srgr = 0;		 /* sample generator not used */
	port->pcr  = 0x000C;   	 /* FSX,FSR,CLKS are inputs; FSR and FSX are active low */
	port->rcr  = 0x000000A0; /* 1-phase 32 bits receive */
	port->xcr  = 0x000000A0; /* 1-phase 32 bits transmit */
	port->dxr  = 0;
	port->spcr = 0x00010001; /* enable tx/rx */
}

int mcbsp1_read()
{
	McBSP *port  = McBSP1_Base;

	if (polling)
		while ( !(port->spcr & 0x2)) ;
	mcbspData.uint = port->drr;
	return mcbspData.uint;
}

void mcbsp1_write(int outdata)
{
	McBSP *port  = McBSP1_Base;

	if (polling)
		while ( !(port->spcr & 0x20000)) ;
	port->dxr = outdata;
}

void c6x11_dsk_init()          /* dsp and periphiral initialization  */
{
	CSR = 0x100;    	     /* disable all interrupts             */
	IER = 1;                 /* disable all interrupts except NMI  */
	ICR = 0xffff;            /* clear all pending interrupts       */
	mcbsp1_activate();
	mcbsp1_init();
}

void comm_poll()		/*added for communication/initialization using polling*/
{
	polling = 1;
	c6x11_dsk_init();
}

void comm_intr()		/*added for communication/initialization using interrupt*/
{
//	mcbsp1_activate();
	c6x11_dsk_init();
//	config_Interrupt_Selector(11, XINT1); /*using transmit INT11*/
//	enableSpecificINT(11);                /*for specific interrupt*/
	enableNMI();              		  /*Enable NMI*/
	enableGlobalINT(); 			  /*Enable GIE for global interrupt*/
	mcbsp1_write(0);   			  /*write to SP0*/
}

int input_sample()                          /*added for input*/
{
	return mcbsp1_read();
}

short input_left_sample()                   /*added for input*/
{
	mcbspData.uint = mcbsp1_read();
	return mcbspData.channel[LEFT];
}

short input_right_sample()                  /*added for input*/
{
	mcbspData.uint = mcbsp1_read();
	return mcbspData.channel[RIGHT];
}

int input_leftright_sample()
{
	mcbspData.uint = mcbsp1_read();
	return mcbspData.uint;
}

void output_sample(int out_data)            /*added for output*/
{
	mcbsp1_write(out_data);
}

void output_left_sample(short out_data)     /*added for output*/
{
	mcbspData.uint = 0;
	mcbspData.channel[LEFT] = out_data;
	mcbsp1_write(mcbspData.uint);
}

void output_right_sample(short out_data)    /*added for output*/
{
	mcbspData.uint = 0;
	mcbspData.channel[RIGHT] = out_data;
	mcbsp1_write(mcbspData.uint);
}

void output_leftright_sample(int out_data)
{
	mcbsp1_write(out_data);
}

void mcbsp1_activate()
{
	// route McBSP1 to daughtercard interface
	MISC |= 0x02;
}
