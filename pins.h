/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2021.
 *
 * Released under the GPL License, Version 3
 */

#pragma once

// Current shunt: P2.8
// there is power resistor of 0.003 ohms and then a Non-inverting Operational Amplifier Configuration, with a gain of 11 (Rf = 10k and R2 = 1k)
// voltage on this pin is 0 volts when motor is not running
// VCC = 5 volts and considering ADC is 12 bits mode
#define CURRENT_SHUNT_ADC_TO_AMPS                       (0.037) // 1 / (0.033 / (5 / 4095))
#define CURRENT_SHUNT__PORT                             2
#define CURRENT_SHUNT__PIN                              8