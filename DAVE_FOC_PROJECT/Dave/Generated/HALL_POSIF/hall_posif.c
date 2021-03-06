/**
 * @file hall_posif.c
 * @date 2015-06-20
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * HALL_POSIF v4.0.10 - To get the motor position and speed using hall sensors separated at 120 degrees.
 * It supports 2-hall and 3-hall configuration.
 *
 * Copyright (c) 2015-2020, Infineon Technologies AG
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
 * 2015-02-20:
 *     - Initial version
 *
 * 2015-06-20:
 *     - ERU initialization modified
 *
 * @endcond
 *
 */


/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "hall_posif.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/
/* Returns the version of the HALL_POSIF App. */
DAVE_APP_VERSION_t HALL_POSIF_GetAppVersion(void)
{
  DAVE_APP_VERSION_t version;

  version.major = HALL_POSIF_MAJOR_VERSION;
  version.minor = HALL_POSIF_MINOR_VERSION;
  version.patch = HALL_POSIF_PATCH_VERSION;

  return version;
}
/**
 * This function initializes the hall_posif App and low level app.
 */
HALL_POSIF_STATUS_t HALL_POSIF_Init(HALL_POSIF_t * const HandlePtr)
{
  HALL_POSIF_STATUS_t status = HALL_POSIF_STATUS_SUCCESS;

#if (HALL_POSIF_ERU_AVALABLE == 1U)
  uint32_t etl_count = 0U;
#endif
  if (HALL_POSIF_UNINITIALISED == HandlePtr->state)
  {

    if (HALL_POSIF_STATUS_FAILURE == (HALL_POSIF_STATUS_t) GLOBAL_POSIF_Init(HandlePtr->global_posif_handle_ptr))
    {
      /* Failure during GLOBAL_POSIF app initialization */
      status = HALL_POSIF_STATUS_FAILURE;
    }

    if (HALL_POSIF_STATUS_FAILURE == (HALL_POSIF_STATUS_t) GLOBAL_CCU4_Init(HandlePtr->global_ccu4_handle_ptr))
    {
      /* Failure during GLOBAL_CCU4 app initialization */
      status = HALL_POSIF_STATUS_FAILURE;
    }

#if (HALL_POSIF_ERU_AVALABLE == 1U)
    /* ERU initialization */
    for(etl_count=0; etl_count<3; etl_count++)
    {
      if ( HandlePtr->config_ptr->enable_eru[etl_count] == 1U)
      {
        XMC_ERU_ETL_Init( HandlePtr->etl_resource_ptr[etl_count]->eru,HandlePtr->etl_resource_ptr[2]->etl_channel,HandlePtr->etl_conf_ptr[etl_count]);
        XMC_ERU_OGU_Init( HandlePtr->etl_resource_ptr[etl_count]->eru,HandlePtr->etl_resource_ptr[etl_count]->ogu_channel, HandlePtr->ogu_conf_ptr[etl_count]);
      }
    }
#endif

    XMC_GPIO_Init(HandlePtr->hallinput_ptr[0]->port, HandlePtr->hallinput_ptr[0]->pin, HandlePtr->hallpinconfig_ptr);
    XMC_GPIO_Init(HandlePtr->hallinput_ptr[1]->port, HandlePtr->hallinput_ptr[1]->pin, HandlePtr->hallpinconfig_ptr);

    if (HALL_POSIF_3HALL == HandlePtr->config_ptr->halltype)
    {
      XMC_GPIO_Init(HandlePtr->hallinput_ptr[2]->port, HandlePtr->hallinput_ptr[2]->pin, HandlePtr->hallpinconfig_ptr);
    }
#if (HALL_POSIF_ERU_AVALABLE == 1U)
    /* If 2-hall sensor mode is enable and hall-3 input via eru is not enabled
     * Then configure ETL,OGU for hall-3. Also set the etl status flag.*/
    else
    {
      if (HandlePtr->config_ptr->enable_eru[2] == 0U)
      {
        XMC_ERU_ETL_Init(HandlePtr->etl_resource_ptr[2]->eru,HandlePtr->etl_resource_ptr[2]->etl_channel,HandlePtr->etl_conf_ptr[2]);
        XMC_ERU_OGU_Init(HandlePtr->etl_resource_ptr[2]->eru,HandlePtr->etl_resource_ptr[2]->ogu_channel, HandlePtr->ogu_conf_ptr[2]);
      }
      /* Flag setting */
      if (HandlePtr->config_ptr->hall3pin == (uint8_t)0)
      {
        XMC_ERU_ETL_ClearStatusFlag(HandlePtr->etl_resource_ptr[2]->eru, HandlePtr->etl_resource_ptr[2]->etl_channel);
      }
      else
      {
        XMC_ERU_ETL_SetStatusFlag(HandlePtr->etl_resource_ptr[2]->eru, HandlePtr->etl_resource_ptr[2]->etl_channel);
      }
    }
#endif

    XMC_CCU4_SLICE_CaptureInit(HandlePtr->capture_ptr->slice_ptr, HandlePtr->capture_init_ptr);
    XMC_CCU4_SLICE_SetPrescaler(HandlePtr->capture_ptr->slice_ptr, HandlePtr->phasedelay_init_ptr->prescaler_initval);
    XMC_CCU4_SLICE_CompareInit(HandlePtr->phasedelay_ptr->slice_ptr, HandlePtr->phasedelay_init_ptr);

    XMC_POSIF_Init(HandlePtr->global_ptr, HandlePtr->posifconfig_ptr);

    if (HALL_POSIF_STATUS_FAILURE
        == (HALL_POSIF_STATUS_t) XMC_POSIF_HSC_Init(HandlePtr->global_ptr, HandlePtr->posifhsc_ptr))
    {
      /* Failure during posif mode configuration */
      status = HALL_POSIF_STATUS_FAILURE;
    }

    XMC_CCU4_SLICE_SetTimerCompareMatch(HandlePtr->phasedelay_ptr->slice_ptr, HandlePtr->config_ptr->blanking_time);
    XMC_CCU4_SLICE_SetTimerPeriodMatch(HandlePtr->phasedelay_ptr->slice_ptr, HandlePtr->config_ptr->phase_delay);

    XMC_CCU4_SLICE_SetTimerCompareMatch(HandlePtr->capture_ptr->slice_ptr,
        (uint16_t)((uint32_t) HandlePtr->config_ptr->phase_delay + HandlePtr->pattern_update_delay));
    XMC_CCU4_SLICE_SetTimerPeriodMatch(HandlePtr->capture_ptr->slice_ptr, 0xFFFFU);
    XMC_CCU4_SLICE_SetTimerValue(HandlePtr->capture_ptr->slice_ptr,
        (uint16_t)(HandlePtr->config_ptr->phase_delay + HandlePtr->pattern_update_delay + 1U));

    XMC_CCU4_EnableShadowTransfer(HandlePtr->phasedelay_ptr->module_ptr,
        (uint32_t) HandlePtr->phasedelay_ptr->shadow_transfer_msk);
    XMC_CCU4_EnableShadowTransfer(HandlePtr->capture_ptr->module_ptr,
        (uint32_t) HandlePtr->capture_ptr->shadow_transfer_msk);

    XMC_CCU4_SLICE_ConfigureEvent(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_EVENT_0,
        HandlePtr->phdelayevent_ptr);
    XMC_CCU4_SLICE_StartConfig(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_EVENT_0,
        XMC_CCU4_SLICE_START_MODE_TIMER_START_CLEAR);

    XMC_CCU4_SLICE_ConfigureEvent(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_EVENT_0,
        HandlePtr->captureevent_ptr);
    XMC_CCU4_SLICE_Capture1Config(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_EVENT_0);

    /* Clear IDLE mode.*/
    XMC_CCU4_EnableClock(HandlePtr->phasedelay_ptr->module_ptr, HandlePtr->phasedelay_ptr->slice_number);
    XMC_CCU4_EnableClock(HandlePtr->capture_ptr->module_ptr, HandlePtr->capture_ptr->slice_number);

    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
        HandlePtr->config_ptr->phasedelay_slice_sr[0]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP,
        HandlePtr->config_ptr->phasedelay_slice_sr[1]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT0,
        HandlePtr->config_ptr->phasedelay_slice_sr[2]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT1,
        HandlePtr->config_ptr->phasedelay_slice_sr[3]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT2,
        HandlePtr->config_ptr->phasedelay_slice_sr[4]);

    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
        HandlePtr->config_ptr->capture_slice_sr[0]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP,
        HandlePtr->config_ptr->capture_slice_sr[1]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT0,
        HandlePtr->config_ptr->capture_slice_sr[2]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT1,
        HandlePtr->config_ptr->capture_slice_sr[3]);
    XMC_CCU4_SLICE_SetInterruptNode(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT2,
        HandlePtr->config_ptr->capture_slice_sr[4]);

    XMC_POSIF_SetInterruptNode(HandlePtr->global_ptr, XMC_POSIF_IRQ_EVENT_CHE, HandlePtr->config_ptr->posif_hsc_sr[0]);
    XMC_POSIF_SetInterruptNode(HandlePtr->global_ptr, XMC_POSIF_IRQ_EVENT_WHE, HandlePtr->config_ptr->posif_hsc_sr[1]);
    XMC_POSIF_SetInterruptNode(HandlePtr->global_ptr, XMC_POSIF_IRQ_EVENT_HALL_INPUT,
        HandlePtr->config_ptr->posif_hsc_sr[2]);

    if (status != HALL_POSIF_STATUS_FAILURE)
    {
      HandlePtr->state = HALL_POSIF_INITIALISED;
    }
  }
  return status;
}

