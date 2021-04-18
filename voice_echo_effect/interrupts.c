/*****************************************************************************
* FILENAME
*   interrupts.c
*
* DESCRIPTION
*   Interrupts enable and disable 
*

******************************************************************************/

/*------------------------------------------------------------------------*/
/* c6x.h contains declarations for the control registers IER, ICR, etc.   */
/* These use the instruction MVC because they are control registers       */
/* They are not declared as *(volatile int*)ICR!                          */
/*------------------------------------------------------------------------*/

#include <c6x.h>
#include "c6713dsk.h"
#include "interrupts.h"

/*-------------------------------------------------------------------------*/
/* timer1_interrupt_enable()                                               */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Enable interrupt for timer 0. Also enables non-maskable interrupt.      */
/* Note: also requires Global Interrupt Enable bit (GIE) in CSR to be 1    */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void timer0_interrupt_enable(void)
{
 IER |= ( INT14 | NMIE); /* Set bits for interrupt 14 and turn on NMI */
}

/*-------------------------------------------------------------------------*/
/* timer1_interrupt_enable()                                               */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Enable interrupt for timer 1. Also enables non-maskable interrupt.      */
/* Note: also requires Global Interrupt Enable bit (GIE) in CSR to be 1.   */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void timer1_interrupt_enable(void)
{
 IER |= ( INT15 | NMIE); /* Set bits for interrupt 15 and turn on NMI */
}

/*-------------------------------------------------------------------------*/
/* global_interrupts_enable()                                              */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Globally enable all interrupts by setting the Global Interrupt Enable   */
/* (GIE) bit in the Control Status Register (CSR). This bit acts as a      */
/* master interrupt enable and must be set to 1 for any maskable interrupt */
/* to work                                                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/
                                  
void global_interrupts_enable(void)
{ 
 /* Control Status Register. Set Global Interrupt Enable bit */

 CSR |= GIE; 
}                                 


/*-------------------------------------------------------------------------*/
/* global_interrupts_disable()                                             */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Globally disable all interrupts by clearing GIE bit in CSR.             */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void global_interrupts_disable(void)
{
 /* Control Status Register */

 CSR = 0x0100;	/* Disable all interrupts. Bit 8 is read only.  */
}                                  

/*-------------------------------------------------------------------------*/
/* individual_interrupts_disable()                                         */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Disable all individual interrupts. Bit 0 always reads as 1.             */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void individual_interrupts_disable(void)
{
 /* Interrupt Enable Register */
 
 IER = 0x0001;    /* Disable all individual interrupts. Bit 0 is read only */
}

/*-------------------------------------------------------------------------*/
/* pending_interrupts_clear()                                              */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Clear any pending interrupts                                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void pending_interrupts_clear(void)
{
  /* Set all interrupt bits of Interrupt Clear Register */
  /* Bits 31 - 16 are reserved.                         */
 
  ICR = 0xFFFF;  /* Clear all pending interrupts        */
}


/*-------------------------------------------------------------------------*/
/* End of interrupts.c                                                     */
/*-------------------------------------------------------------------------*/

