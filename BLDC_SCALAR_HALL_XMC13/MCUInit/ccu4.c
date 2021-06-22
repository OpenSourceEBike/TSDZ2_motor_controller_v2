/**
 * @file ccu4.c
 * @brief CCU4 slices configuration
 * -# CCU4 slice for hall signal blanking time
 * -# CCU4 slice for speed capture is used.
 * -# CCU4 slice is optionally used (Motor0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4) for
 * multi-channel pattern synchronization instead of CCU8 period match to avoid the PWM time delay.
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
 * - Initial version
 * 2016-09-08:
 *     - Updated for sensorless support
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "ccu4.h"

/**********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/

#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
/****************************Start: Phase Delay Slice *****************************************************************/
/**
 * CCU4 slice used for blanking delay and phase delay
 * Single shot mode, Compare mode
 * Starts with any hall edge detected (POSIF.out0)
 * Normal pre-scaler mode
 * Pre-scaler is same as CCU4 capture slice default pre-scaler
 */
XMC_CCU4_SLICE_COMPARE_CONFIG_t Motor0_BLDC_SCALAR_CCU4_3HALL_PhaseDelay_CompareConfig =
{
  .timer_mode          = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot            = 1U,
  .shadow_xfer_clear   = 1U,
  .dither_timer_period = 0U,
  .dither_duty_cycle   = 0U,
  .prescaler_mode      = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .mcm_enable          = 0U,
  .prescaler_initval   = MOTOR0_BLDC_SCALAR_CCU4_PRESCALER,
  .float_limit         = 0U,
  .dither_limit        = 0U,
  .passive_level       = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .timer_concatenation = 0U
};

/** Event 0 is mapped external start event */
XMC_CCU4_SLICE_EVENT_CONFIG_t Motor0_BLDC_SCALAR_CCU4_3HALL_PhaseDelay_StartEventconfig =
{
  .mapped_input = (XMC_CCU4_SLICE_INPUT_t)MOTOR0_BLDC_SCALAR_CCU4_DELAY_EXTSTART_IN,
  .edge         = (XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_t)XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
  .level        = (XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_t)XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
  .duration     = (XMC_CCU4_SLICE_EVENT_FILTER_t)XMC_CCU4_SLICE_EVENT_FILTER_DISABLED
};

/** Compare and period register values for phase delay slice */
CCU4_PH_DELAY_CONFIG_t Motor0_BLDC_SCALAR_CCU4_3Hall_PhaseDelay_Config =
{
  .blanking_time          = (uint16_t)MOTOR0_BLDC_SCALAR_PHASE_DELAY_COMPARE,
  .phase_delay            = (uint16_t)MOTOR0_BLDC_SCALAR_PHASE_DELAY_PERIOD
};
/****************************End: Phase Delay Slice ***************************/

/****************************Start: Capture Slice *****************************/
/**
 * CCU4 slice used for capturing time between two hall edges
 * Capture mode, capture channel 1 is used
 * Captures time on correct hall event (POSIF.out1)
 * Floating pre-scaler is used to increase the speed measurement range
 */
XMC_CCU4_SLICE_CAPTURE_CONFIG_t Motor0_BLDC_SCALAR_CCU4_3HALL_CaptureConfig =
{
  .timer_clear_mode    = XMC_CCU4_SLICE_TIMER_CLEAR_MODE_CAP_HIGH,
  .same_event          = 0U,
  .fifo_enable         = 0U,
  .ignore_full_flag    = 0U
};

/** Event 0 is mapped to external capture channel 1 */
XMC_CCU4_SLICE_EVENT_CONFIG_t Motor0_BLDC_SCALAR_CCU4_3HALL_Capture_ExtCaptureEventConfig =
{
  .mapped_input = (XMC_CCU4_SLICE_INPUT_t)MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_EXTCAPTURE_IN,
  .edge         = (XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_t)XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
  .level        = (XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_t)XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
  .duration     = (XMC_CCU4_SLICE_EVENT_FILTER_t)XMC_CCU4_SLICE_EVENT_FILTER_DISABLED
};
#endif
/****************************End: Capture Slice ******************************************/

/****************************Start: Fast Synchronization Slice ***************************/
#if(1U == MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4)

/**
 * CCU4 used for providing synchronization signal for multi channel pattern transfer
 * to the output lines.
 * Compare mode, period value in the range if 2-5 us
 */
XMC_CCU4_SLICE_COMPARE_CONFIG_t Motor0_BLDC_SCALAR_CCU4_FastSynch_Config =
{
  .timer_mode          = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot            = 0U,
  .shadow_xfer_clear   = 1U,
  .dither_timer_period = 0U,
  .dither_duty_cycle   = 0U,
  .prescaler_mode      = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .mcm_enable          = 0U,
  .prescaler_initval   = 0U,
  .float_limit         = 0U,
  .dither_limit        = 0U,
  .passive_level       = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .timer_concatenation = 0U
};
#endif
/****************************End: Fast Synchronization Slice ***************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * CCU4 slices initialization for 3 hall feedback configuration.
 */
