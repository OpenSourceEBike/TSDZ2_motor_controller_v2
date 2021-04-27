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
	. = ORIGIN(ram);
	.irq_vectors : {
		*(.interrupt_vectors);
	} >ram
	.text (ORIGIN(ram) + 0x0200): {
		*(.text .stext);
	} >ram
	.data : {
		*(.rodata .data);
	} >ram
	.bss : {
		*(.bss);
	} > ram
        IRQ_DATA_VALUES = 0;
        IRQ_DATA_START = 0;
        IRQ_DATA_SIZE = 0;
        INIT_DATA_VALUES = 0;
        INIT_DATA_START = 0;
        INIT_DATA_SIZE = 0;
	BSS_START = ADDR(.bss);
	BSS_SIZE = SIZEOF(.bss);
}
