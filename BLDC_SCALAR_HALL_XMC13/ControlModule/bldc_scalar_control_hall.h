/**
 * @file bldc_scalar_control_hall.h
 * @brief Hall sensor feedback control algorithm
 * @date 2016-09-08
 * @cond
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
 * @endcond
 *
 */
#ifndef BLDC_SCALAR_CTRL_HALL_H
#define BLDC_SCALAR_CTRL_HALL_H

/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup ControlModule
 * @brief  Control algorithm for BLDC motor control <br>
 * @{
 */


/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "bldc_scalar_control_scheme.h"

/***********************************************************************************************************************
 * MACRO
 **********************************************************************************************************************/
#define  BLDC_SCALAR_HALL_MCM(EP,CP)          (((uint32_t)EP << 3) | (uint32_t)CP) /*!< This gives the current and expected hall pattern in a PCONF register format.*/
#define BLDC_SCALAR_HALL_EVENTS_PER_CYCLE (6U)    /*!< Number of hall events per electrical revolution */

#define BLDC_SCALAR_HALL_LEARNING_NUM_OF_PATTERNS    (14U) /*!< Number of hall patterns captured by hall learning algorithm */
#define BLDC_SCALAR_HALL_LEARNING_OPEN_LOOP_COUNT (14U)    /*!< Number of tries to capture hall pattern */

/***********************************************************************************************************************
 * ENUMS
 **********************************************************************************************************************/
/**
 * Enumerates hall learning flag state
 */
typedef enum BLDC_SCALAR_HALL_LEARNING_FLAG
{
  BLDC_SCALAR_HALL_LEARNING_FLAG_DISABLED = 0U,           /*!< Hall learning completed or disabled */
  BLDC_SCALAR_HALL_LEARNING_FLAG_ENABLED  = 1U           /*!< Hall learning is in progress */
} BLDC_SCALAR_HALL_LEARNING_FLAG_t;


/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
/**
 * @brief control parameters of the hall learning algorithm.
 */
typedef struct BLDC_SCALAR_HALL_LEARNING
{
  uint32_t ol_pattup_count;                    /*!< Number of count of phase U one match interrupt after
                                                    that next open loop pattern is applied */
  uint32_t ol_count;                           /*!< Number of pattern count in which motor runs in open
                                                    loop.*/
  uint32_t adapt_algoindex;                    /*!< Number of pattern count in which motor runs in
                                                    open loop.
                                                    Maximum value of this is equal to openloop_count.*/
  uint32_t count;                              /*!< Number of intermediate value in open loop.*/
  uint16_t capt_outpatt[14];                   /*!< This array captures the 14 sample of output pattern in open loop.*/
  uint16_t amplitude;                         /*!< This is the voltage applied in open loop based on gui
                                                    configuration*/
  uint8_t  capt_hallpatt[14];                  /*!< This array capture the 14 sample of hall pattern in open loop.*/
  uint8_t  ol_iter_count;                      /*!< This is the number of iteration count in which motor run in open
                                                    loop.*/
  uint8_t ol_arrayindex;                       /*!< This is the index of open loop pattern array.*/
  uint16_t  openloop_mc_pattern[16];           /*!< open loop multi-channel pattern used to lock the motor */
  uint16_t  closedloop_mc_pattern[7];          /*!< Use this pattern array and configure in the user_config.h file */
} BLDC_SCALAR_HALL_LEARNING_t;

/**
 * @brief hall sensor related parameters
 */
typedef struct BLDC_SCALAR_HALL
{
  uint8_t                    hall_pattern[16];           /*!< Hall pattern for positive and negative direction */
  volatile uint8_t           hall_learning_flag;           /*!< hall pattern detection done*/
  uint8_t                    prev_hall_pos;                /*!< to store previous captured hall pattern - used in wrong hall event to identify hall failure */
} BLDC_SCALAR_HALL_t;

/**
 * @brief Structure for catch free running motor feature
 */
typedef struct BLDC_SCALAR_HALL_CATCH_FREE
{
    uint8_t                    state_identification_done;    /*!< flag to indicate motor state is identified */
    uint32_t                   cf_capval;                    /*!< Speed capture value in state identification state */
    uint32_t                   catch_free_wait_counter;      /*!< run time counter for state identification state */
    int32_t                    identified_direction;         /*!< initial direction of rotation */
    uint8_t                    dir_acquired;                 /*!< flag to indicate that direction is captured in state identification state */
    uint32_t                   sample_capture_counter;       /*!< run time counter for hall edge detection */
    int32_t                    cf_max_speed;                /*!< threshold speed for the catch free running motor */
    uint32_t                   cf_detection_timeout;        /*!< Timeout for the free running motor detection */
} BLDC_SCALAR_HALL_CATCH_FREE_t;

/***********************************************************************************************************************
 * EXTERN
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
extern BLDC_SCALAR_HALL_LEARNING_t Motor0_BLDC_SCALAR_HallLearning;
#endif

extern BLDC_SCALAR_HALL_t Motor0_BLDC_SCALAR_Hall;

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
extern BLDC_SCALAR_HALL_CATCH_FREE_t Motor0_BLDC_SCALAR_HALL_CatchFree;
#endif
#ifdef __cplusplus
   extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Locks the motor at every 60 degrees (at the middle of the hall state change) with the configured open loop speed.
 * This captures the 14 hall and corresponding multi-channel patterns and performs validation to get the commutation table.
 *
 * \par<b>Note</b><br>
 * Read closedloop_mc_pattern to get the closed loop multi-channel pattern corresponding to
 * hall sequence 1 (1 -> 3 -> 2 -> 6 -> 4 -> 5) or hall sequence 2 (1 -> 5 -> 4 -> 6 -> 2 -> 3).
 * closedloop_mc_pattern[0] gives the hall sequence number (1 or 2) and remaining 6 values are the closed loop
 * multi-channel pattern to be configured in bldc_scalar_user_config.h
 */
void Motor0_BLDC_SCALAR_HallPatternCapture(void);
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
/**
 * @return BLDC_SCALAR_STATE_IDENTIFICATION_t status of the state identification \n
 * BLDC_SCALAR_STATE_IDENTIFICATION_PROGRESS  - if 3 hall events are not detected within timeout period \n
 * BLDC_SCALAR_STATE_IDENTIFICATION_COMPLETED - if 3 hall events are detected or timeout whichever is earlier \n <br>
 *
 * \par<b>Description:</b><br>
 * Waits for the 3 hall events or timeout. If hall events are detected, this function determines the speed of the free running motor.
 */
BLDC_SCALAR_STATE_IDENTIFICATION_t Motor0_BLDC_SCALAR_State_Identification(void);
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Finds if motor is stalled based on stall detection timeout (@ref MOTOR0_BLDC_SCALAR_STALL_DETECTION_TIME_mS) and
 * time difference between last captured value and time since last hall event (@ref MOTOR0_BLDC_SCALAR_STALL_TIME_DIFF_RATIO)
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_StallDetection(void)
{
  uint16_t timer = 0U;          /* Timer value of the CCU4 capture slice */
  uint32_t curr_psc = 0U;        /* prescaler value */
  uint32_t elapsed_time = 0U;   /* Elapsed time since last hall event */
  int32_t diff = 0;             /* Difference between previous capture value and elapsed time */
  uint32_t comparison_time;      /* Time to which difference between captured values is compared */

  Motor0_BLDC_SCALAR.stall_detection_counter++;

  /*
   * No Hall event is detected within the configured stall detection time
   */
  if((Motor0_BLDC_SCALAR.stall_detection_counter > Motor0_BLDC_SCALAR.stall_detection_count))
  {
    Motor0_BLDC_SCALAR.error_status |= ((uint32_t) 1 << (uint32_t) BLDC_SCALAR_EID_STALL);
    Motor0_BLDC_SCALAR.msm_state = (BLDC_SCALAR_MSM_t)BLDC_SCALAR_MSM_ERROR;
    Motor0_BLDC_SCALAR_MotorStop();
  }
  /*
   * Ignore stall detection for first 6 hall events
   */
  else if (Motor0_BLDC_SCALAR.stall_check > BLDC_SCALAR_STALL_IGNORE_COUNT)
  {
    /*
     * Check if there is large difference in the captured values between this hall event and last hall event
     * Difference ratio is governed by MOTOR0_BLDC_SCALAR_STALL_TIME_DIFF_RATIO
     * Configure higher ratio value if high ramp rate or step input is required in the application to avoid false stall detection error
     */
    /* Read the capture timer value */
    timer = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetCapTimerVal();
    curr_psc = ((uint32_t)(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE->FPC & CCU4_CC4_FPC_PVAL_Msk) >> (uint32_t)CCU4_CC4_FPC_PVAL_Pos);
    elapsed_time = BLDC_SCALAR_SPEED_POS_HALL_Cap_Array[(curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)] + (((uint32_t)1 << (uint32_t)(curr_psc - MOTOR0_BLDC_SCALAR_CCU4_PRESCALER)) * timer);

    /* Stall is detected if the difference in the previous capture value and elapsed_time is greater than ratio */
    diff = ((int32_t)elapsed_time - (int32_t)Motor0_BLDC_SCALAR_SPEED_POS_HALL.capval);
    if (diff < 0)
    {
      diff = -1 * diff;
    }
    comparison_time = ((Motor0_BLDC_SCALAR_SPEED_POS_HALL.capval * Motor0_BLDC_SCALAR.stall_time_diff_ratio) >> BLDC_SCALAR_SHIFT_4);
    /* Stop the motor if time difference is more than the ratio */
    if (diff > (int32_t)(comparison_time))
    {
      Motor0_BLDC_SCALAR.error_status |= ((uint32_t) 1 << (uint32_t) BLDC_SCALAR_EID_STALL);
      Motor0_BLDC_SCALAR.msm_state = (BLDC_SCALAR_MSM_t)BLDC_SCALAR_MSM_ERROR;
      Motor0_BLDC_SCALAR_MotorStop();
    }
  }

}
#endif


/**
 * @param output Output of the control scheme
 * @param amplitude Modified amplitude based on direction control
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Decides when to change the direction of rotation if seamless bi-direction control is enabled
 * This returns the absolute value of the amplitude to be applied to PWM
 *
 * \par<b>Execution Time:</b><br>
 * using O3 optimization level \n
 * without bi-direction control: <b>0.120 uSec</b> \n
 * with bi-direction control (normal operation): <b>0.820 uSec </b>\n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_DirectionControl(int32_t output, uint32_t *amplitude)
{
#if(MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 1U)
  uint8_t index;     /* hall pattern */
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  int32_t speed;     /* set speed from user or from potentiometer */
#endif

  /*
   * Change the direction when control scheme output is of reverse polarity of the set motor direction
   * Get the absolute value of the amplitude
   */
  if (output < 0)
  {
    output = -1 * output;

    if (Motor0_BLDC_SCALAR.motor_set_direction == BLDC_SCALAR_POSITIVE_DIR)
    {
      Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_NEGATIVE_DIR;
      index = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern();
      Motor0_BLDC_SCALAR_PatternInitiator(index);
    }
  }
  else if (output > 0)
  {
    if (Motor0_BLDC_SCALAR.motor_set_direction == BLDC_SCALAR_NEGATIVE_DIR)
    {
      Motor0_BLDC_SCALAR.motor_set_direction = BLDC_SCALAR_POSITIVE_DIR;
      index = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetLastHallPattern();
      Motor0_BLDC_SCALAR_PatternInitiator(index);
    }
  }
  else
  {

  }
  *amplitude = (uint32_t)output;

  /* zero speed handling in speed control with bi-directional control */
  #if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
    speed = Motor0_BLDC_SCALAR.analogip_val;
  #else
    speed = Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
  #endif
  if (speed == 0)
  {
    /* Limiting speed to 0 when motor speed with in the range of 2% */
    if ((Motor0_BLDC_SCALAR.motor_speed < Motor0_BLDC_SCALAR.min_speed) && (Motor0_BLDC_SCALAR.motor_speed > -Motor0_BLDC_SCALAR.min_speed))
    {
      Motor0_BLDC_SCALAR.motor_speed = 0;
      Motor0_BLDC_SCALAR.motor_current = 0;
      Motor0_BLDC_SCALAR_SpeedControl_PI.ik = 0;

      /* Reset speed calculation related variables */
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearSpeedFilter();

      #if (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL)
      Motor0_BLDC_SCALAR.motor_current = 0;
      Motor0_BLDC_SCALAR_CurrentControl_PI.ik = 0;
      #endif
    }
  }
  #endif

#else
  /* Absolute value of the output voltage */
  output = output * Motor0_BLDC_SCALAR.motor_set_direction;
  if (output < 0)
  {
    output = 0;
  }
  *amplitude = (uint32_t) output;
#endif
}


/**
 * @param curpos Current hall state
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes hall and multi-channel pattern as per current hall state @ref curpos.
 * This performs the immediate shadow transfer of patterns and also loads next patterns in the shadow register.
 *
 * \par<b>Note</b><br>
 * This should be called before switching to closed loop to make sure that hall and multi-channel patterns are loaded
 * in actual and shadow registers of POSIF.
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PatternInitiator(uint8_t curpos);

/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif
