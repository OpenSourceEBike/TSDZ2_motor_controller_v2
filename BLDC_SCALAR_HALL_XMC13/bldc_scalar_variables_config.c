/**
 * @file bldc_scalar_variables_config.c
 * @brief Data structure initialization as per user configurations
 * @date 2016-08-09
 *
 **********************************************************************************************************************
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
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "../ControlModule/bldc_scalar_control_hall.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
/************************START : Hall Learning ***********************************/
#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
/** Hall learning data structure*/
BLDC_SCALAR_HALL_LEARNING_t Motor0_BLDC_SCALAR_HallLearning =
{
  .ol_pattup_count   = (uint32_t)MOTOR0_BLDC_SCALAR_HALL_LEARNING_OL_COUNT,
  .ol_count          = (uint32_t)BLDC_SCALAR_HALL_LEARNING_OPEN_LOOP_COUNT,
  .adapt_algoindex   = (uint32_t)0,
  .capt_outpatt      = {(uint16_t)0},
  .amplitude         = (uint16_t)MOTOR0_BLDC_SCALAR_HALL_LEARNING_OL_DUTY,
  .capt_hallpatt     = {(uint8_t)0},
  .ol_iter_count     = (uint8_t)0,
  .ol_arrayindex     = (uint8_t)0,
  .openloop_mc_pattern  = {
                            0x0U, WH_VL_UOFF, WOFF_VL_UH, WL_VOFF_UH,
                            WL_VH_UOFF, WOFF_VH_UL, WH_VOFF_UL, 0x00U,
                            0x0U, WH_VOFF_UL, WOFF_VH_UL, WL_VH_UOFF,
                            WL_VOFF_UH, WOFF_VL_UH, WH_VL_UOFF, 0x00U
                          },
};
#endif    /* end of #if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U) */
/************************END : Hall Learning ***********************************/

/************************START : Speed Control ***********************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/** Speed control PI */
BLDC_SCALAR_PI_CONTROLLER_t Motor0_BLDC_SCALAR_SpeedControl_PI =
{
  .uk_limit_min = -((int32_t)MOTOR0_BLDC_SCALAR_SPEED_PI_OP),
  .uk_limit_max = (int32_t)MOTOR0_BLDC_SCALAR_SPEED_PI_OP,
  .kp           = (uint16_t)MOTOR0_BLDC_SCALAR_SPEED_KP,
  .ki           = (uint16_t)MOTOR0_BLDC_SCALAR_SPEED_KI,
  .scale_kpki   = (uint8_t)MOTOR0_BLDC_SCALAR_SPEED_PI_SCALE,
  .sat_state    = 1U
};
#endif   /* end of #if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL)) */
/************************END : Speed Control ***********************************/

/************************START : Current Control ***********************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/** Current control PI */
BLDC_SCALAR_PI_CONTROLLER_t Motor0_BLDC_SCALAR_CurrentControl_PI =
{
  .uk_limit_min = -((int32_t)MOTOR0_BLDC_SCALAR_CURRENT_PI_OP),
  .uk_limit_max = (int32_t)MOTOR0_BLDC_SCALAR_CURRENT_PI_OP,
  .kp           = (uint16_t)MOTOR0_BLDC_SCALAR_CURRENT_KP,
  .ki           = (uint16_t)MOTOR0_BLDC_SCALAR_CURRENT_KI,
  .scale_kpki   = (uint8_t)MOTOR0_BLDC_SCALAR_CURRENT_PI_SCALE,
  .sat_state    = 1U
};
#endif   /* end of #if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL)) */
/************************END : Current Control ***********************************/

/************************START : Voltage Compensation Filter ***********************************/
#if ((MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U))
#if ((MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION_FILTER == 1U))
/** Voltage compensation low pass filter*/
BLDC_SCALAR_PT1_FILTER_t  Motor0_BLDC_SCALAR_PT1_VoltageComp =
{
  .z1      = (int32_t)MOTOR0_BLDC_SCALAR_VOLTCOMP_FILTER_Z,
  .y_max   = (int32_t)BLDC_SCALAR_PT1_VOLT_COMP_MAX_LIMIT,
  .y_min   = (int32_t)BLDC_SCALAR_PT1_VOLT_COMP_MIN_LIMIT,
  .pt1_buf = (int32_t)BLDC_SCALAR_PT1_VOLT_COMP_BUF_VAL
};
#endif
#endif   /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U) */
/************************END : Voltage Compensation Filter ***********************************/

