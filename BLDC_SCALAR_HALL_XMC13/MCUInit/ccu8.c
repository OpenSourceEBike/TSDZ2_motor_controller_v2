/**
 * @file ccu8.c
 * @brief Three CCU8 slices are used to drive three motor phases (U, V and W) with PWM signals.
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
#include "ccu8.h"

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
/** Event2 - Trap event configuration structure*/
const XMC_CCU8_SLICE_EVENT_CONFIG_t Motor0_BLDC_SCALAR_CCU8TrapEventConf =
{
  .mapped_input = (uint32_t)MOTOR0_BLDC_SCALAR_CCU8_PH_U_CTRAP_EVT2_IN,  /* Required input signal for the trap Event.*/
  .level        = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_LOW,     /* Event level of the input signal*/
  .duration     = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED                   /* Event filter disabled */
};
#endif

/** Event 0 - External start event configuration structure*/
const XMC_CCU8_SLICE_EVENT_CONFIG_t Motor0_BLDC_SCALAR_CCU8ExtStartEventConf =
{
  .mapped_input = (uint32_t)MOTOR0_BLDC_SCALAR_CCU8_PH_U_EXTSTART_EVT0_IN, /* Required input signal for the start Event.*/
  .edge         = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,     /* Event edge of the input signal*/
  .duration     = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED                   /* Event filter disabled */
};

/** Event 1 - External stop event configuration structure*/
const XMC_CCU8_SLICE_EVENT_CONFIG_t Motor0_BLDC_SCALAR_CCU8ExtStopEventConf =
{
  .mapped_input = (uint32_t)MOTOR0_BLDC_SCALAR_CCU8_PH_U_EXTSTART_EVT1_IN, /* Required input signal for the start Event.*/
  .edge         = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_FALLING_EDGE,     /* Event edge of the input signal*/
  .duration     = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED                    /* Event filter disabled */
};

/** CCU8 dead time value and divider configuration.*/
XMC_CCU8_SLICE_DEAD_TIME_CONFIG_t Motor0_BLDC_SCALAR_CCU8_DeadTimeConfig =
{
 .div                               = (uint8_t)XMC_CCU8_SLICE_DTC_DIV_1,     /* Channel-1 dead time divider configuration */
 .channel1_st_rising_edge_counter   = (uint8_t)MOTOR0_BLDC_SCALAR_RISING_DEAD_TIME_COUNT,    /* Channel-1, rising edge dead time configuration */
 .channel1_st_falling_edge_counter  = (uint8_t)MOTOR0_BLDC_SCALAR_FALLING_DEAD_TIME_COUNT    /* Channel-1, falling edge dead time configuration */

};

/** CCU8 slice timer Initialization configuration. All three phases(phase-u/v/w) share the common configurations.*/
const XMC_CCU8_SLICE_COMPARE_CONFIG_t Motor0_BLDC_SCALAR_CCU8CompareConf =
{
  .timer_mode           = (uint8_t)XMC_CCU8_SLICE_TIMER_COUNT_MODE_CA,     /* Center Aligned */
  .prescaler_mode       = (uint8_t)XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL,   /* Normal prescaler mode */
  .passive_level_out0   = (~(uint32_t)MOTOR0_BLDC_SCALAR_HS_SWITCH_ACTIVE_LEVEL & (uint32_t)0x1),     /* Passive level  */
  .passive_level_out1   = (~(uint32_t)MOTOR0_BLDC_SCALAR_LS_SWITCH_ACTIVE_LEVEL & (uint32_t)0x1),     /* Passive level */
  .mcm_ch1_enable       = 1U,                                              /* Enable multi channel for channel-1 */
  .slice_status         = (uint8_t)XMC_CCU8_SLICE_STATUS_CHANNEL_1,        /* CCU8 channel-1 status configuration */
  .invert_out0          = 0U,                                              /* ST1 --> OUT00 (High Side) */
  .invert_out1          = 1U,                                              /* ST1 --> OUT01 (Low Side) */
  .prescaler_initval    = (uint8_t)MOTOR0_BLDC_SCALAR_CCU8_PRESCALER       /* Prescaler configuration*/
};