void HALL_POSIF_Start(HALL_POSIF_t* const HandlePtr)
{
  uint32_t curpos = 0U;
  if (HandlePtr->state == HALL_POSIF_INITIALISED)
  {
    HandlePtr->state = HALL_POSIF_RUNNING;

    XMC_POSIF_Stop(HandlePtr->global_ptr);
    XMC_CCU4_SLICE_ClearTimer(HandlePtr->phasedelay_ptr->slice_ptr);
    XMC_CCU4_SLICE_ClearTimer(HandlePtr->capture_ptr->slice_ptr);

    XMC_CCU4_SLICE_ConfigureEvent(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_EVENT_0,
        HandlePtr->phdelayevent_ptr);
    XMC_CCU4_SLICE_ConfigureEvent(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_EVENT_0,
        HandlePtr->captureevent_ptr);

    /* Clear IDLE mode.*/
    XMC_CCU4_EnableClock(HandlePtr->phasedelay_ptr->module_ptr, HandlePtr->phasedelay_ptr->slice_number);
    XMC_CCU4_EnableClock(HandlePtr->capture_ptr->module_ptr, HandlePtr->phasedelay_ptr->slice_number);

    XMC_CCU4_SLICE_SetTimerCompareMatch(HandlePtr->phasedelay_ptr->slice_ptr, HandlePtr->config_ptr->blanking_time);
    XMC_CCU4_SLICE_SetTimerPeriodMatch(HandlePtr->phasedelay_ptr->slice_ptr, HandlePtr->config_ptr->phase_delay);

    XMC_CCU4_SLICE_SetTimerCompareMatch(HandlePtr->capture_ptr->slice_ptr,
        (uint16_t)(HandlePtr->config_ptr->phase_delay + HandlePtr->pattern_update_delay));
    XMC_CCU4_SLICE_SetTimerPeriodMatch(HandlePtr->capture_ptr->slice_ptr, (uint16_t) 0xFFFF);
    XMC_CCU4_SLICE_SetTimerValue(HandlePtr->capture_ptr->slice_ptr,
        (uint16_t)(HandlePtr->config_ptr->phase_delay + HandlePtr->pattern_update_delay + 1U));

    XMC_CCU4_EnableShadowTransfer(HandlePtr->phasedelay_ptr->module_ptr,
        (uint32_t) HandlePtr->phasedelay_ptr->shadow_transfer_msk);
    XMC_CCU4_EnableShadowTransfer(HandlePtr->capture_ptr->module_ptr,
        (uint32_t) HandlePtr->capture_ptr->shadow_transfer_msk);

    /*Enable CHE and WHE interrupt*/
    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_1) == HALL_POSIF_BIT_POS_1)
    {
      XMC_POSIF_EnableEvent(HandlePtr->global_ptr, XMC_POSIF_IRQ_EVENT_CHE);
    }
    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_2) == HALL_POSIF_BIT_POS_2)
    {
      XMC_POSIF_EnableEvent(HandlePtr->global_ptr, XMC_POSIF_IRQ_EVENT_WHE);
    }

    /*Enable period match interrupt of slice 0*/
    XMC_CCU4_SLICE_EnableEvent(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);

    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_3) == HALL_POSIF_BIT_POS_3)
    {
      XMC_CCU4_SLICE_EnableEvent(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);
    }
    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_4) == HALL_POSIF_BIT_POS_4)
    {
      XMC_CCU4_SLICE_EnableEvent(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT0);
    }

    /* Get the initial position by reading hall input pins. From this position
     * initialize the start position of the rotation. If this position is not
     * valid then return error.
     */
    curpos = (uint32_t) HALL_POSIF_GetHallPosition(HandlePtr);

    if (HALL_POSIF_2HALL == HandlePtr->config_ptr->halltype)
    {
      curpos = curpos & (uint8_t) 0x3;
    }

    XMC_POSIF_HSC_SetHallPatterns(HandlePtr->global_ptr,
        (uint8_t)(
            HandlePtr->hall_pattern[curpos + (uint32_t) HandlePtr->direction]
                | (uint32_t) HandlePtr->config_ptr->hall3pin));

    XMC_POSIF_HSC_UpdateHallPattern(HandlePtr->global_ptr);

    HandlePtr->speedindex = 0U;
    HandlePtr->speedcheck = 0U;
    HandlePtr->captureval[0] = 0U;
    HandlePtr->captureval[1] = 0U;
    HandlePtr->captureval[2] = 0U;
    HandlePtr->captureval[3] = 0U;
    HandlePtr->captureval[4] = 0U;
    HandlePtr->captureval[5] = 0U;
    HandlePtr->capval = 0x7FFFU;
    HandlePtr->speedaccum = 0U;

    /*Set RUN bit of the POSIF and
     * CC41 First slice will be started on external start trigger */
    XMC_POSIF_Start(HandlePtr->global_ptr);
    XMC_CCU4_SLICE_StartTimer(HandlePtr->capture_ptr->slice_ptr);
  }
}

