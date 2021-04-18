		.sect "all_interrupts"
		.def NIM_ISR
		.def TINT0_ISR
		.def TINT1_ISR
		.def SDINT_ISR
		.def GPINT4_ISR
		.def GPINT5_ISR
		.def GPINT6_ISR
		.def GPINT7_ISR
		.def EDMAINT_ISR
		.def XINT0_ISR
		.def RINT0_ISR
		.def XINT1_ISR
		.def RINT1_ISR

NIM_ISR:	B IRP
			NOP 5
TINT0_ISR:	MVKL 0x90080000,B0	;led register
			MVKH 0x90080000,B0
			LDB *B0,B1
			NOP 4
			MVKL 0x4,B3		;2nd led
			AND B1,B3,B2	;isolation of the 2nd led
	[!B2] 	B OPEN		;check status
			NOP 5
	[B2]	B CLOSE
			NOP 5


OPEN:		SET B1,2,2,B1	;turn on the led
			STB B1,*B0
			NOP 3
			B IRP	;return to the loop
			NOP 5

CLOSE:		CLR B1,2,2,B1	;turn of the led
			STB	B1,*B0
			NOP 3
			B IRP	;return to the loop
			NOP 5

TINT1_ISR:	B IRP
		NOP 5
XINT0_ISR:	B IRP
		NOP 5
RINT0_ISR:	B IRP
		NOP 5
XINT1_ISR:	B IRP
		NOP 5
RINT1_ISR:	B IRP
		NOP 5
SDINT_ISR:	B IRP
		NOP 5
GPINT4_ISR:	B IRP
		NOP 5
GPINT5_ISR:	B IRP
		NOP 5
GPINT6_ISR:	B IRP
		NOP 5
GPINT7_ISR:	B IRP
		NOP 5
EDMAINT_ISR:B IRP
		NOP 5

