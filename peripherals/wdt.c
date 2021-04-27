#include "xmc1100.h"
#include "wdt.h"
#include "nvic.h"
#include "scu.h"

unsigned int wdtEnable(const unsigned int lower_bound,
                       const unsigned int upper_bound,
                       const unsigned int enable_prewarning) {
	// Ungate the RTC clock.
	scuUngatePeripheralClock(CGATCLR0_WDT);

	// Check module identification
	if ((WDT_ID >> 8) != 0x0000ADC0) {
		return 1;
	}

	WDT_WLB = lower_bound;
	WDT_WUB = upper_bound;

	// Enable the WDT prewarning interrupt.
	SCU_SRMSK |= SRMSK_PRWARN;
	enableInterrupt(1, 5);

	// BIT0: Enable
	// BIT1: Prewarning.  Counts to upper bound twice, firing the
	//       prewarning interrupt after the first count and rebooting
	//       after second count.
	if (enable_prewarning) {
		WDT_CTR = BIT0 | BIT1;
	} else {
		WDT_CTR = BIT0;
	}

	return 0;
}

unsigned int wdtDisable(void) {
	WDT_CTR = 0;
	scuGatePeripheralClock(CGATCLR0_WDT);
	if (SCU_SRMSK & SRMSK_PRWARN) {
		SCU_SRMSK ^= SRMSK_PRWARN;
	}
	return 0;
}

// Interrupt handler for the RTC
// Normally this should not fire.  It indicates that we missed the window
// without calling wdtService()
// void __attribute__((interrupt("IRQ"))) SCU_SR1(void) {
//	unsigned int wdt_stat = WDT_WDTSTS;;
//	if (wdt_stat & WDT_ALMS) {
//		...
//		// Clear event bits.
//		WDT_WDTCLR = WDT_ALMS;
//	}