void HALL_POSIF_Stop(HALL_POSIF_t* const HandlePtr)
{
  if (HandlePtr->state == HALL_POSIF_RUNNING)
  {
    HandlePtr->state = HALL_POSIF_INITIALISED;
    /*Clear RUN bit and Set IDLE bit*/
    XMC_CCU4_SLICE_StopTimer(HandlePtr->phasedelay_ptr->slice_ptr);
    XMC_CCU4_SLICE_StopTimer(HandlePtr->capture_ptr->slice_ptr);
    XMC_POSIF_Stop(HandlePtr->global_ptr);
    /*Disable CHE and WHE interrupt*/
    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_1) == HALL_POSIF_BIT_POS_1)
    {
      XMC_POSIF_DisableEvent(HandlePtr->global_ptr, XMC_POSIF_IRQ_EVENT_CHE);
    }
    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_2) == HALL_POSIF_BIT_POS_2)
    {
      XMC_POSIF_DisableEvent(HandlePtr->global_ptr, XMC_POSIF_IRQ_EVENT_WHE);
    }

    /*Disable period match interrupt of slice 0*/
    XMC_CCU4_SLICE_DisableEvent(HandlePtr->phasedelay_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);

    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_3) == HALL_POSIF_BIT_POS_3)
    {
      XMC_CCU4_SLICE_DisableEvent(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);
    }
    if ((HandlePtr->config_ptr->interrupt_enable & HALL_POSIF_BIT_POS_4) == HALL_POSIF_BIT_POS_4)
    {
      XMC_CCU4_SLICE_DisableEvent(HandlePtr->capture_ptr->slice_ptr, XMC_CCU4_SLICE_IRQ_ID_EVENT0);
    }
  }
}

