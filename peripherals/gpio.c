#include "xmc1100.h"
#include "gpio.h"

static volatile unsigned int *p0_iocr = PTR_32(P0_BASE + 0x10);
static volatile unsigned int *p1_iocr = PTR_32(P1_BASE + 0x10);
static volatile unsigned int *p2_iocr = PTR_32(P2_BASE + 0x10);
static const unsigned int iocr_masks[] = {
	0xffffff00, 0xffff00ff, 0xff00ffff, 0x00ffffff
};

void clearPin(const unsigned int port, const unsigned int pin) {
	const unsigned int bits = 0x00010000 << pin;
	switch (port) {
	case 0:	P0_OMR = bits;
		break;
	case 1:	P1_OMR = bits;
		break;
	case 2:	P2_OMR = bits;
		break;
	}
}

void setPin(const unsigned int port, const unsigned int pin) {
	const unsigned int bits = 0x00000001 << pin;
	switch (port) {
	case 0:	P0_OMR = bits;
		break;
	case 1:	P1_OMR = bits;
		break;
	case 2:	P2_OMR = bits;
		break;
	}
}

static int setPinMode(volatile unsigned int *iocr,
                      const unsigned int pin, unsigned int mode) {
	const unsigned int iocr_reg = pin >> 2;
	const unsigned int iocr_index = pin & 0x03;
	if (pin > 15) {
		return -1;
	}
	mode <<= (iocr_index * 8);

	// Configure port function.
	iocr[iocr_reg] &= iocr_masks[iocr_index];
	iocr[iocr_reg] |= mode;

	return 0;
}

int enablePin(const unsigned int port, const unsigned int pin,
              const unsigned int mode) {
	int rc = -1;
	unsigned int mask = 0xFFFFFFFF ^ (1 << pin);

	clearPin(port, pin);
	switch (port) {
	case 0:	rc = setPinMode(p0_iocr, pin, mode);
		P0_PPS &= mask;  // Clear power save
		break;
	case 1:	rc = setPinMode(p1_iocr, pin, mode);
		P1_PPS &= mask;  // Clear power save
		break;
	case 2:	rc = setPinMode(p2_iocr, pin, mode);
		P2_PPS &= mask;  // Clear power save
		P2_PDISC &= mask;  // Enable both analog and digital paths
		break;
	}
	return rc;

}

int disablePin(const unsigned int port, const unsigned int pin) {
	unsigned int mask = 1 << pin;
	clearPin(port, pin);
	P1_PPS |= mask;  // Set power save
	return 0;
}

