/*******************************************************************************
* FILENAME
*   switches.c
*
* DESCRIPTION
*   TMS320C6711 DSK User switches
******************************************************************************/

#include <stdio.h>
#include "c6713dsk.h"

/*-------------------------------------------------------------------------*/
/* user_switches_read()                                                    */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Read user switches and return a value in the range 0 to 7.              */
/*                                                                         */
/*-------------------------------------------------------------------------*/

unsigned int user_switches_read(void)
{
 unsigned int new_switch_value;

 new_switch_value = * (unsigned volatile int *) IO_PORT;

 /* Shift value of switches into bits 0, 1 and 2 */

 new_switch_value = ( (new_switch_value >> 4) & 0x00000007);

 return(new_switch_value);
}

/*-------------------------------------------------------------------------*/
/* End of switches.c                                                       */
/*-------------------------------------------------------------------------*/