/************************START : Direct current filter ***********************************/
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U)
/** Direct current low pass filter */
BLDC_SCALAR_PT1_FILTER_t  Motor0_BLDC_SCALAR_PT1_DirectCurrent =
{
  .z1      = (int32_t)MOTOR0_BLDC_SCALAR_CURRENT_FILTER_Z,
  .y_max   = (int32_t)BLDC_SCALAR_PT1_LIMIT,
  .y_min   = (int32_t)0,
  .pt1_buf = (int32_t)0
};
#endif
#endif    /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U) */

/************************END : Direct current filter ***********************************/

/************************START : Average current filter ***********************************/
#if (((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U)))
#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_AVERAGE_CURRENT_FILTER == 1U)
/** Average current low pass filter */
BLDC_SCALAR_PT1_FILTER_t  Motor0_BLDC_SCALAR_PT1_AverageCurrent =
{
  .z1      = (int32_t)MOTOR0_BLDC_SCALAR_IDC_AVERAGE_CURRENT_FILTER_Z,
  .y_max   = (int32_t)BLDC_SCALAR_PT1_LIMIT,
  .y_min   = (int32_t)-BLDC_SCALAR_PT1_LIMIT,
  .pt1_buf = (int32_t)0
};
#endif
#endif
/************************END : Average current filter ***********************************/


#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_POTENTIOMETER_PT1_FILTER_ENABLE == 1U)
/** Potentiometer low pass filter */
BLDC_SCALAR_PT1_FILTER_t Motor0_BLDC_SCALAR_PT1_Potentiometer =
{
  .z1      = (int32_t)MOTOR0_BLDC_SCALAR_POTENTIOMETER_FILTER_Z,
  .y_max   = (int32_t)BLDC_SCALAR_PT1_LIMIT,
  .y_min   = (int32_t)-BLDC_SCALAR_PT1_LIMIT,
  .pt1_buf = (int32_t)0
};
#endif
#endif

/************************START : Ramp Generator ***********************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
/** Linear Ramp */
BLDC_SCALAR_RAMP_t Motor0_BLDC_SCALAR_Ramp =
{
  .set_value             = 0,
  .ramp_up_rate          = (uint32_t)(MOTOR0_BLDC_SCALAR_RAMP_UP_RATE_T),
  .ramp_down_rate        = (uint32_t)(MOTOR0_BLDC_SCALAR_RAMP_DOWN_RATE_T),
};
#endif   /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */
/************************END : Ramp Generator ***********************************/

/************************START : Block commutation PWM generator ***********************************/
/** Data structure initialization of PWM_BC module */
BLDC_SCALAR_PWM_BC_t Motor0_BLDC_SCALAR_PWM_BC =
{
  .ccu8_handle_ptr = &Motor0_BLDC_SCALAR_CCU8_PWM_Config,
#if (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE)
  .shadow_modulation_ptr    = Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod,
#elif (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_LOWSIDE)
  .shadow_modulation_ptr    = Motor0_BLDC_SCALAR_PWM_BC_LsShadowMod,
#elif (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE_SYNCHRECTI)
  .shadow_modulation_ptr    = Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod_SyncRect,
#endif

#if (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE)
  .immediate_modulation_ptr    = Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod,
#elif (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_LOWSIDE)
  .immediate_modulation_ptr    = Motor0_BLDC_SCALAR_PWM_BC_LsImmediateMod,
#elif (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE_SYNCHRECTI)
  .immediate_modulation_ptr    = Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod_SyncRect,
#endif

  .modulation_type        = (PWM_BC_MOD_t)MOTOR0_BLDC_SCALAR_MODULATION,

  .ph_cmpval              = {0U},
  .ph_mcpatt_compmask     = {(uint16_t)((uint32_t)0x1U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)),
      (uint16_t)((uint32_t)0x1U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) ,
      (uint16_t)((uint32_t)0x1U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM))},

  .ph_bothside_compmask   = { (uint16_t)((uint32_t)0x3U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)),
      (uint16_t)((uint32_t)0x3U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) ,
      (uint16_t)((uint32_t)0x3U << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)) },

  .amplitude_scale        = ((uint16_t)MOTOR0_BLDC_SCALAR_AMPLITUDE_SCALE) + 1U,
  .inverter_pin           = (PWM_BC_INVERTERPINLEVEL_t)MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF
};
/************************END : Block commutation PWM generator ***********************************/

