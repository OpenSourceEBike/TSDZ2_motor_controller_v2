/**
 * @file vadc.c
 * @brief VADC initialization for selected channels
 * -# DC link current
 * -# Average DC link current
 * -# DC link voltage
 * -# Potentiometer
 * -# User defined voltage
 * @date 2016-09-08
 *
 *********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with
 * Infineon Technologies AG dave@infineon.com).
 *********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2016-05-25:
 *     - Initial version <br>
 *
 * @endcond
 *
 */

/**********************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************/
#include "vadc.h"

/**********************************************************************************************************
 * MACROS
 **********************************************************************************************************/
/** Trigger dummy conversion for 9* 2000 times.*/
#define VADC_DUMMY_CONVERSION_COUNTER (18000U)
/** Delay cycles to complete startup calibration */
#define VADC_CALIBRATION_CYCLE_DELAY  (20U)
/**********************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************/

/**************************** Global ADC configuration ***************************************************/
/**
 * This structure contains the VADC global module configuration.
 */
const XMC_VADC_GLOBAL_CONFIG_t Motor0_BLDC_SCALAR_VADC_GLOBAL_config =
{
  .boundary0                      = 0U, /* Global boundary 0  */
  .boundary1                      = 0U, /* Global boundary 1  */
  .data_reduction_control         = 0U, /* Data Reduction disabled*/
  .wait_for_read_mode             = 0U, /* GLOBRES Register will not be overwritten until the previous value is read*/
  .event_gen_enable               = 0U, /* Result Event from GLOBRES is disabled*/
  .disable_sleep_mode_control     = 0U  /* Sleep mode is enabled*/
};

/**************************** Group ADC configuration ***************************************************/
  /**
   * This structure contains the Group class - 0 Configuration.
   */
const XMC_VADC_GROUP_CLASS_t Motor0_BLDC_SCALAR_VADC_GROUP_class0 =
{
  .sample_time_std_conv            = 1U,                /*The Sample time is (3*tadci)*/
  .conversion_mode_standard        = (uint32_t) XMC_VADC_CONVMODE_12BIT,     /* 12bit conversion Selected*/
  .sampling_phase_emux_channel     = 0U,                /*The Sample time is (2*tadci)*/
  .conversion_mode_emux            = (uint32_t) XMC_VADC_CONVMODE_12BIT      /* 12bit conversion Selected*/
};  /* !<ICLASS-0 */

/**************************** Queue configuration *******************************************************/
#if(VADC_ENABLE_GROUP_QUEUE_0 == 1U)
/**
 * ADC QUEUE LLD Handle for configuring the ADC_QUEUE_0
 */
const XMC_VADC_QUEUE_CONFIG_t Motor0_BLDC_SCALAR_VADC_QUEUE_0_cfg =
{
  .conv_start_mode  = (uint32_t) XMC_VADC_STARTMODE_WFS,       /* Conversion start mode WFS/CIR/CNR*/
  .req_src_priority = (uint32_t) XMC_VADC_GROUP_RS_PRIORITY_1, /*The queue request source priority */
  .trigger_signal   = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_TRIGGER_SIGNAL,  /*If trigger needed the signal input*/
  .trigger_edge     = (uint32_t) XMC_VADC_TRIGGER_EDGE_RISING,   /*Trigger edge needed if trigger enabled*/
  .gate_signal      = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_GATE_SIGNAL,     /*If gating needed the signal input*/
  .timer_mode       = 0U,                            /* Disabled equi-distant sampling*/
  .external_trigger = 1U                             /*External trigger Enabled/Disabled*/
};
#endif

#if(VADC_ENABLE_GROUP_QUEUE_1 == 1U)
/**
 * ADC QUEUE LLD Handle for configuring the ADC_QUEUE_1
 */
const XMC_VADC_QUEUE_CONFIG_t Motor0_BLDC_SCALAR_VADC_QUEUE_1_cfg =
{
  .conv_start_mode  = (uint32_t)XMC_VADC_STARTMODE_WFS,       /* Conversion start mode WFS/CIR/CNR*/
  .req_src_priority = (uint32_t)XMC_VADC_GROUP_RS_PRIORITY_1, /*The queue request source priority */
  .trigger_signal   = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_TRIGGER_SIGNAL,  /*If trigger needed the signal input*/
  .trigger_edge     = (uint32_t)XMC_VADC_TRIGGER_EDGE_RISING,   /*Trigger edge needed if trigger enabled*/
  .gate_signal      = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_GATE_SIGNAL,     /*If gating needed the signal input*/
  .timer_mode       = 0U,                            /* Disabled equidistant sampling*/
  .external_trigger = 1U                             /*External trigger Enabled/Disabled*/
};
#endif

