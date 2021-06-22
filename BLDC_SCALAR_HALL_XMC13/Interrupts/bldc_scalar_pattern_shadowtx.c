/**
 * @file bldc_scalar_pattern_shadowtx.c
 * @brief POSIF multi channel pattern shadow transfer interrupt.
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

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "../ControlModule/bldc_scalar_control_scheme.h"
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
#include "../ControlModule/bldc_scalar_control_hall.h"


/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_HALL_MOTOR_DIR_INDEX        (0x8U)
#define BLDC_SCALAR_HALL_STALL_IGNORE_COUNT     (6U)
#define BLDC_SCALAR_HALL_CAPVAL_POS             (8U)
/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup Interrupt Interrupts
 * @brief  Interrupt Service Routines  <br>
 * @{
 */
/**
 * @param none
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Multi-channel pattern shadow transfer interrupt ISR. \n
 * Prepare hall and multi-channel pattern for the next commutation.
 * Calculate the Speed based on captured value in CCU4 capture slice.
 */

RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PatternShadowTx_ISR(void)
{

  uint8_t pos;            /* array index variable */
  uint16_t mcmval;  /*current multi-channel pattern */
  uint16_t mcmvals; /*shadow multi-channel pattern */
  uint32_t capval;  /* calculated time between last two hall events */
  uint8_t status;   /* return status of the API to read the captured value from capture register */
  uint32_t speed = 0U; /* electrical speed in RPM */
  uint8_t direction = (uint8_t)Motor0_BLDC_SCALAR.motor_set_direction & BLDC_SCALAR_HALL_MOTOR_DIR_INDEX;  /* intended direction */

  /* store the sampled pattern */
  Motor0_BLDC_SCALAR_Hall.prev_hall_pos = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern();
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
#if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U)
  /* To blank the direct DC link current measurement at the commutation point */
  Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_enable = 1U;
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U) */
#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) */

  /*Get the expected hall pattern.*/
  pos = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetExpectedPattern();
  /*Set next hall pattern and MCM pattern based on the expected hall pattern.*/
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
          (uint8_t)(Motor0_BLDC_SCALAR_Hall.hall_pattern[(uint8_t) pos + (uint32_t) direction]));
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetMultiChannelPattern(
      (uint16_t)Motor0_BLDC_SCALAR.mc_pattern[Motor0_BLDC_SCALAR_PWM_BC.modulation_type][(pos) +
                                          (uint8_t)direction]);

  /*Get the shadow multi-channel pattern value and apply the PWM modulation.*/
  mcmval = (uint16_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetMultiChannelPattern();
  mcmvals = (uint16_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetShadowMultiChannelPattern();
  Motor0_BLDC_SCALAR_PWM_BC.shadow_modulation_ptr(mcmval,mcmvals);

    /*Get the captured value from capture timer */
  status = (uint8_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL_ReadCaptureValue(&capval);

#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
  /* Reset the stall detection count as hall event is detected for timeout*/
  Motor0_BLDC_SCALAR.stall_detection_counter = 0U;
#endif
  /* if valid speed capture value */
  if (status == (uint8_t)BLDC_SCALAR_SPEED_POS_HALL_STATUS_SUCCESS)
  {
    /* speed calculation */
    Motor0_BLDC_SCALAR_SPEED_POS_HALL_SpeedCalculation(capval, &speed);

    Motor0_BLDC_SCALAR.actual_motor_direction = Motor0_BLDC_SCALAR.motor_set_direction;
    Motor0_BLDC_SCALAR.motor_speed = ((Motor0_BLDC_SCALAR.actual_motor_direction * (int32_t)speed *
        (int32_t)Motor0_BLDC_SCALAR.speed_mech_scale) >> BLDC_SCALAR_SPEED_SCALE_RES);

#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
    /*
     * stall_check is used to ignore stall detection for first 6 hall events
     */
    if (Motor0_BLDC_SCALAR.amplitude > Motor0_BLDC_SCALAR.stall_min_amplitude)
    {
      if(Motor0_BLDC_SCALAR.stall_check <= BLDC_SCALAR_STALL_IGNORE_COUNT)
      {
        Motor0_BLDC_SCALAR.stall_check++;
      }
    }
#endif
  }

}
#endif /* end of #if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL) */

/**
 * @}
 */
/**
 * @}
 */
