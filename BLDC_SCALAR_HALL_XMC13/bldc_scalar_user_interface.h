/**
 * @file bldc_scalar_user_interface.h
 * @brief User interface APIs allow to change control algorithm parameters like set value, direction, PI parameters.
 * @date 2016-09-08

 ***********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 * Copyright (c) 2015, Infineon Technologies AG
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
 * @addtogroup UserInterface
 * @brief  User APIs to read and write control algorithm parameters <br>
 * @{
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#ifndef BLDC_SCALAR_USER_INTERFACE_H_
#define BLDC_SCALAR_USER_INTERFACE_H_


#include "../ControlModule/bldc_scalar_control_hall.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
/** Shift by 15 bits */
#define BLDC_SCALAR_15 (15)
/** Shift by 14 bits */
#define BLDC_SCALAR_14 (14)
/** For mA and mV quantities */
#define BLDC_SCALAR_MILLI (1000)
/** percentage */
#define BLDC_SCALAR_PERCENTAGE   (100)

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
* Initializes required peripherals (CCU8, CCU4, POSIF, SYSTICK) and prepares for
* the BLDC motor control
*/
void Motor0_BLDC_SCALAR_Init(void);

/**
 * @return none <br>
 *
 * \par<b>Description:</b><br>
 * changes the motor state to START
 */
void Motor0_BLDC_SCALAR_MotorStart(void);

/**
 * @return none <br>
 *
 * \par<b>Description:</b><br>
 * Stops CCU8 and POSIF peripherals.\n
 * This changes the motor state to STOP state if error_status is zero or else \n
 *                              to ERROR state
 */
void Motor0_BLDC_SCALAR_MotorStop(void);

#if(MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U)
/**
 * @param direction motor rotation direction
 * @return BLDC_SCALAR_STATUS_t status of the API execution \n
 * BLDC_SCALAR_STATUS_SUCCESS: if motor is in STOP state \n
 * BLDC_SCALAR_STATUS_FAILURE: if motor is already running \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if direction value is wrong \n<br>
 *
 * \par<b>Description:</b><br>
 * Sets the direction of rotation.
 *
 * \par<b>Note:</b><br>
 * This API is applicable only when seamless bi-directional control is disabled.
 * In uni-direction control, direction can be set only when motor is in STOP state.
 */

__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetDirection(int32_t direction)
{
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_FAILURE;
  if (Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_STOP)
  {
    if (((direction == BLDC_SCALAR_POSITIVE_DIR) || ((direction == BLDC_SCALAR_NEGATIVE_DIR))) && (direction != Motor0_BLDC_SCALAR.motor_set_direction))
    {
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 0U)
      Motor0_BLDC_SCALAR.motor_set_direction = direction;
#if (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL)
      Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set = -1 * Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set;
      Motor0_BLDC_SCALAR_VoltageControl.user_start_voltage_set = -1 * Motor0_BLDC_SCALAR_VoltageControl.user_start_voltage_set;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
      Motor0_BLDC_SCALAR_SpeedControl.user_speed_set = -1 * Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
      Motor0_BLDC_SCALAR_SpeedControl.user_start_speed_set = -1 * Motor0_BLDC_SCALAR_SpeedControl.user_start_speed_set;
#elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
      Motor0_BLDC_SCALAR_CurrentControl.user_current_set = -1 * Motor0_BLDC_SCALAR_CurrentControl.user_current_set;
      Motor0_BLDC_SCALAR_CurrentControl.user_start_current_set = -1 * Motor0_BLDC_SCALAR_CurrentControl.user_start_current_set;
#endif

#else
      Motor0_BLDC_SCALAR.motor_set_direction = direction;
#endif

      status = BLDC_SCALAR_STATUS_SUCCESS;
    }
    else
    {
      status = BLDC_SCALAR_STATUS_INVALID_PARAM;
    }
  }
  return status;
}
#endif

