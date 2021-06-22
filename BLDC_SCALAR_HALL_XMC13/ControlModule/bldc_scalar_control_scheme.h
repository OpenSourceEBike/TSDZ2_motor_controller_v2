/**
 * @file bldc_scalar_control_scheme.h
 * @brief Control algorithm routines like control scheme, voltage compensation, stall detection
 * @date 2016-09-08
 * @cond
 ***********************************************************************************************************************
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
 * 2016-09-08:
 *     - Updated for sensorless support
 * @endcond
 *
 */
#ifndef BLDC_SCALAR_CONTROL_SCHEME_H
#define BLDC_SCALAR_CONTROL_SCHEME_H

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

#include "../MidSys/bldc_scalar_pwm_bc.h"
#include "../MidSys/bldc_scalar_speed_pos_hall.h"

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT))
#include "../MidSys/bldc_scalar_current_motor.h"
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
#include "../MidSys/bldc_scalar_volt_dcbus.h"
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
#include "../MidSys/bldc_scalar_volt_potentiometer.h"
#endif

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U) || \
(MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U))
#include "../MidSys/bldc_scalar_volt_userdef.h"
#endif

#include "../MCUInit/nvic.h"
#include "../MCUInit/systick.h"
#include "../MCUInit/vadc.h"


#include "../ControlModule/bldc_scalar_pi.h"
#include "../ControlModule/bldc_scalar_pt1_filter.h"
#include "../ControlModule/bldc_scalar_ramp_generator.h"

/***********************************************************************************************************************
 * #errors
 **********************************************************************************************************************/
#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U))
/* For over-current protection with direct DC link current as source, VADC measurement for direct DC link current should be enabled */
#if ((MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_DIRECT_CURRENT))
  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT != 1U)
  #error "Over Current detection is enabled but direct DC Link current measurement is not enabled. Enable MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT in the Configuration/bldc_scalar_user_config.h file "
  #endif

/* For over-current protection with average DC link current as source, VADC measurement for average DC link current should be enabled */
#elif ((MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_AVG_CURRENT))
  #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT != 1U))
  #error "Over Current detection is enabled but DC Link average current measurement is not enabled. Enable MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT in the Configuration/bldc_scalar_user_config.h file "
  #endif
#endif
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL)||(MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/* For current control with direct DC link current as feedback, VADC measurement for direct DC link current should be enabled */
#if ((MOTOR0_BLDC_SCALAR_CURRENT_FEEDBACK == BLDC_SCALAR_IDC_AVG_CURRENT) && ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT != 1U) &&(MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK != 1U)))
#error "Current control is enabled but DC Link average current measurement is not enabled. Enable MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT or MOTOR0_BLDC_SCALAR_VADC_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK  in the Configuration/bldc_scalar_user_config.h file "
#endif
/* For current control with average DC link current as feedback, VADC measurement for average DC link current should be enabled */
#if ((MOTOR0_BLDC_SCALAR_CURRENT_FEEDBACK == BLDC_SCALAR_IDC_DIRECT_CURRENT) && (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT != 1U))
#error "Current control is enabled but DC Link direct current measurement is not enabled. Enable MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT in the Configuration/bldc_scalar_user_config.h file "
#endif
#endif

/* For voltage protection, VADC measurement for DC link voltage should be enabled */
#if (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U)
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT != 1U)
#error "Under/Over voltage detection is enabled but DC link voltage measurement is not enabled. Enable MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT in the Configuration/bldc_scalar_user_config.h file "
#endif
#endif

/* If voltage compensation enabled then VADC measurement should be enabled for DC link voltage */
#if(MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U)
#if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT != 1U)
#error "Voltage compensation is enabled but DC link voltage measurement is not enabled.Enable MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT in the Configuration/bldc_scalar_user_config.h file "
#endif
#endif

/* If ramp down voltage clamping enabled then VADC measurement should be enabled for DC link voltage */
#if(MOTOR0_BLDC_SCALAR_ENABLE_RAMP_DOWN_VOLTAGE_CLAMPING == 1U)
#if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT != 1U)
#error "Ramp down DC bus voltage clamping is enabled but DC link voltage measurement is not enabled.Enable MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT in the Configuration/bldc_scalar_user_config.h file "
#endif
#endif

/***********************************************************************************************************************
   * MACROS
 **********************************************************************************************************************/