/*This function will set the direction of rotation.*/
void HALL_POSIF_SetDirection(HALL_POSIF_t* const HandlePtr, HALL_POSIF_DIRECTION_t Dir)
{
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    HandlePtr->direction = (HALL_POSIF_DIRECTION_t) Dir;
  }
}

/*This function will return the direction of rotation.*/
HALL_POSIF_DIRECTION_t HALL_POSIF_GetDirection(HALL_POSIF_t * const HandlePtr)
{
  return ((HALL_POSIF_DIRECTION_t) HandlePtr->direction);
}

/* This function will update the next hall pattern in the shadow hall register*/
void HALL_POSIF_SetNextHallPatt(HALL_POSIF_t * const HandlePtr, uint8_t index)
{
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    XMC_POSIF_HSC_SetHallPatterns(HandlePtr->global_ptr,
        (uint8_t)(HandlePtr->hall_pattern[(uint8_t) index + (uint32_t) HandlePtr->direction]));
  }
}

/*This function will update the next hall pattern in the shadow hall register for 2-Hall configuration */
void HALL_POSIF_SetNext2HallPatt(HALL_POSIF_t * const HandlePtr, uint8_t index)
{
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    XMC_POSIF_HSC_SetHallPatterns(HandlePtr->global_ptr,
        (uint8_t)(
            HandlePtr->hall_pattern[(uint8_t) index + (uint32_t) HandlePtr->direction]
                | (uint32_t) HandlePtr->config_ptr->hall3pin));
  }
}

/*This function will calculate the speed based upon the captured time values.*/
void HALL_POSIF_SpeedCalculation(HALL_POSIF_t* const HandlePtr, uint32_t* Speed)
{
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    HandlePtr->speedaccum -= HandlePtr->captureval[HandlePtr->speedindex];

    HandlePtr->captureval[HandlePtr->speedindex] = HandlePtr->capval;

    HandlePtr->speedaccum += HandlePtr->captureval[HandlePtr->speedindex];

    if (HandlePtr->speedaccum > 0U)
    {
      if (HandlePtr->speedcheck == 0U)
      {
        *Speed = 0U;
      }
      else
      {
        *Speed = (HandlePtr->config_ptr->speed_constant_avg) / (HandlePtr->speedaccum);
      }
    }
    else
    {
      *Speed = 0U;
    }
    HandlePtr->speedindex++;

    if (HandlePtr->speedindex > HALL_POSIF_SPEEDACCUMLIMITCHECK)
    {
      HandlePtr->speedindex = 0U;
      HandlePtr->speedcheck = 1U;
    }
  }
}

/*This function will calculate period register(phase delay slice) and compare
 * register (capture slice) values based upon last captured value and the given angle */
void HALL_POSIF_UpdateTimerValues(HALL_POSIF_t* const HandlePtr)
{
  uint32_t TempVal;
  uint32_t CapVal = HandlePtr->capval;

  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    if (HALL_POSIF_STATUS_SUCCESS == HALL_POSIF_ReadCaptureValue(HandlePtr))
    {
      /* Read the last captured value from the dynamic handle */
      CapVal = HandlePtr->capval & (uint32_t) 0xFFFF;
    }
    /* find the value of the phase delay from the last captured value */
    TempVal = ((((uint32_t) HandlePtr->phaseconst * CapVal) >> 15));

    /* At low speed with higher phase delay(more than 30 degree),
     limit the capture value */
    if ((TempVal > ((uint32_t) HandlePtr->pattern_update_delay)) && (HandlePtr->phaseconst > (uint32_t) 0x3FFF))
    {
      TempVal -= (uint32_t) HandlePtr->pattern_update_delay;
    }

    if (TempVal < HandlePtr->config_ptr->phase_delay)
    {
      TempVal = HandlePtr->config_ptr->phase_delay;
    }
    XMC_CCU4_SLICE_SetTimerPeriodMatch(HandlePtr->phasedelay_ptr->slice_ptr, (uint16_t) TempVal);
    TempVal = TempVal + HandlePtr->pattern_update_delay;
    XMC_CCU4_SLICE_SetTimerCompareMatch(HandlePtr->capture_ptr->slice_ptr, (uint16_t) TempVal);

    XMC_CCU4_SLICE_StopTimer(HandlePtr->capture_ptr->slice_ptr);

    /* initiate SW shadow transfer */
    TempVal =
        (((uint32_t) 0x01 << (HALL_POSIF_SHADOWTRANSFERBITPOS * (uint8_t) HandlePtr->phasedelay_ptr->slice_number))
            | ((uint32_t) 0x01 << (HALL_POSIF_SHADOWTRANSFERBITPOS * (uint8_t) HandlePtr->capture_ptr->slice_number)));
    XMC_CCU4_EnableShadowTransfer(HandlePtr->global_ccu4_handle_ptr->module_ptr, TempVal);
    /* immediate shadow transfer of the compare register */
    XMC_CCU4_SLICE_StartTimer(HandlePtr->capture_ptr->slice_ptr);
  }
}

/* This function will read the captured time value which corresponds the
 * time between two correct hall events.This function takes care of the floating
 * prescaler and gives the result in terms of the base resolution.*/