#if(VADC_ENABLE_GROUP_QUEUE_2 == 1U)
/**
 * ADC QUEUE LLD Handle for configuring the ADC_QUEUE_2
 */
const XMC_VADC_QUEUE_CONFIG_t Motor0_BLDC_SCALAR_VADC_QUEUE_2_cfg =
{
  .conv_start_mode  = (uint32_t) XMC_VADC_STARTMODE_WFS,       /* Conversion start mode WFS/CIR/CNR*/
  .req_src_priority = (uint32_t) XMC_VADC_GROUP_RS_PRIORITY_1, /*The queue request source priority */
  .trigger_signal   = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_TRIGGER_SIGNAL,  /*If trigger needed the signal input*/
  .trigger_edge     = (uint32_t) XMC_VADC_TRIGGER_EDGE_NONE,   /*Trigger edge needed if trigger enabled*/
  .gate_signal      = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_GATE_SIGNAL,     /*If gating needed the signal input*/
  .timer_mode       = 0U,                            /* Disabled equi-distant sampling*/
  .external_trigger = 1U                             /*External trigger Enabled/Disabled*/
};
#endif

#if(VADC_ENABLE_GROUP_QUEUE_3 == 1U)
/**
 * ADC QUEUE LLD Handle for configuring the ADC_QUEUE_1
 */
const XMC_VADC_QUEUE_CONFIG_t Motor0_BLDC_SCALAR_VADC_QUEUE_3_cfg =
{
  .conv_start_mode  = (uint32_t) XMC_VADC_STARTMODE_WFS,       /* Conversion start mode WFS/CIR/CNR*/
  .req_src_priority = (uint32_t) XMC_VADC_GROUP_RS_PRIORITY_1, /*The queue request source priority */
  .trigger_signal   = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_TRIGGER_SIGNAL,  /*If trigger needed the signal input*/
  .trigger_edge     = (uint32_t) XMC_VADC_TRIGGER_EDGE_NONE,   /*Trigger edge needed if trigger enabled*/
  .gate_signal      = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_GATE_SIGNAL,     /*If gating needed the signal input*/
  .timer_mode       = (uint32_t) 0,                            /* Disabled equidistant sampling*/
  .external_trigger = (uint32_t) 1                             /*External trigger Enabled/Disabled*/
};
#endif

/**************************** Queue configuration *******************************************************/

/* Queue Entries,Channel and result configuration ... */
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
/** Queue entry for DC link current measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_IDCLink_queue_entry =
{
  .channel_num        = MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_CH_NUM,    /**< VADC Channel number */
  .external_trigger   = (uint32_t) 1,                        /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                        /**< Generates a queue request source event */
  .refill_needed      = (uint32_t)1,              /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for DC link current measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_IDCLink_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,   /**< Global ICLASS 0 selected. */
#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U))
  #if (MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_DIRECT_CURRENT)
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_OUTBOUND,       /**< Outbound channel event */
  #else
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,               /**< Channel Event disabled. */
  #endif /* end of #if (MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_DIRECT_CURRENT) */
#else
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,          /**< Channel Event disabled. */
#endif /* #if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)) */
  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_RES_REG_NUM, /**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,         /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1,                                      /**< Alias feature not selected. */
  .lower_boundary_select    = (uint32_t)XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,          /**< Group boundary 0 is used for limit checking */
  .upper_boundary_select    = (uint32_t)XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND1           /**< Group boundary 1 is used for limit checking */
};

/** Result register configuration for DC link current measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_IDCLink_Res_handle =
{
  .data_reduction_control  = (uint8_t)  0,                                      /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode      = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo            = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable        = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)
/** Queue entry for DC link average current measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_IDCAverage_queue_entry =
{
  .channel_num        = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM,              /**< VADC Channel number */
  .external_trigger   = (uint32_t) 0,                                /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                                     /**< Generates a queue request source event */
  .refill_needed      = (uint32_t)1,                                                /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for DC link average current measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_IDCAverage_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,       /**< Global ICLASS 0 selected. */
