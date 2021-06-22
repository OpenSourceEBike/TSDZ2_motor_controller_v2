/**
 * @file bldc_scalar_control_loop.c
 * @brief CCU8 one match event is used to execute control loop. Event timing is based on PWM frequency.
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
 *     - Updated for under, over voltage
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
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
#include "../ControlModule/bldc_scalar_control_hall.h"
#endif
#if(MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE==1)
#include "../uCProbe/uCProbe.h"
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_OSC_ENABLE ==1) && (MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE==1))
uint32_t BLDC_SCALAR_hall1,BLDC_SCALAR_hall2,BLDC_SCALAR_hall3;
#endif
/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/**
 * @param None
 * @return none <br>
 *
 * \par<b>Description:</b><br>
 * CCU8 one match interrupt.\n
 * Control loop interrupt is based on the PWM frequency.\n
 * This ISR executes the control scheme (PI), direction control, current and voltage reading,
 * voltage compensation and updates the duty cycle of the PWM.
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_ControlLoop_ISR(void)
{
  int32_t voltage_output = 0;  /* output of the control scheme */
  uint32_t duty_cycle;
#if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U)
  uint32_t compensated_duty_cycle = 0U;
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
  int32_t direct_current;   /* ADC value of direct current in Q14 */
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) */
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U))
  int32_t avg_current;      /* ADC reading of average current in Q14 */
#endif /* end of #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U)) */
#if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U)
  Motor0_BLDC_SCALAR.control_loop_exec_count = 1U;
  Motor0_BLDC_SCALAR_PWM_BC_DisableEvent(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[0U],XMC_CCU8_SLICE_IRQ_ID_ONE_MATCH);
#endif/*end of #if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U)*/
  /***************** Current Reading ***************************************/
  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
  /* Get the IDC Link instantaneous current value */
  Motor0_BLDC_SCALAR_GetCurrentValue(&direct_current);
  Motor0_BLDC_SCALAR.motor_current = Motor0_BLDC_SCALAR.motor_set_direction * direct_current;
  #endif  /* end of #if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) */

  #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U))
  /* Get the IDC Link average current value */
  Motor0_BLDC_SCALAR_GetAverageCurrentValue(&avg_current);
  Motor0_BLDC_SCALAR.motor_average_current = Motor0_BLDC_SCALAR.motor_set_direction * avg_current;
  #endif /* end of #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U))*/

  #if (MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)
  /* Over-current detection timing */
  if (Motor0_BLDC_SCALAR.overcurrent_counter != 0U)
  {
    Motor0_BLDC_SCALAR.overcurrent_counter--;
  }
  #endif

  /*****************Duty cycle and direction control**************************/
  /* Call control scheme function*/
#if (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL)
  /* Voltage control */
  Motor0_BLDC_SCALAR_VoltageControlScheme(&voltage_output);
#elif (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL)
  /* Speed control */
  Motor0_BLDC_SCALAR.speedcontrol_rate_counter++;
  if (Motor0_BLDC_SCALAR.speedcontrol_rate_counter >= Motor0_BLDC_SCALAR.speedcontrol_rate)
  {
    Motor0_BLDC_SCALAR_SpeedControlScheme(&voltage_output);
    Motor0_BLDC_SCALAR.speedcontrol_rate_counter = 0U;
  }
  else
  {
    voltage_output = Motor0_BLDC_SCALAR_SpeedControl_PI.uk;
  }
#elif (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL)
  /* Current control */
  Motor0_BLDC_SCALAR_CurrentControlScheme(&voltage_output);
#elif (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL)
  /* Speed inner current control */
  Motor0_BLDC_SCALAR.speedcontrol_rate_counter++;
  if (Motor0_BLDC_SCALAR.speedcontrol_rate_counter >= Motor0_BLDC_SCALAR.speedcontrol_rate)
  {
    Motor0_BLDC_SCALAR_SpeedControlScheme(&voltage_output);
    Motor0_BLDC_SCALAR.speedcontrol_rate_counter = 0U;
  }
  else
  {
    voltage_output = Motor0_BLDC_SCALAR_SpeedControl_PI.uk;
  }

  Motor0_BLDC_SCALAR_CurrentControlScheme(&voltage_output);
