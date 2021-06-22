/**
 * @file bldc_scalar_derived_parameter.h
 * @brief Target (scaled) value calculation from the user configurations.
 * These values are assigned to the respective data structures.
 * Do NOT change the macros in this file.
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

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#ifndef BLDC_SCALAR_DERIVED_PARAM_H_
#define BLDC_SCALAR_DERIVED_PARAM_H_

#include "bldc_scalar_user_config.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/* common macros */
#define BLDC_SCALAR_POW_4   (15U)
#define BLDC_SCALAR_POW_8   (255U)
#define BLDC_SCALAR_POW_10  (1023U)
#define BLDC_SCALAR_POW_12  (4095U)
#define BLDC_SCALAR_POW_13  (8191U)
#define BLDC_SCALAR_POW_14  (16383U)
#define BLDC_SCALAR_POW_15  (32767U)
#define BLDC_SCALAR_POW_16  (65535U)
#define BLDC_SCALAR_POW_24  (16777215U)

#define BLDC_SCALAR_SPEED_SCALE_RES (10)
#define BLDC_SCALAR_TEN             (10U)

#if defined ( __GNUC__ )
#define RAM_ATTRIBUTE  __attribute__((section(".ram_code")))
#else
#define RAM_ATTRIBUTE
#endif

/** CPU clock frequency in MHz*/
#define   MOTOR0_BLDC_SCALAR_CPU_FREQ                    (32.0F)
/** CCU module frequency in MHz*/
#define   MOTOR0_BLDC_SCALAR_CCU_FREQ                    (64.0F)

/***********************Base Parameters for Scaling****************************************/
/* Maximum current that can be measured with the power board. */
#define   MOTOR0_BLDC_SCALAR_MAX_CURRENT               (((1000.0F * ((MOTOR0_BLDC_SCALAR_VADC_REF_VOLTAGE) - ((MOTOR0_BLDC_SCALAR_CURRENT_AMPLIFIER_OFFSET) * (float)(MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN)))) / \
                                                 ((MOTOR0_BLDC_SCALAR_CURRENT_RSHUNT) * (MOTOR0_BLDC_SCALAR_CURRENT_AMPLIFIER_GAIN) * (float)(MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN))))
/*
 * Ratio with Base value represent 1PU in Q14 format with 2'S compliment
 * Speed, voltage & current variables are scaled to PU with base value
 * Maximum value with this format is 2PU without overflow
 * Enter value to get best resolution & dynamic range as per end needs.
 */
#define   MOTOR0_BLDC_SCALAR_BASE_SPEED_MECH_RPM       (MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED)
#define   MOTOR0_BLDC_SCALAR_BASE_VOLTAGE              (MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT)
#define   MOTOR0_BLDC_SCALAR_BASE_CURRENT              (MOTOR0_BLDC_SCALAR_MAX_CURRENT)


/**************************** CCU8 configuration parameters ************************************/
#define MOTOR0_BLDC_SCALAR_CCU8_PRESCALER            (0U)
#define MOTOR0_BLDC_SCALAR_CCU8_RESOLUTION        ((1000.0F/MOTOR0_BLDC_SCALAR_CCU_FREQ) * (float)((uint32_t)1 << ((uint32_t)MOTOR0_BLDC_SCALAR_CCU8_PRESCALER)))
#define MOTOR0_BLDC_SCALAR_CCU8_PERIOD_REG            ((((1000000000.0F/MOTOR0_BLDC_SCALAR_PWM_FREQ)/MOTOR0_BLDC_SCALAR_CCU8_RESOLUTION) /2.0F) - 1.0F)
#define MOTOR0_BLDC_SCALAR_CCU8_PERIOD            (1000000.0F / MOTOR0_BLDC_SCALAR_PWM_FREQ)

#define MOTOR0_BLDC_SCALAR_RISING_DEAD_TIME_COUNT    ((MOTOR0_BLDC_SCALAR_RISING_DEAD_TIME * 1000U) / MOTOR0_BLDC_SCALAR_CCU8_RESOLUTION)
#define MOTOR0_BLDC_SCALAR_FALLING_DEAD_TIME_COUNT   ((MOTOR0_BLDC_SCALAR_FALLING_DEAD_TIME * 1000U) / MOTOR0_BLDC_SCALAR_CCU8_RESOLUTION)
#define MOTOR0_BLDC_SCALAR_CURRENT_OFFSET_COUNT      ((MOTOR0_BLDC_SCALAR_CURRENT_TRIGGER_OFFSET * 1000.0F) / MOTOR0_BLDC_SCALAR_CCU8_RESOLUTION)
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U)
#define MOTOR0_BLDC_SCALAR_DEMAGNETIZATION_TIME_COUNT  ((MOTOR0_BLDC_SCALAR_DEMAGNET_BLANKING_TIME) / MOTOR0_BLDC_SCALAR_CCU8_PERIOD)
#endif /* #if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U)*/
#endif /* end of #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)) */

/************************ Systick configuration parameters  ***********************************************/
#define   MOTOR0_BLDC_SCALAR_SYSTICK_COUNT         (MOTOR0_BLDC_SCALAR_CPU_FREQ * MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD)

/************************* CCU4 configuration parameters *******************************************************/
#define MOTOR0_BLDC_SCALAR_CCU4_PRESCALER      (5U)
#define MOTOR0_BLDC_SCALAR_CCU4_RESOLUTION        ((1000.0F/MOTOR0_BLDC_SCALAR_CCU_FREQ) * (float)((uint32_t)1 << ((uint32_t)MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)))

#if (MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4 == 1U)
#define MOTOR0_BLDC_SCALAR_MCM_SYNCTRANSFER_PERIOD    (MOTOR0_BLDC_SCALAR_MCM_SYNCTRANSFER_TIME * MOTOR0_BLDC_SCALAR_CCU_FREQ)
#endif

#define MOTOR0_BLDC_SCALAR_PHASE_DELAY_PERIOD        ((MOTOR0_BLDC_SCALAR_PH_DELAY_TIME * 1000.0F) / MOTOR0_BLDC_SCALAR_CCU4_RESOLUTION)
#define MOTOR0_BLDC_SCALAR_PHASE_DELAY_COMPARE       ((MOTOR0_BLDC_SCALAR_BLANKING_TIME * 1000.0F) / MOTOR0_BLDC_SCALAR_CCU4_RESOLUTION)
#define MOTOR0_BLDC_SCALAR_SPEED_CONSTANT_AVG        ((1000000000.0F/MOTOR0_BLDC_SCALAR_CCU4_RESOLUTION) * 60.0F)


/************************* Scaling ************************************************************/
/* Scale to convert physical current (A) to target current in Q14*/
#define MOTOR0_BLDC_SCALAR_CURRENT_SCALE             (((float)BLDC_SCALAR_POW_15 * MOTOR0_BLDC_SCALAR_BASE_CURRENT)/(float)BLDC_SCALAR_POW_14)
/*Scale to convert physical voltage (volts) to target voltage in Q14 */
#define MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE             (((float)BLDC_SCALAR_POW_15 * (float)MOTOR0_BLDC_SCALAR_BASE_VOLTAGE)/(float)BLDC_SCALAR_POW_14)
/* Scale to convert physical speed (RPM) to target speed in Q14*/
#define MOTOR0_BLDC_SCALAR_SPEED_SCALE               (((float)BLDC_SCALAR_POW_15 * (float)MOTOR0_BLDC_SCALAR_BASE_SPEED_MECH_RPM)/(float)BLDC_SCALAR_POW_14)
/* Scale to convert electrical speed to target mechanical speed in Q14*/
#define MOTOR0_BLDC_SCALAR_SPEED_MECH_SCALE          (((BLDC_SCALAR_POW_15 * BLDC_SCALAR_POW_10)/((uint32_t)MOTOR0_BLDC_SCALAR_SPEED_SCALE * MOTOR0_BLDC_SCALAR_MOTOR_POLE_PAIRS)))
/* Scale to convert output of the control scheme to the CCU8 compare value */
#define MOTOR0_BLDC_SCALAR_AMPLITUDE_SCALE           (MOTOR0_BLDC_SCALAR_CCU8_PERIOD_REG/((float)BLDC_SCALAR_POW_14 / (float)BLDC_SCALAR_POW_14))
/* Scale to convert ADC voltage reading to target voltage in Q14*/
#define MOTOR0_BLDC_SCALAR_VOLTAGE_ADC_SCALE         ((((4.0F * (MOTOR0_BLDC_SCALAR_VADC_REF_VOLTAGE) * 100.0F) / \
                         ((MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT) * (MOTOR0_BLDC_SCALAR_VOLTAGE_DIVIDER_RATIO))) * (float)BLDC_SCALAR_POW_14))
/* Scale to convert ADC current reading to target current in Q14 */
#define MOTOR0_BLDC_SCALAR_CURRENT_ADC_SCALE         (((MOTOR0_BLDC_SCALAR_MAX_CURRENT * 4.0F) / (MOTOR0_BLDC_SCALAR_BASE_CURRENT)) * (MOTOR0_BLDC_SCALAR_VADC_REF_VOLTAGE/(MOTOR0_BLDC_SCALAR_VADC_REF_VOLTAGE - MOTOR0_BLDC_SCALAR_CURRENT_AMPLIFIER_OFFSET)) * (float)BLDC_SCALAR_POW_14)

/************************ Control scheme parameters ******************************************/
/***********************Speed Control ********************************************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
#define MOTOR0_BLDC_SCALAR_USER_RAMP_INITIAL_SPEED_T (((int32_t)(MOTOR0_BLDC_SCALAR_RAMP_INITIAL_VALUE * (float)BLDC_SCALAR_POW_15) /MOTOR0_BLDC_SCALAR_SPEED_SCALE))
#define MOTOR0_BLDC_SCALAR_USER_SPEED_SET_T          (((int32_t)(MOTOR0_BLDC_SCALAR_SPEED_SET * (float)BLDC_SCALAR_POW_15) /MOTOR0_BLDC_SCALAR_SPEED_SCALE))
#define MOTOR0_BLDC_SCALAR_SPEED_PI_OP               ((MOTOR0_BLDC_SCALAR_SPEED_PI_LIMIT * (float)BLDC_SCALAR_POW_14) / 100.0F)
#define MOTOR0_BLDC_SCALAR_RAMP_UP_RATE_T             (((((MOTOR0_BLDC_SCALAR_RAMP_UP_RATE * MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD) / 1000000.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_SPEED_SCALE) * (float)BLDC_SCALAR_POW_16)
#define MOTOR0_BLDC_SCALAR_RAMP_DOWN_RATE_T           (((((MOTOR0_BLDC_SCALAR_RAMP_DOWN_RATE * MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD) / 1000000.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_SPEED_SCALE) * (float)BLDC_SCALAR_POW_16)
#endif

/***********************Current Control *****************************************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
#define MOTOR0_BLDC_SCALAR_CURRENT_PI_OP              ((MOTOR0_BLDC_SCALAR_CURRENT_PI_LIMIT * (float)BLDC_SCALAR_POW_14) / 100.0F)
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
#define MOTOR0_BLDC_SCALAR_USER_RAMP_INITIAL_CURRENT_T  ((int32_t)((MOTOR0_BLDC_SCALAR_RAMP_INITIAL_VALUE * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_CURRENT_SCALE))
#define MOTOR0_BLDC_SCALAR_USER_CURRENT_SET_T           ((int32_t)((MOTOR0_BLDC_SCALAR_CURRENT_SET * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_CURRENT_SCALE))
#define MOTOR0_BLDC_SCALAR_RAMP_UP_RATE_T             (((((MOTOR0_BLDC_SCALAR_RAMP_UP_RATE * MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD) / 1000000.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_CURRENT_SCALE) * (float)BLDC_SCALAR_POW_16)
#define MOTOR0_BLDC_SCALAR_RAMP_DOWN_RATE_T           (((((MOTOR0_BLDC_SCALAR_RAMP_DOWN_RATE * MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD) / 1000000.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_CURRENT_SCALE) * (float)BLDC_SCALAR_POW_16)
#endif
#endif

/***********************Voltage Control *****************************************************/
#if (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL)
#define MOTOR0_BLDC_SCALAR_USER_RAMP_INITIAL_VOLTAGE_T  ((int32_t)(((MOTOR0_BLDC_SCALAR_RAMP_INITIAL_VALUE * (float)BLDC_SCALAR_POW_15)) / MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE))
#define MOTOR0_BLDC_SCALAR_USER_VOLTAGE_SET_T         ((int32_t)(((MOTOR0_BLDC_SCALAR_VOLTAGE_SET * (float)BLDC_SCALAR_POW_15)) / MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE))
#define MOTOR0_BLDC_SCALAR_RAMP_UP_RATE_T             (((((MOTOR0_BLDC_SCALAR_RAMP_UP_RATE * MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD) / 1000000.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE) * (float)BLDC_SCALAR_POW_16)
#define MOTOR0_BLDC_SCALAR_RAMP_DOWN_RATE_T           (((((MOTOR0_BLDC_SCALAR_RAMP_DOWN_RATE * MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD) / 1000000.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE) * (float)BLDC_SCALAR_POW_16)

#endif

/***********************Common ramp increment count for all the schemes ********************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP_DOWN_VOLTAGE_CLAMPING == 1U)
#define MOTOR0_BLDC_SCALAR_RAMP_DOWN_VOLTAGE_LIMIT_T  ((( MOTOR0_BLDC_SCALAR_RAMP_DOWN_VOLTAGE_LIMIT * (float)BLDC_SCALAR_POW_14 * (float)BLDC_SCALAR_POW_14)/(MOTOR0_BLDC_SCALAR_VOLTAGE_ADC_SCALE * 100.0F)))
#endif

/* Minimum amplitude */
#define MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE_T           ((MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE * (float)BLDC_SCALAR_POW_14) / 100.0F)
/* MAximum amplitude */
#define MOTOR0_BLDC_SCALAR_MAX_AMPLITUDE_T           ((MOTOR0_BLDC_SCALAR_MAX_AMPLITUDE * (float)BLDC_SCALAR_POW_14) / 100.0F)


/* target value of the max speed */
#define MOTOR0_BLDC_SCALAR_MAX_SPEED_T           ((MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED * BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_SPEED_SCALE)
#if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U)
#define MOTOR0_BLDC_SCALAR_MIN_SPEED_T               ((((MOTOR0_BLDC_SCALAR_MIN_SPEED * (float)MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED) / 100.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_SPEED_SCALE)
#endif

#define MOTOR0_BLDC_SCALAR_AMPLITUDE_HIGH_THRESHOLD_T      (((float)BLDC_SCALAR_POW_14 * MOTOR0_BLDC_SCALAR_AMPLITUDE_HIGH_THRESHOLD) / 100.0F)

/* target value for DC link voltage */
#define MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT_T      ((((int32_t)(MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT * (float)BLDC_SCALAR_POW_15))/(int32_t)MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE))

/**********************************ADC scaling *********************************************/
/* ADC POT scaling */
#define     MOTOR0_BLDC_SCALAR_POT_ADC_SCALE                   (4U)
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
#if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U)
#define MOTOR0_BLDC_SCALAR_MIN_ANALOG_INPUT_LOW_LIMIT_T  (((float)BLDC_SCALAR_POW_14 * MOTOR0_BLDC_SCALAR_MIN_ANALOG_INPUT_LOW_LIMIT) / 100.0F)
#else
#define MOTOR0_BLDC_SCALAR_MIN_ANALOG_INPUT_LOW_LIMIT_T  (((float)BLDC_SCALAR_POW_13 * MOTOR0_BLDC_SCALAR_MIN_ANALOG_INPUT_LOW_LIMIT) / 100.0F)
#endif
#endif

/*************************** Measurement *********************************************/

