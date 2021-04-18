//C6xinterrupts.c  Provided by TI

#define DSPINT    0x0	/* 00000b  DSPINT Host port host to DSP interrupt */
#define TINT0     0x1	/* 00001b  TINT0 Timer 0 interrupt */
#define TINT1     0x2	/* 00010b  TINT1 Timer 1 interrupt */
#define SD_INT    0x3	/* 00011b  SD_INT EMIF SDRAM timer interrupt */
#define EXT_INT4  0x4	/* 00100b  EXT_INT4 External interrupt 4 */
#define EXT_INT5  0x5	/* 00101b  EXT_INT5 External interrupt 5 */
#define EXT_INT6  0x6	/* 00110b  EXT_INT6 External interrupt 6 */
#define EXT_INT7  0x7	/* 00111b  EXT_INT7 External interrupt 7 */
#define EDMA_INT  0x8	/* 01000b  EDMA_INT EDMA channel (0 through 15) interrupt */
#define XINT0     0xC	/* 01100b  XINT0 McBSP 0 transmit interrupt */
#define RINT0     0xD	/* 01101b  RINT0 McBSP 0 receive interrupt */
#define XINT1     0xE	/* 01110b  XINT1 McBSP 1 transmit interrupt */
#define RINT1     0xF	/* 01111b  RINT1 McBSP 1 receive interrupt */

/*********************************************************
 *  Interrupt Initialization Functions
 *
 *  (CSR and IER are CPU registers defined in c6x.h)
 *
 *********************************************************/
/* Enable Interrupts Globally (set GIE bit in CSR = 1)   */
void enableGlobalINT(void)
{
  CSR |= 0x1;
}

/* Enable NMI (non-maskable interrupt); must be enabled 
 * or no other interrupts can be recognized by 'C6000 CPU */
void enableNMI(void)
{
  IER = _set(IER, 1, 1);
}

/* Enable a specific interrupt; 
 *  (INTnumber = {4,5,6,...,15})                      */
void enableSpecificINT(int INTnumber)
{
  IER = _set(IER, INTnumber, INTnumber); 
}

/*********************************************************
 * C6000 devices have hardware configurable interrupts.
 * To use the McBSP interrupts you must configure them since
 *    they are selected by default. 
 * You must set the appropriate interrupt select bits in the
 *    IML and IMH memory-mapped int select registers.
 * IML and IMH addresses are defined in c6211dsk.h.
 *********************************************************/
void config_Interrupt_Selector(int INTnumber, int INTsource)
{
   /* INTnumber = {4,5,6,...,15}
      INTsource = see #define list above
  */

  union 
  {
  struct
   { unsigned int INTSEL4  : 5;
     unsigned int INTSEL5  : 5;
  	 unsigned int INTSEL6  : 5;
	 unsigned int rsvbit15 : 1;
	 unsigned int INTSEL7  : 5;
     unsigned int INTSEL8  : 5;
	 unsigned int INTSEL9  : 5;
	 unsigned int rsvbit31 : 1;
   }exp; 
   unsigned int reg;
   }IMLvalue;					/* = {0,0,0,0,0,0,0,0}; */
  
  union
  {
   unsigned int reg;
   struct
   { unsigned int INTSEL10  : 5;
     unsigned int INTSEL11  : 5;
	 unsigned int INTSEL12  : 5;
	 unsigned int rsvbit15  : 1;
	 unsigned int INTSEL13  : 5;
     unsigned int INTSEL14  : 5;
	 unsigned int INTSEL15  : 5;
	 unsigned int rsvbit31  : 1;
   }exp; 
   }IMHvalue;
     
  IMLvalue.reg = *(unsigned volatile int *)IML;
  IMHvalue.reg = *(unsigned volatile int *)IMH;

  switch (INTnumber)
  {
    case 4 :
      IMLvalue.exp.INTSEL4 = INTsource;
      break;
    
    case 5 :
      IMLvalue.exp.INTSEL5 = INTsource;
      break;

    case 6 :
      IMLvalue.exp.INTSEL6 = INTsource;
      break;

    case 7 :
      IMLvalue.exp.INTSEL7 = INTsource;
      break;

    case 8 :
      IMLvalue.exp.INTSEL8 = INTsource;
      break;

    case 9 :
      IMLvalue.exp.INTSEL9 = INTsource;
      break;

    case 10 :
      IMHvalue.exp.INTSEL10 = INTsource;
      break;

    case 11 :
      IMHvalue.exp.INTSEL11 = INTsource;
      break;

    case 12 :
      IMHvalue.exp.INTSEL12 = INTsource;
      break;

    case 13 :
      IMHvalue.exp.INTSEL13 = INTsource;
      break;

    case 14 :
      IMHvalue.exp.INTSEL14 = INTsource;
      break;

    case 15 :
      IMHvalue.exp.INTSEL15 = INTsource;
      break;

    default : break;
  }

  *(unsigned volatile int *)IML = IMLvalue.reg;
  *(unsigned volatile int *)IMH = IMHvalue.reg;
                                           
  return;
}
