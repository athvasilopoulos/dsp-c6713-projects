/*******************************************************************************
*	TEXAS INSTRUMENTS, INC.
*
*	Copyright © Texas Instruments Incorporated 1998
*
*	TI retains all right, title and interest in this code and authorizes its
*	use solely and exclusively with digital signal processing devices
*	manufactured by or for TI.  This code is intended to provide an
*	understanding of the benefits of using TI digital signal processing devices.
*	It is provided "AS IS".  TI disclaims all warranties and representations,
*	including but not limited to, any warranty of merchantability or fitness
*	for a particular purpose.  This code may contain irregularities not found
*	in commercial software and is not intended to be used in production
*	applications.  You agree that prior to using or incorporating this code
*	into any commercial product you will thoroughly test that product and the
*	functionality of the code in that product and will be solely responsible
*	for any problems or failures.  
*
*	TI retains all rights not granted herein.
*******************************************************************************/
//File renamed C6xdsk.h

/*******************************************************************************
* FILENAME
*   c6211dsk.h -   Renamed C6xdsk.h
*
* DESCRIPTION
*   DSK Header File
*
*******************************************************************************/

/* Register definitions for C6211 chip on DSK */

/* Define EMIF Registers  */
#define EMIF_GCR 		0x1800000	/* Address of EMIF global control		*/
#define EMIF_CE0		0x1800008	/* Address of EMIF CE0 control			*/
#define EMIF_CE1		0x1800004	/* Address of EMIF CE1 control			*/
#define EMIF_SDCTRL		0x1800018	/* Address of EMIF SDRAM control		*/
#define EMIF_SDRP		0x180001c	/* Address of EMIF SDRM refresh period	*/
#define EMIF_SDEXT		0x1800020	/* Address of EMIF SDRAM extension		*/

#define MISC (*(volatile unsigned char*)0x90080006)
 
/* Define McBSP0 Registers */
#define McBSP0_DRR      0x18c0000   /* Address of data receive reg.         */
#define McBSP0_DXR      0x18c0004   /* Address of data transmit reg.        */
#define McBSP0_SPCR     0x18c0008   /* Address of serial port contl. reg.   */
#define McBSP0_RCR      0x18c000C   /* Address of receive control reg.      */
#define McBSP0_XCR      0x18c0010   /* Address of transmit control reg.     */
#define McBSP0_SRGR     0x18c0014   /* Address of sample rate generator     */
#define McBSP0_MCR      0x18c0018   /* Address of multichannel reg.         */
#define McBSP0_RCER     0x18c001C   /* Address of receive channel enable.   */
#define McBSP0_XCER     0x18c0020   /* Address of transmit channel enable.  */
#define McBSP0_PCR      0x18c0024   /* Address of pin control reg.          */

/* Define McBSP1 Registers */
#define McBSP1_DRR      0x1900000   /* Address of data receive reg.         */
#define McBSP1_DXR      0x1900004   /* Address of data transmit reg.        */
#define McBSP1_SPCR     0x1900008   /* Address of serial port contl. reg.   */
#define McBSP1_RCR      0x190000C   /* Address of receive control reg.      */
#define McBSP1_XCR      0x1900010   /* Address of transmit control reg.     */
#define McBSP1_SRGR     0x1900014   /* Address of sample rate generator     */
#define McBSP1_MCR      0x1900018   /* Address of multichannel reg.         */
#define McBSP1_RCER     0x190001C   /* Address of receive channel enable.   */
#define McBSP1_XCER     0x1900020   /* Address of transmit channel enable.  */
#define McBSP1_PCR      0x1900024   /* Address of pin control reg.          */

/* Define L2 Cache Registers */
#define L2CFG           0x1840000   /* Address of L2 config reg             */
#define MAR0            0x1848200   /* Address of mem attribute reg         */

/* Define Interrupt Registers */
#define IMH             0x19c0000   /* Address of Interrupt Multiplexer High*/
#define IML             0x19c0004   /* Address of Interrupt Multiplexer Low */

/* Define Timer0 Registers */
#define TIMER0_CTRL     0x1940000	/* Address of timer0 control reg.       */
#define TIMER0_PRD      0x1940004	/* Address of timer0 period reg.        */
#define TIMER0_COUNT    0x1940008	/* Address of timer0 counter reg.       */

/* Define Timer1 Registers */
#define TIMER1_CTRL     0x1980000	/* Address of timer1 control reg.       */
#define TIMER1_PRD      0x1980004	/* Address of timer1 period reg.        */
#define TIMER1_COUNT    0x1980008	/* Address of timer1 counter reg.       */