#define  BLDC_SCALAR_STALL_IGNORE_COUNT       (6U)   /*!< Ignore first 6 hall events for stall detection */
#define  BLDC_SCALAR_SHIFT_8                  (8U)   /*!< Shift by 8 bits */
#define  BLDC_SCALAR_SHIFT_4                  (4U)   /*!< Shift by 4 bits */

/**********************************************************************************************************************
* ENUMS
**********************************************************************************************************************/

/**
 * This enumerates the error codes of the control which can occur during run-time.
 */
typedef enum BLDC_SCALAR_EID
{
  BLDC_SCALAR_EID_CTRAP_ERROR            = 0U,       /*!< Trap condition is detected.  error_status = 1*/
  BLDC_SCALAR_EID_OVERCURRENT            = 1U,       /*!< Over current is detected. error_status = 2 */
  BLDC_SCALAR_EID_SHORTCIRCUIT           = 2U,       /*!< Short circuit current protection. error_status = 4 */
  BLDC_SCALAR_EID_WRONGHALL              = 3U,       /*!< Wrong hall is detected. error_status = 8 */
  BLDC_SCALAR_EID_HALL_LEARNING_TIMEOUT  = 4U,       /*!< Hall pattern capturing failed. error_status = 16 */
  BLDC_SCALAR_EID_STALL                  = 5U,       /*!< Motor stall is detected. error_status = 32 */
  BLDC_SCALAR_EID_UNDER_OVER_VOLTAGE     = 6U,       /*!< Under/over voltage is detected. error_status = 64 */
  BLDC_SCALAR_EID_MOTOR_FREE_RUNNING     = 7U,       /*!< Motor is running above threshold speed and catch free is disabled. error_status = 128 */
  BLDC_SCALAR_EID_MOTOR_FREE_REV_RUNNING = 8U,       /*!< Motor is running above threshold speed in reveres direction. error_status = 256 */
  BLDC_SCALAR_EID_STARTUP_FAILURE        = 9U        /*!< Startup failure for multiple times. error_status = 512 */
} BLDC_SCALAR_EID_t;


/**
 * States of the control algorithm
 */
typedef enum BLDC_SCALAR_MSM
{
  BLDC_SCALAR_MSM_STOP                          = 0U,         /*!< Motor Stop state. This is the state after power on reset. */
  BLDC_SCALAR_MSM_START                         = 1U,         /*!< Motor control starts with this state when MotorStart function is called */
  BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION    = 2U,         /*!< Initial motor state identification to check if motor is freely running  */
  BLDC_SCALAR_MSM_BOOTSTRAP                     = 3U,         /*!< Bootstrap state to charge bootstrap capacitors */
  BLDC_SCALAR_MSM_HALL_LEARNING                 = 4U,         /*!< Hall pattern detection to find the commutation table*/
  BLDC_SCALAR_MSM_ROTOR_POSITION_IDENTIFICATION = 5U,         /*!< Rotor initial position identification. */
  BLDC_SCALAR_MSM_TRANSITION                    = 6U,         /*!< Transition from free running motor to closed loop. Not applicable for this version.  */
  BLDC_SCALAR_MSM_NORMAL_OPERATION              = 7U,         /*!< Closed loop control */
  BLDC_SCALAR_MSM_ERROR                         = 8U,         /*!< Error state. Motor stops running */
  BLDC_SCALAR_MSM_IDLE                          = 9U         /*!< Idle state - when voltage, speed or current command is zero. This state is applicable only when
                                                                   seamless bi-directional feature is disabled. */
} BLDC_SCALAR_MSM_t;

/**
 * This enumerates Bootstrap Status
 */
typedef enum BLDC_SCALAR_BOOTSTRAP
{
  BLDC_SCALAR_BOOTSTRAP_ACTIVE = 0U,            /*!< Bootstrap is active */
  BLDC_SCALAR_BOOTSTRAP_COMPLETED          /*!< Bootstrap is completed */

} BLDC_SCALAR_BOOTSTRAP_t;
/**
 * This enumerates free running motor state identification
 */
typedef enum BLDC_SCALAR_STATE_IDENTIFICATION
{
  BLDC_SCALAR_STATE_IDENTIFICATION_PROGRESS = 0U,          /*!< motor state identification is active */
  BLDC_SCALAR_STATE_IDENTIFICATION_COMPLETED          /*!< motor state identification is completed */

} BLDC_SCALAR_STATE_IDENTIFICATION_t;

/**
 * Enumerates the return status of API
 */
