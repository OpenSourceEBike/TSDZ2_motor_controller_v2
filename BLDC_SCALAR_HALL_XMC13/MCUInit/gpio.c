/**
 * @file gpio.c
 * @brief Input and output pins for BLDC motor control. \n
 * -# Input: 3 hall sensor pins and 1 trap pin
 * -# Output: 6 PWM output pins and 1 inverter enable pin
 * @date 2016-09-08
 *
 **********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2016-05-25:
 *     - Initial version
 * 2016-09-08:
 *     - Updated for sensorless support
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "gpio.h"

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/

/** GPIO Init handle for Phase U High Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_PhU_High_Config =
{
 .mode             = MOTOR0_BLDC_SCALAR_GPIO_PH_U_HS_MODE,
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};

/** GPIO Init handle for Phase U Low Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_PhU_Low_Config =
{
 .mode             = MOTOR0_BLDC_SCALAR_GPIO_PH_U_LS_MODE,
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};

/** GPIO Init handle for Phase V High Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_PhV_High_Config =
{
 .mode             = MOTOR0_BLDC_SCALAR_GPIO_PH_V_HS_MODE,
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};

/** GPIO Init handle for Phase V Low Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_PhV_Low_Config =
{
 .mode             = MOTOR0_BLDC_SCALAR_GPIO_PH_V_LS_MODE,
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};

/** GPIO Init handle for Phase W High Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_PhW_High_Config =
{
 .mode             = MOTOR0_BLDC_SCALAR_GPIO_PH_W_HS_MODE,
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};

/** GPIO Init handle for Phase W Low Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_PhW_Low_Config =
{
 .mode             = MOTOR0_BLDC_SCALAR_GPIO_PH_W_LS_MODE,
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};

#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
/** GPIO Init handle for hall sensor input pins */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_Hall_Config  =
{
  .mode            = (XMC_GPIO_MODE_t)XMC_GPIO_MODE_INPUT_TRISTATE,
  .output_level    = (XMC_GPIO_OUTPUT_LEVEL_t)XMC_GPIO_OUTPUT_LEVEL_LOW,
  .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};
#endif

/** GPIO PWM structure, hold the address of all the PWM pin objects*/
const GPIO_PWM_INIT_t Motor0_BLDC_SCALAR_GPIO_PWM_Config =
{
  .PhUHighpin_Config = &Motor0_BLDC_SCALAR_GPIO_PhU_High_Config,
  .PhULowpin_Config  = &Motor0_BLDC_SCALAR_GPIO_PhU_Low_Config,
  .PhVHighpin_Config = &Motor0_BLDC_SCALAR_GPIO_PhV_High_Config,
  .PhVLowpin_Config  = &Motor0_BLDC_SCALAR_GPIO_PhV_Low_Config,
  .PhWHighpin_Config = &Motor0_BLDC_SCALAR_GPIO_PhW_High_Config,
  .PhWLowpin_Config  = &Motor0_BLDC_SCALAR_GPIO_PhW_Low_Config
};


/** GPIO Init handle for Inverter enable Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_Inverter_Config =
{
 .mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF == BLDC_SCALAR_INV_ACTIVE_HIGH)
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
#elif (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF == BLDC_SCALAR_INV_ACTIVE_LOW)
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
#endif
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0,
};

#if(MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
/** GPIO Init handle for Trap Pin */
const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_Trap_Config =
{
 .mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
 .output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
 .input_hysteresis = (XMC_GPIO_INPUT_HYSTERESIS_t)0
};
#endif

/***********************************************************************************************************************
 * APIs
 **********************************************************************************************************************/
/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as output pins of CCU8 slices for PWM generation.
 */
void Motor0_BLDC_SCALAR_GPIO_PWM_Init(void)
{
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_PH_U_HS, &Motor0_BLDC_SCALAR_GPIO_PhU_High_Config);
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_PH_U_LS, &Motor0_BLDC_SCALAR_GPIO_PhU_Low_Config);
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_PH_V_HS, &Motor0_BLDC_SCALAR_GPIO_PhV_High_Config);
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_PH_V_LS, &Motor0_BLDC_SCALAR_GPIO_PhV_Low_Config);
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_PH_W_HS, &Motor0_BLDC_SCALAR_GPIO_PhW_High_Config);
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_PH_W_LS, &Motor0_BLDC_SCALAR_GPIO_PhW_Low_Config);
}

#if(MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as input pin to the CCU8 external trap event.
 */
void Motor0_BLDC_SCALAR_GPIO_Trap_Init(void)
{
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_TRAP, &Motor0_BLDC_SCALAR_GPIO_Trap_Config);
  XMC_GPIO_SetHardwareControl(MOTOR0_BLDC_SCALAR_GPIO_TRAP, GPIO_TRAP_HWSEL);
}
#endif

#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as input pins to the POSIF to sense HALL feedback.
 */
void Motor0_BLDC_SCALAR_GPIO_3Hall_Init(void)
{
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_HALL_1, &Motor0_BLDC_SCALAR_GPIO_Hall_Config);
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_HALL_2, &Motor0_BLDC_SCALAR_GPIO_Hall_Config);
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_HALL_3, &Motor0_BLDC_SCALAR_GPIO_Hall_Config);
}
#endif

#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as general purpose output pin for inverter enable.
 */
void Motor0_BLDC_SCALAR_GPIO_Inverter_Init(void)
{
  XMC_GPIO_Init(MOTOR0_BLDC_SCALAR_GPIO_INV_ENABLE, &Motor0_BLDC_SCALAR_GPIO_Inverter_Config);
}
#endif
