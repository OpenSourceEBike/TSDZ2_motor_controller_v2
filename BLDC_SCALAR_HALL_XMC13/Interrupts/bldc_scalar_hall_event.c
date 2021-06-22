/**
 * @file bldc_scalar_hall_event.c
 * @brief Wrong hall event (always enabled ) and Correct hall event (only for state identification)
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
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "../ControlModule/bldc_scalar_control_scheme.h"
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
#include "../ControlModule/bldc_scalar_control_hall.h"
#endif
#include "../bldc_scalar_user_interface.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_HALL_MOTOR_DIR_INDEX        (0x8U)
#define BLDC_SCALAR_HALL_PATTERN_POS            (3U)
#define BLDC_SCALAR_HALL_CAPTURE_COUNTER        (3U)
#define BLDC_SCALAR_HALL_CAPTURE_PRESCALAR_MASK (0xF0000U)
#define BLDC_SCALAR_HALL_CAPTURE_PRESCALAR_POS  (16U)
#define BLDC_SCALAR_HALL_CAPTURE_MASK           (0xFFFF)

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
static void Motor0_BLDC_SCALAR_CorrectHallEvent(void);
#endif

#if (((MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)) || \
    ((MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U) && (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 0U) && (MOTOR0_BLDC_SCALAR_REVERSE_HALL == 1U)))
static void Motor0_BLDC_SCALAR_WrongHallEvent(void);
#endif
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup Interrupt Interrupts
 * @brief  Interrupt Service Routines  <br>
 * @{
 */
/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/**
 * @param None
 * @return none <br>
 *
 * \par<b>Description:</b><br>
 * Event is mapped to correct and wrong hall event of POSIF.\n
 * Correct hall - used ONLY in STATE_IDENTIFICATION state to get the speed, position and direction of the freely running motor.\n
 * Wrong hall - used to find direction reversal or real wrong hall event (hall failure) \n
 * For reverse hall, apply next hall and multi-channel pattern based on the intended direction.
 * For hall failure, stop the motor and change the state to ERROR.
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_HallEvent_ISR(void)
{
  /* Wrong hall event */
  if (Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetEventStatus(XMC_POSIF_IRQ_EVENT_WHE) == (uint8_t)1)
  {
#if (((MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)))
    /* handle reverse hall event and correct the pattern */
    Motor0_BLDC_SCALAR_WrongHallEvent();
#elif (MOTOR0_BLDC_SCALAR_REVERSE_HALL == 1U)
    /* handle reverse hall event and correct the pattern */
    Motor0_BLDC_SCALAR_WrongHallEvent();
#else
    /* stop the motor in wrong hall event */
    Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_WRONGHALL;
    Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
    Motor0_BLDC_SCALAR_MotorStop();
#endif
  }
#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
  /* Correct hall event */
  else
  {
    Motor0_BLDC_SCALAR_CorrectHallEvent();
  }
#endif
}
/**
 * @}
 */
/**
 * @}
 */

#if (((MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)) || \
    ((MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U) && (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 0U) && (MOTOR0_BLDC_SCALAR_REVERSE_HALL == 1U)))
/*
 * if sampled hall pattern matches the pattern in the reverse direction, apply the next
 * hall and multi-channel pattern for the intended direction and perform forced shadow transfer.
 * Restart capture timer and calculate the speed.
 *
 * if hall failure, stop the motor and change the state to ERROR.
 */
static void Motor0_BLDC_SCALAR_WrongHallEvent(void)
{
  uint8_t sampled_pat;      /* Sampled hall pattern */
  uint8_t reverse_pat;      /* Expected reverse direction pattern based on last sample pattern */
  uint8_t correct_pat;      /* Expected correct direction pattern based on last sample pattern */

  /* 0: positive direction, 8: negative direction to access the pattern table */
  uint8_t direction = (uint8_t) Motor0_BLDC_SCALAR.motor_set_direction & BLDC_SCALAR_HALL_MOTOR_DIR_INDEX;  /* intended direction */
  int32_t temp_dir  = (-Motor0_BLDC_SCALAR.motor_set_direction);
  uint8_t rev_direction = ((uint8_t)(temp_dir) & BLDC_SCALAR_HALL_MOTOR_DIR_INDEX);    /* reverse direction */
#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
  uint8_t pos;           /* array index variable */
#endif
  uint32_t speed = 0U;     /* electrical speed in RPM */

  uint16_t timer;          /* Elapsed time since last hall event */
  uint32_t curr_psc;       /* Prescaler value */
  uint32_t capval;         /* Calculated time between two hall events */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
#if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U)
  /* To blank the direct DC link current measurement at the commutation point */
  Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_enable = 1U;
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U) */
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) */
#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
  /* Reset the stall detection count as hall event is detected for timeout*/
  Motor0_BLDC_SCALAR.stall_detection_counter = 0U;