/************************START : Speed and Position ***********************************/
/** Data structure initialization of SPEED_POS_HALL module */
BLDC_SCALAR_SPEED_POS_HALL_t Motor0_BLDC_SCALAR_SPEED_POS_HALL =
{
  .index                  = 0U,
  .speedindex             = 0U,
  .capval                 = (uint32_t)MOTOR0_BLDC_SCALAR_SPEED_CONSTANT_AVG,
  .speedcheck             = 0U,
  .captureval             = {0U,0U,0U,0U,0U,0U},
  .speedaccum             = 0U,
  .speed_constant         = (uint32_t) MOTOR0_BLDC_SCALAR_SPEED_CONSTANT_AVG,
};
/************************END : Speed and Position ***********************************/

/************************START : Current Measurement ***********************************/
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) ||(MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U))
/** DC link current measurement */
BLDC_SCALAR_CURRENT_MEASUREMENT_t Motor0_BLDC_SCALAR_CurrentMeasurement =
{
  .direct_dc_amplifier_offset     = (int32_t)MOTOR0_BLDC_SCALAR_AMPL_OFFSET_T,
  .avg_dc_amplifier_offset        = (int32_t)MOTOR0_BLDC_SCALAR_AMPL_OFFSET_T,
  .current_adc_scale              = (uint32_t)MOTOR0_BLDC_SCALAR_CURRENT_ADC_SCALE,
#if (MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)
  .short_circuit_current          = (int32_t)MOTOR0_BLDC_SCALAR_SHORTCIRCUIT_CURRENT_T,
#endif
  .amplitude                      = &Motor0_BLDC_SCALAR.amplitude,
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U)
  .demagnetization_blanking_count = (uint32_t)MOTOR0_BLDC_SCALAR_DEMAGNETIZATION_TIME_COUNT,
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U) */
#endif /* #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)) */
};
#endif
/************************END : Current Measurement ***********************************/

/************************START : Control Schemes ***********************************/

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_VOLTAGE_CTRL))
/** Voltage control */
BLDC_SCALAR_VOLTAGE_CONTROL_t Motor0_BLDC_SCALAR_VoltageControl =
{
  .user_start_voltage_set       = (int32_t)MOTOR0_BLDC_SCALAR_USER_RAMP_INITIAL_VOLTAGE_T,
  .user_voltage_set             = (int32_t)MOTOR0_BLDC_SCALAR_USER_VOLTAGE_SET_T
};
#endif

/***********************************************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/** Speed control */
BLDC_SCALAR_SPEED_CONTROL_t Motor0_BLDC_SCALAR_SpeedControl =
{
  .user_start_speed_set         = (int32_t)MOTOR0_BLDC_SCALAR_USER_RAMP_INITIAL_SPEED_T,
  .user_speed_set               = (int32_t)MOTOR0_BLDC_SCALAR_USER_SPEED_SET_T
};
#endif

/***********************************************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
/** Current control */
BLDC_SCALAR_CURRENT_CONTROL_t Motor0_BLDC_SCALAR_CurrentControl =
{
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
  .user_start_current_set       = (int32_t)MOTOR0_BLDC_SCALAR_USER_RAMP_INITIAL_CURRENT_T,
  .user_current_set             = (int32_t)MOTOR0_BLDC_SCALAR_USER_CURRENT_SET_T,
#endif
  .ref_current                  = 0,
  .fdbk_current                 = 0
};
#endif

/***********************************************************/
/************************END : Control Schemes ***********************************/