typedef enum BLDC_SCALAR_STATUS
{
  BLDC_SCALAR_STATUS_SUCCESS = 0U,              /*!< Function executed successfully */
  BLDC_SCALAR_STATUS_FAILURE,              /*!< Function execution failed */
  BLDC_SCALAR_STATUS_INVALID_PARAM         /*!< Arguments are invalid */
} BLDC_SCALAR_STATUS_t;


/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/

/**
 * @brief Speed control parameters
 */
typedef struct BLDC_SCALAR_SPEED_CONTROL
{
  int32_t                    user_start_speed_set;     /*!< initial speed */
  int32_t                    user_speed_set;           /*!< end speed */
  int32_t                    ref_speed;           /*!< this is user_set if ramp is disabled OR
                                                             set_value if ramp is enabled */
  int32_t                    fdbk_speed;          /*!< points to measured feedback speed  */
} BLDC_SCALAR_SPEED_CONTROL_t;


/**
 * @brief Current control parameters
 */
typedef struct BLDC_SCALAR_CURRENT_CONTROL
{
  int32_t user_start_current_set;                     /*!< initial current */
  int32_t user_current_set;                           /*!< end current */
  int32_t ref_current;                          /*!< this is user_set if ramp is disabled OR
                                                                           set_value if ramp is enabled */
  int32_t fdbk_current;                         /*!< points to measured feedback current */
} BLDC_SCALAR_CURRENT_CONTROL_t;

/**
 * @brief Voltage control parameters
 */
typedef struct BLDC_SCALAR_VOLTAGE_CONTROL
{
  int32_t user_start_voltage_set;          /*!< initial voltage */
  int32_t user_voltage_set;            /*!< end voltage */
  int32_t ref_voltage;                /*!< this id user_voltage_set if ramp is disabled OR set_value if ramp is enabled */
} BLDC_SCALAR_VOLTAGE_CONTROL_t;


/**
 *  @brief Structure contains the motor parameters, measured values
 */
typedef struct BLDC_SCALAR
{
  int32_t                     set_val;                   /*!< set value based on the control scheme */

  uint16_t                    mc_pattern[3][16];          /*!< multi-channel commutation pattern array for all modulation types*/

  volatile BLDC_SCALAR_MSM_t  msm_state;                 /*!< motor state as per the state machine */
  uint32_t                    error_status;              /*!< error status where each bit represents particular run time error status.
                                                              bit position is given by BLDC_SCALAR_EID_t */

  int32_t                    motor_speed;                /*!< calculated mechanical motor speed in Q14 format */
  int32_t                    motor_current;              /*!< measured DC link instantaneous current in Q14 format */
  int32_t                    motor_average_current;      /*!< measured DC link average current in Q14 format */
  int32_t                    motor_set_direction;        /*!< Commanded motor direction */
  int32_t                    actual_motor_direction;     /*!< Actual motor direction */
  uint32_t                   dclink_voltage;             /*!< measured DC link voltage in Q14 format */
  uint32_t                   max_dc_link_voltage;        /*!< Ramp down is disabled if dc_link_voltage is greater than this voltage */
  uint32_t                   nominal_dc_link_voltage;    /*!< Nominal DC link voltage in Q14 format */
  int32_t                    analogip_val;               /*!< measured analog input value in Q14 format */
  int32_t                    min_analogip_val;           /*!< Minimum analog input value below which value is considered as zero */

  uint32_t                   amplitude;                  /*!< actual amplitude in Q14 format */
  uint32_t                   amplitude_high_threshold;   /*!< High threshold value above which 100% amplitude is applied to avoid discharge of bootstrap capacitor */
  uint32_t                   min_amplitude_configured;   /*!< Minimum amplitude configured in Q14 format */
  uint32_t                   min_amplitude;              /*!< Minimum amplitude in Q14 format */
  uint32_t                   max_amplitude;              /*!< Maximum amplitude in Q14 format */
#if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U)
  uint32_t                   control_loop_exec_rate;     /*!<It is to control the frequency of execution of control loop. This rate is based on
                                                             PWM frequency which tells how may times once the control loop should execute*/
  uint32_t                   control_loop_exec_count;    /*!<Control loop execution counter*/
#endif
  int32_t                    min_speed;                  /*!< Minimum speed in seamless bi-directional control to handle zero speed */

#if (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U)
  uint32_t                   over_under_voltage_count;  /*!< voltage counter */
  uint32_t                   over_under_voltage_counter;  /*!< run time voltage counter */
  int32_t                    over_voltage_limit;          /*!< Maximum DC link voltage that is allowed */
  int32_t                    under_voltage_limit;         /*!< Minimum DC link voltage that is allowed */
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
  uint32_t                   stall_detection_count;      /*!< stall counter */
  uint32_t                   stall_detection_counter;    /*!< run time stall counter */
  uint32_t                   stall_min_amplitude;        /*!< Minimum amplitude below which stall is not detected */
  uint32_t                   stall_time_diff_ratio;      /*!< ratio of time between two hall events */
  uint8_t                    stall_check;                /*!< to skip the stall detection at the start when reference is zero */
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)
  uint32_t                   overcurrent_count;         /*!< over current counter */
  uint32_t                   overcurrent_counter;         /*!< run time over current counter */
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
  uint32_t                   bootstrap_count;           /*!< bootstrap count */
  uint32_t                   bootstrap_counter;          /*!< run time bootstrap count */
