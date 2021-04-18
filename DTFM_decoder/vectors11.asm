    			.ref 		_serial_port_rcv_isr    ;ISR used in C program
    			.ref     	_c_int00	;entry address
				.sect   	"vectors"	;section for vectors

RESET_RST:		mvkl	.S2	_c_int00,B0
    			mvkh  .S2   _c_int00,B0
    			B	.S2	B0
				NOP
				NOP
				NOP
				NOP
				NOP
NMI_RST: 		.loop 8
			NOP
			.endloop
RESV1:		.loop 8
			NOP
			.endloop
RESV2:		.loop 8
			NOP
			.endloop
INT4: 		.loop 8
			NOP
			.endloop
INT5: 		.loop 8
			NOP
			.endloop
INT6:  		.loop 8
			NOP
			.endloop
INT7:		.loop 8
			NOP
			.endloop
INT8: 		.loop 8
			NOP
			.endloop
INT9:		.loop 8
			NOP
			.endloop
INT10:		.loop 8
			NOP
			.endloop
INT11:	    b  _serial_port_rcv_isr
			.loop 7
			NOP
			.endloop
INT12: 		.loop 8
			NOP
			.endloop
INT13:		.loop 8
			NOP
			.endloop
INT14: 		.loop 8
			NOP
			.endloop
INT15: 		.loop 8
			NOP
			.endloop

