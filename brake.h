/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2021.
 *
 * Released under the GPL License, Version 3
 */

#pragma once

#include "pins.h"

void brake_init(void);
uint8_t brake_is_set(void);