#ifndef MOTOR0_BLDC_SCALAR_VADC_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK
#define MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK (0U)
#else
#define MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK (MOTOR0_BLDC_SCALAR_VADC_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK)
#endif

/* Current amplifier offset */
#define MOTOR0_BLDC_SCALAR_AMPL_OFFSET_T             ((MOTOR0_BLDC_SCALAR_CURRENT_AMPLIFIER_OFFSET * (float)MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN * (float)BLDC_SCALAR_POW_12) / MOTOR0_BLDC_SCALAR_VADC_REF_VOLTAGE)


/******************************* Protection *******************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)
#define MOTOR0_BLDC_SCALAR_OVER_CURRENT_VADC_BOUND0_T ((uint32_t)((MOTOR0_BLDC_SCALAR_AMPL_OFFSET_T)-((MOTOR0_BLDC_SCALAR_OVER_CURRENT * (BLDC_SCALAR_POW_12 - (MOTOR0_BLDC_SCALAR_AMPL_OFFSET_T))) / MOTOR0_BLDC_SCALAR_MAX_CURRENT)))
#define MOTOR0_BLDC_SCALAR_OVER_CURRENT_VADC_BOUND1_T ((uint32_t)((MOTOR0_BLDC_SCALAR_AMPL_OFFSET_T)+((MOTOR0_BLDC_SCALAR_OVER_CURRENT * (BLDC_SCALAR_POW_12 - (MOTOR0_BLDC_SCALAR_AMPL_OFFSET_T))) / MOTOR0_BLDC_SCALAR_MAX_CURRENT)))
#define MOTOR0_BLDC_SCALAR_SHORTCIRCUIT_CURRENT_T     ((int32_t)((MOTOR0_BLDC_SCALAR_SHORTCIRCUIT_CURRENT * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_CURRENT_SCALE))
#define MOTOR0_BLDC_SCALAR_CURRENT_PROTECTION_COUNT   ((MOTOR0_BLDC_SCALAR_CURRENT_PROTECTION_TIME * 1000.0F) / MOTOR0_BLDC_SCALAR_CCU8_PERIOD)
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U)
#define MOTOR0_BLDC_SCALAR_MIN_DC_LINK_VOLTAGE_T     ((MOTOR0_BLDC_SCALAR_MIN_DC_LINK_VOLTAGE * (float)(BLDC_SCALAR_POW_14))/100.0F)
#define MOTOR0_BLDC_SCALAR_MAX_DC_LINK_VOLTAGE_T     ((MOTOR0_BLDC_SCALAR_MAX_DC_LINK_VOLTAGE * (float)(BLDC_SCALAR_POW_14))/100.0F)
#define MOTOR0_BLDC_SCALAR_VOLTAGE_PROTECTION_COUNT  ((MOTOR0_BLDC_SCALAR_VOLTAGE_PROTECTION_TIME * 1000.0F) / MOTOR0_BLDC_SCALAR_CCU8_PERIOD)
#endif


#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
#define MOTOR0_BLDC_SCALAR_STALL_DETECTION_COUNT    ((MOTOR0_BLDC_SCALAR_STALL_DETECTION_TIME * 1000.0F) / MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD)
#define MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE_FOR_STALL_T ((BLDC_SCALAR_POW_14 * MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE_FOR_STALL) / 100U)
#endif

/************************ Bootstrap **********************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
#define MOTOR0_BLDC_SCALAR_BOOTSTRAP_COUNT           ((MOTOR0_BLDC_SCALAR_BOOTSTRAP_TIME * 1000.0F) / MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD)
#endif

/************************ PT1 Filter Coefficients **********************************************************/
#if ((MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U))
#define MOTOR0_BLDC_SCALAR_VOLTCOMP_FILTER_Z       (((1.0F) - ((MOTOR0_BLDC_SCALAR_VOLTCOMP_FILTER_TIMECONST)/ \
                        ((MOTOR0_BLDC_SCALAR_VOLTCOMP_FILTER_TIMECONST) + ((MOTOR0_BLDC_SCALAR_CCU8_PERIOD)/(1000000.0F))))) * (float)BLDC_SCALAR_POW_16)