#endif

  uint32_t                    speed_scale;                 /*!< Speed scale to convert the motor speed to target value in Q14 format*/
  uint32_t                    current_scale;               /*!< Current scale to convert the motor current to target value in Q14 format*/
  uint32_t                    voltage_scale;               /*!< Voltage scale to convert the motor voltage to target value in Q14 format*/
  uint32_t                    speed_mech_scale;            /*!< Scale to convert the electrical speed to mechanical speed in Q14 format*/

  uint16_t                   period;                       /*!< CCU8 period register value */


#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  uint8_t                    speedcontrol_rate;            /*!< Execution rate of speed control loop */
  uint8_t                    speedcontrol_rate_counter;    /*!< run time counter for speed control execution rate */
#endif
} BLDC_SCALAR_t;



/**********************************************************************************************************************
* EXTERN
**********************************************************************************************************************/
extern BLDC_SCALAR_t Motor0_BLDC_SCALAR;


#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL))
extern BLDC_SCALAR_VOLTAGE_CONTROL_t Motor0_BLDC_SCALAR_VoltageControl;
#endif
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
extern BLDC_SCALAR_SPEED_CONTROL_t Motor0_BLDC_SCALAR_SpeedControl;
#endif
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
extern BLDC_SCALAR_CURRENT_CONTROL_t Motor0_BLDC_SCALAR_CurrentControl;
#endif


extern void Motor0_BLDC_SCALAR_MotorStop(void);
extern RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PatternInitiator(uint8_t curpos);

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U)
/**
 * @param dc_volt DC link voltage in Q14
 * @param amplitude Amplitude in Q14 to be compensated
 * @param compensated_amplitude compensated amplitude in Q14 format
 * @return None <br>
 *
 *  \par<b>Description:</b><br>
 * This compensates DC link voltage ripple error and adjusts the amplitude value.
 * This is called by control loop interrupt.
 *
 * \par<b>Execution Time:</b><br>
 * using O3 optimization level \n
 * without PT1 filter: <b>8.8 uSec </b>\n
 * with PT1 filter: <b>9.66 uSec</b> \n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_VoltageCompensation(uint32_t dc_volt, uint32_t amplitude, uint32_t *compensated_amplitude)
{
  int32_t voltage = (int32_t)dc_volt;    /* DC link voltage */

  /* Filter DC link voltage if filter is enabled */
#if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION_FILTER == 1U)
  /* first order low pass filtering of measured DC link voltage */
  Motor0_BLDC_SCALAR_PT1_Filter(&Motor0_BLDC_SCALAR_PT1_VoltageComp, (int32_t)dc_volt);
  voltage = Motor0_BLDC_SCALAR_PT1_VoltageComp.pt1_out_val;
#endif

  /* Adjust the amplitude based upon DC link voltage ripple */
  if (voltage != 0)
  {
    __disable_irq();
    /*Do the voltage compensation based on dc link value*/
    *compensated_amplitude = (uint32_t)(((uint32_t)amplitude * Motor0_BLDC_SCALAR.nominal_dc_link_voltage) /
                             ((uint32_t)voltage));
    __enable_irq();
  }
}
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
/**
 * @return BLDC_SCALAR_BOOTSTRAP_t bootstrap status \n
 * BLDC_SCALAR_BOOTSTRAP_ACTIVE - Bootstrap is in progress \n
 * BLDC_SCALAR_BOOTSTRAP_COMPLETED - Bootstrapping is done \n <br>
 *
 * \par<b>Description:</b><br>
 * This function switches lower side switch of a phase one by one to enable charging of bootstrap capacitor
 * Bootstrap time is configured as @ref MOTOR0_BLDC_SCALAR_BOOTSTRAP_TIME_mS
 * This function is called  by state machine interrupt in the BOOTSTRAP state.
 */
