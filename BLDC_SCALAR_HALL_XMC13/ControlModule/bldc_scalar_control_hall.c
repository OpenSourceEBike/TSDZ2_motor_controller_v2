/**
 * @file bldc_scalar_control_hall.c
 * @brief Hall sensor feedback control algorithm
 * @date 2016-09-08
 *
 * @cond
 ***********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 * Copyright (c) 2015, Infineon Technologies AG
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
#include "bldc_scalar_control_hall.h"
#include "../bldc_scalar_user_interface.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_HALL_VALIDATION_COUNT          (8U)
#define BLDC_SCALAR_HALL_DIRECTION_INDEX           (8U)
#define BLDC_SCALAR_HALL_LEARNING_ITERATION_COUNT  (20U)
#define BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE     (7U)
#define BLDC_SCALAR_HALL_MCM_SYNC_UPDATE_COUNT     (3U)
/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/
extern void Motor0_BLDC_SCALAR_MotorStop(void);
/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
/**
 * @brief This function validates the open loop captured pattern.
 * If pattern is not valid then reset adapt_algoindex counter.
 */

static void Motor0_BLDC_SCALAR_OpenLoopPatternValidation(void);
/**
 * @brief This function updates the hall pattern and multi channel pattern
 * for forward and reverse direction based on the captured pattern.
 * which is used when motor runs in close loop.
 */
static void Motor0_BLDC_SCALAR_UpdateCloseLoopPattern(void);

/**
 * @brief This function validates and updates the pattern
 */
static void Motor0_BLDC_SCALAR_ValidationAndUpdate(void);
#endif /* end of #if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U) */


/**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)

/*Validate the capture pattern */
static void Motor0_BLDC_SCALAR_OpenLoopPatternValidation(void)
{
  uint32_t iter_count = 0U;    /* loop count for pattern validation */

  if (Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex == Motor0_BLDC_SCALAR_HallLearning.ol_count)
  {
    /*Validate the captured pattern */
    for (iter_count = 0U;iter_count < BLDC_SCALAR_HALL_VALIDATION_COUNT; iter_count++)
    {
      /* reset the index if validation fails */
      if (Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_LEARNING_NUM_OF_PATTERNS] !=
          Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_DIRECTION_INDEX])
      {
        Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex = 0U;
      }
      if (Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[iter_count] == Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[iter_count + 1U])
      {
        Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex = 0U;
      }
    }
  }

}

