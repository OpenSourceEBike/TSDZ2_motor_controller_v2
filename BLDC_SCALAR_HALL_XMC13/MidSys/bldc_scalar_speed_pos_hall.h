/**
 * @file bldc_scalar_speed_pos_hall.h
 * @brief Speed and position interface using 3 hall sensor feedback. This uses floating prescaler feature of CCU4 for speed capture
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
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided with the distribution.
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
 *
 * 2016-05-25:
 *     - Initial version
 *
 * @endcond
 *
 */
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup MidSys
 * @{
 */
#ifndef BLDC_SCALAR_SPEED_POS_HALL_H_
#define BLDC_SCALAR_SPEED_POS_HALL_H_

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "../MCUInit/ccu4.h"
#include "../MCUInit/gpio.h"
#include "../MCUInit/posif.h"


/**********************************************************************************************************************
* MACROS
**********************************************************************************************************************/
/** This defines speed accumulation limit value*/
#define BLDC_SCALAR_SPEED_POS_HALL_SPEEDACCUMLIMITCHECK             (5U)
/** Maximum period value of CCU4 slice */
#define BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL                     (0xFFFFU)
/** Capture register number */
#define BLDC_SCALAR_HALL_CAPTURE_REGITSER                           (3U)

/**********************************************************************************************************************
* ENUMS
**********************************************************************************************************************/
/**
 * @brief return value of API
 */
typedef enum BLDC_SCALAR_SPEED_POS_HALL_STATUS
{
  BLDC_SCALAR_SPEED_POS_HALL_STATUS_SUCCESS = 0U,   /*!< API execution is successful */
  BLDC_SCALAR_SPEED_POS_HALL_STATUS_FAILURE        /*!< API execution is failed */

} BLDC_SCALAR_SPEED_POS_HALL_STATUS_t;

/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/**
 * @brief structure to get the position and speed
 */
typedef struct BLDC_SCALAR_SPEED_POS_HALL
{
  uint32_t captureval[6];      /*!< captured time value between two correct hall events */
  uint32_t capval;             /*!< Captured time Value */
  uint32_t speedcheck;         /*!< whether motor speed can be calculated */
  uint32_t speedaccum;         /*!< accumulated speed of the motor for 6 samples */
  uint32_t speed_constant;     /*!< constant value used for speed calculation */
  uint8_t index;               /*!< index of an array of hall pattern */
  uint8_t speedindex;          /*!< index of an array of the speed capture variables */
} BLDC_SCALAR_SPEED_POS_HALL_t;


/**********************************************************************************************************************
* EXTERN
**********************************************************************************************************************/
extern BLDC_SCALAR_SPEED_POS_HALL_t Motor0_BLDC_SCALAR_SPEED_POS_HALL;
extern uint32_t BLDC_SCALAR_SPEED_POS_HALL_Cap_Array[16];

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
 * Return the current state of the POSIF input pins to which hall sensors are connected.
 */
uint32_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallPosition(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes the peripheral required for position and speed identification.
 * This initializes the POSIF and CCU4 module.
 */
void Motor0_BLDC_SCALAR_SPEED_POS_HALL_Init(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 *  Starts CCU4 and POSIF modules required for position and speed detection.
 *  It also reinitializes the speed calculation related variables.
 */
void Motor0_BLDC_SCALAR_SPEED_POS_HALL_Start(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 *  Stops CCU4 and POSIF modules required for position and speed detection.
 */
void Motor0_BLDC_SCALAR_SPEED_POS_HALL_Stop(void);


/**
 * @return none <br>
 *
 * \par<b>Description:</b><br>
 * Resets variables related to speed calculation.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearSpeedFilter(void)
{
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedindex = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedcheck = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[0] = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[1] = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[2] = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[3] = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[4] = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[5] = 0U;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.capval = Motor0_BLDC_SCALAR_SPEED_POS_HALL.speed_constant;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedaccum = 0U;
}

/**
 * @param capval captured value calculated from captured timer and prescaler
 * @return BLDC_SCALAR_SPEED_POS_HALL_STATUS_t status of API execution \n
 * BLDC_SCALAR_SPEED_POS_HALL_STATUS_FAILURE: if valid capture value is not available \n
 * BLDC_SCALAR_SPEED_POS_HALL_STATUS_SUCCESS: if valid capture value is available \n
 *  <br>
 *
 * \par<b>Description:</b><br>
 *  Calculates the captured time from timer value and current prescaler value in capture register
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.7 uSec </b>using O3 optimization level
 */
__STATIC_INLINE BLDC_SCALAR_SPEED_POS_HALL_STATUS_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_ReadCaptureValue(uint32_t *capval)
{
  BLDC_SCALAR_SPEED_POS_HALL_STATUS_t status = BLDC_SCALAR_SPEED_POS_HALL_STATUS_FAILURE;  /* return status */
  uint32_t temp_capval; /* capture register value */
  uint32_t curr_psc;    /* prescaler value */

  temp_capval = (uint32_t)XMC_CCU4_SLICE_GetCaptureRegisterValue(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, BLDC_SCALAR_HALL_CAPTURE_REGITSER);

  /*If Full flag is set, read the captured value and save in the dynamic handle */
  if (((temp_capval & (uint32_t)CCU4_CC4_CV_FFL_Msk) >> CCU4_CC4_CV_FFL_Pos) == 1U)
  {
    curr_psc = ((temp_capval & (uint32_t)CCU4_CC4_CV_FPCV_Msk) >> (uint32_t)CCU4_CC4_CV_FPCV_Pos);
    temp_capval = temp_capval & BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL;
    Motor0_BLDC_SCALAR_SPEED_POS_HALL.capval =
        (uint32_t)(BLDC_SCALAR_SPEED_POS_HALL_Cap_Array[(curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)] +
            (((uint32_t)1 << (curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)) * (uint32_t)temp_capval));
    *capval = (uint32_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL.capval;
    status = BLDC_SCALAR_SPEED_POS_HALL_STATUS_SUCCESS;
  }
  else
  {
    *capval = 0U;
  }

  return (status);
}

/**
 * @param capval time between two hall events (60 degrees)
 * @param speed Calculated electrical speed in RPM
 * @return None
 *  <br>
 *
 * \par<b>Description:</b><br>
 * Calculates the speed based upon the captured time value between two correct hall events.
 * It uses the floating prescaler for better resolution and low speed value.
 */
/*This function will calculate the speed based upon the captured time values.*/
RAM_ATTRIBUTE __STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_SpeedCalculation(uint32_t capval, uint32_t* speed)
{
  /* Moving average to calculate the speed */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedaccum -= Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedindex];
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedindex] = capval;
  Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedaccum += Motor0_BLDC_SCALAR_SPEED_POS_HALL.captureval[Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedindex];

  Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedindex++;

  /* Speed calculation starts after 6 hall events */
  if (Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedindex > BLDC_SCALAR_SPEED_POS_HALL_SPEEDACCUMLIMITCHECK)
  {
    Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedindex = 0U;
    Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedcheck = 1U;
  }

  if (Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedcheck == 1U)
  {
    if (Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedaccum > 0U)
    {
      __disable_irq();
      *speed = (Motor0_BLDC_SCALAR_SPEED_POS_HALL.speed_constant) / (Motor0_BLDC_SCALAR_SPEED_POS_HALL.speedaccum);
      __enable_irq();
    }
  }
  else
  {
    *speed = 0U;
  }
}
/**
 * @param pattern The 16b multi-channel pattern [0-65535]
 * @retval None
 *
 * \par<b>Description</b><br>
 * Configures \a MCSM register with Multi-Channel Pattern.\n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetMultiChannelPattern(uint16_t pattern)
{

  XMC_POSIF_MCM_SetMultiChannelPattern(MOTOR0_BLDC_SCALAR_POSIF_MODULE, pattern);

}
/**
 * @retval None <br>
 *
 * \par<b>Description</b><br>
 * Performs shadow transfer of the Multi-Channel Pattern register by configuring.\n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateMultiChannelPattern(void)
{
  XMC_POSIF_MCM_UpdateMultiChannelPattern(MOTOR0_BLDC_SCALAR_POSIF_MODULE);
}
/**
 * @retval uint16_t Returns configured multi channel pattern <br>
 *
 * \par<b>Description</b><br>
 * Returns configured multi channel pattern of \a peripheral. \n
 */
__STATIC_INLINE uint16_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetMultiChannelPattern(void)
{
  uint16_t pattern;
  pattern = XMC_POSIF_MCM_GetMultiChannelPattern(MOTOR0_BLDC_SCALAR_POSIF_MODULE);
  return(pattern);
}
/**
 * @retval uint16_t Returns configured multi channel pattern present in shadow transfer register <br>
 *
 * \par<b>Description</b><br>
 * Returns configured multi channel pattern in shadow register of \a peripheral. \n
 */
__STATIC_INLINE uint16_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetShadowMultiChannelPattern(void)
{
  uint16_t pattern;
  pattern = XMC_POSIF_MCM_GetShadowMultiChannelPattern(MOTOR0_BLDC_SCALAR_POSIF_MODULE);
  return(pattern);
}
/**
 * @param pattern The hall sensor pattern mask [0-63] Format of mask: (expected_pattern << 3) | (current_pattern)
 * @retval None <br>
 *
 * \par<b>Description</b><br>
 * Configures current and expected hall pattern of \a peripheral. \n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(uint8_t pattern)
{
  XMC_POSIF_HSC_SetHallPatterns(MOTOR0_BLDC_SCALAR_POSIF_MODULE, pattern);
}
/**
 * @retval None <br>
 *
 * \par<b>Description</b><br>
 * The transfer of hall sensor pattern shadow registers content to the hall sensor pattern register happens
 * on hardware trigger.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateHallPattern(void)
{
  XMC_POSIF_HSC_UpdateHallPattern(MOTOR0_BLDC_SCALAR_POSIF_MODULE);
}
/**
 * @retval pattern The hall sensor pattern to be programmed into current pattern [0-7] <br>
 *
 * \par<b>Description</b><br>
 * Retrieves the expected hall sensor pattern from \a HALP register's \a HEP bit field of \a peripheral.\n
 */
__STATIC_INLINE uint8_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetExpectedPattern(void)
{
  uint8_t pattern;
  pattern = XMC_POSIF_HSC_GetExpectedPattern(MOTOR0_BLDC_SCALAR_POSIF_MODULE);
  return(pattern);
}
/**
 * @retval interval between two hall events <br>
 *
 * \par<b>Description</b><br>
 * Return time between two hall events\n
 */
__STATIC_INLINE uint32_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallEventTime(void)
{
  uint32_t period;
  period = XMC_CCU4_SLICE_GetCaptureRegisterValue(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, BLDC_SCALAR_HALL_CAPTURE_REGITSER);
  return(period);
}
/**
 * @retval uint8_t Returns last sampled hall sensor pattern. Range : [0-7] <br>
 *
 * \par<b>Description</b><br>
 * Returns last sampled hall sensor pattern of \a peripheral.\n
 */
__STATIC_INLINE uint8_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern(void)
{
  uint8_t hall_pattern;
  hall_pattern = XMC_POSIF_HSC_GetLastSampledPattern(MOTOR0_BLDC_SCALAR_POSIF_MODULE);
  return(hall_pattern);
}
/**
 * @retval None <br>
 *
 * \par<b>Description</b><br>
 * Reset the capture timer prescaler value.\n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_ResetCaptureTimePrescaler(void)
{
  /*
   * Stop timer and prescalar.
   * initialize timer and prescalar value and restert the timer
   */
  XMC_CCU4_SLICE_StopTimer(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE);
  XMC_CCU4_StopPrescaler(MOTOR0_BLDC_SCALAR_CCU4_MODULE);
  XMC_CCU4_SLICE_SetTimerValue(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, 0U);
  XMC_CCU4_SLICE_SetPrescaler(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE, MOTOR0_BLDC_SCALAR_CCU4_PRESCALER);
  XMC_CCU4_StartPrescaler(MOTOR0_BLDC_SCALAR_CCU4_MODULE);
  XMC_CCU4_SLICE_StartTimer(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE);
}
/**
 * @retval Hall event capture timer current value <br>
 *
 * \par<b>Description</b><br>
 * Return Hall event capture timer current value\n
 */
__STATIC_INLINE uint16_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetCapTimerVal(void)
{
  uint16_t period;
  period = XMC_CCU4_SLICE_GetTimerValue(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE);
  return(period);
}

/**
 * @param event Event ID to be checked for status
 * @retval uint8_t Returns event status <br>
 *
 * \par<b>Description</b><br>
 * Returns event status of peripheral. \n
 */
__STATIC_INLINE uint8_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetEventStatus(const XMC_POSIF_IRQ_EVENT_t event)
{
  return XMC_POSIF_GetEventStatus(MOTOR0_BLDC_SCALAR_POSIF_MODULE, event);
}

/**
 * @param event Event to be acknowledged
 * @retval None
 *
 * \par<b>Description</b><br>
 * Clears event by acknowledgment of peripheral. \n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearEvent(const XMC_POSIF_IRQ_EVENT_t event)
{
  XMC_POSIF_ClearEvent(MOTOR0_BLDC_SCALAR_POSIF_MODULE, event);
}

/**
 * @brief Disables an IRQ generation capable event
 * @param event Event to be disabled
 * @retval None
 *
 * \par<b>Description</b><br>
 * Disables event generation of peripheral.\n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_SPEED_POS_HALL_DisableEvent(const XMC_POSIF_IRQ_EVENT_t event)
{
  XMC_POSIF_DisableEvent(MOTOR0_BLDC_SCALAR_POSIF_MODULE, event);
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
#endif /* BLDC_SCALAR_SPEED_POS_HALL_H_ */

