/**
 * @file posif.c
 * @brief POSIF in hall sensor configuration for BLDC motor control with hall sensor feedback.
 * @date 2016-09-08
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
 * 2016-09-08:
 *     - Updated for sensorless support
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "posif.h"

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
/**
 * Hall sensor mode configurations
 * Blanking signal is connected to CCU4 blanking slice compare match
 */
const XMC_POSIF_HSC_CONFIG_t Motor0_BLDC_SCALAR_POSIF_HALL_Config =
{
  .disable_idle_signal    = 1U,
  .sampling_trigger       = MOTOR0_BLDC_SCALAR_POSIF_BLANKING_SIGNAL_SEL,
  .sampling_trigger_edge  = XMC_POSIF_HSC_TRIGGER_EDGE_RISING,
  .external_error_port    = XMC_POSIF_INPUT_PORT_A,
  .external_error_enable  = 0U,
  .external_error_level   = XMC_POSIF_INPUT_ACTIVE_LEVEL_HIGH
};

/**
 * POSIF configured with hall sensor mode and input multiplexer configurations
 */
const XMC_POSIF_CONFIG_t Motor0_BLDC_SCALAR_POSIF_GLOBAL_Config =
{
  .mode   = XMC_POSIF_MODE_HALL_SENSOR,               /**< POSIF Operational mode */
  .input0 = MOTOR0_BLDC_SCALAR_POSIF_HALL_0_INSEL,    /**< Choice of input for Input-1 */
  .input1 = MOTOR0_BLDC_SCALAR_POSIF_HALL_1_INSEL,    /**< Choice of input for Input-2 */
  .input2 = MOTOR0_BLDC_SCALAR_POSIF_HALL_2_INSEL,    /**< Choice of input for Input-3 */
  .filter = XMC_POSIF_FILTER_16_CLOCK_CYCLE    /**< Input filter configuration */
};

/*
 * POSIF multi-channel configurations
 * Multi-channel pattern update signal is connected to CCU4 blanking signal period match or
 * CCU4 fast synchronization period match
 */
const XMC_POSIF_MCM_CONFIG_t Motor0_BLDC_SCALAR_POSIF_MCM_Config =
{
  .pattern_sw_update      = 0U,
  .pattern_update_trigger = MOTOR0_BLDC_SCALAR_POSIF_PATTERN_UPDATE_SEL,
  .pattern_trigger_edge   = XMC_POSIF_HSC_TRIGGER_EDGE_RISING,
  .pwm_sync               = MOTOR0_BLDC_SCALAR_POSIF_PWM_SYNC_SIGNAL_SEL
};

/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/*
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * This function initializes the POSIF peripheral in hall sensor mode.
 * Enables below events  and connects to interrupt node
 * - Correct hall event,
 * - Wrong hall event,
 * - Multi-channel pattern shadow transfer event
 */
void Motor0_BLDC_SCALAR_POSIF_3Hall_Init()
{
  XMC_POSIF_Init(MOTOR0_BLDC_SCALAR_POSIF_MODULE, &Motor0_BLDC_SCALAR_POSIF_GLOBAL_Config);
  XMC_POSIF_MCM_Init(MOTOR0_BLDC_SCALAR_POSIF_MODULE, &Motor0_BLDC_SCALAR_POSIF_MCM_Config);
  XMC_POSIF_HSC_Init(MOTOR0_BLDC_SCALAR_POSIF_MODULE, &Motor0_BLDC_SCALAR_POSIF_HALL_Config);

  /*Bind interrupt node*/
  XMC_POSIF_SetInterruptNode(MOTOR0_BLDC_SCALAR_POSIF_MODULE, XMC_POSIF_IRQ_EVENT_CHE,
      MOTOR0_BLDC_SCALAR_POSIF_HALL_SR);
  XMC_POSIF_SetInterruptNode(MOTOR0_BLDC_SCALAR_POSIF_MODULE, XMC_POSIF_IRQ_EVENT_WHE,
      MOTOR0_BLDC_SCALAR_POSIF_HALL_SR);
  XMC_POSIF_SetInterruptNode(MOTOR0_BLDC_SCALAR_POSIF_MODULE, XMC_POSIF_IRQ_EVENT_MCP_SHADOW_TRANSFER,
      MOTOR0_BLDC_SCALAR_POSIF_MCP_SR);

  XMC_POSIF_EnableEvent(MOTOR0_BLDC_SCALAR_POSIF_MODULE, XMC_POSIF_IRQ_EVENT_CHE);
  XMC_POSIF_EnableEvent(MOTOR0_BLDC_SCALAR_POSIF_MODULE, XMC_POSIF_IRQ_EVENT_WHE);
  XMC_POSIF_EnableEvent(MOTOR0_BLDC_SCALAR_POSIF_MODULE, XMC_POSIF_IRQ_EVENT_MCP_SHADOW_TRANSFER);
}
