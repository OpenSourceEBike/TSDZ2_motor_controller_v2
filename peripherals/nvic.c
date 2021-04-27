#include "xmc1100.h"
#include "nvic.h"

static volatile unsigned int *nvic_ipr = PTR_32(NVIC_BASE + 0x300);
static const unsigned int nvic_masks[] = {
	0xffffff00, 0xffff00ff, 0xff00ffff, 0x00ffffff
};
static unsigned int unhandled_interrupts = 0;

void enableInterrupt(unsigned int interrupt, unsigned int priority) {
	const unsigned int ipr_reg = interrupt >> 2;
	const unsigned int ipr_index = interrupt & 0x03;
	priority <<= (ipr_index * 8);
	nvic_ipr[ipr_reg] &= nvic_masks[ipr_index];
	nvic_ipr[ipr_reg] |= priority;
	NVIC_ISER = 1 << interrupt;
}

void __attribute__((interrupt("IRQ"))) unhandledIRQ(void) {
	// IPSR holds the ISR number.
	// Special return addresses:
	//   0xFFFFFFF1: Return to handler mode (main stack, use MSP).
	//   0xFFFFFFF9: Return to thread mode (MSP, MSP).
	//   0xFFFFFFFD: Return to thread mode (PSP, PSP).
	unhandled_interrupts++;
}

void __attribute__((interrupt("IRQ"))) hardfaultDefault(void) {
	// Wait for the user to fix things (or the wdt).
	while(1) {
		asm("wfi");
	}
}

// Weak interrupt handler definitions.  Declaring another function of the
// same name will override the default unhandledIRQ handler for that interrupt.
void __attribute__((weak, alias("hardfaultDefault"))) hardfaultHandler(void);
void __attribute__((weak, alias("unhandledIRQ"))) svcallHandler(void);
void __attribute__((weak, alias("unhandledIRQ"))) pendsvHandler(void);
void __attribute__((weak, alias("unhandledIRQ"))) systickHandler(void);
void __attribute__((weak, alias("unhandledIRQ"))) SCU_SR0(void);
void __attribute__((weak, alias("unhandledIRQ"))) SCU_SR1(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ02(void);
void __attribute__((weak, alias("unhandledIRQ"))) ERU_SR0(void);
void __attribute__((weak, alias("unhandledIRQ"))) ERU_SR1(void);
void __attribute__((weak, alias("unhandledIRQ"))) ERU_SR2(void);
void __attribute__((weak, alias("unhandledIRQ"))) ERU_SR3(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ07(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ08(void);
void __attribute__((weak, alias("unhandledIRQ"))) USIC_SR0(void);
void __attribute__((weak, alias("unhandledIRQ"))) USIC_SR1(void);
void __attribute__((weak, alias("unhandledIRQ"))) USIC_SR2(void);
void __attribute__((weak, alias("unhandledIRQ"))) USIC_SR3(void);
void __attribute__((weak, alias("unhandledIRQ"))) USIC_SR4(void);
void __attribute__((weak, alias("unhandledIRQ"))) USIC_SR5(void);
void __attribute__((weak, alias("unhandledIRQ"))) VADC0_SR0(void);
void __attribute__((weak, alias("unhandledIRQ"))) VADC0_SR1(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ17(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ18(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ19(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ20(void);
void __attribute__((weak, alias("unhandledIRQ"))) CCU40_SR0(void);
void __attribute__((weak, alias("unhandledIRQ"))) CCU40_SR1(void);
void __attribute__((weak, alias("unhandledIRQ"))) CCU40_SR2(void);
void __attribute__((weak, alias("unhandledIRQ"))) CCU40_SR3(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ25(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ26(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ27(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ28(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ29(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ30(void);
void __attribute__((weak, alias("unhandledIRQ"))) IRQ31(void);

// The interrupt vectors are relocated to RAM where a jump table should
// be placed to the actual interrupt handlers.  The jump table takes the
// following form:
//	ldr R0,=handler_address
//  mov PC,R0
// This pair of instructions fits into 4 bytes which fits neatly into
// a jump table entry.
inline void __attribute__(( section(".interrupt_vectors"))) JumpTable(void) {
	asm(" .long 0 "); // -15 Power up and warm reset
	asm(" .long 0 "); // -14 NMI (mapped to hardfaultHandler)
	asm(" ldr R0,=(hardfaultHandler) "); // -13 HardFault handler
	asm(" mov PC,R0");
	asm(" .long 0 "); // -12 reserved (not mapped)
	asm(" .long 0 "); // -11 reserved (not mapped)
	asm(" .long 0 "); // -10 reserved (not mapped)
	asm(" .long 0 "); // -9 reserved (not mapped)
	asm(" .long 0 "); // -8 reserved (not mapped)
	asm(" .long 0 "); // -7 reserved (not mapped)
	asm(" .long 0 "); // -6 reserved (not mapped)
	asm(" ldr R0,=(svcallHandler) "); // -5 SVCall
	asm(" mov PC,R0 ");
	asm(" .long 0 "); // -4 Debug monitor (not mapped)
	asm(" .long 0 "); // -3 reserved (not mapped)
	asm(" ldr R0,=(pendsvHandler) "); // -2 SVCall
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(systickHandler) "); // -1 Systick handler
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(SCU_SR0) ");     // 00: System Control SR0 (critical)
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(SCU_SR1) ");     // 01: System Control SR1 (common)
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ02) ");      // 02: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(ERU_SR0) ");    // 03
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(ERU_SR1) ");    // 04
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(ERU_SR2) ");    // 05
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(ERU_SR3) ");    // 06
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ07) ");      // 07: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ08) ");      // 08: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(USIC_SR0) ");   // 09
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(USIC_SR1) ");   // 10
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(USIC_SR2) ");   // 11
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(USIC_SR3) ");   // 12
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(USIC_SR4) ");   // 13
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(USIC_SR5) ");   // 14
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(VADC0_SR0) ");  // 15
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(VADC0_SR1) ");  // 16
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ17) ");      // 17: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ18) ");      // 18: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ19) ");      // 19: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ20) ");      // 20: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(CCU40_SR0) ");  // 21
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(CCU40_SR1) ");  // 22
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(CCU40_SR2) ");  // 23
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(CCU40_SR3) ");  // 24
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ25) ");      // 25: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ26) ");      // 26: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ27) ");      // 27: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ28) ");      // 28: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ29) ");      // 29: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ30) ");      // 30: Reserved
	asm(" mov PC,R0 ");
	asm(" ldr R0,=(IRQ31) ");      // 31: Reserved
	asm(" mov PC,R0 ");
};