HALL_POSIF_STATUS_t HALL_POSIF_ReadCaptureValue(HALL_POSIF_t* const HandlePtr)
{
  HALL_POSIF_STATUS_t status = HALL_POSIF_STATUS_FAILURE;
  uint32_t TempCapVal;
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    TempCapVal = XMC_CCU4_SLICE_GetCaptureRegisterValue(HandlePtr->capture_ptr->slice_ptr, (uint8_t) 3);

    /*If Full flag is set, read the captured value and save in the dynamic handle */
    if (((TempCapVal & CCU4_CC4_CV_FFL_Msk) >> CCU4_CC4_CV_FFL_Pos) == 1U)
    {
      HandlePtr->capval = TempCapVal & (uint32_t) 0xFFFF;
      status = HALL_POSIF_STATUS_SUCCESS;
    }
  }
  return (status);
}

/*This function will return the current state of the POSIF input pins to
 * which hall sensors are connected. This is required information before
 * starting the app to know the start position of the motor.*/
uint32_t HALL_POSIF_GetHallPosition(HALL_POSIF_t* const HandlePtr)
{
  uint32_t hallposition = 0U;
  uint32_t hall[3] = { 0U };
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    /*Read the input pins.*/
    hall[0] = XMC_GPIO_GetInput(HandlePtr->hallinput_ptr[0]->port, HandlePtr->hallinput_ptr[0]->pin);
    hall[1] = XMC_GPIO_GetInput(HandlePtr->hallinput_ptr[1]->port, HandlePtr->hallinput_ptr[1]->pin);
    hallposition = (uint32_t)(hall[0] | ((uint32_t) hall[1] << 1));
    if (HandlePtr->config_ptr->halltype == HALL_POSIF_3HALL)
    {
      hall[2] = (uint32_t) XMC_GPIO_GetInput(HandlePtr->hallinput_ptr[2]->port, HandlePtr->hallinput_ptr[2]->pin);
      hallposition |= ((uint32_t)(hall[2] << 2));
    }
  }
  return ((uint32_t)(hallposition & 0x7U));
}

/*This function will enable phase advancing feature at run time.*/
void HALL_POSIF_EnablePhAdvance(HALL_POSIF_t* const HandlePtr)
{
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    HandlePtr->phadvance = (HALL_POSIF_PHASEADVANCE_t) HALL_POSIF_PHASEADVANCE_ENABLE;

    HandlePtr->phaseconst = HandlePtr->phaseadvconst;
  }
}

/*This function will disable phase advancing feature at run time.*/
void HALL_POSIF_DisablePhAdvance(HALL_POSIF_t* const HandlePtr)
{
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    HandlePtr->phadvance = (HALL_POSIF_PHASEADVANCE_t) HALL_POSIF_PHASEADVANCE_DISABLE;

    HandlePtr->phaseconst = HandlePtr->config_ptr->phase_delay_const;
  }
}

/*This function will set the phase advance angle.*/
HALL_POSIF_STATUS_t HALL_POSIF_SetPhAdvanceAngle(HALL_POSIF_t * const HandlePtr, uint32_t Angle)
{
  HALL_POSIF_STATUS_t status = HALL_POSIF_STATUS_SUCCESS;
  if (HandlePtr->state != HALL_POSIF_UNINITIALISED)
  {
    if ((Angle > HALL_POSIF_PHASEADVMINLIMIT) && (Angle < HALL_POSIF_PHASEADVMAXLIMIT))
    {
      HandlePtr->phaseadvconst = (uint16_t)(((HALL_POSIF_SIXTYDEGREE - Angle) << 15) / HALL_POSIF_SIXTYDEGREE);

      if (HandlePtr->phadvance == (HALL_POSIF_PHASEADVANCE_t) HALL_POSIF_PHASEADVANCE_ENABLE)
      {
        HandlePtr->phaseconst = HandlePtr->phaseadvconst;
      }
    }
    else
    {
      status = HALL_POSIF_STATUS_INVALID_PARAM;
    }
  }
  return status;
}

/*This function will return the phase advance angle.*/
uint32_t HALL_POSIF_GetPhAdvanceAngle(HALL_POSIF_t * const HandlePtr)
{
  return (uint32_t)(HALL_POSIF_SIXTYDEGREE - (((uint32_t) HandlePtr->phaseadvconst * HALL_POSIF_SIXTYDEGREE) >> 15));
}



