/*****************************************************************************
* FILENAME
*   bargraph.c
*
* DESCRIPTION
*   User LEDs used as bargraph display for audio level.
    User LEDs on DSK show audio level in 6dB intervals.   
*
*****************************************************************************/

#include <stdio.h>
#include <c6x.h>
#include "c6713dsk.h"
#include "bargraph.h"

/*-------------------------------------------------------------------------*/
/* Important. When using bargraphs, the DSK must always be in 32-bit mode, */
/* otherwise the output is lost                                            */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* bargraph()                                                              */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Bargraph display on 3 user LEDS in steps of 6 dB.                       */
/*                                                                         */
/* A short int can lie in the range -32768 to +32767. Note that the value  */
/* -32768 cannot be simply converted to a positive value by changing the   */
/* sign. Instead it must be treated as a special case.                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void bargraph(short int input)
{
 /* Put into 32-bit mode */
 
 //*(unsigned volatile int *)EMIF_CE1 = CE1_32; /* EMIF CE1 control, 32-bit async */

 /* Convert all negative values to positive */

 if ( -32768 == input)
  {
   input = 32767; /* Special case. There is no +32768. */
  } 
 else if ( input < 0 )
  {  
   input = -input; /* Make negative input a positive number */
  }
  
 if ( input > MAXIMUM_INPUT/2)      /* - 6 dB */
  {  
   *(unsigned volatile int *)IO_PORT = 0x00000007; /* turn on three leds */
  }
 else if (input > MAXIMUM_INPUT/4)  /* - 12 dB */
  {
   *(unsigned volatile int *)IO_PORT = 0x00000003; /* turn on two leds */
  } 
 else if( input > MAXIMUM_INPUT/8)  /* -18 dB */
  {
   *(unsigned volatile int *)IO_PORT = 0x00000001; /* turn on one led */
  } 
 else
  {
   *(unsigned volatile int *)IO_PORT = 0x00000000; /* turn off three leds    */
  }

 /* Do no put back into 8-bit mode. LEDs don't turn on properly. */
  
}


/*-------------------------------------------------------------------------*/
/* End of bargraph.c            		  				                   */
/*-------------------------------------------------------------------------*/


