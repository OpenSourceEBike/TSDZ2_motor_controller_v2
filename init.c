/* Initialization and interrupt vectors for the infineon XMC1100 microcontroller
   Based on work by Frank Duignan, modified by Sean Burford.
   http://eleceng.dit.ie/frank/arm/BareMetalXMC2Go/index.html */

extern int main();
static void _init(void);

// The following are 'declared' in the linker script
extern unsigned int IRQ_DATA_VALUES;
extern unsigned int IRQ_DATA_START;
extern unsigned int IRQ_DATA_SIZE;
extern unsigned int INIT_DATA_VALUES;
extern unsigned int INIT_DATA_START;
extern unsigned int INIT_DATA_SIZE;
extern unsigned int BSS_START;
extern unsigned int BSS_SIZE;

// init() should be the first function in this file so that jumping to
// the start of .text works when running from sram.
//
// The XMC2Go demo app ships with vectors configured to provide an initial
// stack pointer of 0x20000920.  If we use linker.sram.ld to run from SRAM
// we don't want init() to push the callers registers to that address as it
// will stomp on our code or data.  Making this function naked solves that.
static void __attribute__((naked)) init()
{
	// Set up stack pointer, leaving some space for our caller's stack.
	asm("mov sp, %0;" : : "r"(0x20003f00));
	_init();
	// Defensive infinite loop.
	while(1)
		asm("wfi");
}

static void _memcpy4(void *dst, void *src, const int len) {
	int i = len - 4;
	if (src && dst && len) {
		while ( i >= 0) {
			*(unsigned int *)(dst + i) = *(unsigned int *)(src + i);
			i -= 4;
		}
	}
}

static void _init(void) {
	// Do global/static data initialization
	// Copy initialized data and the remapped IRQ jump table vectors to RAM.
	_memcpy4(&IRQ_DATA_START, &IRQ_DATA_VALUES, (int)&IRQ_DATA_SIZE);
	_memcpy4(&INIT_DATA_START, &INIT_DATA_VALUES, (int)&INIT_DATA_SIZE);

	// Zero out the uninitialized global/static variables
	int len;
	unsigned int *const bss = &BSS_START;
	for(len=(int)&BSS_SIZE / 4; len >= 0; len--)
		bss[len] = 0;

	main();
}

// The XMC1100 remaps interrupt vectors to RAM.  The boot loader
// looks for the program entry address at 0x10001004 and the
// initial stack pointer as 0x10001000.  These are defined in
// the "vectors" section below.  The section "vectors" is
// placed at the beginning of flash by the linker script
// Another useful feature of this chip is that you can
// pre-program startup considtions such as CPU speed and
// which periperals.  This is done by writing values in to
// CLK_VAL1 and CLK_VAL2 below
const void *FlashVectors[] __attribute__((section(".vectors"))) ={
	(void *)0x20004000,	/* Top of stack  0x10001000 */
	init,			/* Reset Handler 0x10001004 */
	(void *)0	,	/* 0x10001008 */
	(void *)0,		/* 0x1000100c */
	(void *)0xffffffff,	/* CLK_VAL1   0x10001010 */
	(void *)0xffffffff	/* CLK_VAL2   0x10001014 */
};


