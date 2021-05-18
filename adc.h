/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2021.
 *
 * Released under the GPL License, Version 3
 */

#pragma once

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)

extern uint32_t adc_throttle;

void VADC_Init(void);