#endif
  /*Get the sampled hall pattern*/
  sampled_pat = (uint8_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern();
  reverse_pat = (Motor0_BLDC_SCALAR_Hall.hall_pattern[Motor0_BLDC_SCALAR_Hall.prev_hall_pos + rev_direction] >> BLDC_SCALAR_HALL_PATTERN_POS);
  correct_pat = (Motor0_BLDC_SCALAR_Hall.hall_pattern[Motor0_BLDC_SCALAR_Hall.prev_hall_pos + direction] >> BLDC_SCALAR_HALL_PATTERN_POS);

  /* Check if the pattern matches the correct or reverse hall pattern */
  if (( reverse_pat == sampled_pat) || ( correct_pat == sampled_pat))
  {
    /* Reverse hall event detected */

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
    /* BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION  - to get the direction of freely running motor */
    if ((Motor0_BLDC_SCALAR_HALL_CatchFree.state_identification_done == 0U) &&
          (Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION))
    {
      /* Find the direction of rotation if motor is already running */
      Motor0_BLDC_SCALAR_HALL_CatchFree.identified_direction = (int32_t) (Motor0_BLDC_SCALAR.motor_set_direction * -1);
      direction = (uint8_t) Motor0_BLDC_SCALAR_HALL_CatchFree.identified_direction & BLDC_SCALAR_HALL_MOTOR_DIR_INDEX;
      Motor0_BLDC_SCALAR_HALL_CatchFree.dir_acquired = 1U;

      /* Update the hall pattern in shadow register and perform immediate transfer */
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
          (uint8_t) (Motor0_BLDC_SCALAR_Hall.hall_pattern[((uint8_t) sampled_pat + (uint32_t) direction)]));
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateHallPattern();
      pos =  Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetExpectedPattern();
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
          (uint8_t) (Motor0_BLDC_SCALAR_Hall.hall_pattern[(uint8_t) pos + (uint32_t) direction]));
    }

    /* BLDC_SCALAR_MSM_MOTOR_NORMAL_OPERATION - handle reverse rotation*/
    /* Apply hall pattern and multi-channel pattern for intended direction */
    else
    {
#endif
      /* Update actual motor direction */
      Motor0_BLDC_SCALAR.actual_motor_direction = (-Motor0_BLDC_SCALAR.motor_set_direction);

      Motor0_BLDC_SCALAR_PatternInitiator(sampled_pat);

      /* Restart the capture slice which is used for speed calculation */
      timer = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetCapTimerVal();
      curr_psc = ((uint32_t)((uint32_t)MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE->FPC & (uint32_t)CCU4_CC4_FPC_PVAL_Msk) >> (uint32_t)CCU4_CC4_FPC_PVAL_Pos);

      /* Stop timer and prescaler and restart with reset values*/
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_ResetCaptureTimePrescaler();

      /* speed calculation */
      capval = BLDC_SCALAR_SPEED_POS_HALL_Cap_Array[(curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)]
                                                             + (((uint32_t)1 << (uint32_t)(curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)) * timer);
      Motor0_BLDC_SCALAR_SPEED_POS_HALL.capval = capval;
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_SpeedCalculation(capval, &speed);
      Motor0_BLDC_SCALAR.motor_speed = (((int32_t)speed * Motor0_BLDC_SCALAR.actual_motor_direction *
          (int32_t)Motor0_BLDC_SCALAR.speed_mech_scale) >> BLDC_SCALAR_SPEED_SCALE_RES);
#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
    }