#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U))
  #if (MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_AVG_CURRENT)
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_OUTBOUND,            /**< Outbound Channel Event  */
  #else
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,               /**< Channel Event disabled. */
  #endif /* end of #if (MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE == BLDC_SCALAR_IDC_AVG_CURRENT) */
#else
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,               /**< Channel Event disabled. */
#endif /* end of #if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U)) */
  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_RES_REG_NUM,   /**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,                /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1,                                           /**< Alias feature not selected. */
  .lower_boundary_select    = (uint32_t)XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,          /**< Group boundary 0 is used for limit checking */
  .upper_boundary_select    = (uint32_t)XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND1           /**< Group boundary 1 is used for limit checking */
};

/* Result register configuration for DC link average current measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_IDCAverage_Res_handle =
{
  .data_reduction_control  = (uint8_t)  0,                                      /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode      = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo            = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable        = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
/** Queue entry for DC link voltage measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_VDCLink_queue_entry =
{
  .channel_num        = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_CH_NUM,  /**< VADC Channel number */
  .external_trigger   = (uint32_t) 0,                      /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                      /**< Generates a queue request source event */
  .refill_needed      = (uint32_t)1,                                 /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for DC link voltage measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_VDCLink_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,   /**< Global ICLASS 0 selected. */

  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,          /**< Channel Event disabled. */

  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_RES_REG_NUM, /**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,           /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1,                                      /**< Alias feature not selected. */
  .lower_boundary_select    = 0U,                                               /**< Group boundary 0 is used for limit checking */
  .upper_boundary_select    = 0U                                                /**< Group boundary 1 is used for limit checking */

};

/** Result register configuration for DC link voltage measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_VDCLink_Res_handle =
{
  .data_reduction_control  = (uint8_t)  0,                                    /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode     = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo          = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable      = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
/** Queue entry for Analog input-POT measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_AnalogInput_queue_entry =
{
  .channel_num        = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_CH_NUM,            /**< VADC Channel number */
  .external_trigger   = (uint32_t) 0,                               /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                                    /**< Generates a queue request source event */
  .refill_needed      = (uint32_t)1,                                               /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for Analog input-POT measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_AnalogInput_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,       /**< Global ICLASS 0 selected. */
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,              /**< Channel Event disabled. */
  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_RES_REG_NUM, /**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,               /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1                                           /**< Alias feature not selected. */
};

/** Result register configuration for Analog input-POT measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_AnalogInput_Res_handle =
{
  .data_reduction_control  = (uint8_t)  0,                                      /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode     = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo          = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable      = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U)
/** Queue entry for user defined channel 1 measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef1_queue_entry =
{
  .channel_num        = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_CH_NUM,        /**< VADC Channel number */
  .external_trigger   = (uint32_t) 0,                                       /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                                       /**< Generates a queue request source event */
  .refill_needed      = (uint32_t) 1,                                       /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for User defined -1 measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef1_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,   /**< Global ICLASS 0 selected. */
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,          /**< Channel Event disabled. */
  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_RES_REG_NUM,/**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,           /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1                                       /**< Alias feature not selected. */
};

/** Result register configuration for User defined-1 measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef1_Res_handle =
{
  .data_reduction_control  = (uint32_t)  0,                                      /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode      = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo            = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable        = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U)
/** Queue entry for user defined channel 2 measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef2_queue_entry =
{
  .channel_num        = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_CH_NUM,        /**< VADC Channel number */
  .external_trigger   = (uint32_t) 0,                                       /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                                       /**< Generates a queue request source event */
  .refill_needed      = (uint32_t) 1,                                       /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for User defined -2 measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef2_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,   /**< Global ICLASS 0 selected. */
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,          /**< Channel Event disabled. */
  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_RES_REG_NUM,/**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,           /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1                                       /**< Alias feature not selected. */
};

/** Result register configuration for User defined-2 measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef2_Res_handle =
{
  .data_reduction_control  = (uint32_t)  0,                                      /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode      = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo            = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable        = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U)
/** Queue entry for user defined channel 3 measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef3_queue_entry =
{
  .channel_num        = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_CH_NUM,        /**< VADC Channel number */
  .external_trigger   = (uint32_t) 0,                                       /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                                       /**< Generates a queue request source event */
  .refill_needed      = (uint32_t) 1,                                       /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for User defined -3 measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef3_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,   /**< Global ICLASS 0 selected. */
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,          /**< Channel Event disabled. */
  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_RES_REG_NUM,/**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,           /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1                                       /**< Alias feature not selected. */
};