/**
 * @param direction  Motor rotation direction
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the motor rotation direction
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetDirection(int32_t *direction)
{
  *direction = Motor0_BLDC_SCALAR.motor_set_direction;
}

/**
 * @param speed  Motor mechanical speed in RPM
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the motor mechanical speed in RPM
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetMotorSpeed(int32_t *speed)
{
  *speed = ((Motor0_BLDC_SCALAR.motor_speed * (int32_t)Motor0_BLDC_SCALAR.speed_scale) >> BLDC_SCALAR_15);
}

/**
 * @param avg_current  Motor DC link average current in mA
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the motor DC link average current in mA
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetAverageDCLinkCurrent(int32_t *avg_current)
{
  *avg_current = (int32_t)(((int64_t)BLDC_SCALAR_MILLI * Motor0_BLDC_SCALAR.motor_average_current *
      (int32_t)Motor0_BLDC_SCALAR.current_scale) >> BLDC_SCALAR_15);
}

/**
 * @param dc_current  Motor DC link current in mA
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the motor DC link current in mA
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetInstantaneousDCLinkCurrent(int32_t *dc_current)
{
  *dc_current = (int32_t)(((int64_t)BLDC_SCALAR_MILLI * Motor0_BLDC_SCALAR.motor_current *
      (int32_t)Motor0_BLDC_SCALAR.current_scale) >> BLDC_SCALAR_15);
}

#if (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL)
/**
 * @param voltage Voltage set value in mV
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the voltage set value in mV
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetVoltageVal(int32_t *voltage)
{
  *voltage = (int32_t)(((int64_t)BLDC_SCALAR_MILLI * Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set * (int32_t)Motor0_BLDC_SCALAR.voltage_scale) >> BLDC_SCALAR_15);
}

/**
 * @param voltage Voltage set value in mV Range: -(MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT*1000) to (MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT*1000)
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if voltage parameter is greater than nominal DC link voltage \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the voltage value <i>user_voltage_set </i> if input is within the range.
 *
 * \par<b>Note:</b><br>
 * For unidirection control, set voltage value should be of same polarity like
 * -# -(MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT*1000) to 0 for BLDC_SCALAR_NEGATIVE_DIR
 * -# 0 to (MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT*1000) for BLDC_SCALAR_POSITIVE_DIR
 *
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetVoltageVal(int32_t voltage)
{
  int32_t voltage_scale;
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  int32_t max_dc_link_millivolt = (int32_t)(MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT * 1000.0F);
  if ((voltage <= max_dc_link_millivolt) && (voltage >= -max_dc_link_millivolt))
  {
    voltage_scale = (int32_t)Motor0_BLDC_SCALAR.voltage_scale * BLDC_SCALAR_MILLI;
    Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set = (int32_t)(((int64_t)voltage << BLDC_SCALAR_15) / voltage_scale);
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

#endif


#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/**
 * @param speed Speed set value in RPM
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the speed set value in RPM
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetSpeedVal(int32_t *speed)
{
  *speed = ((Motor0_BLDC_SCALAR_SpeedControl.user_speed_set * (int32_t)Motor0_BLDC_SCALAR.speed_scale) >> BLDC_SCALAR_15);
}

/**
 * @param speed Speed set value in RPM Range: -(MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED) to (MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED)
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if speed parameter is greater than no load speed \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the speed value <i>user_speed_set </i> if input is within the range.
 *
 * \par<b>Note:</b><br>
 * For unidirection control, set voltage value should be of same polarity like
 * -# -(MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED) to 0 for BLDC_SCALAR_NEGATIVE_DIR
 * -# 0 to (MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED) for BLDC_SCALAR_POSITIVE_DIR
 *
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetSpeedVal(int32_t speed)
{
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  if ((speed <= (int32_t)MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED) && (speed >= -(int32_t)MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED))
  {
    Motor0_BLDC_SCALAR_SpeedControl.user_speed_set =
        ((speed << BLDC_SCALAR_15) / (int32_t)Motor0_BLDC_SCALAR.speed_scale);
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param kp Proportional gain. Range: 0 to 2^15
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if parameter is greater than 2^15 \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the proportional gain of the speed PI control.
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetSpeedProportionalGain(uint16_t kp)
{
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  if (kp <= BLDC_SCALAR_POW_15)
  {
    Motor0_BLDC_SCALAR_SpeedControl_PI.kp = kp;
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param kp Integral gain. Range: 0 to 2^15
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if parameter is greater than 2^15 \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the integral gain of the speed PI control.
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetSpeedIntegralGain(uint16_t ki)
{
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  if (ki <= BLDC_SCALAR_POW_15)
  {
    Motor0_BLDC_SCALAR_SpeedControl_PI.ki = ki;
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param percentage_limit PI output limit in %. Range: 0 to 100
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if parameter is greater than 100 \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the speed PI output limit
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetSpeedPILimit(uint8_t percentage_limit)
{
  uint32_t limit;
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  if (percentage_limit <= (uint8_t)BLDC_SCALAR_PERCENTAGE)
  {
    limit = (BLDC_SCALAR_POW_14 * (uint32_t)percentage_limit) / (uint32_t)BLDC_SCALAR_PERCENTAGE;
    Motor0_BLDC_SCALAR_SpeedControl_PI.uk_limit_max = (int32_t)limit;
    Motor0_BLDC_SCALAR_SpeedControl_PI.uk_limit_min = -(int32_t)limit;
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param kp proportional gain
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the proportional gain of speed PI control
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetSpeedProportionalGain(uint16_t *kp)
{
  *kp = Motor0_BLDC_SCALAR_SpeedControl_PI.kp;
}

/**
 * @param ki Integral gain
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the integral gain of speed PI control
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetSpeedIntegralGain(uint16_t *ki)
{
  *ki = Motor0_BLDC_SCALAR_SpeedControl_PI.ki;
}

/**
 * @param percentage_limit PI output limit
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the speed PI control output limit in %
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetSpeedPILimit(uint8_t *percentage_limit)
{
  int32_t percentage = (Motor0_BLDC_SCALAR_SpeedControl_PI.uk_limit_max * BLDC_SCALAR_PERCENTAGE) >> BLDC_SCALAR_14;
  *percentage_limit = (uint8_t)percentage;
}
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))


/**
 * @param speed current set value in mA Range: -(MOTOR0_BLDC_SCALAR_MAX_CURRENT * 1000) to (MOTOR0_BLDC_SCALAR_MAX_CURRENT * 1000)
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if current parameter is greater than no load speed \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the current value <i>user_current_set </i> if input is within the range.
 *
 * \par<b>Note:</b><br>
 * For unidirection control, set current value should be of same polarity like
 * -# -(MOTOR0_BLDC_SCALAR_MAX_CURRENT *1000) to 0 for BLDC_SCALAR_NEGATIVE_DIR
 * -# 0 to (MOTOR0_BLDC_SCALAR_MAX_CURRENT * 1000) for BLDC_SCALAR_POSITIVE_DIR
 *
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetCurrentVal(int32_t current)
{
  int32_t current_scale;
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  int32_t max_current_milliamps = (int32_t) (MOTOR0_BLDC_SCALAR_MAX_CURRENT * 1000.0F);
  if ((current <= max_current_milliamps) && (current >= -max_current_milliamps))
  {
    current_scale = (int32_t)Motor0_BLDC_SCALAR.current_scale * BLDC_SCALAR_MILLI;
    Motor0_BLDC_SCALAR_CurrentControl.user_current_set =
        (int32_t)(((int64_t)current << BLDC_SCALAR_15) / current_scale);
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param current Current set value in mA
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the current set value in mA
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetCurrentVal(int32_t *current)
{
  *current = (int32_t)(((int64_t)BLDC_SCALAR_MILLI * Motor0_BLDC_SCALAR_CurrentControl.user_current_set *
      (int64_t)Motor0_BLDC_SCALAR.current_scale) >> BLDC_SCALAR_15);
}

#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/**
 * @param kp Proportional gain. Range: 0 to 2^15
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if parameter is greater than 2^15 \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the proportional gain of the current PI control.
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetCurrentProportionalGain(uint16_t kp)
{
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  if (kp <= BLDC_SCALAR_POW_15)
  {
    Motor0_BLDC_SCALAR_CurrentControl_PI.kp = kp;
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param kp Integral gain. Range: 0 to 2^15
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if parameter is greater than 2^15 \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the integral gain of the current PI control.
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetCurrentIntegralGain(uint16_t ki)
{
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  if (ki <= BLDC_SCALAR_POW_15)
  {
    Motor0_BLDC_SCALAR_CurrentControl_PI.ki = ki;
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param limit PI output limit in %. Range: 0 to 100
 * @return BLDC_SCALAR_STATUS_t status of API execution \n
 * BLDC_SCALAR_STATUS_INVALID_PARAM: if parameter is greater than 100 \n
 * BLDC_SCALAR_STATUS_SUCCESS: if successful <br>
 *
 * \par<b>Description:</b><br>
 * Sets the current PI output limit
 */