/* Define EDMA Registers */
#define PQSR			0x01A0FFE0	/* Address of priority queue status     */
#define CIPR			0x01A0FFE4	/* Address of channel interrupt pending */
#define CIER			0x01A0FFE8	/* Address of channel interrupt enable  */
#define CCER			0x01A0FFEC	/* Address of channel chain enable      */
#define ER				0x01A0FFF0	/* Address of event register            */
#define EER				0x01A0FFF4	/* Address of event enable register     */
#define ECR				0x01A0FFF8	/* Address of event clear register      */
#define ESR				0x01A0FFFC	/* Address of event set register        */

/* Define EDMA Transfer Parameter Entry Fields */
#define OPT				0*4			/* Options Parameter                    */
#define SRC				1*4			/* SRC Address Parameter                */
#define CNT				2*4			/* Count Parameter                      */
#define DST				3*4			/* DST Address Parameter                */
#define IDX				4*4			/* IDX Parameter                        */
#define LNK				5*4			/* LNK Parameter                        */
						
/* Define EDMA Parameter RAM Addresses */ 
#define EVENT0_PARAMS 0x01A00000
#define EVENT1_PARAMS EVENT0_PARAMS + 0x18
#define EVENT2_PARAMS EVENT1_PARAMS + 0x18
#define EVENT3_PARAMS EVENT2_PARAMS + 0x18
#define EVENT4_PARAMS EVENT3_PARAMS + 0x18
#define EVENT5_PARAMS EVENT4_PARAMS + 0x18
#define EVENT6_PARAMS EVENT5_PARAMS + 0x18
#define EVENT7_PARAMS EVENT6_PARAMS + 0x18
#define EVENT8_PARAMS EVENT7_PARAMS + 0x18
#define EVENT9_PARAMS EVENT8_PARAMS + 0x18
#define EVENTA_PARAMS EVENT9_PARAMS + 0x18
#define EVENTB_PARAMS EVENTA_PARAMS + 0x18
#define EVENTC_PARAMS EVENTB_PARAMS + 0x18
#define EVENTD_PARAMS EVENTC_PARAMS + 0x18
#define EVENTE_PARAMS EVENTD_PARAMS + 0x18
#define EVENTF_PARAMS EVENTE_PARAMS + 0x18
#define EVENTN_PARAMS EVENTF_PARAMS + 0x18
#define EVENTO_PARAMS EVENTN_PARAMS + 0x18

/* Define QDMA Memory Mapped Registers */
#define QDMA_OPT		0x02000000	/* Address of QDMA options register     */
#define QDMA_SRC		0x02000004	/* Address of QDMA SRC address register */
#define QDMA_CNT		0x02000008	/* Address of QDMA counts register      */
#define QDMA_DST		0x0200000C	/* Address of QDMA DST address register */
#define QDMA_IDX		0x02000010	/* Address of QDMA index register       */
 
/* Define QDMA Pseudo Registers */
#define QDMA_S_OPT		0x02000020	/* Address of QDMA options register     */
#define QDMA_S_SRC		0x02000024	/* Address of QDMA SRC address register */
#define QDMA_S_CNT		0x02000028	/* Address of QDMA counts register      */
#define QDMA_S_DST		0x0200002C	/* Address of QDMA DST address register */
#define QDMA_S_IDX		0x02000030	/* Address of QDMA index register       */

/* Definitions for the DSK Board and SW */
#define PI				3.1415926
#define IO_PORT			0x90080000  /* I/O port Address,top byte valid data */
#define INTERNAL_MEM_SIZE (0x3000)>>2
#define EXTERNAL_MEM_SIZE (0x400000)>>2
#define FLASH_SIZE		0x20000 
#define POST_SIZE		0x10000 
#define FLASH_WRITE_SIZE 0x80 
#define INTERNAL_MEM_START 0xD000
#define EXTERNAL_MEM_START 0x80000000
#define FLASH_START		0x90000000
#define POST_END		0x90010000 
#define FLASH_ADR1		0x90005555
#define FLASH_ADR2		0x90002AAA
#define FLASH_KEY1		0xAA
#define FLASH_KEY2		0x55
#define FLASH_KEY3		0xA0
#define ALL_A			0xaaaaaaaa
#define ALL_5			0x55555555
#define ALT_A5			0xa5a5a5a5
#define ALT_5A			0x5a5a5a5a
#define CE1_8			0xffffff03  /* reg to set CE1 as 8bit async */
#define CE1_32			0xffffff23  /* reg to set CE1 as 32bit async */
