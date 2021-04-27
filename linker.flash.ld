/* Based on work by Frank Duignan, modified by Sean Burford.
   http://eleceng.dit.ie/frank/arm/BareMetalXMC2Go/index.html
   useful reference: www.linuxselfhelp.com/gnu/ld/html_chapter/ld_toc.html */
MEMORY
{
	flash : org = 0x10001000, len = 64k
	ram : org = 0x20000000, len = 16k
}

SECTIONS
{
	. = ORIGIN(flash);
	.vectors : {
		*(.vectors)
	} >flash
	.text : {
		*(.text);
	} >flash
	.rodata : {
		*(.rodata);
	} >flash
	. = ORIGIN(ram);
	.irq_vectors : {
		*(.interrupt_vectors);
	} >ram AT>flash
	.data : {
		*(.stext .data);
	} >ram AT>flash
	.bss : {
		*(.bss);
	} > ram
	IRQ_DATA_VALUES = LOADADDR(.irq_vectors);
	IRQ_DATA_START = ADDR(.irq_vectors);
	IRQ_DATA_SIZE = SIZEOF(.irq_vectors);
	INIT_DATA_VALUES = LOADADDR(.data);
	INIT_DATA_START = ADDR(.data);
	INIT_DATA_SIZE = SIZEOF(.data);
	BSS_START = ADDR(.bss);
	BSS_SIZE = SIZEOF(.bss);
}
