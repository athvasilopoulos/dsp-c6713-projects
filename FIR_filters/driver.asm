	.align 2
buffer_right		.space 512
output_buffer		.space 512

DXR	.set 0x1900004
DRR	.set 0x1900000
RCR	.set 0x190000C
XCR	.set 0x1900010
IML .set 0x19C0004

	.text
	.def _entry
	.ref RINT1_ISR
	.ref coef
	.def buffer_right
	.def output_buffer

_entry: MVKL RCR,A0
		MVKH RCR,A0
		MVKL XCR,A1
		MVKH XCR,A1
		MVKL 0xA0,A4
		STW A4,*A0	;set rcr
		STW A4,*A1	;set xcr

		MVKL DXR,A2
		MVKH DXR,A2
		MVKL DRR,A3
		MVKH DRR,A3

		MVKL buffer_right,A7
		MVKH buffer_right,A7
		MV A7,B6
		MVKL output_buffer,A14
		MVKH output_buffer,A14
		MVKL 0x100,A1	;counter

		MVKL coef,B5 ;filter coefficients
		MVKH coef,B5


		;set rint1 to int4
		MVKL IML,A4 ;IML
		MVKH IML,A4
		LDW *A4,A5
		NOP 4
		SET A5,0,3,A5
		STW A5,*A4

		;activate nmi,int4(rint1)
		MVC CSR,B0
		SHL B0,1,B0
		SET B0,0,0,B0
		MVC B0,CSR

		MVC IER,B0
		SET B0,1,1,B0
		SET B0,4,4,B0
		MVC B0,IER


		;infinite loop, because ints dont work on IDLE
loop:	B loop
		NOP 5
		.end
