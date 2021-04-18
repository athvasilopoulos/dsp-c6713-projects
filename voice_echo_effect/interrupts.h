
/*******************************************************************************
* FILENAME
*   interrupts.h
*
* DESCRIPTION
*   Interrupts for Timer 0 and Timer 1 and global enable / disable.
*
*******************************************************************************/

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#define NMIE  0x0002   /* Non-maskable Interrupt Enable */
#define GIE   0x0001   /* Global Interrupt Enable */

#define INT14 0x4000   /* Interrupt number for timer 0 */
#define INT15 0x8000   /* Interrupt number for timer 1 */

void timer0_interrupt_enable(void);
void timer1_interrupt_enable(void);

void global_interrupts_enable(void);

void global_interrupts_disable(void);

void individual_interrupts_disable(void);
void pending_interrupts_clear(void);

#endif

/*-----------------------------------------------------------------------*/
/* End of interrupts.h                                                   */
/*-----------------------------------------------------------------------*/