/** Structure initialization of CCU8 slices connected to phase U, V & W */
CCU8_PWM_INIT_t Motor0_BLDC_SCALAR_CCU8_PWM_Config =
{
  .phase_ptr              = {
                             MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE,
                             MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE,
                             MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE
                            }, /*Slice pointer for all three phase*/
  .phase_number           = {
                             MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM,
                             MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM,
                             MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM
                            },/*All three phase number*/
  .current_trigger        = (uint16_t)(MOTOR0_BLDC_SCALAR_CCU8_PERIOD_REG - MOTOR0_BLDC_SCALAR_CURRENT_OFFSET_COUNT),      /* VADC current trigger for Queue */
  .period                 = (uint16_t)MOTOR0_BLDC_SCALAR_CCU8_PERIOD_REG,                                           /*PWM period configuration*/
};

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/
static void Motor0_BLDC_SCALAR_CCU8_Slice_Init(uint32_t count);

/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/*
 * @param slice_ptr - CCU8 slice number
 *        IrqId     - Interrupt node ID
 *        SrId      - Service request node ID <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initialize CCU8 slice for enable event and SR binding to the node.
 */
void BLDC_SCALAR_CCU8_Event_Init(XMC_CCU8_SLICE_t* slice_ptr, XMC_CCU8_SLICE_IRQ_ID_t irq_id, XMC_CCU8_SLICE_SR_ID_t sr_id)
{
  /*Bind slice event SR(service request) to interrupt node*/
  XMC_CCU8_SLICE_SetInterruptNode(slice_ptr,irq_id,sr_id);

  /* Enable slice event */
  XMC_CCU8_SLICE_EnableEvent(slice_ptr,irq_id);
}

/*
 * @param handle_ptr    - CCU8 slice initialization data structure pointer
 *        slice_ptr     - CCU8 slice pointer
 *        slice_number  - CCU8 slice number <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initialize CCU8 slice.
 */


static void Motor0_BLDC_SCALAR_CCU8_Slice_Init(uint32_t count)
{
  XMC_CCU8_SLICE_t* const slice_ptr = Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[count];

  /* Enable clock for slice*/
  XMC_CCU8_EnableClock(MOTOR0_BLDC_SCALAR_CCU8_MODULE, Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_number[count]);

  /* CCU8 Slice configuration */
  XMC_CCU8_SLICE_CompareInit(slice_ptr, &Motor0_BLDC_SCALAR_CCU8CompareConf);
  /* Update CCU8 slice period registers */
  XMC_CCU8_SLICE_SetTimerPeriodMatch(slice_ptr,Motor0_BLDC_SCALAR_CCU8_PWM_Config.period);

  /*
   * Mapped slice to EVENT-0 (sync start event)
   * External Start Function triggered by Event-0 rising edge
   * Clears the timer and sets run bit.
   */
  XMC_CCU8_SLICE_ConfigureEvent(slice_ptr,(XMC_CCU8_SLICE_EVENT_t)XMC_CCU8_SLICE_EVENT_0,
      &Motor0_BLDC_SCALAR_CCU8ExtStartEventConf);
  XMC_CCU8_SLICE_StartConfig(slice_ptr,XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START_CLEAR);

  /*
   * Mapped slice to EVENT-1 (sync stop event)
   * External Stop Function triggered by Event-1 falling edge
   * Clears the timer and run bit
   */
  XMC_CCU8_SLICE_ConfigureEvent(slice_ptr,(XMC_CCU8_SLICE_EVENT_t)XMC_CCU8_SLICE_EVENT_1,
      &Motor0_BLDC_SCALAR_CCU8ExtStopEventConf);
  XMC_CCU8_SLICE_StopConfig(slice_ptr,XMC_CCU8_SLICE_EVENT_1,  XMC_CCU8_SLICE_END_MODE_TIMER_STOP_CLEAR);

  #if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
  /*
   * Trap configurations
   * Mapped slice to EVENT-2 (trap event)
   * TRAP function connected to Event 2
   * TRAP enable for CCU8x.OUTy0 and CCU8x.OUTy1
   */
  XMC_CCU8_SLICE_ConfigureEvent(slice_ptr,(XMC_CCU8_SLICE_EVENT_t)XMC_CCU8_SLICE_EVENT_2,
      &Motor0_BLDC_SCALAR_CCU8TrapEventConf);
  slice_ptr->CMC |= ((uint32_t) 1) << CCU8_CC8_CMC_TS_Pos;
  #endif

  /* Configure the dead time value */
  XMC_CCU8_SLICE_DeadTimeInit(slice_ptr,&Motor0_BLDC_SCALAR_CCU8_DeadTimeConfig);
}

