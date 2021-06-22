/**
 * @file bldc_scalar_control_scheme.c
 * @brief Control algorithm routines like control scheme, voltage compensation, stall detection
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
#include "bldc_scalar_control_scheme.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

#define BLDC_SCALAR_VADC_CONVERSION_DELAY  (0xFU)
/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/


/**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/


/* Reset and Initialize of the motor control parameters */
void Motor0_BLDC_SCALAR_MotorParamInit(void)
{
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 0U)
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP)
  int32_t start_value;    /* ramp initial value of control scheme */
#endif
  int32_t end_value;      /* set value of the control scheme */
#endif
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) && (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U))
  volatile uint32_t adc_conversion_delay;  /* wait for the conversion delay */
#endif
  /* Reset runtime control parameters */
  Motor0_BLDC_SCALAR.amplitude               = 0U;
  Motor0_BLDC_SCALAR.motor_speed             = 0;
  Motor0_BLDC_SCALAR.motor_current           = 0;
  Motor0_BLDC_SCALAR.motor_average_current   = 0;
  Motor0_BLDC_SCALAR.dclink_voltage          = 0U;

#if (MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)
  Motor0_BLDC_SCALAR.overcurrent_counter         = 0U;
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
  Motor0_BLDC_SCALAR.bootstrap_counter           = 0U;
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
  Motor0_BLDC_SCALAR.stall_detection_counter     = 0U;
  Motor0_BLDC_SCALAR.stall_check = 1U;
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U)
  Motor0_BLDC_SCALAR.over_under_voltage_counter  = 0U;
#endif
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
#if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING ==1U)
  Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_counter = 0U;
#endif /* if(MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U) */
#if(MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U)
  Motor0_BLDC_SCALAR_PT1_DirectCurrent.pt1_buf = 0;          /* Reset PT1 buffer */
#endif/* if(MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U) */
#endif /* if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) */

  /* Reset PT1 buffer */
#if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U)
#if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION_FILTER == 1U)
  Motor0_BLDC_SCALAR_PT1_VoltageComp.pt1_buf = BLDC_SCALAR_PT1_VOLT_COMP_BUF_VAL;
#endif /* if(MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION_FILTER == 1U) */
#endif /* if(MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U) */


#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
#if (MOTOR0_BLDC_SCALAR_POTENTIOMETER_PT1_FILTER_ENABLE == 1U)
  Motor0_BLDC_SCALAR_PT1_Potentiometer.pt1_buf = 0;          /* Reset PT1 buffer */
#endif /* if(MOTOR0_BLDC_SCALAR_POTENTIOMETER_PT1_FILTER_ENABLE == 1U) */
#endif /* if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) */

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) ||(MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_AVERAGE_CURRENT_FILTER == 1U)
  Motor0_BLDC_SCALAR_PT1_AverageCurrent.pt1_buf = 0;          /* Reset PT1 buffer */
#endif /* if(MOTOR0_BLDC_SCALAR_ENABLE_IDC_AVERAGE_CURRENT_FILTER == 1U) */
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 0U)
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP)
  start_value = Motor0_BLDC_SCALAR_SpeedControl.user_start_speed_set;
#endif
  end_value = Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP)
  start_value = Motor0_BLDC_SCALAR_CurrentControl.user_start_current_set;
#endif
  end_value = Motor0_BLDC_SCALAR_CurrentControl.user_current_set;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL))
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP)
  start_value = Motor0_BLDC_SCALAR_VoltageControl.user_start_voltage_set;
#endif
  end_value = Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set;
#endif
#endif

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) && (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U))

#elif (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  /* Read potentiometer value and decide the direction */
  XMC_VADC_GROUP_QueueTriggerConversion((void *) MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP);
  for (adc_conversion_delay = 0U; adc_conversion_delay < (uint32_t)BLDC_SCALAR_VADC_CONVERSION_DELAY; adc_conversion_delay++)
  {

  }
  Motor0_BLDC_SCALAR_AnalogIpMeasurement();

  if (Motor0_BLDC_SCALAR.analogip_val < 0)
  {
    Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_NEGATIVE_DIR;
  }
  else
  {
    Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_POSITIVE_DIR;
  }
#else
  /* Initialize the rotation direction */

#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
  if (start_value == (int32_t)0)
  {
    if (end_value >= (int32_t)0)
    {
      Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_POSITIVE_DIR;
    }
    else
    {
      Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_NEGATIVE_DIR;
    }
  }
  else
  {
    if (start_value > (int32_t)0)
    {
      Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_POSITIVE_DIR;
    }
    else
    {
      Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_NEGATIVE_DIR;
    }
  }
