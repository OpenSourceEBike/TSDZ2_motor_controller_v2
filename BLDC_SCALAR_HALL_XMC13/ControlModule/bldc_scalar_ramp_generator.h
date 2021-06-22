/**
 * @file bldc_scalar_ramp_generator.h
 * @brief Linear ramp generator
 * @date 2016-09-08
 * @cond
 **********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 *
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
 *
 * @endcond
 *
 */

#ifndef CONTROLMODULE_BLDC_SCALAR_RAMP_GENERATOR_H_
#define CONTROLMODULE_BLDC_SCALAR_RAMP_GENERATOR_H_

/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup ControlModule
 * @brief  Control algorithm for BLDC motor control <br>
 * @{
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "../Configuration/bldc_scalar_derived_parameter.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/

/**  @brief structure for ramp generator */
typedef struct BLDC_SCALAR_RAMP
{
  int32_t set_value;                /*!< output of the ramp. This will be connected to ref_ptr of the control scheme */
  int32_t input_value;              /*!< end value of the controlled variable. This points to user_<x>_set or analogip_value if analog measurement is enabled */
  uint32_t ramp_rate;               /*!< holds either ramp up or down rate based on set value and direction */
  uint32_t ramp_up_rate;            /*!< count value in terms of the time for ramp up */
  uint32_t ramp_down_rate;          /*!< count value in terms of time for ramp down */
} BLDC_SCALAR_RAMP_t;

/**********************************************************************************************************************
* EXTERN
**********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
extern BLDC_SCALAR_RAMP_t Motor0_BLDC_SCALAR_Ramp;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Changes the instantaneous value of the controlled parameter (voltage or speed or current) linearly based on ramp rate.
 * It is possible to configure different ramp up and ramp down rate.
 */

RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_Ramp_Linear(void);
#endif

/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* CONTROLMODULE_BLDC_SCALAR_RAMP_GENERATOR_H_ */