#endif

  /*
   * Calculate absolute value of amplitude and
   * if seamless bi-directional control is enabled, change the direction of the rotation at the appropriate time.
   */
  Motor0_BLDC_SCALAR_DirectionControl(voltage_output, &duty_cycle);

  /***************** DC link voltage reading ***************************************/
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
  /* Get the DC link voltage value */
  Motor0_BLDC_SCALAR_VOLT_DCBUS_GetDCLinkVoltage(&Motor0_BLDC_SCALAR.dclink_voltage);

  /* Check if Under/Over voltage protection is enabled */
  #if(MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U)
  /* Check whether the measured dc link voltage is not in set voltage limit */
  if ((Motor0_BLDC_SCALAR.dclink_voltage > Motor0_BLDC_SCALAR.over_voltage_limit) ||
      (Motor0_BLDC_SCALAR.dclink_voltage < Motor0_BLDC_SCALAR.under_voltage_limit))
  {
    /* Increment the counter by 1 and compare with the detection time */
    Motor0_BLDC_SCALAR.over_under_voltage_counter ++;
    /* Stop the motor when voltage stays above or below the configured limit for more than configured detection time */
    if (Motor0_BLDC_SCALAR.over_under_voltage_counter > Motor0_BLDC_SCALAR.over_under_voltage_count)
    {
      Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_UNDER_OVER_VOLTAGE;
      Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
      Motor0_BLDC_SCALAR_MotorStop();
    }
  }
  else
  {
    if(Motor0_BLDC_SCALAR.over_under_voltage_counter > 0U)
    {
      /*decrement the counter as voltage is in specified limits*/
      Motor0_BLDC_SCALAR.over_under_voltage_counter--;
    }
  }
  #endif /* end of #if(MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U) */


  /* Check if voltage compensation is enabled */
  #if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U)
  Motor0_BLDC_SCALAR_VoltageCompensation(Motor0_BLDC_SCALAR.dclink_voltage, duty_cycle, &compensated_duty_cycle);
  duty_cycle = compensated_duty_cycle;
  #endif /*#if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U) */

#endif /*#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U) */

  /* Limit the amplitude to configured min and max values */
#if ((MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE_SYNCHRECTI) || (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE))
  /*
   * To avoid discharging of the bootstrap capacitor in high side modulation,
   * apply 100% voltage if voltage amplitude is greater than amplitude threshold limit
   */
  if (duty_cycle > Motor0_BLDC_SCALAR.amplitude_high_threshold)
  {
    duty_cycle = Motor0_BLDC_SCALAR.max_amplitude;
  }
#endif  /* end of #if ((MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE_SYNCHRECTI) || (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE)) */

  /* max_amplitude is decided by MOTOR0_BLDC_SCALAR_MAX_AMPLITUDE */
  if (duty_cycle > Motor0_BLDC_SCALAR.max_amplitude)
  {
    duty_cycle = Motor0_BLDC_SCALAR.max_amplitude;
  }
  /* min_amplitude is decided by MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE */
  if (duty_cycle < Motor0_BLDC_SCALAR.min_amplitude)
  {
    duty_cycle = 0U;
  }
  Motor0_BLDC_SCALAR.amplitude = duty_cycle;
  /* Update the CCU8 compare values */
  Motor0_BLDC_SCALAR_PWM_BC_DutyCycleUpdate((uint16_t)Motor0_BLDC_SCALAR.amplitude);

#if ((MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_OSC_ENABLE ==1) && (MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE==1))
   ProbeScope_Sampling();

   BLDC_SCALAR_hall1 =Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern() &0x1;
   BLDC_SCALAR_hall2 =(Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern() &0x2)>>1;
   BLDC_SCALAR_hall3 =(Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern() &0x4)>>2;
  #endif
}
/**
 * @}
 */
/**
 * @}
 */