/*Update the hall and MCM pattern */
static void Motor0_BLDC_SCALAR_UpdateCloseLoopPattern(void)
{
  uint32_t iter_count;       /* loop count for one electrical revolution */
  uint8_t rev_direction;     /* reverse direction */
  uint16_t count;            /* loop count to update multi-channel pattern */
  uint8_t direction = (uint8_t)Motor0_BLDC_SCALAR.motor_set_direction & BLDC_SCALAR_HALL_DIRECTION_INDEX;  /* intended direction */

  /* Find reverse direction */
  if (BLDC_SCALAR_POSITIVE_DIR == Motor0_BLDC_SCALAR.motor_set_direction)
  {
    rev_direction = (uint8_t)BLDC_SCALAR_NEGATIVE_DIR & BLDC_SCALAR_HALL_DIRECTION_INDEX;
  }
  else
  {
    rev_direction = (uint8_t)BLDC_SCALAR_POSITIVE_DIR & BLDC_SCALAR_HALL_DIRECTION_INDEX;
  }

  for (iter_count = (uint32_t)0; iter_count<(uint32_t)(BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE - 1U); iter_count++)
  {
    /*Update close loop Hall pattern*/
    Motor0_BLDC_SCALAR_Hall.hall_pattern[Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_DIRECTION_INDEX] + direction] =
    (uint8_t)BLDC_SCALAR_HALL_MCM((uint32_t)Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE],
                                  (uint32_t)Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_DIRECTION_INDEX]);
    /*Update close loop Multi channel pattern*/
    Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_HIGHSIDE][Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_DIRECTION_INDEX] + direction] =
    (uint16_t)Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_EVENTS_PER_CYCLE];
    Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_LOWSIDE][Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_DIRECTION_INDEX] + direction] =
    (uint16_t)Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_EVENTS_PER_CYCLE];

    /*Update close loop Multi channel pattern for sync modulation*/
    for (count = 0U; count < BLDC_SCALAR_HALL_MCM_SYNC_UPDATE_COUNT; count++)
    {
      /* Find high side switch is on */
      if (Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] ==
          (Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_EVENTS_PER_CYCLE] & Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count]))
      {
        /* Update table for both side modulation by oring with "BLDC_SCALAR_PWM_BC.ph_bothside_compmask[count]" */
        Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_HIGHSIDE_SYNCRECTI][Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_DIRECTION_INDEX] + direction] =
        (Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex + iter_count) - BLDC_SCALAR_HALL_EVENTS_PER_CYCLE] | Motor0_BLDC_SCALAR_PWM_BC.ph_bothside_compmask[count]);
      }
    }

    /*Update close loop Hall pattern for opposite direction*/
    Motor0_BLDC_SCALAR_Hall.hall_pattern[Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[((Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex - iter_count) - 1U)] + rev_direction] =
    (uint8_t)BLDC_SCALAR_HALL_MCM(Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex - (iter_count + 2U))],Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[(Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex - (iter_count + 1U))]);
  }

  /*Update close loop Multi channel pattern for opposite direction*/
  for (iter_count = 1U; iter_count < BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE; iter_count++)
  {
    Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_HIGHSIDE][iter_count + rev_direction] =
        Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_HIGHSIDE][BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE - (iter_count - direction)];
    Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_LOWSIDE][iter_count + rev_direction] =
        Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_LOWSIDE][BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE - (iter_count - direction)];
    Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_HIGHSIDE_SYNCRECTI][iter_count + rev_direction] =
        Motor0_BLDC_SCALAR.mc_pattern[PWM_BC_MOD_HIGHSIDE_SYNCRECTI][BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE - (iter_count - direction)];
  }

  /* Update pattern array to be used for user configuration update */
  for (count = 0U; count < BLDC_SCALAR_HALL_LEARNING_NUM_OF_PATTERNS; count++)
  {
    if (Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[count] == (uint8_t)0x1)
    {
      /* hall pattern 1->5 transition */
      if (Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[count + 1U] == 0x5U)
      {
        if (Motor0_BLDC_SCALAR.motor_set_direction == BLDC_SCALAR_POSITIVE_DIR)
        {
          Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[0U] = (uint16_t)BLDC_SCALAR_HALL_SEQ_2;
        }
        else
        {
          Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[0U] = (uint16_t)BLDC_SCALAR_HALL_SEQ_1;
        }
      }

      /* hall pattern 1-> 3 transition */
      if (Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[count + 1U] == (uint8_t)0x3)
      {
        if (Motor0_BLDC_SCALAR.motor_set_direction == BLDC_SCALAR_POSITIVE_DIR)
        {
          Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[0U] = (uint16_t)BLDC_SCALAR_HALL_SEQ_1;
        }
        else
        {
          Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[0U] = (uint16_t)BLDC_SCALAR_HALL_SEQ_2;
        }
      }

      if (count < BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE)
      {
        Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[1U] = Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[count + 2U];
        Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[2U] = Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[count + 3U];
        Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[3U] = Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[count + 4U];
        Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[4U] = Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[count + 5U];
        Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[5U] = Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[count + 6U];
        Motor0_BLDC_SCALAR_HallLearning.closedloop_mc_pattern[6U] = Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[count + 7U];
      }
      break;
    }
  }

}

static void Motor0_BLDC_SCALAR_ValidationAndUpdate(void)
{
  if (Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex == Motor0_BLDC_SCALAR_HallLearning.ol_count)
  {
    Motor0_BLDC_SCALAR_OpenLoopPatternValidation();

    if (Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex != Motor0_BLDC_SCALAR_HallLearning.ol_count)
    {
      Motor0_BLDC_SCALAR_HallLearning.ol_iter_count++;
      /* Try for 20 iterations to learn hall patterns */
      if ((uint8_t)BLDC_SCALAR_HALL_LEARNING_ITERATION_COUNT == Motor0_BLDC_SCALAR_HallLearning.ol_iter_count)
      {
        /* Log the error as hall learning failed */
        Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_HALL_LEARNING_TIMEOUT;
        Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
        Motor0_BLDC_SCALAR_MotorStop();
        Motor0_BLDC_SCALAR_HallLearning.ol_iter_count = (uint8_t)0;
      }
    }
    else
    {
      Motor0_BLDC_SCALAR_UpdateCloseLoopPattern();
    }
  }
}

