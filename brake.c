/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2021.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include "xmc_gpio.h"

void brake_init(void)
{
  const XMC_GPIO_CONFIG_t pin_config = {
    .mode             = XMC_GPIO_MODE_INPUT_PULL_UP,
    .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
    .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
  };

  XMC_GPIO_Init((XMC_GPIO_PORT_t *)BRAKE__PORT, BRAKE__PIN, &pin_config);
}

uint8_t brake_is_set(void)
{
  return (XMC_GPIO_GetInput((XMC_GPIO_PORT_t *)BRAKE__PORT, BRAKE__PIN) == 0);
}