/** Result register configuration for User defined-3 measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef3_Res_handle =
{
  .data_reduction_control  = (uint32_t)  0,                                      /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode      = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo            = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable        = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U)
/** Queue entry for user defined channel 4 measurement. */
XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef4_queue_entry =
{
  .channel_num        = (uint32_t)MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_CH_NUM,        /**< VADC Channel number */
  .external_trigger   = (uint32_t) 0,                                       /**< External trigger Enabled/Disabled*/
  .generate_interrupt = (uint32_t) 0,                                       /**< Generates a queue request source event */
  .refill_needed      = (uint32_t) 1,                                       /**< Conversion completed channel gets inserted back into the queue */
};

/** VADC Channel configuration for User defined -4 measurement. */
XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef4_CH_handle =
{
  .input_class              = (uint32_t) XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,   /**< Global ICLASS 0 selected. */
  .event_gen_criteria       = (uint32_t) XMC_VADC_CHANNEL_EVGEN_NEVER,          /**< Channel Event disabled. */
  .result_reg_number        = (uint32_t) MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_RES_REG_NUM,/**< Configured result register for Phase C voltage measurement. */
  .result_alignment         = (uint32_t) XMC_VADC_RESULT_ALIGN_RIGHT,           /**< Result alignment - Right Aligned. */
  .alias_channel            = (int8_t) -1                                       /**< Alias feature not selected. */
};

/** Result register configuration for User defined-4 measurement. */
XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef4_Res_handle =
{
  .data_reduction_control  = (uint32_t)  0,                                      /**< No Accumulation. */
  .post_processing_mode    = (uint32_t) XMC_VADC_DMM_REDUCTION_MODE,
  .wait_for_read_mode      = (uint32_t) 0,                                      /**< Result registers are updated as and when the conversion is finished.*/
  .part_of_fifo            = (uint32_t) 0,                                      /**< FIFO has been disabled.*/
  .event_gen_enable        = (uint32_t) 0                                       /**< result event generation disabled.*/
};

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U) */

/* Boundary configuration structure declaration */
VADC_BOUNDARY_CONFIG_t VADC_BoundaryConfig;

 /*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/
#if(UC_STEP == AA_STEP)
/* This API is used for VADC gain calibration. */
/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Calibrates VADC by triggering dummy conversion for XMC13 AA STEP micro-controllers as per ADC_AI.004 errata.
 */
static void VADC_GainCalib(void)
{
  volatile uint16_t dummy_conv_counter = VADC_DUMMY_CONVERSION_COUNTER;  /* Used for keeping track for dummy conversions */
  volatile uint32_t adc_result_aux;                                      /* Used for reading ADC values after dummy conversions */

  /* ADC_AI.004 errata*/
  *SHS0_CALCTR = 0X3F100400U;

  /* add a channel in group-0 for dummy conversion*/
  VADC->BRSSEL[0] = VADC_BRSSEL_CHSELG0_Msk;

  /*Clear the DPCAL0, DPCAL1 and SUCAL bits*/
  VADC->GLOBCFG &= ~( (uint32_t)VADC_GLOBCFG_DPCAL0_Msk | (uint32_t)VADC_GLOBCFG_DPCAL1_Msk | (uint32_t)VADC_GLOBCFG_SUCAL_Msk);

  /* Clear offset calibration values*/
  CLEAR_OFFSET_CALIB_VALUES;

  VADC->BRSMR = ((uint32_t)1 << (uint32_t)VADC_BRSMR_ENGT_Pos);
  #if UC_SERIES != XMC11
  VADC_G0->ARBPR = (VADC_G_ARBPR_ASEN2_Msk);
  #endif
  /*Trigger dummy conversion for 9* 2000 times*/

  while (dummy_conv_counter > 0U)
  {
    /*load event */
    VADC->BRSMR |= (uint32_t)VADC_BRSMR_LDEV_Msk;
    #if (UC_SERIES != XMC11)
    /*Wait until a new result is available*/
    while (VADC_G0->VFR == 0U)
    {

    }

    /*dummy read of result */
    adc_result_aux = VADC_G0->RES[0];
    #else
    /*Wait untill a new result is available*/
    while ((VADC->GLOBRES & VADC_GLOBRES_VF_Msk) == 0)
    {

    }

    /*dummy read of result */
    adc_result_aux = VADC->GLOBRES;
    #endif

    /* Clear offset calibration values*/
    CLEAR_OFFSET_CALIB_VALUES;
    dummy_conv_counter--;
  }

  /* To avoid a warning*/
  adc_result_aux &= 0U;

  /* Wait until last gain calibration step is finished */
  while ( (SHS0->SHSCFG & (uint32_t)SHS_SHSCFG_STATE_Msk) != 0U )
  {
    /* Clear offset calibration values*/
    CLEAR_OFFSET_CALIB_VALUES;
  }
  /* Re enable SUCAL DPCAL */
  VADC->GLOBCFG |= ( (uint32_t)VADC_GLOBCFG_DPCAL0_Msk | (uint32_t)VADC_GLOBCFG_DPCAL1_Msk);
  VADC->BRSMR     = (uint32_t)0x00;
  VADC->BRSSEL[0] = (uint32_t)0x00;
  #if (UC_SERIES != XMC11)
  VADC_G0->REFCLR = 1U;
  VADC_G0->ARBPR &= ~((uint32_t)VADC_G_ARBPR_ASEN2_Msk);
  #endif
}