/************************START : BLDC SCALAR ***********************************/
/** Hall sensor feedback */
BLDC_SCALAR_HALL_t Motor0_BLDC_SCALAR_Hall =
{
#if (MOTOR0_BLDC_SCALAR_HALL_POSITIVE_DIR_SEQ == BLDC_SCALAR_HALL_SEQ_1)
  .hall_pattern           = {
                              (uint8_t)BLDC_SCALAR_HALL_MCM(0,0),(uint8_t)BLDC_SCALAR_HALL_MCM(3,1),(uint8_t)BLDC_SCALAR_HALL_MCM(6,2),(uint8_t)BLDC_SCALAR_HALL_MCM(2,3),
                              (uint8_t)BLDC_SCALAR_HALL_MCM(5,4),(uint8_t)BLDC_SCALAR_HALL_MCM(1,5),(uint8_t)BLDC_SCALAR_HALL_MCM(4,6),(uint8_t)BLDC_SCALAR_HALL_MCM(0,0),
                              (uint8_t)BLDC_SCALAR_HALL_MCM(0,0),(uint8_t)BLDC_SCALAR_HALL_MCM(5,1),(uint8_t)BLDC_SCALAR_HALL_MCM(3,2),(uint8_t)BLDC_SCALAR_HALL_MCM(1,3),
                              (uint8_t)BLDC_SCALAR_HALL_MCM(6,4),(uint8_t)BLDC_SCALAR_HALL_MCM(4,5),(uint8_t)BLDC_SCALAR_HALL_MCM(2,6),(uint8_t)BLDC_SCALAR_HALL_MCM(0,0)
                          },
#else
  .hall_pattern           = {
                              (uint8_t)BLDC_SCALAR_HALL_MCM(0,0),(uint8_t)BLDC_SCALAR_HALL_MCM(5,1),(uint8_t)BLDC_SCALAR_HALL_MCM(3,2),(uint8_t)BLDC_SCALAR_HALL_MCM(1,3),
                              (uint8_t)BLDC_SCALAR_HALL_MCM(6,4),(uint8_t)BLDC_SCALAR_HALL_MCM(4,5),(uint8_t)BLDC_SCALAR_HALL_MCM(2,6),(uint8_t)BLDC_SCALAR_HALL_MCM(0,0),
                              (uint8_t)BLDC_SCALAR_HALL_MCM(0,0),(uint8_t)BLDC_SCALAR_HALL_MCM(3,1),(uint8_t)BLDC_SCALAR_HALL_MCM(6,2),(uint8_t)BLDC_SCALAR_HALL_MCM(2,3),
                              (uint8_t)BLDC_SCALAR_HALL_MCM(5,4),(uint8_t)BLDC_SCALAR_HALL_MCM(1,5),(uint8_t)BLDC_SCALAR_HALL_MCM(4,6),(uint8_t)BLDC_SCALAR_HALL_MCM(0,0),
                          },
#endif
#if ((MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U))
  .hall_learning_flag           = MOTOR0_BLDC_SCALAR_HALL_LEARNING,
#endif
};

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
BLDC_SCALAR_HALL_CATCH_FREE_t Motor0_BLDC_SCALAR_HALL_CatchFree =
{
  .cf_max_speed                 = (int32_t)MOTOR0_BLDC_SCALAR_CATCH_FREE_MAX_LIMIT_T,
  .cf_detection_timeout         = (uint32_t)MOTOR0_BLDC_SCALAR_CATCH_FREE_DETECTION_TIMEOUT_COUNT,
};
#endif

/** BLDC_SCALAR handle - contains the control parameters */
BLDC_SCALAR_t Motor0_BLDC_SCALAR =
{
  .msm_state                    = BLDC_SCALAR_MSM_STOP,
  .error_status                 = (uint32_t)0,

  .period                       = (uint16_t)MOTOR0_BLDC_SCALAR_CCU8_PERIOD_REG,
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) && (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U))
  .motor_set_direction          = MOTOR0_BLDC_SCALAR_MOTOR_DIRECTION,
#else
  .motor_set_direction          = BLDC_SCALAR_POSITIVE_DIR,
