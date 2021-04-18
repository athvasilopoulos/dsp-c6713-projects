	.text
	.def entry
	
entry:
	.include "set_ints.asm"
		;activate global interrupt
		MVC CSR,B0
		SHL B0,1,B0
		SET B0,0,0,B0
		MVC B0,CSR
		;activate NMI and INT4 (TIMER 0) IER interrupt
		MVC IER,B0
		SET B0,1,1,B0
		SET B0,4,4,B0
		MVC B0,IER

		MVKL 0x1940000,A0	;timer control register
		MVKH 0x1940000,A0
		LDW *A0,A1
		MVKL 0x35A4E90,A2	;clock cycles to count
		MVKH 0x35A4E90,A2
		MVKL 0x1940004,A3	;timer period register
		MVKH 0x1940004,A3
		STW A2,*A3		;set the period
		CLR A1,0,0,A1	;func bit
		CLR A1,2,2,A1	;dataout bit
		SET A1,6,7,A1	;go kai hold bit
		SET A1,9,9,A1	;clksrc bit
		STW A1,*A0
		NOP 3

		;infinite loop, because ints dont work on IDLE
LOOP:	B LOOP
		NOP 5
		.end