/*
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Turn on Group 0 converter to calibrates VADC by triggering dummy conversions.
 * This startup calibration is required only for XMC13 AA STEP micro-controllers as per ADC_AI.004 errata.
 */
void VADC_StartupCalibration(void)
{
  volatile uint32_t dealy_counter; /* Delay counter for the startup calibration to complete. */
  *SHS0_CALOC0 = REG_RESET;
  *SHS0_CALOC1 = REG_RESET;

  #if(VADC_ENABLE_GROUP_QUEUE_0 != 1U)
  /* Enable Group 0 for Calibration */
  XMC_VADC_GROUP_SetPowerMode(VADC_G0,XMC_VADC_GROUP_POWERMODE_NORMAL);
  #endif

  /* Enable the StartUp calibration in the VADC */
  VADC->GLOBCFG |= (((uint32_t)1 << (uint32_t)VADC_GLOBCFG_SUCAL_Pos) & (uint32_t)VADC_GLOBCFG_SUCAL_Msk) |
                   (((uint32_t)1 << (uint32_t)VADC_GLOBCFG_DPCAL0_Pos) & (uint32_t)VADC_GLOBCFG_DPCAL0_Msk);

  /* Wait for 1920cycles or 60us for the startup calibration to complete. */
  dealy_counter = VADC_CALIBRATION_CYCLE_DELAY;

  while (dealy_counter > 0U)
  {
    dealy_counter--;
    /* Clear offset calibration values */
    CLEAR_OFFSET_CALIB_VALUES;
  }
  VADC_GainCalib();

  /* Switch off Group 0 converter if it is not used for any conversions */
  #if(VADC_ENABLE_GROUP_QUEUE_0 != 1U)
  XMC_VADC_GROUP_SetPowerMode(VADC_G0,XMC_VADC_GROUP_POWERMODE_OFF);
  #endif
}
#endif /*end of #if(UC_STEP == AA_STEP) */

/*
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes VADC peripheral and power on the required VADC Group and Queues.
 * Only required converters will be turned on to optimize power consumption.
 */
