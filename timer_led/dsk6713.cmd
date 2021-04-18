MEMORY
{
 	VECS: org = 0h, len = 0x220
 	I_HS_MEM: org = 0x00000220, len = 0x00000020
 	IRAM: org = 0x00000240, len = 0x0000FDC0
 	SDRAM: org = 0x80000000, len = 0x01000000
 	FLASH: org = 0x90000000, len = 0x00020000
}
SECTIONS
{
 	vectors :> VECS
 	.text :> IRAM
}
