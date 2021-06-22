/**
 * @file gpio.h
 * @brief Input and output pins for BLDC motor control. \n
 * -# Input: 3 hall sensor pins and 1 trap pin
 * -# Output: 6 PWM output pins and 1 inverter enable pin
 * @date 2016-09-08

 ***********************************************************************************************************************
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
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup MCUInit
 * @brief  MCU peripheral initialization <br>
 * @{
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#ifndef MCUINIT_GPIO_H_
#define MCUINIT_GPIO_H_

#include "../Configuration/bldc_scalar_derived_parameter.h"
#include "../Configuration/bldc_scalar_mcuhw_config.h"
/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
/** HWSEL configuration for trap pin */
#define GPIO_TRAP_HWSEL       (XMC_GPIO_HWCTRL_DISABLED)

/**********************************************************************************************************************
* ENUM
**********************************************************************************************************************/


/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/**  @brief  GPIO data structure for PWM pin configuration */
typedef struct GPIO_PWM_INIT
{
  const XMC_GPIO_CONFIG_t* const PhUHighpin_Config;   /*!< Phase U high side pin configuration */
  const XMC_GPIO_CONFIG_t* const PhULowpin_Config;    /*!< Phase U low side pin configuration */
  const XMC_GPIO_CONFIG_t* const PhVHighpin_Config;   /*!< Phase V high side pin configuration */
  const XMC_GPIO_CONFIG_t* const PhVLowpin_Config;    /*!< Phase V low side pin configuration */
  const XMC_GPIO_CONFIG_t* const PhWHighpin_Config;   /*!< Phase W high side pin configuration */
  const XMC_GPIO_CONFIG_t* const PhWLowpin_Config;    /*!< Phase W low side pin configuration */

} GPIO_PWM_INIT_t;

#ifdef __cplusplus
   extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as output pins of CCU8 slices for PWM generation.
 */
void Motor0_BLDC_SCALAR_GPIO_PWM_Init(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as input pin to the CCU8 external trap event.
 */
void Motor0_BLDC_SCALAR_GPIO_Trap_Init(void);

#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as general purpose output pin for inverter enable.
 */
void Motor0_BLDC_SCALAR_GPIO_Inverter_Init(void);
#endif

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Configures GPIO as input pins to the POSIF to sense HALL feedback.
 */
void Motor0_BLDC_SCALAR_GPIO_3Hall_Init(void);

/**********************************************************************************************************************
* EXTERN
**********************************************************************************************************************/
 extern const GPIO_PWM_INIT_t Motor0_BLDC_SCALAR_GPIO_PWM_Config;
 extern const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_Inverter_Config;
 extern const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_Trap_Config;
 extern const XMC_GPIO_CONFIG_t Motor0_BLDC_SCALAR_GPIO_Hall_Config;

 /**
  * @}
  */

 /**
  * @}
  */
 #ifdef __cplusplus
 }
 #endif

#endif /* MCUINIT_GPIO_H_ */
