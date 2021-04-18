;    .ref    _timer0_isr
    .ref    _c_int00
        
  
	.sect "vectors"
RESET_RST:
    
    mvkl .S2 _c_int00, B0
    mvkh .S2 _c_int00, B0
    B    .S2 B0
	NOP
	NOP
	NOP
	NOP
    NOP
NMI_RST:    
    NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

RESV1:
    NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

RESV2:
    NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT4:   NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT5:   NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
                   
INT6: NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT7:   NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT8:   NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT9:   NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT10:   NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT11:  NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT12:  NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT13:   NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT14:  NOP ; b _timer0_isr
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

INT15:  NOP ; b _timer1_isr
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
 