#endif

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U)
#define MOTOR0_BLDC_SCALAR_CURRENT_FILTER_Z        ((1.0F - (MOTOR0_BLDC_SCALAR_IDC_LINK_CURRENT_FILTER_TIMECONST/ \
                        (MOTOR0_BLDC_SCALAR_IDC_LINK_CURRENT_FILTER_TIMECONST + (MOTOR0_BLDC_SCALAR_CCU8_PERIOD/1000000.0F)))) * (float)BLDC_SCALAR_POW_16)
#endif
#endif

#if (((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) ||(MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U)))
#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_AVERAGE_CURRENT_FILTER == 1U)
#define MOTOR0_BLDC_SCALAR_IDC_AVERAGE_CURRENT_FILTER_Z        ((1.0F - (MOTOR0_BLDC_SCALAR_IDC_AVERAGE_CURRENT_FILTER_TIMECONST/ \
                        (MOTOR0_BLDC_SCALAR_IDC_AVERAGE_CURRENT_FILTER_TIMECONST + (MOTOR0_BLDC_SCALAR_CCU8_PERIOD/1000000.0F)))) * (float)BLDC_SCALAR_POW_16)
#endif
#endif

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_POTENTIOMETER_PT1_FILTER_ENABLE == 1U)
#define MOTOR0_BLDC_SCALAR_POTENTIOMETER_FILTER_Z  ((1.0F - (MOTOR0_BLDC_SCALAR_POTENTIOMETER_FILTER_TIMECONST/ \
                        (MOTOR0_BLDC_SCALAR_POTENTIOMETER_FILTER_TIMECONST + (MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD/1000000.0F)))) * (float)BLDC_SCALAR_POW_16)
#endif
#endif

/*************************** Hall pattern learning *********************************************/
#ifndef MOTOR0_BLDC_SCALAR_ENABLE_HALL_LEARNING
#define MOTOR0_BLDC_SCALAR_HALL_LEARNING (0U)
#else
#define MOTOR0_BLDC_SCALAR_HALL_LEARNING (MOTOR0_BLDC_SCALAR_ENABLE_HALL_LEARNING)
#endif

#ifndef MOTOR0_BLDC_SCALAR_ENABLE_REVERSE_HALL
#define MOTOR0_BLDC_SCALAR_REVERSE_HALL (0U)
#else
#define MOTOR0_BLDC_SCALAR_REVERSE_HALL (MOTOR0_BLDC_SCALAR_ENABLE_REVERSE_HALL)
#endif


#if ((MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL) && (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U))
#define MOTOR0_BLDC_SCALAR_HALL_LEARNING_OL_DUTY          ((((MOTOR0_BLDC_SCALAR_OPEN_LOOP_VOLTAGE * MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT)/100.0F) * (float)BLDC_SCALAR_POW_15) / MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE)
#define MOTOR0_BLDC_SCALAR_HALL_LEARNING_OL_COUNT         ((60.0F *(1000000.0F/MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD))/ (6.0F * ((MOTOR0_BLDC_SCALAR_OPEN_LOOP_SPEED * (float)MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED)/ 100.0F)))
#endif
/*************************** Catch free running *********************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
#define MOTOR0_BLDC_SCALAR_CATCH_FREE_MAX_LIMIT_T   (((((MOTOR0_BLDC_SCALAR_CATCH_FREE_MAX_LIMIT * (float)MOTOR0_BLDC_SCALAR_MOTOR_NO_LOAD_SPEED) /100.0F) * (float)BLDC_SCALAR_POW_15) /MOTOR0_BLDC_SCALAR_SPEED_SCALE))
#define MOTOR0_BLDC_SCALAR_CATCH_FREE_DETECTION_TIMEOUT_COUNT         ((MOTOR0_BLDC_SCALAR_CATCH_FREE_DETECTION_TIMEOUT * 1000.0F) / MOTOR0_BLDC_SCALAR_SYSTICK_PERIOD)
#endif

#endif /* BLDC_SCALAR_DERIVED_PARAM_H_ */
