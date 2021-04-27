#include "xmc1100.h"
#include "systick.h"

void systickEnable(const unsigned int period) {
	// Set the reload register (timebase in effect)
	SYST_RVR = period;
	SYST_CVR = 5; // Start the counter at a value close to zero
	// Use processor clock, enable interrupt request and enable counter
	SYST_CSR |= BIT0 | BIT1 | BIT2;
}

void systickDisable(void) {
	SYST_CSR = 0;
}