void Motor0_BLDC_SCALAR_CCU4_3Hall_Init(void)
{
  /* Enable CCU4 module */
  XMC_CCU4_Init(MOTOR0_BLDC_SCALAR_CCU4_MODULE,XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
  /*Phase delay slice initialization*/
  Motor0_BLDC_SCALAR_CCU4_3Hall_PhaseDelay_Init();
  /*Speed capture slice initialization*/
  Motor0_BLDC_SCALAR_CCU4_3Hall_SpeedCapture_Init();
#if(1U == MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4)
  /*Fast sync slice initialization*/
  Motor0_BLDC_SCALAR_CCU4_MCMSync_Init();
#endif
}

/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes phase delay CCU4 slice for MCM pattern update .
 */
void Motor0_BLDC_SCALAR_CCU4_3Hall_PhaseDelay_Init(void)
{
  /*Phase delay slice compare timer initiation*/
  XMC_CCU4_SLICE_CompareInit(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE,
      &Motor0_BLDC_SCALAR_CCU4_3HALL_PhaseDelay_CompareConfig);

  /*Phase delay blanking time configuration*/
  XMC_CCU4_SLICE_SetTimerCompareMatch(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE,
      Motor0_BLDC_SCALAR_CCU4_3Hall_PhaseDelay_Config.blanking_time);

  /*Phase delay slice period value(phase delay timing) configuration*/
  XMC_CCU4_SLICE_SetTimerPeriodMatch(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE,
      Motor0_BLDC_SCALAR_CCU4_3Hall_PhaseDelay_Config.phase_delay);

  /*enable shadow transfer for compare and period value*/
  XMC_CCU4_EnableShadowTransfer(MOTOR0_BLDC_SCALAR_CCU4_MODULE,MOTOR0_BLDC_SCALAR_CCU4_DELAY_SHADOWTRANSFER);

  /*Configure Event 0 signal for phase delay slice*/
  XMC_CCU4_SLICE_ConfigureEvent(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE, XMC_CCU4_SLICE_EVENT_0,
      &Motor0_BLDC_SCALAR_CCU4_3HALL_PhaseDelay_StartEventconfig);

  /*Configure Event 0 signal as start signal for phase delay slice*/
  XMC_CCU4_SLICE_StartConfig(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE, XMC_CCU4_SLICE_EVENT_0,
      XMC_CCU4_SLICE_START_MODE_TIMER_START_CLEAR);

  /* Clear IDLE mode.*/
  XMC_CCU4_EnableClock(MOTOR0_BLDC_SCALAR_CCU4_MODULE, MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE_NUM);

  /*bind interrupt node for period match of phase delay*/
  XMC_CCU4_SLICE_SetInterruptNode(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
      MOTOR0_BLDC_SCALAR_CCU4_PHASE_DELAY_PM_SR);

  /*Enable period match interrupt of slice 0*/
  XMC_CCU4_SLICE_EnableEvent(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
}

/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes capture CCU4 slice for motor speed calculations from HALL events.
 */
void Motor0_BLDC_SCALAR_CCU4_3Hall_SpeedCapture_Init(void)
{
  /*capture slice initiation*/
  XMC_CCU4_SLICE_CaptureInit(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, &Motor0_BLDC_SCALAR_CCU4_3HALL_CaptureConfig);

  /*Set prescaler value*/
  XMC_CCU4_SLICE_SetPrescaler(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, MOTOR0_BLDC_SCALAR_CCU4_PRESCALER);
  /* enable floating prescaler for capture slice*/
  XMC_CCU4_SLICE_EnableFloatingPrescaler(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE);

  /* configure Event 0 signal as capture event*/
  XMC_CCU4_SLICE_ConfigureEvent(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, XMC_CCU4_SLICE_EVENT_0,
      &Motor0_BLDC_SCALAR_CCU4_3HALL_Capture_ExtCaptureEventConfig);

  /* configure channel for speed capture*/
  XMC_CCU4_SLICE_Capture1Config(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, XMC_CCU4_SLICE_EVENT_0);

  /* Clear IDLE mode.*/
  XMC_CCU4_EnableClock(MOTOR0_BLDC_SCALAR_CCU4_MODULE, MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE_NUM);

}
#endif   /* end of #if(MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL) */

#if(1U == MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4)
/* Fast synchronization slice initialization */
/*
 * @param None <br>
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes synchronization CCU4 slice for fast synchronization of MCM update after HALL event.
 */
void Motor0_BLDC_SCALAR_CCU4_MCMSync_Init(void)
{
  /*Timer initiation*/
  XMC_CCU4_SLICE_CompareInit(MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE, &Motor0_BLDC_SCALAR_CCU4_FastSynch_Config);
  /*Disable single shot mode by setting repeat mode*/
  XMC_CCU4_SLICE_SetTimerRepeatMode(MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE, XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT);
  /*set period value*/
  XMC_CCU4_SLICE_SetTimerPeriodMatch(MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE,
      (uint16_t)MOTOR0_BLDC_SCALAR_MCM_SYNCTRANSFER_PERIOD);
  /*Enable clock - Idle mode clear*/
  XMC_CCU4_EnableClock(MOTOR0_BLDC_SCALAR_CCU4_MODULE, MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE_NUM);
  /*Enable shadow transfer*/
  XMC_CCU4_EnableShadowTransfer(MOTOR0_BLDC_SCALAR_CCU4_MODULE, MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SHADOWTRANSFER);
  XMC_CCU4_SLICE_StartTimer(MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE);
}
#endif
