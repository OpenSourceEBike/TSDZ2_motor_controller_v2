#include "xmc1100.h"
#include "scu.h"

// Bit protection scheme enable and disable.
#define PASSWD_MODE_DISABLED 0x00C0
#define PASSWD_MODE_ENABLED 0x00C3

// Clock control register.
#define CLKCR_VDDC2HIGH BIT31
#define CLKCR_VDDC2LOW BIT30

// Convenience function to get reset reason and set clock speed.
unsigned int scuPostReset(const unsigned int clkcr)
{
	unsigned int reason = scuResetReason();
	scuResetControl(RSTCON_ALL);
	scuClockControl(clkcr);
	return reason;
}

// Get reason for previous reset (12.4.2)
unsigned int scuResetReason(void)
{
	unsigned int reason;
	reason = SCU_RSTSTAT & 0x3FF;
	SCU_RSTCLR = BIT0;
	// Reset on ECC error, loss of clock.
	SCU_RSTCON = BIT1 | BIT0;
	return reason;
}

// Set reset triggers.
void scuResetControl(const unsigned int rstcon) {
	SCU_RSTCON = rstcon;
}

// Set CPU and peripheral clock speeds.
void scuClockControl(const unsigned int clkcr) {
	SCU_PASSWD = PASSWD_MODE_DISABLED;
	SCU_CLKCR = clkcr;
	SCU_PASSWD = PASSWD_MODE_ENABLED;
	// wait for vccp to stabilise.
	while (SCU_CLKCR & (CLKCR_VDDC2HIGH | CLKCR_VDDC2LOW));
}

// Enable specified peripheral clock.
unsigned int scuUngatePeripheralClock(const unsigned int peripheral) {
	SCU_PASSWD = PASSWD_MODE_DISABLED;
	SCU_CGATCLR0 = peripheral;
	SCU_PASSWD = PASSWD_MODE_ENABLED;
	// wait for vccp to stabilise.
	while (SCU_CLKCR & (CLKCR_VDDC2HIGH | CLKCR_VDDC2LOW));
	return 0;
}

// Disable specified peripheral clock.
unsigned int scuGatePeripheralClock(const unsigned int peripheral) {
	SCU_PASSWD = PASSWD_MODE_DISABLED;
	SCU_CGATSET0 = peripheral;
	SCU_PASSWD = PASSWD_MODE_ENABLED;
	// wait for vccp to stabilise.
	while (SCU_CLKCR & (CLKCR_VDDC2HIGH | CLKCR_VDDC2LOW));
	return 0;
}
