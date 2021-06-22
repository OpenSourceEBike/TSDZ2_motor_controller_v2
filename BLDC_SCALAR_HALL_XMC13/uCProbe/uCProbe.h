/**
 * @file ucProbe.h
 * @brief Non-configurable defines
 * @date 2016-06-15
 *
 ***********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v0.2.0 - BLDC motor control using block commutation
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
 * 2016-06-15:
 *     - Initial version
 *
 * @endcond
 *
 */
#ifndef BLDC_SCALAR_CTRL_UCPROBE_H_
#define BLDC_SCALAR_CTRL_UCPROBE_H_


#define MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_OSC_ENABLE 1
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_OSC_ENABLE ==1) && (MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE==1))
#include "../uCProbe/ProbeScope/probe_scope_cfg.h"
#include "../uCProbe/ProbeScope/probe_scope.h"
#endif
/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define MOTOR0_BLDC_SCALAR_UCPROBE_CONFIG_ADDR (uint32_t *)0x10032C00                                /* Start address of flash*/
#define BLDC_SCALAR_UCPROBE_MAX_PARAMETER 24                                          /*Maximum number of parameter to be saved in Flash*/

#define MOTOR0_BLDC_SCALAR_UCPROBE_FLASH_VALID_ID (0x1235)                                   /*16 bit Validation ID to check whether flash has any valid data*/
//#define MOTOR0_BLDC_SCALAR_UCPROBE_FLASH_VALID_ID (0x1234+MOTOR0_BLDC_SCALAR_CTRL_SCHEME)  /*Validation ID to check whether flash has any valid data*/

/***********************************************************************************************************************
 * ENUMS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
/*
 * @brief Structure for UCPROBE interface for BLDC Scalar  motor control
 */
typedef struct BLDC_SCALAR_UCPROBE
{
	uint32_t user_config[BLDC_SCALAR_UCPROBE_MAX_PARAMETER];         /*Local array to store flash variable*/

	uint32_t default_config[BLDC_SCALAR_UCPROBE_MAX_PARAMETER];      /*Local array to store default values of flash variable*/
	volatile uint32_t control_word;                         /*UCPROBE control word to send comments from GUI*/

	volatile uint32_t  max_speed_RPM;                               /*Maximum speed of the motor in RPM*/
	volatile uint32_t  max_voltage_Volt ;                           /*DC link voltage in Volt*/
	volatile uint32_t  max_current_mA;                              /*Maximum DC link current in mA*/

	volatile int32_t dclinkgvoltage_Volt;                           /*Actual DC link voltage in Volt*/
	volatile int32_t motor_current_mA;                              /*Actual motor current in mA*/
	volatile int32_t motor_speed_RPM;                               /*Actual motor speed in RPM*/


	volatile int32_t speed_pi_error;                               /*Speed control PI error*/
	volatile int32_t speed_set_RPM;                                /*Actual motor speed set value in RPM*/
	volatile int32_t current_pi_error;                             /*Current control PI error*/
	volatile int32_t current_set_mA;                               /*Actual motor current set value in mA*/
	volatile int32_t voltage_set_Volt;                             /*Actual motor voltage set value in Volt*/

} BLDC_SCALAR_UCPROBE_t;
/***********************************************************************************************************************
 * EXTERN
 **********************************************************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
/**
 * @return None
 *
 * Description:
 * UCPROBE scheduler function to handle ucprobe comments from UI
 */
void Motor0_BLDC_SCALAR_uCProbe_Scheduler(void);
/**
 * @return None
 *
 * Description:
 * UCPROBE variable initialization
 */
void Motor0_BLDC_SCALAR_uCProbe_Init(void);
/**
 * @return None
 *
 * Description:
 * Handling flash variable, if flash contain any valid data, write to actual variable from flash
 */
void Motor0_BLDC_SCALAR_Flash_Var_Init(void);
/**
 * @return None
 *
 * Description:
 * Clear flash variable data in the flash
 */
void Motor0_BLDC_SCALAR_Clear_Flash(void);

#ifdef __cplusplus
}
#endif
#endif /* BLDC_SCALAR_CTRL_UCPROBE_H_ */
