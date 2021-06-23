/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2021.
 *
 * Released under the GPL License, Version 3
 */

#pragma once

/* Connections:
 *
 * Motor PHASE_A: blue wire
 * Motor PHASE_B: green wire
 * Motor PHASE_C: yellow wire
 * 
 * LM258
 * opamp pins 1, 2 and 3, is configured with as a unity gain buffer, providing at output a 2.5 volts signal (probably for the offset voltage used by the other MCP602 opamps measuring the phase currents)
 * opamp pins 7, 6 and 5, is used to amplify the torque sensor signal.
 * 
 * MCP602 1 (near shunt resistor):
 * opamp pins 1, 2 and 3, green phase resistor measurement, amplification factor 10, 2.5 volts offset
 * opamp pins 7, 6 and 5, shunt resistor measurement, amplification factor -11
 * 
 * MCP602 2:
 * opamp pins 1, 2 and 3, yellow phase resistor measurement, amplification factor 10, 2.5 volts offset
 * opamp pins 7, 6 and 5, blue phase resistor measurement, amplification factor 10, 2.5 volts offset
 *
 */

// Current shunt: P2.8
// there is power resistor of 0.003 ohms and then a Non-inverting Operational Amplifier Configuration (MCP602, ouput pin 7), with a gain of -11 (Rf = 10k and R2 = 1k)
// voltage on this pin is 0 volts when motor is not running
// VCC = 5 volts and considering ADC is 12 bits mode
#define CURRENT_SHUNT_ADC_TO_AMPS                       (0.037) // 1 / (0.033 / (5 / 4095))
#define CURRENT_SHUNT__PORT                             2
#define CURRENT_SHUNT__PIN                              8

#define BRAKE__PORT                                     PORT0_BASE
#define BRAKE__PIN                                      10