/*
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initialize CCU8 slice for all 3 phases PWM generation.
 */
void Motor0_BLDC_SCALAR_CCU8_PWM_Init(void)
{
  uint32_t count;

  /*
   * Enable CCU8 module
   * Start the pre-scaler
   * Configure multi channel Shadow transfer request
   */
  XMC_CCU8_Init(MOTOR0_BLDC_SCALAR_CCU8_MODULE, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  /*Initialize CCU8 Phase-U, V and W Slice*/
  for (count = 0U; count < CCU8_MAXPHASE_COUNT;count++)
  {
    Motor0_BLDC_SCALAR_CCU8_Slice_Init(count);
  }

  /*
   * Initialize Phase-U one match event and Bind Phase-U one match event SR(service request)
   * to interrupt node for control loop execution.
   */
  BLDC_SCALAR_CCU8_Event_Init(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[0U],
 (XMC_CCU8_SLICE_IRQ_ID_t)XMC_CCU8_SLICE_IRQ_ID_ONE_MATCH, (XMC_CCU8_SLICE_SR_ID_t)MOTOR0_BLDC_SCALAR_CCU8_ONEMATCH_SR);
  /* Configures status ST2 of phase u mapping to STy */
  XMC_CCU8_SLICE_ConfigureStatusBitOutput(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[0U],XMC_CCU8_SLICE_STATUS_CHANNEL_2);

  #if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
  /*
   * Initialize Phase-U event-2 and Bind Phase-U event-2 SR(service request)
   * to interrupt node for trap control.
   */
  BLDC_SCALAR_CCU8_Event_Init(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[0U],
  (XMC_CCU8_SLICE_IRQ_ID_t)XMC_CCU8_SLICE_IRQ_ID_EVENT2, (XMC_CCU8_SLICE_SR_ID_t)MOTOR0_BLDC_SCALAR_CCU8_CTRAP_EVT2_SR);

  #endif

  /*
   * DC link current measurement trigger
   * phase-V compare match 2 down event
   */
  /* Initialize phase-V compare match 2 down event and bind SR to interrupt node for ADC trigger */
  BLDC_SCALAR_CCU8_Event_Init(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[1U],
   (XMC_CCU8_SLICE_IRQ_ID_t)XMC_CCU8_SLICE_IRQ_ID_COMPARE_MATCH_DOWN_CH_2, (XMC_CCU8_SLICE_SR_ID_t)MOTOR0_BLDC_SCALAR_CCU8_COMPMATCH_SR);

  XMC_CCU8_SLICE_SetTimerCompareMatch(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[1U], XMC_CCU8_SLICE_COMPARE_CHANNEL_2,
      Motor0_BLDC_SCALAR_CCU8_PWM_Config.current_trigger);

  /*Enable CCU8 shadow transfer*/
  XMC_CCU8_EnableShadowTransfer(MOTOR0_BLDC_SCALAR_CCU8_MODULE, MOTOR0_BLDC_SCALAR_CCU8_SHADOW_TRANSFER);
}