#else
  if (end_value >= (int32_t)0)
  {
    Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_POSITIVE_DIR;
  }
  else
  {
    Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_NEGATIVE_DIR;
  }

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */
#endif  /* End of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) */

  Motor0_BLDC_SCALAR.actual_motor_direction = (Motor0_BLDC_SCALAR.motor_set_direction);

  /* Initialize the start value of the ramp */
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)

  /* Start the ramp from start value if analog input is disabled */
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 0U)
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  Motor0_BLDC_SCALAR_Ramp.set_value = Motor0_BLDC_SCALAR_SpeedControl.user_start_speed_set;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
  Motor0_BLDC_SCALAR_Ramp.set_value = Motor0_BLDC_SCALAR_CurrentControl.user_start_current_set;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL))
  Motor0_BLDC_SCALAR_Ramp.set_value = Motor0_BLDC_SCALAR_VoltageControl.user_start_voltage_set;
#endif
#else /* potentiometer enabled */
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  Motor0_BLDC_SCALAR_Ramp.set_value = (int32_t)0;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
  Motor0_BLDC_SCALAR_Ramp.set_value = (int32_t)0;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL))
  Motor0_BLDC_SCALAR_Ramp.set_value = (int32_t)0;
#endif /*if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 0U)*/
#endif

#endif /* if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */

  /* Reset the PI integral buffer */
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  Motor0_BLDC_SCALAR_SpeedControl_PI.ik = 0;
  Motor0_BLDC_SCALAR_SpeedControl_PI.uk = 0;
  Motor0_BLDC_SCALAR_SpeedControl_PI.sat_state = 1U;
  Motor0_BLDC_SCALAR.speedcontrol_rate_counter = 0U;
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  Motor0_BLDC_SCALAR_CurrentControl_PI.ik = 0;
  Motor0_BLDC_SCALAR_CurrentControl_PI.sat_state = 1U;
#endif

}

#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)


/* This API will be called periodically from state machine during bootstrapping time. */

BLDC_SCALAR_BOOTSTRAP_t Motor0_BLDC_SCALAR_Bootstrap(void)
{
  BLDC_SCALAR_BOOTSTRAP_t status = BLDC_SCALAR_BOOTSTRAP_ACTIVE;

  /*Enable Bootstrap for Phase U*/
  if (Motor0_BLDC_SCALAR.bootstrap_counter < Motor0_BLDC_SCALAR.bootstrap_count)
  {
    /*
     * Disable multi-channel mode for phase U so that low side switch of phase U is continuously ON
     * Make sure that compare value of phase U is set greater than period value.
     */
    Motor0_BLDC_SCALAR_PWM_BC_DisableMCMPhaseU();
  }

  /*Enable Bootstrap for Phase V*/
  else if (Motor0_BLDC_SCALAR.bootstrap_counter < (Motor0_BLDC_SCALAR.bootstrap_count * 2U))
  {
    /*
     * Disable multi-channel mode for phase V so that low side switch of phase V is continuously ON
     * Make sure that compare value of phase V is set greater than period value.
     */
    Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseU();
    Motor0_BLDC_SCALAR_PWM_BC_DisableMCMPhaseV();
  }

  /*Enable Bootstrap for Phase W*/
  else if (Motor0_BLDC_SCALAR.bootstrap_counter < (Motor0_BLDC_SCALAR.bootstrap_count * 3U))
  {
    /*
     * Disable multi-channel mode for phase W so that low side switch of phase W is continuously ON
     * Make sure that compare value of phase W is set greater than period value.
     */
    Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseV();
    Motor0_BLDC_SCALAR_PWM_BC_DisableMCMPhaseW();
  }

  else
  {
    /*Configure default values*/
    Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseU();
    Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseV();
    Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseW();
    /* Update channel 1 compare value (CR1) of slice */
    Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseU(0U);
    /* Update channel 1 compare value (CR1) of slice */
    Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseV(0U);
    /* Update channel 1 compare value (CR1) of slice */
    Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseW(0U);

    /*Enable the shadow transfer for all three consumed slice*/
    Motor0_BLDC_SCALAR_PWM_BC_EnableShadowTransfer();
    status = BLDC_SCALAR_BOOTSTRAP_COMPLETED;
  }
  Motor0_BLDC_SCALAR.bootstrap_counter++;
  return (status);
}
#endif


#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
/*
 * This function will measure the potentiometer value based on which motor speed
 * will be controlled
 */
void Motor0_BLDC_SCALAR_AnalogIpMeasurement(void)
{
  int32_t potvalue;

  /*Read the pot result */
  Motor0_BLDC_SCALAR_GetPotentiometerVal(&potvalue);

  #if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U)
  /*Assign pot value to user_endvalue*/
  potvalue = (potvalue - (int32_t)BLDC_SCALAR_POW_13) * 2;
  #else
  /*Assign pot value to user_endvalue*/
  potvalue = (Motor0_BLDC_SCALAR.motor_set_direction * potvalue);
  #endif

  if ((potvalue < (int32_t) Motor0_BLDC_SCALAR.min_analogip_val) && (potvalue > (-1 * (int32_t) Motor0_BLDC_SCALAR.min_analogip_val)))
  {
    potvalue = 0;
  }
  Motor0_BLDC_SCALAR.analogip_val = potvalue;
}
#endif




/**
 * @endcond
 */
