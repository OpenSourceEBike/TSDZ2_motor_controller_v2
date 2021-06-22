/**
 * @file bldc_scalar_protection_error.c
 * @brief VADC channel event used for current protection and voltage protection
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
 *
 */
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup Interrupt Interrupts
 * @brief  Interrupt Service Routines  <br>
 * @{
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "../ControlModule/bldc_scalar_control_scheme.h"
#include "../bldc_scalar_user_interface.h"

/** Short circuit current maximum limit (0.25% of max current).
     If current reaches this value, short circuit current error is set. */
#define BLDC_SCALAR_VADC_MAX_CURRENT_LIMIT   (16344)

/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/

/**
 * @param none
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Event to handle current and voltage protection. \n
 * This is the VADC channel event generated when result is outside boundary \n
 * Current protection - Global boundary \n
 * Voltage protection - Group specific boundary \n
 */
#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U))
void Motor0_BLDC_SCALAR_Protection_ISR(void)
{
#if (MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)
  int32_t current;   /* ADC value of the current in Q14 */
  /*******************************Current Protection ****************************************************/
  /* Direct DC link current measurement is used for over-current protection */
#if ((MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_DIRECT_CURRENT) && (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U))
  /* Check whether the interrupt is due to current limit overshoot */
  if ((((MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP->CEFLAG) >> MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_CH_NUM) & 0x1U) == 0x1U)
  {
    /* Read the current value for short-circuit protection */
    Motor0_BLDC_SCALAR_GetCurrentValue(&current);
    if ((current > Motor0_BLDC_SCALAR_CurrentMeasurement.short_circuit_current) ||
        (current > BLDC_SCALAR_VADC_MAX_CURRENT_LIMIT))
    {
      /* Stop the motor immediately if current is greater than configured short circuit current */
      Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_SHORTCIRCUIT;
      Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
      Motor0_BLDC_SCALAR_MotorStop();
    }
    else
    {
      /* Increment the counter by 2 and compare with the detection time */
      Motor0_BLDC_SCALAR.overcurrent_counter += 2U;

      /* Stop the motor when current stays above the configured limit for more than configured detection time */
      if (Motor0_BLDC_SCALAR.overcurrent_counter > Motor0_BLDC_SCALAR.overcurrent_count)
      {
        Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_OVERCURRENT;
        Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
        Motor0_BLDC_SCALAR_MotorStop();
      }
    }
  }
#endif /* end of #if (MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_DIRECT_CURRENT)*/

/* Average DC link current measurement is used for over-current protection */
#if ((MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_AVG_CURRENT) && (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U))
  if (((MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP->CEFLAG >> MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM) & 0x1) == 0x1)
  {
    /* Read the current value for short-circuit protection */
    Motor0_BLDC_SCALAR_GetAverageCurrentValue(&current);
    /* Stop the motor immediately if current is greater than configured short circuit current */
    if ((current > Motor0_BLDC_SCALAR_CurrentMeasurement.short_circuit_current) ||
        (current > BLDC_SCALAR_VADC_MAX_CURRENT_LIMIT))
    {
      Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_SHORTCIRCUIT;
      Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
      Motor0_BLDC_SCALAR_MotorStop();
    }
    else
    {
      /* Increment the counter by 2 and compare with the detection time */
      Motor0_BLDC_SCALAR.overcurrent_counter += 2U;

      if (Motor0_BLDC_SCALAR.overcurrent_counter > Motor0_BLDC_SCALAR.overcurrent_count)
      {
        /* Stop the motor when current stays above the configured limit for more than configured detection time */
        Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_OVERCURRENT;
        Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
        Motor0_BLDC_SCALAR_MotorStop();
      }
    }
  }
#endif /* end of #if (MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_AVG_CURRENT)*/
#endif


}
#endif

/**
 * @}
 */
/**
 * @}
 */
