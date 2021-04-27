/*
 * TSDZ2 motor controller V2 firmware
 *
 * Copyright (C) Casainho, 2021
 *
 * Released under the GPL License, Version 3
 * 
 */

// this initial firmware, makefile, linkerscripts, were based from: https://github.com/SeanBurford/xmc1100

#include "peripherals/xmc1100.h"
#include "peripherals/gpio.h"

static void blink(void) {
	enablePin(0, 0, GPIO_OUT_PP);  // LED

	static unsigned int count = 0;
	while(1) {

		for (count = 500000; count > 0; ) {
			count--;
		}
		togglePinP0(0);
	}
}

int main() {
	blink();
	return 0;
}