#endif
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  .min_analogip_val             = (int32_t)MOTOR0_BLDC_SCALAR_MIN_ANALOG_INPUT_LOW_LIMIT_T,
#endif
  .amplitude_high_threshold     = (uint32_t)MOTOR0_BLDC_SCALAR_AMPLITUDE_HIGH_THRESHOLD_T,
  .min_amplitude_configured     = (uint32_t)MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE_T,
  .min_amplitude                = (uint32_t)MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE_T,
  .max_amplitude                = (uint32_t)MOTOR0_BLDC_SCALAR_MAX_AMPLITUDE_T,
#if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U)
  .control_loop_exec_rate       = (uint32_t)MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE,
  .control_loop_exec_count      = 1U,
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U)
  .min_speed                    = (int32_t)MOTOR0_BLDC_SCALAR_MIN_SPEED_T,
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP_DOWN_VOLTAGE_CLAMPING == 1U)
  .max_dc_link_voltage          = (((uint32_t)MOTOR0_BLDC_SCALAR_RAMP_DOWN_VOLTAGE_LIMIT_T * (uint32_t)MOTOR0_BLDC_SCALAR_VOLTAGE_ADC_SCALE) >> BLDC_SCALAR_SHIFT_14),
#endif
  .nominal_dc_link_voltage      = (uint32_t)MOTOR0_BLDC_SCALAR_NOMINAL_DC_LINK_VOLT_T,
#if (MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)
  .overcurrent_count            = (uint32_t)MOTOR0_BLDC_SCALAR_CURRENT_PROTECTION_COUNT,
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U)
  .over_under_voltage_count     = (uint32_t)MOTOR0_BLDC_SCALAR_VOLTAGE_PROTECTION_COUNT,
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
  .stall_detection_count        = (uint32_t)MOTOR0_BLDC_SCALAR_STALL_DETECTION_COUNT,
  .stall_min_amplitude          = (uint32_t)MOTOR0_BLDC_SCALAR_MIN_AMPLITUDE_FOR_STALL_T,
  .stall_time_diff_ratio        = (uint32_t)(MOTOR0_BLDC_SCALAR_STALL_TIME_DIFF_RATIO * BLDC_SCALAR_POW_4),
  .stall_check                  = 1U,
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
  .bootstrap_count              = (uint32_t)MOTOR0_BLDC_SCALAR_BOOTSTRAP_COUNT,
#endif
#if (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U)
  .over_voltage_limit           = (int32_t)MOTOR0_BLDC_SCALAR_MAX_DC_LINK_VOLTAGE_T,
  .under_voltage_limit          = (int32_t)MOTOR0_BLDC_SCALAR_MIN_DC_LINK_VOLTAGE_T,
#endif

  .speed_scale                  = (uint32_t)MOTOR0_BLDC_SCALAR_SPEED_SCALE,
  .current_scale                = (uint32_t)MOTOR0_BLDC_SCALAR_CURRENT_SCALE,
  .voltage_scale                = (uint32_t)MOTOR0_BLDC_SCALAR_VOLTAGE_SCALE,
  .speed_mech_scale             = (uint32_t)MOTOR0_BLDC_SCALAR_SPEED_MECH_SCALE,

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  .speedcontrol_rate           = MOTOR0_BLDC_SCALAR_SPEED_CTRL_EXECUTION_RATE,
#endif
#if (MOTOR0_BLDC_SCALAR_HALL_POSITIVE_DIR_SEQ == BLDC_SCALAR_HALL_SEQ_1)
  .mc_pattern             = {
                              /* high side synchronous rectification modulation - patterns are initialized in Init function*/
                              {
                                0x0U
                              },
                              /* high side modulation */
                              {
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)0x00U,
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)0x00U
                              },
                              /* low side modulation */
                              {
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)0x00U,
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)0x00U
                              }
             },
#else
  .mc_pattern             = {
                              /* high side synchronous rectification modulation - patterns are initialized in Init function*/
                              {
                                0x0U
                              },
                              /* high side modulation */
                              {
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)0x00U,
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)0x00U
                              },
                              /* low side modulation */
                              {
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)0x00U,
                                  (uint16_t)0x0U,                 (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_D, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_B, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_C,
                                  (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_F, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_E, (uint16_t)MOTOR0_BLDC_SCALAR_MC_PAT_A, (uint16_t)0x00U
                              }
             },
#endif

};

/************************END : BLDC SCALAR ***********************************/


