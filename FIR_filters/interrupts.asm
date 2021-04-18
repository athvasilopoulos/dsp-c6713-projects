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
		.ref buffer_right
		.ref output_buffer

		
NIM_ISR:	B IRP
			NOP 5
TINT0_ISR:	B IRP
			NOP 5
TINT1_ISR:	B IRP
		NOP 5
XINT0_ISR:	B IRP
			NOP 5
RINT0_ISR:	B IRP
			NOP 5
XINT1_ISR:	B IRP
			NOP 5
RINT1_ISR:
	[!A1]	B full
			NOP 5
			LDW *A3,A8				;loads input
			NOP 4
			MV A8,A9
			SHR A9,16,A9
			STH A8,*A7++			;channel right
			;STH A9,*A6++			;channel left
			SUB A1,1,A1				;counter for full buffer
			MV A7,A12					;copy of the pointer
			MVKL 0x200,B7			;length of the buffer
			MVKL 0x29,B2			;length of the coefs(0x51 for bandpass)
			ZERO B14
			ZERO A10

conv:		SUB A12,B6,B1		;check if in range
			ADD B6,B7,B3			;create pointer at the end of the buffer
	[!B1]	MV B3,A12				;copy new address if out of range
			NOP 4
			LDH *--A12,A8			;load the input word
			LDH *+B5[B14],A9	;load the filter word
			NOP 4
			MPY A8,A9,A15			;math
			NOP
			SHR A15,15,A15
			ADD B14,1,B14			;increment for the filter
			ADD A15,A10,A10		;add in the accumulator
			SUB B2,1,B2				;counter for the conv length
	[B2]    B conv
			NOP 5
			STH A10,*A14++		;store it in the output buffer
			NOP 4
			B IRP
			NOP 5

full:	MVKL buffer_right,A7
		MVKH buffer_right,A7
		MVKL output_buffer,A14
		MVKH output_buffer,A14
		MVKL 0x100,A1
		B RINT1_ISR
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