#endif
    Motor0_BLDC_SCALAR_Hall.prev_hall_pos = (uint8_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern();
  }

  /* Hall failure - sampled hall pattern does not match with either direction pattern */
  else
  {
    /* wrong hall event */
    Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_WRONGHALL;
    Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
    Motor0_BLDC_SCALAR_MotorStop();
  }
  /* clear wrong hall event */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearEvent(XMC_POSIF_IRQ_EVENT_WHE);
}
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
/*
 * Find the direction of the motor in free running condition.
 * This event is disabled once control is switched to closed loop.
 */
static void Motor0_BLDC_SCALAR_CorrectHallEvent(void)
{
  /* 0: positive direction, 8: negative direction to access the pattern table */
  uint8_t direction = (uint8_t) Motor0_BLDC_SCALAR.motor_set_direction & BLDC_SCALAR_HALL_MOTOR_DIR_INDEX;  /* intended direction */
  uint32_t capval;        /* Calculated time between last two hall events */
  uint8_t pos;          /* Array index variable */
  uint32_t capture_reg;   /* capture register value */
  uint32_t curr_psc;      /* Prescaler value */

  /* Speed is calculated based on last two hall events */
  Motor0_BLDC_SCALAR_HALL_CatchFree.sample_capture_counter++;
  Motor0_BLDC_SCALAR_HALL_CatchFree.catch_free_wait_counter = 0U;

  /*
   * if correct hall event is the first event after the state machine has started,
   * identified direction is the intended direction.
   * If wrong hall event is the first event after the state machine has started,
   * identified direction is the reverse direction.
   */
  if ((Motor0_BLDC_SCALAR_HALL_CatchFree.sample_capture_counter == 1U) && (Motor0_BLDC_SCALAR_HALL_CatchFree.dir_acquired == 0U))
  {
    Motor0_BLDC_SCALAR_HALL_CatchFree.identified_direction = (int32_t) Motor0_BLDC_SCALAR.motor_set_direction;
    Motor0_BLDC_SCALAR_HALL_CatchFree.dir_acquired = 1U;
  }

  direction = (uint8_t) Motor0_BLDC_SCALAR_HALL_CatchFree.identified_direction & BLDC_SCALAR_HALL_MOTOR_DIR_INDEX;

  /* Read the captured value */
  capture_reg = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallEventTime();
  if ((Motor0_BLDC_SCALAR_HALL_CatchFree.sample_capture_counter > 1U) && (Motor0_BLDC_SCALAR_HALL_CatchFree.state_identification_done == 0U))
  {
    capture_reg = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallEventTime();

    capval = (capture_reg & (uint32_t) BLDC_SCALAR_HALL_CAPTURE_MASK);
    curr_psc = (capture_reg & BLDC_SCALAR_HALL_CAPTURE_PRESCALAR_MASK) >> BLDC_SCALAR_HALL_CAPTURE_PRESCALAR_POS;
    Motor0_BLDC_SCALAR_HALL_CatchFree.cf_capval += BLDC_SCALAR_SPEED_POS_HALL_Cap_Array[(curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)]
                                                   + (((uint32_t)1 << (uint32_t)(curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)) * capval);

    /*
     * STATE_IDENTIFICATION state execution needs three correct hall events. First
     * event is ignored and speed is calculated based on last two events
     */
    if (Motor0_BLDC_SCALAR_HALL_CatchFree.sample_capture_counter == BLDC_SCALAR_HALL_CAPTURE_COUNTER)
    {
      Motor0_BLDC_SCALAR_HALL_CatchFree.state_identification_done = 1U;
    }
  }
  Motor0_BLDC_SCALAR_Hall.prev_hall_pos = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern();
  pos = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetExpectedPattern();

  /* next hall pattern in hall shadow register*/
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
      (uint8_t) (Motor0_BLDC_SCALAR_Hall.hall_pattern[(uint8_t) pos + (uint32_t) direction]));

  /* clear correct hall event */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearEvent(XMC_POSIF_IRQ_EVENT_CHE);
}
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U) */