__STATIC_INLINE BLDC_SCALAR_STATUS_t Motor0_BLDC_SCALAR_SetCurrentPILimit(uint8_t percentage_limit)
{
  uint32_t limit;
  BLDC_SCALAR_STATUS_t status = BLDC_SCALAR_STATUS_INVALID_PARAM;
  if (percentage_limit <= (uint8_t)BLDC_SCALAR_PERCENTAGE)
  {
    limit = (BLDC_SCALAR_POW_14 * (uint32_t)percentage_limit) / (uint32_t)BLDC_SCALAR_PERCENTAGE;
    Motor0_BLDC_SCALAR_CurrentControl_PI.uk_limit_max = (int32_t)(limit);
    Motor0_BLDC_SCALAR_CurrentControl_PI.uk_limit_min = -(int32_t)(limit);
    status = BLDC_SCALAR_STATUS_SUCCESS;
  }
  return status;
}

/**
 * @param kp proportional gain
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the proportional gain of current PI control
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetCurrentProportionalGain(uint16_t *kp)
{
  *kp = Motor0_BLDC_SCALAR_CurrentControl_PI.kp;
}

/**
 * @param ki Integral gain
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the integral gain of current PI control
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetCurrentIntegralGain(uint16_t *ki)
{
  *ki = Motor0_BLDC_SCALAR_CurrentControl_PI.ki;
}

/**
 * @param percentage_limit PI output limit
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with the current PI control output limit in %
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetCurrentPILimit(uint8_t *percentage_limit)
{
  int32_t percentage = (Motor0_BLDC_SCALAR_CurrentControl_PI.uk_limit_max * BLDC_SCALAR_PERCENTAGE) >> BLDC_SCALAR_14;
  *percentage_limit = (uint8_t)percentage;
}

#endif

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Clears the error_status variable.
 *
 * \par<b>Description:</b><br>
 * This API should be called to clear errors before restarting the motor.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_ClearErrorState(void)
{
  Motor0_BLDC_SCALAR.error_status = 0U;
}

/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif /* BLDC_SCALAR_USER_INTERFACE_H_ */