BLDC_SCALAR_BOOTSTRAP_t Motor0_BLDC_SCALAR_Bootstrap(void);
#endif




#if (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL)
/**
 * @param output Output of the voltage control
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Returns the output voltage
 * This is called from control loop event.
 *
 * \par<b>Execution Time:</b><br>
 * <b>0.33 uSec </b>using O3 optimization level
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_VoltageControlScheme(int32_t *output)
{
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
  Motor0_BLDC_SCALAR_VoltageControl.ref_voltage = Motor0_BLDC_SCALAR_Ramp.set_value;
#elif (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_VoltageControl.ref_voltage = Motor0_BLDC_SCALAR.analogip_val;
#else
  Motor0_BLDC_SCALAR_VoltageControl.ref_voltage = Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set;
#endif
  *output = (Motor0_BLDC_SCALAR_VoltageControl.ref_voltage);
}
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/**
 * @param output Output of the speed control
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Executes speed PI loop and returns the output voltage
 * This is called from control loop event.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.820 uSec </b>using O3 optimization level
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SpeedControlScheme(int32_t *output)
{
  int32_t error;
  Motor0_BLDC_SCALAR_SpeedControl.fdbk_speed = Motor0_BLDC_SCALAR.motor_speed;
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
  Motor0_BLDC_SCALAR_SpeedControl.ref_speed = Motor0_BLDC_SCALAR_Ramp.set_value;
#elif (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_SpeedControl.ref_speed = Motor0_BLDC_SCALAR.analogip_val;
#else
  Motor0_BLDC_SCALAR_SpeedControl.ref_speed = Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
#endif

  error = (int32_t)(Motor0_BLDC_SCALAR_SpeedControl.ref_speed) - (int32_t)(Motor0_BLDC_SCALAR_SpeedControl.fdbk_speed);

  /*Speed Control based on PI technique*/
  Motor0_BLDC_SCALAR_PI_Controller(&Motor0_BLDC_SCALAR_SpeedControl_PI,(int32_t)error);

  *output = Motor0_BLDC_SCALAR_SpeedControl_PI.uk;
}
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/**
 * @param output Output of the current control
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Executes current PI loop and returns the output voltage
 * This is called from control loop event.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.56 uSec </b>using O3 optimization level
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_CurrentControlScheme(int32_t *output)
{
  int32_t error;
#if(MOTOR0_BLDC_SCALAR_CURRENT_FEEDBACK == BLDC_SCALAR_IDC_DIRECT_CURRENT)
  Motor0_BLDC_SCALAR_CurrentControl.fdbk_current = Motor0_BLDC_SCALAR.motor_current;
#else
  Motor0_BLDC_SCALAR_CurrentControl.fdbk_current = Motor0_BLDC_SCALAR.motor_average_current;
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
  #if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
    Motor0_BLDC_SCALAR_CurrentControl.ref_current = Motor0_BLDC_SCALAR_Ramp.set_value;
  #elif (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
    Motor0_BLDC_SCALAR_CurrentControl.ref_current = Motor0_BLDC_SCALAR.analogip_val;
  #else
    Motor0_BLDC_SCALAR_CurrentControl.ref_current = Motor0_BLDC_SCALAR_CurrentControl.user_current_set;
  #endif

#else
    Motor0_BLDC_SCALAR_CurrentControl.ref_current = *output;
#endif

  error = (int32_t)(Motor0_BLDC_SCALAR_CurrentControl.ref_current) - (int32_t)(Motor0_BLDC_SCALAR_CurrentControl.fdbk_current);

  /*Current Control based on PI technique*/
  Motor0_BLDC_SCALAR_PI_Controller(&Motor0_BLDC_SCALAR_CurrentControl_PI,(int32_t)error);

  *output = Motor0_BLDC_SCALAR_CurrentControl_PI.uk;
}
#endif



#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Reads the potentiometer value and modifies the value based on seamless bi-directional control
 * For unidirectional control, potentiometer value is 0 to 2^14 or -2^14 to 0
 * For seamless bi-directional control, potentiometer value is -2^14 to 2^14
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_AnalogIpMeasurement(void);
#endif

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * This is the state machine function called from state machine event.
 * This handles the state transitions.
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_MSM(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Resets the motor control variables like PI buffers, PT1 buffers,
 * measured quantities like speed, current.
 *
 */
void Motor0_BLDC_SCALAR_MotorParamInit(void);

/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* BLDC_SCALAR_CONTROL_SCHEME_H */