void Motor0_BLDC_SCALAR_VADC_Init(void)
{
  /* Initialize an instance of VADC Global hardware */
  XMC_VADC_GLOBAL_Init(VADC, &Motor0_BLDC_SCALAR_VADC_GLOBAL_config);

  /* Power on only required converters for Configured measurements. */
  #if(VADC_ENABLE_GROUP_QUEUE_0 == 1U)
  /* Switch on the converter of the Group[0]*/
  XMC_VADC_GROUP_SetPowerMode(VADC_G0,XMC_VADC_GROUP_POWERMODE_NORMAL);
  #endif
  #if(VADC_ENABLE_GROUP_QUEUE_1 == 1U)
  /* Switch on the converter of the Group[1]*/
  XMC_VADC_GROUP_SetPowerMode(VADC_G1,XMC_VADC_GROUP_POWERMODE_NORMAL);
  #endif
  #if(VADC_ENABLE_GROUP_QUEUE_2 == 1U)
  /* Switch on the converter of the Group[2]*/
  XMC_VADC_GROUP_SetPowerMode(VADC_G2,XMC_VADC_GROUP_POWERMODE_NORMAL);
  #endif
  #if(VADC_ENABLE_GROUP_QUEUE_3 == 1U)
  /* Switch on the converter of the Group[3]*/
  XMC_VADC_GROUP_SetPowerMode(VADC_G3,XMC_VADC_GROUP_POWERMODE_NORMAL);
  #endif

  /* VADC Startup Calibration */
  #if (MOTOR0_BLDC_SCALAR_ENABLE_VADC_STARTUP_CALIBRATION == 1U)
  #if((UC_STEP == AA_STEP) && (UC_SERIES == XMC13))
  VADC_StartupCalibration();
  #else
  XMC_VADC_GLOBAL_StartupCalibration(VADC);
  #endif
  #endif

  /* Initialize Group and Queue related configuration. */
  #if(VADC_ENABLE_GROUP_QUEUE_0 == 1U)
  /* Program the input classes for Group[0] */
  XMC_VADC_GROUP_InputClassInit(VADC_G0, Motor0_BLDC_SCALAR_VADC_GROUP_class0, XMC_VADC_GROUP_CONV_STD,0U);
  /* Initialize the Queue0 */
  XMC_VADC_GROUP_QueueInit(VADC_G0, &Motor0_BLDC_SCALAR_VADC_QUEUE_0_cfg);
  /* Configure the gating mode for queue0*/
  XMC_VADC_GROUP_QueueSetGatingMode(VADC_G0, (XMC_VADC_GATEMODE_t)MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_GATING);
  /* Flush any entries that are currently in the queue0 buffer */
  XMC_VADC_GROUP_QueueFlushEntries(VADC_G0);
  #endif  /* end of #if(VADC_ENABLE_GROUP_QUEUE_0 == 1U) */

  #if(VADC_ENABLE_GROUP_QUEUE_1 == 1U)
  /* Program the input classes for Group[1] */
  XMC_VADC_GROUP_InputClassInit(VADC_G1,Motor0_BLDC_SCALAR_VADC_GROUP_class0,XMC_VADC_GROUP_CONV_STD,0U);
  /* Initialize the Queue1 */
  XMC_VADC_GROUP_QueueInit(VADC_G1,&Motor0_BLDC_SCALAR_VADC_QUEUE_1_cfg);
  /* Configure the gating mode for queue1 */
  XMC_VADC_GROUP_QueueSetGatingMode(VADC_G1, (XMC_VADC_GATEMODE_t)MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_GATING);
  /* Flush any entries that are currently in the queue1 buffer */
  XMC_VADC_GROUP_QueueFlushEntries(VADC_G1);
  #endif  /* end of #if(VADC_ENABLE_GROUP_QUEUE_1 == 1U) */

  #if(VADC_ENABLE_GROUP_QUEUE_2 == 1U)
  /* Program the input classes for Group[2] */
  XMC_VADC_GROUP_InputClassInit(VADC_G2,Motor0_BLDC_SCALAR_VADC_GROUP_class0,XMC_VADC_GROUP_CONV_STD,0U);
  /* Initialize the Queue2 */
  XMC_VADC_GROUP_QueueInit(VADC_G2,&Motor0_BLDC_SCALAR_VADC_QUEUE_2_cfg);
  /* Configure the gating mode for queue2 */
  XMC_VADC_GROUP_QueueSetGatingMode(VADC_G2, (XMC_VADC_GATEMODE_t)MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_GATING);
  /* Flush any entries that are currently in the queue2 buffer */
  XMC_VADC_GROUP_QueueFlushEntries(VADC_G2);
  #endif  /* end of #if(VADC_ENABLE_GROUP_QUEUE_2 == 1U) */

  #if(VADC_ENABLE_GROUP_QUEUE_3 == 1U)
  /* Program the input classes for Group[3] */
  XMC_VADC_GROUP_InputClassInit(VADC_G3,Motor0_BLDC_SCALAR_VADC_GROUP_class0,XMC_VADC_GROUP_CONV_STD,0U);
  /* Initialize the Queue3 */
  XMC_VADC_GROUP_QueueInit(VADC_G3,&Motor0_BLDC_SCALAR_VADC_QUEUE_3_cfg);
  /* Configure the gating mode for queue3 */
  XMC_VADC_GROUP_QueueSetGatingMode(VADC_G3, (XMC_VADC_GATEMODE_t)MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_GATING);
  /* Flush any entries that are currently in the queue3 buffer */
  XMC_VADC_GROUP_QueueFlushEntries(VADC_G3);
  #endif  /* end of #if(VADC_ENABLE_GROUP_QUEUE_3 == 1U) */
}
/*********************************************************************************************************************/