/*Adaptive Pattern Capture*/
void Motor0_BLDC_SCALAR_HallPatternCapture(void)
{
  uint8_t hall_patt;        /* Read hall pattern from GPIO */
  uint16_t mcmval;          /* Actual multi-channel pattern */
  uint16_t mcm_patt;        /* multi-channel pattern used to lock the rotor */
  uint8_t arrayindex_adv;  /* index used to lock the rotor */

  uint8_t direction = (uint8_t)Motor0_BLDC_SCALAR.motor_set_direction & BLDC_SCALAR_HALL_DIRECTION_INDEX;  /* intended direction */

  if (Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex < Motor0_BLDC_SCALAR_HallLearning.ol_count)
  {
    /*
     * Read the hall state
     * Update the hall and multi-channel pattern in captured array
     * Apply next multi-channel pattern
     */
    if (Motor0_BLDC_SCALAR_HallLearning.count > Motor0_BLDC_SCALAR_HallLearning.ol_pattup_count)
    {
      Motor0_BLDC_SCALAR_HallLearning.count = 0U;
      hall_patt = (uint8_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallPosition();

      if (Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex < Motor0_BLDC_SCALAR_HallLearning.ol_count)
      {
        Motor0_BLDC_SCALAR_HallLearning.capt_hallpatt[Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex] = hall_patt;
        Motor0_BLDC_SCALAR_HallLearning.capt_outpatt[Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex] =
        (uint16_t)Motor0_BLDC_SCALAR_HallLearning.openloop_mc_pattern[Motor0_BLDC_SCALAR_HallLearning.ol_arrayindex + direction];
        Motor0_BLDC_SCALAR_HallLearning.adapt_algoindex++;
      }

      if (++(Motor0_BLDC_SCALAR_HallLearning.ol_arrayindex) > (uint8_t)(BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE - 1U) )
      {
        Motor0_BLDC_SCALAR_HallLearning.ol_arrayindex = (uint8_t)1;
      }
      arrayindex_adv = Motor0_BLDC_SCALAR_HallLearning.ol_arrayindex + 1U;

      if (arrayindex_adv > (uint8_t)(BLDC_SCALAR_HALL_CLOSE_LOOP_ARRAY_SIZE - 1U))
      {
        arrayindex_adv = 1U;
      }

      mcm_patt = (Motor0_BLDC_SCALAR_HallLearning.openloop_mc_pattern[Motor0_BLDC_SCALAR_HallLearning.ol_arrayindex + direction]) |
                 (Motor0_BLDC_SCALAR_HallLearning.openloop_mc_pattern[arrayindex_adv + direction]);

      Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetMultiChannelPattern(mcm_patt);
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateMultiChannelPattern();
      mcmval = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetMultiChannelPattern();
      Motor0_BLDC_SCALAR_PWM_BC.immediate_modulation_ptr(mcmval);

      /*update open loop duty cycle*/
      Motor0_BLDC_SCALAR_PWM_BC_DutyCycleUpdate(Motor0_BLDC_SCALAR_HallLearning.amplitude);
      Motor0_BLDC_SCALAR_ValidationAndUpdate();
    }
    Motor0_BLDC_SCALAR_HallLearning.count++;
  }
  else
  {
    Motor0_BLDC_SCALAR_Hall.hall_learning_flag = (uint8_t)BLDC_SCALAR_HALL_LEARNING_FLAG_DISABLED;
  }
}
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U) */

RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PatternInitiator(uint8_t curpos)
{
  uint8_t pattern_index;         /* Index of the pattern */
  uint16_t mcmval;       /* Actual multi-channel pattern */
  uint16_t mcmshadow;    /* Shadow multi-channel pattern */
  uint8_t direction = (uint8_t) Motor0_BLDC_SCALAR.motor_set_direction & BLDC_SCALAR_HALL_DIRECTION_INDEX;   /* Intended direction */

  /* Load hall and multi-channel pattern in shadow and perform immediate transfer */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
      (uint8_t) (Motor0_BLDC_SCALAR_Hall.hall_pattern[curpos + (uint32_t) direction]));
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateHallPattern();

  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetMultiChannelPattern(
      (uint16_t) Motor0_BLDC_SCALAR.mc_pattern[Motor0_BLDC_SCALAR_PWM_BC.modulation_type][(curpos) + (uint8_t) direction]);
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateMultiChannelPattern();

  /* Prepare for block commutation for phases which are conducting */
  mcmval = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetMultiChannelPattern();
  Motor0_BLDC_SCALAR_PWM_BC.immediate_modulation_ptr(mcmval);

  /*
   * Load next hall and multi-channel pattern in shadow registers to prepare for the
   * shadow transfer when correct hall event occurs
   */
  pattern_index = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetExpectedPattern();
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
      (uint8_t) (Motor0_BLDC_SCALAR_Hall.hall_pattern[(uint8_t) pattern_index + (uint32_t) direction]));
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetMultiChannelPattern(
      (uint16_t) Motor0_BLDC_SCALAR.mc_pattern[Motor0_BLDC_SCALAR_PWM_BC.modulation_type][(pattern_index) + (uint8_t) direction]);

  /* Prepare for block commutation for a phase which is inactive */
  mcmval = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetMultiChannelPattern();
  mcmshadow = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetShadowMultiChannelPattern();
  Motor0_BLDC_SCALAR_PWM_BC.shadow_modulation_ptr(mcmval, mcmshadow);
}

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
BLDC_SCALAR_STATE_IDENTIFICATION_t Motor0_BLDC_SCALAR_State_Identification(void)
{
  BLDC_SCALAR_STATE_IDENTIFICATION_t status = BLDC_SCALAR_STATE_IDENTIFICATION_PROGRESS;
  uint32_t speed;
  /* 3 hall events are detected */
  if (Motor0_BLDC_SCALAR_HALL_CatchFree.state_identification_done == 1U)
  {
    /* Calculate the speed and change the status */
    Motor0_BLDC_SCALAR_SPEED_POS_HALL_DisableEvent(XMC_POSIF_IRQ_EVENT_CHE);
    Motor0_BLDC_SCALAR_HALL_CatchFree.cf_capval = (Motor0_BLDC_SCALAR_HALL_CatchFree.cf_capval >> 1U) * BLDC_SCALAR_HALL_EVENTS_PER_CYCLE;
    speed = (Motor0_BLDC_SCALAR_SPEED_POS_HALL.speed_constant / (Motor0_BLDC_SCALAR_HALL_CatchFree.cf_capval));
    speed = ((speed * Motor0_BLDC_SCALAR.speed_mech_scale) >> BLDC_SCALAR_SPEED_SCALE_RES);
    Motor0_BLDC_SCALAR.motor_speed = (int32_t)((int32_t)speed * Motor0_BLDC_SCALAR_HALL_CatchFree.identified_direction);
    status = BLDC_SCALAR_STATE_IDENTIFICATION_COMPLETED;
  }
  else
  {
    /* Wait for timeout */
    Motor0_BLDC_SCALAR_HALL_CatchFree.catch_free_wait_counter++;
    if (Motor0_BLDC_SCALAR_HALL_CatchFree.catch_free_wait_counter >= Motor0_BLDC_SCALAR_HALL_CatchFree.cf_detection_timeout)
    {
      Motor0_BLDC_SCALAR.motor_speed = 0;
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_DisableEvent(XMC_POSIF_IRQ_EVENT_CHE);
      status = BLDC_SCALAR_STATE_IDENTIFICATION_COMPLETED;
    }
  }
  return status;
}
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U) */
