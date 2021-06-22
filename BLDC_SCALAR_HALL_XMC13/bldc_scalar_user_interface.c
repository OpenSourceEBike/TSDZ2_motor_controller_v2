/**
 * @file bldc_scalar_user_interface.c
 * @brief User interface APIs allow to change control algorithm parameters like set value, direction, PI parameters.
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
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "bldc_scalar_user_interface.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_SETTLING_TIME          (0x7FFFFU)
#define BLDC_SCALAR_MCM_PATTERN_TABLE_SIZE (15U)
/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/
/**
 * One time initialization of the BLDC_SCALAR data structure variables based on configuration
 */
static void Motor0_BLDC_SCALAR_MotorVarInit(void);

/**
 * Initialization of VADC
 */
static void Motor0_BLDC_SCALAR_MeasurementInit(void);
/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/* One time initialization of the BLDC_SCALAR data structure variables based on configuration */
static void Motor0_BLDC_SCALAR_MotorVarInit(void)
{
  uint8_t mcm_index;              /* loop count to update multi-channel pattern for sync rectification PWM */

/*******************************************************************************/
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
#endif /*end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 0U)*/

#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */

/******************start: mc_pattern table*****************************/
  /* multi-channel pattern generation for high side sync modulation */
  for (mcm_index = 0U; mcm_index <= BLDC_SCALAR_MCM_PATTERN_TABLE_SIZE; mcm_index++)
  {
    if ((Motor0_BLDC_SCALAR.mc_pattern[1][mcm_index] & ((uint32_t)0xFU << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM))) ==
        ((uint32_t)0x1U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)))
    {
      Motor0_BLDC_SCALAR.mc_pattern[0][mcm_index] =  (uint16_t)((Motor0_BLDC_SCALAR.mc_pattern[1][mcm_index] | ((uint32_t)0x2U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM))));
    }
    else if ((Motor0_BLDC_SCALAR.mc_pattern[1][mcm_index] & ((uint32_t)0xFU << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM))) ==
        ((uint32_t)0x1U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)))
    {
      Motor0_BLDC_SCALAR.mc_pattern[0][mcm_index] =  (uint16_t)((Motor0_BLDC_SCALAR.mc_pattern[1][mcm_index] | ((uint32_t)0x2U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM))));
    }
    else if ((Motor0_BLDC_SCALAR.mc_pattern[1][mcm_index] & ((uint32_t)0xFU << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM))) ==
        ((uint32_t)0x1U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)))
    {
      Motor0_BLDC_SCALAR.mc_pattern[0][mcm_index] =  (uint16_t)((Motor0_BLDC_SCALAR.mc_pattern[1][mcm_index] | ((uint32_t)0x2U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM))));
    }
    else
    {

    }
  }
  /******************end: mc_pattern table*****************************/

}


static void Motor0_BLDC_SCALAR_MeasurementInit(void)
{
  /* Initialize VADC peripheral */
  Motor0_BLDC_SCALAR_VADC_Init();

  /* Channel,Result register and Queue entry configuration for configured channels */
  /* Calling sequence of below functions will decide the Queue entries sequence in corresponding Queues. */
  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Current_Measurment_Init();
  #endif

  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_AverageCurrent_Measurment_Init();
  #endif

  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Volt_DCBus_Measurement_Init();
  #endif

  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Volt_Potentiometer_Init();
  #endif

  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Volt_Userdef1_Init();
  #endif

  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Volt_Userdef2_Init();
  #endif

  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Volt_Userdef3_Init();
  #endif

  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Volt_Userdef4_Init();
  #endif
}


/* Initialize the required peripherals, modules and interrupts */
void Motor0_BLDC_SCALAR_Init(void)
{
  volatile uint32_t delay_counter;

  /* Initialization settling period */
  for (delay_counter = 0U; delay_counter < (uint32_t)BLDC_SCALAR_SETTLING_TIME; delay_counter++)
  {

  }

  /* Initializes block commutation module along with the peripherals - CCU8, GPIO */
  Motor0_BLDC_SCALAR_PWM_BC_Init();

  /* Initializes hall feedback module along with the peripherals - POSIF, CCU4, GPIO */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_Init();

  /* Initializes measurement module along with the peripherals - VADC, GPIO */
  Motor0_BLDC_SCALAR_MeasurementInit();

  /* Initializes BLDC_SCALAR data structure elements based on the user configurations */
  Motor0_BLDC_SCALAR_MotorVarInit();

  /* Initializes systick - this will start the statemachine interrupt */
  BLDC_SCALAR_SYSTICK_TIMER_Init();

}

void Motor0_BLDC_SCALAR_MotorStart(void)
{
  /*
   * Motor State machine should be in STOP state to start the motor.
  * In case of any error, motor start function won't be started
  * until clear all the errors.
  */
  if (Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_STOP)
  {
     Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_START;
     Motor0_BLDC_SCALAR_MSM();
  }
}

void Motor0_BLDC_SCALAR_MotorStop(void)
{
  /*stop pwm bc*/
  Motor0_BLDC_SCALAR_PWM_BC_Stop();

  /*stop posif*/
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_Stop();

#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
  /*disable inverter*/
  Motor0_BLDC_SCALAR_PWM_BC_InverterDisable();
#endif

  Motor0_BLDC_SCALAR.motor_speed = 0;
  Motor0_BLDC_SCALAR.motor_current = 0;
  Motor0_BLDC_SCALAR.motor_average_current = 0;

  if (Motor0_BLDC_SCALAR.error_status != 0U)
  {
    Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
    /*Change motor control state machine to error*/
    Motor0_BLDC_SCALAR_MSM();
  }
  else
  {
    /* Change motor control state machine to stop */
    Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_STOP;
  }
}



/**
* @endcond
*/
