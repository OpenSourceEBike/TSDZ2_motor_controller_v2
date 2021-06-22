/**
 * @file bldc_scalar_hall_state_machine.c
 * @brief system timer event used for state machine
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


#if(MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE==1)
#include "../uCProbe/uCProbe.h"
#endif

/*********************************************************************************************************************
 * MACROS
 * *******************************************************************************************************************/
#define BLDC_SCALAR_HALL_MOTOR_DIR_INDEX        (0x8U)
#define BLDC_SCALAR_HALL_CAPVAL_POS             (0x8U)
#define BLDC_SCALAR_BOOTSTRAP_CMP_VAL           (0xFFFFU)
#define BLDC_SCALAR_PRESCALER_CMP_VALUE        (11U)
/*********************************************************************************************************************
 * Local API's
 * ******************************************************************************************************/
/* Function for the state - START */
static void Motor0_BLDC_SCALAR_MSM_START_Func(void);
/* Exit Function for the state - START */
static void Motor0_BLDC_SCALAR_MSM_START_Exit_Func(void);

#if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U)
/* Entry Function for the state - IDLE */
static void Motor0_BLDC_SCALAR_MSM_IDLE_Entry_Func(void);
/* Function for the state - IDLE */
static void Motor0_BLDC_SCALAR_MSM_IDLE_Func(void);
/* Exit Function for the state - IDLE */
static void Motor0_BLDC_SCALAR_MSM_IDLE_Exit_Func(void);
#endif

/* Entry Function for the state - NORMAL_OPERATION */
static void Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func(void);
/* Function for the state - NORMAL_OPERATION */
static void Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Func(void);

#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
/* Entry Function for the state - HALL_LEARNING */
static void Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Entry_Func(void);
/* Function for the state - HALL_LEARNING */
static void Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Func(void);
#endif

static void Motor0_BLDC_SCALAR_MSM_ERROR_Func(void);

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
/* Entry Function for the state - STATE_IDENTIFICATION */
static void Motor0_BLDC_SCALAR_MSM_STATE_IDENTIFICATION_Entry_Func(void);
/* Function for the state - STATE_IDENTIFICATION */
static void Motor0_BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION_Func(void);
/* Exit Function for the state - STATE_IDENTIFICATION */
static void Motor0_BLDC_SCALAR_MSM_STATE_IDENTIFICATION_Exit_Func(void);
#endif


#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
/* Entry Function for the state - BOOTSTRAP */
static void Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Entry_Func(void);
/* Function for the state - BOOTSTRAP */
static void Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Func(void);
/* Exit Function for the state - BOOTSTRAP */
static void Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Exit_Func(void);
#endif


/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup Interrupt Interrupts
 * @brief  Interrupt Service Routines  <br>
 * @{
 */
/**
 * @param None
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Systick event handler for motor state machine \n
 * This is the lowest priority interrupt which handles the state transitions and also
 * performs less time critical tasks like ramp, potentiometer reading.\n
 */
void SysTick_Handler(void)
{
  /* Call motor control state machine */
  Motor0_BLDC_SCALAR_MSM();
}

/**
 * @}
 */
/**
 * @}
 */

RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_MSM(void)
{
  switch (Motor0_BLDC_SCALAR.msm_state)
  {
    case BLDC_SCALAR_MSM_NORMAL_OPERATION:
      Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Func();
      break;

#if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U)
    case BLDC_SCALAR_MSM_IDLE:
      Motor0_BLDC_SCALAR_MSM_IDLE_Func();
      break;
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
    case BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION:
      Motor0_BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION_Func();
      break;
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
    case BLDC_SCALAR_MSM_BOOTSTRAP:
      Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Func();
      break;
#endif

    case BLDC_SCALAR_MSM_ERROR:
      Motor0_BLDC_SCALAR_MSM_ERROR_Func();
      break;

    case BLDC_SCALAR_MSM_START:
      Motor0_BLDC_SCALAR_MSM_START_Func();
      break;

#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
    case BLDC_SCALAR_MSM_HALL_LEARNING:
      Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Func();
      break;
#endif

    case BLDC_SCALAR_MSM_STOP:
      Motor0_BLDC_SCALAR_MotorStop();
      break;

    default:
      break;

  }

  if (Motor0_BLDC_SCALAR.error_status != 0U)
  {
    Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
  }

  #if (MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE == 1)
  Motor0_BLDC_SCALAR_uCProbe_Scheduler();
  #endif
}

/****************************start: BLDC_SCALAR_MSM_START ***********************/
/**
 * START state:
 * Initialize Motor control variables
 * Enable inverter
 * Enable interrupt for ctrap and protection
 */
static void Motor0_BLDC_SCALAR_MSM_START_Func(void)
{
  /*Initialize all run time parameters*/
  Motor0_BLDC_SCALAR_MotorParamInit();
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
  /*Enable inverter*/
  Motor0_BLDC_SCALAR_PWM_BC_InverterEnable();
#endif

#if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
  /* Clear if any pending trap events and enable the trap */
  Motor0_BLDC_SCALAR_PWM_BC_ClearTrapEvent();
  Motor0_BLDC_SCALAR_PWM_BC_EnableTrap();
#endif
  /* ISR Init for trap */
  BLDC_SCALAR_NVIC_NodeInit(MOTOR0_BLDC_SCALAR_CTRAP_NODE, MOTOR0_BLDC_SCALAR_TRAP_NVIC_PRIO);

#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U))
  /* ISR Init for VADC channel event handler*/
  BLDC_SCALAR_NVIC_NodeInit(MOTOR0_BLDC_SCALAR_VADC_PROTECTION_NODE, MOTOR0_BLDC_SCALAR_VADC_PROTECTION_NVIC_PRIO);
#endif

  Motor0_BLDC_SCALAR_MSM_START_Exit_Func();
}

/*
 * START exit:
 * Next state
 * STATE_IDENTIFICATION: if catch free running motor feature is enabled
 * BOOTSTRAP: if catch free running motor feature is disabled and bootstrap feature is enabled
 * HALL_LEARNING: if catch free running motor feature is disabled and bootstrap feature is disabled, and hall learning feature is enabled
 * NORMAL_OPERATION: if catch free running motor, bootstrap and hall learning features are disabled
 */
static void Motor0_BLDC_SCALAR_MSM_START_Exit_Func(void)
{
#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
  Motor0_BLDC_SCALAR_MSM_STATE_IDENTIFICATION_Entry_Func();

#else  /* catch-free disabled */
    /*Current amplifier bias voltage calibration*/
#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U)
  Motor0_BLDC_SCALAR_AmpBiasVoltCalibration();
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U) */
#endif

  #if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
    /*Bootstrap Configuration */
    Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Entry_Func();
  #elif (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
    Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Entry_Func();
  #else
    Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
  #endif
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U) */
}

/****************************end: BLDC_SCALAR_MSM_START ***********************/

/****************************start: BLDC_SCALAR_MSM_NORMAL_OPERATION ***********************/
/*
 * NORMAL_OPERATION entry:
 * Prepare hall and multi-channel pattern and start the POSIF and CCU4
 * Start the CCU8 for PWM
 * Disable correct hall event
 * Enable wrong hall event, multi-channel pattern shadow transfer event and CCU8 one match event
 */
static void Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func(void)
{
  /* Disable correct hall event */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_DisableEvent(XMC_POSIF_IRQ_EVENT_CHE);
  Motor0_BLDC_SCALAR_Hall.prev_hall_pos = (uint8_t) Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallPosition();
  Motor0_BLDC_SCALAR_PatternInitiator(Motor0_BLDC_SCALAR_Hall.prev_hall_pos);
  NVIC_ClearPendingIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);
#if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U)
  /*
     * Initialize Phase-V period match event and Bind Phase-U period match event SR(service request)
     * to interrupt node for trap.
     */
  BLDC_SCALAR_CCU8_Event_Init(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[1U],
  (XMC_CCU8_SLICE_IRQ_ID_t)XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH, (XMC_CCU8_SLICE_SR_ID_t)MOTOR0_BLDC_SCALAR_CCU8_CTRAP_EVT2_SR);
#endif/*end of #if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U)*/


  /* POSIF is in running mode in MOTOR_STATE_IDENTIFICATION state */
  if (Motor0_BLDC_SCALAR.msm_state != BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION)
  {
    /* Start POSIF */
    Motor0_BLDC_SCALAR_SPEED_POS_HALL_Start();

    /* ISR Init for wrong hall event*/
    BLDC_SCALAR_NVIC_NodeInit(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE,MOTOR0_BLDC_SCALAR_HALL_NVIC_PRIO);
  }

  /* ISR Init for pattern update handler */
  BLDC_SCALAR_NVIC_NodeInit(MOTOR0_BLDC_SCALAR_PATTERN_UPDATE_NODE, MOTOR0_BLDC_SCALAR_PATTERN_UPDATE_NVIC_PRIO);
  /* ISR Init for control loop */
  BLDC_SCALAR_NVIC_NodeInit(MOTOR0_BLDC_SCALAR_CTRL_LOOP_NODE, MOTOR0_BLDC_SCALAR_CTRL_LOOP_NVIC_PRIO);

  if ((Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_START) || (Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION))
  {
    /* Start CCU8 */
    Motor0_BLDC_SCALAR_CCU8_PWM_Start();
  }
  Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_NORMAL_OPERATION;
}

/*
 * NORMAL_OPERATION state:
 * Potentiometer measurement
 * Ramp
 * Stall detection
 * zero duty condition handling
 */
static void Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Func(void)
{
  uint32_t curr_psc;        /* Prescaler value */
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
  int32_t setval_diff;          /* difference between ramp input and output value */
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  /* Potentiometer measurement */
  Motor0_BLDC_SCALAR_AnalogIpMeasurement();
#endif

  /************************** Ramp start**************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
  Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_Ramp.set_value;
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR.analogip_val;
#else  /* potentiometer disabled */
  #if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  /* Speed control */
    Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
  #elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
    /* Current control */
    Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR_CurrentControl.user_current_set;
  #else
    /* Voltage control */
    Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set;
  #endif

#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) */

  setval_diff =  ((Motor0_BLDC_SCALAR_Ramp.input_value) - Motor0_BLDC_SCALAR_Ramp.set_value) *
                 Motor0_BLDC_SCALAR.motor_set_direction;

  /* Find whether ramp up or down is required based on set value */
  if (setval_diff < 0)
  {
    Motor0_BLDC_SCALAR_Ramp.ramp_rate = Motor0_BLDC_SCALAR_Ramp.ramp_down_rate;
  }
  else
  {
    Motor0_BLDC_SCALAR_Ramp.ramp_rate = Motor0_BLDC_SCALAR_Ramp.ramp_up_rate;
  }

  #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U) && (MOTOR0_BLDC_SCALAR_ENABLE_RAMP_DOWN_VOLTAGE_CLAMPING == 1U))
  if (setval_diff < 0)
  {
    /* Ramp down - If DC Link voltage within threshold limit then only ramp down */
    if (Motor0_BLDC_SCALAR.dclink_voltage < Motor0_BLDC_SCALAR.max_dc_link_voltage)
    {
      Motor0_BLDC_SCALAR_Ramp_Linear();
    }
  }
  else
  {
    Motor0_BLDC_SCALAR_Ramp_Linear();
  }
  #else /* #if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U) */

  Motor0_BLDC_SCALAR_Ramp_Linear();
  #endif
#else /*#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR.analogip_val;
#else  /* potentiometer disabled */
  #if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  /* Speed control */
    Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
  #elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
    /* Current control */
    Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_CurrentControl.user_current_set;
  #else
    /* Voltage control */
    Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set;
  #endif

#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) */
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */

  /************************** Ramp end**************************/

  /************************** Stall detection start**************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
  if (Motor0_BLDC_SCALAR.amplitude < Motor0_BLDC_SCALAR.stall_min_amplitude)
  {
    if (Motor0_BLDC_SCALAR.set_val == 0)
    {
      Motor0_BLDC_SCALAR.stall_check = 1U;
    }
#endif
    /* zero speed handling */
    curr_psc = (uint32_t)((uint32_t)MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE->FPC >> BLDC_SCALAR_HALL_CAPVAL_POS);
    /* reset the speed calculation related variables when prescaler is greater 11 */
    if (curr_psc > BLDC_SCALAR_PRESCALER_CMP_VALUE)
    {
      /* Reset speed calculation related variables */
      Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearSpeedFilter();
      Motor0_BLDC_SCALAR.motor_speed = 0;
    }
#if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U)
  }

  else
  {
    Motor0_BLDC_SCALAR_StallDetection();
  }
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_STALL_DETECTION == 1U) */
  /************************** Stall detection end**************************/

  /*************************IDLE condition check*************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U)
  /* Switch off all the PWM outputs when reference is zero and duty is zero */
  if ((Motor0_BLDC_SCALAR.set_val == 0) && (Motor0_BLDC_SCALAR.amplitude == 0U))
  {
    Motor0_BLDC_SCALAR_MSM_IDLE_Entry_Func();
  }
#endif

}
/****************************end: BLDC_SCALAR_MSM_NORMAL_OPERATION ***********************/


/****************************start: BLDC_SCALAR_MSM_HALL_LEARNING ***********************/
#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
/*
 * HALL_LEARNING entry:
 * Start CCU8 for PWM
 * Stop POSIF if already running
 */
static void Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Entry_Func(void)
{
  if (Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_START)
  {
    Motor0_BLDC_SCALAR_CCU8_PWM_Start();
  }
  if (Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION)
  {
    /* Stop POSIF */
    Motor0_BLDC_SCALAR_SPEED_POS_HALL_Stop();
    NVIC_ClearPendingIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);
    /* ISR Init for wrong hall event and correct hall event handler*/
    NVIC_DisableIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);
  }
  Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_HALL_LEARNING;
}

/*
 * HALL_LEARNING state:
 * Lock the rotor at the middle of the hall change @0, 60, 120 .... degrees
 * Change to  NORMAL_OPERATION state if hall learning is successful
 */
static void Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Func(void)
{
  /* HALL Learning enabled */
  Motor0_BLDC_SCALAR_HallPatternCapture();
 if ((uint8_t)BLDC_SCALAR_HALL_LEARNING_FLAG_DISABLED == Motor0_BLDC_SCALAR_Hall.hall_learning_flag)
 {
   Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
 }

}
#endif
/****************************end: BLDC_SCALAR_MSM_HALL_LEARNING ***********************/

/****************************start: BLDC_SCALAR_MSM_STATE_IDENTIFICATION****************/
/*
 * STATE_IDENTIFICATION entry:
 * Prepare initial hall and multi-channel pattern
 * Start POSIF
 * Enable correct and wrong hall event
 */

#if (MOTOR0_BLDC_SCALAR_ENABLE_CATCH_FREE == 1U)
static void Motor0_BLDC_SCALAR_MSM_STATE_IDENTIFICATION_Entry_Func(void)
{
  uint8_t pattern_index;       /* hall pattern index */
  uint8_t direction = (uint8_t) Motor0_BLDC_SCALAR.motor_set_direction & BLDC_SCALAR_HALL_MOTOR_DIR_INDEX;

  Motor0_BLDC_SCALAR_HALL_CatchFree.identified_direction = Motor0_BLDC_SCALAR.motor_set_direction;

  /* Load initial hall pattern and start the POSIF */
  Motor0_BLDC_SCALAR_Hall.prev_hall_pos = (uint8_t) Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallPosition();

  /* Update the hall pattern in shadow register and perform immediate transfer */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
      (uint8_t) (Motor0_BLDC_SCALAR_Hall.hall_pattern[Motor0_BLDC_SCALAR_Hall.prev_hall_pos + (uint32_t) direction]));
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateHallPattern();
  /*Get Expected Pattern*/
  pattern_index = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetExpectedPattern();
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetHallPattern(
      (uint8_t) (Motor0_BLDC_SCALAR_Hall.hall_pattern[(uint8_t) pattern_index + (uint32_t) direction]));

  /* Start POSIF */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_Start();
  /* ISR Init for wrong hall event and correct hall event handler*/
  BLDC_SCALAR_NVIC_NodeInit(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE, MOTOR0_BLDC_SCALAR_HALL_NVIC_PRIO);
  /*Change Motor Control State to motor state identification */
  Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION;
}

/*
 * STATE_IDENTIFICATION state:
 * Wait for detection timeout or state identification flag to be set; whichever is earlier
 */
static void Motor0_BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION_Func(void)
{
  if (BLDC_SCALAR_STATE_IDENTIFICATION_COMPLETED == Motor0_BLDC_SCALAR_State_Identification())
  {
    Motor0_BLDC_SCALAR_MSM_STATE_IDENTIFICATION_Exit_Func();
  }
}

/*
 * STATE_IDENTIFICATION exit:
 * Disable correct hall event
 * Next state:
 * NORMAL_OPERATION: if motor is freely running in the intended direction with speed greater than threshold speed OR
 *                   if motor is running in reverse direction with speed less than threshold speed
 * ERROR: if motor is freely running in reverse direction with speed greater than threshold speed OR
 *        if identified speed is greater than threshold speed with highside sync rectification PWM
 * BOOTSTRAP: if motor is freely running in the intended direction with speed less than threshold speed and bootstrap is enabled OR
 *            if motor is running in reverse direction with speed less than threshold speed and bootstrap is enabled
 * HALL_LEARNING: if motor is freely running in the intended direction with speed less than threshold speed and bootstrap is disabled and hall learning is enabled OR
 *            if motor is running in reverse direction with speed less than threshold speed and bootstrap is disabled and hall learning is enabled
 */
static void Motor0_BLDC_SCALAR_MSM_STATE_IDENTIFICATION_Exit_Func(void)
{
  /* Disable correct hall event */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_DisableEvent(XMC_POSIF_IRQ_EVENT_CHE);

  /* Motor is freely running in the intended direction */
  if (Motor0_BLDC_SCALAR_HALL_CatchFree.identified_direction == Motor0_BLDC_SCALAR.motor_set_direction)
  {
#if (MOTOR0_BLDC_SCALAR_MODULATION == BLDC_SCALAR_PWM_HIGHSIDE_SYNCHRECTI)
    /* Closed loop switching is not allowed for Synchronous rectification PWM modulation if speed is greater than threshold speed */
    if ((Motor0_BLDC_SCALAR.motor_speed > (int32_t)(Motor0_BLDC_SCALAR_HALL_CatchFree.cf_max_speed)) ||
        (Motor0_BLDC_SCALAR.motor_speed < -(Motor0_BLDC_SCALAR_HALL_CatchFree.cf_max_speed)))
    {
      /* Change the state to ERROR and stop the motor */
      Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
      Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_MOTOR_FREE_RUNNING;
      Motor0_BLDC_SCALAR_MotorStop();
    }
    /* speed is less than threshold speed */
    else
    {
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) && (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U))
      Motor0_BLDC_SCALAR_Ramp.set_value = Motor0_BLDC_SCALAR.motor_speed;
#endif
        /*Current amplifier bias voltage calibration*/
    #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U))
    #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U)
      Motor0_BLDC_SCALAR_AmpBiasVoltCalibration();
    #endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U) */
    #endif

    #if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
        /*Bootstrap Configuration */
        Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Entry_Func();
    #elif (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
        if (BLDC_SCALAR_HALL_LEARNING_FLAG_DISABLED == Motor0_BLDC_SCALAR_Hall.hall_learning_flag)
        {
          Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Entry_Func();
        }
    #else
        Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
    #endif
    }
#else
    /* if speed is greater than threshold speed, go to closed loop operation */
    if ((Motor0_BLDC_SCALAR.motor_speed > (int32_t)Motor0_BLDC_SCALAR_HALL_CatchFree.cf_max_speed) ||
        (Motor0_BLDC_SCALAR.motor_speed < -Motor0_BLDC_SCALAR_HALL_CatchFree.cf_max_speed))
    {
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) && (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U))
      Motor0_BLDC_SCALAR_Ramp.set_value = Motor0_BLDC_SCALAR.motor_speed;
#endif
      /* Normal operation */
      Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
    }

    /* Speed is less than threshold */
    else
    {
      /*Current amplifier bias voltage calibration*/
    #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U))
    #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U)
      Motor0_BLDC_SCALAR_AmpBiasVoltCalibration();
    #endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U) */
    #endif

    #if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
      /*Bootstrap Configuration */
      Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Entry_Func();
    #elif (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
      if (BLDC_SCALAR_HALL_LEARNING_FLAG_DISABLED == Motor0_BLDC_SCALAR_Hall.hall_learning_flag)
      {
        Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Entry_Func();
      }
    #else
      Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
    #endif
    }
#endif
  }
  /* reverse direction free running */
  else
  {
    if ((Motor0_BLDC_SCALAR.motor_speed > (int32_t)Motor0_BLDC_SCALAR_HALL_CatchFree.cf_max_speed) ||
        (Motor0_BLDC_SCALAR.motor_speed < -Motor0_BLDC_SCALAR_HALL_CatchFree.cf_max_speed))
    {
      Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
      Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_MOTOR_FREE_RUNNING;
      Motor0_BLDC_SCALAR_MotorStop();
    }
    else
    {
      /*Current amplifier bias voltage calibration*/
    #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U))
    #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U)
      Motor0_BLDC_SCALAR_AmpBiasVoltCalibration();
    #endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U) */
    #endif

    #if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)
      /*Bootstrap Configuration */
      Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Entry_Func();
    #elif (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
      if (BLDC_SCALAR_HALL_LEARNING_FLAG_DISABLED == Motor0_BLDC_SCALAR_Hall.hall_learning_flag)
      {
        Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Entry_Func();
      }
    #else
      Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
    #endif
    }
  }
}
#endif

/****************************end: BLDC_SCALAR_MSM_STATE_IDENTIFICATION****************/

/****************************start: BLDC_SCALAR_MSM_BOOTSTRAP****************/
/*
 * BOOTSTRAP entry:
 * Compare value = 0xFFFF
 * Stop POSIF
 * Disable hall event
 * Start CCU8
 */
#if (MOTOR0_BLDC_SCALAR_ENABLE_BOOTSTRAP == 1U)

/* Initialize CCU8 slices for bootstrap */
static void Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Entry_Func(void)
{
  /* Update channel 1 compare value (CR1) of slice */
  Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseU((uint16_t)BLDC_SCALAR_BOOTSTRAP_CMP_VAL);
  /* Update channel 1 compare value (CR1) of slice */
  Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseV((uint16_t)BLDC_SCALAR_BOOTSTRAP_CMP_VAL);
  /* Update channel 1 compare value (CR1) of slice */
  Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseW((uint16_t)BLDC_SCALAR_BOOTSTRAP_CMP_VAL);

  /*Enable the shadow transfer for all three consumed slice*/
  Motor0_BLDC_SCALAR_PWM_BC_EnableShadowTransfer();

  if (Motor0_BLDC_SCALAR.msm_state == BLDC_SCALAR_MSM_MOTOR_STATE_IDENTIFICATION)
  {
    /* Stop POSIF */
    Motor0_BLDC_SCALAR_SPEED_POS_HALL_Stop();
    NVIC_ClearPendingIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);
    /* ISR Init for wrong hall event and correct hall event handler*/
    NVIC_DisableIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);
  }

  Motor0_BLDC_SCALAR_CCU8_PWM_Start();

  /*Change Motor Control State Machine to Boot Strap*/
  Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_BOOTSTRAP;

}

/*
 * BOOSTRAP state:
 * Wait for the boostrap time
 */
static void Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Func(void)
{
  if (BLDC_SCALAR_BOOTSTRAP_COMPLETED == Motor0_BLDC_SCALAR_Bootstrap())
  {
    Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Exit_Func();
  }
}

/*
 * BOOTSTRAP exit:
 * Next state:
 * HALL_LEARNING: if hall learning feature is enabled
 * NORMAL_OPERATION: if hall learning feature is disabled
 */
static void Motor0_BLDC_SCALAR_MSM_BOOTSTRAP_Exit_Func(void)
{
#if (MOTOR0_BLDC_SCALAR_HALL_LEARNING == 1U)
  Motor0_BLDC_SCALAR_MSM_HALL_LEARNING_Entry_Func();
#else
  Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
#endif
}
#endif
/****************************end: BLDC_SCALAR_MSM_BOOTSTRAP****************/

/****************************start: BLDC_SCALAR_MSM_ERROR****************/
/*
 * ERROR state:
 * Change the state to STOP when all the errors are cleared
 */
static void Motor0_BLDC_SCALAR_MSM_ERROR_Func(void)
{
/* Change the state to STOP when all the errors are cleared */
  if (Motor0_BLDC_SCALAR.error_status == 0U)
  {
    Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_STOP;
  }
}

/****************************end: BLDC_SCALAR_MSM_ERROR****************/

/****************************start: BLDC_SCALAR_MSM_IDLE****************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_BIDIRECTIONAL_CTRL == 0U)
/*
 * IDLE entry:
 * Multi-channel pattern as 0x00
 * Stop the POSIF
 * Disable hall event, multi-channel shadow transfer event
 * Disable CCU8 one match event
 */
static void Motor0_BLDC_SCALAR_MSM_IDLE_Entry_Func(void)
{
  Motor0_BLDC_SCALAR.motor_speed = 0;
  Motor0_BLDC_SCALAR.motor_current = 0;
  Motor0_BLDC_SCALAR.motor_average_current = 0;

  /* Disable CCU8 outputs by applying multi-channel pattern as 0 */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_SetMultiChannelPattern(0x0U);
  /*Immediate Shadow transfer update of multi-channel pattern*/
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_UpdateMultiChannelPattern();

  /* Stop POSIF */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_Stop();
  /*Disable Inverter*/
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
  Motor0_BLDC_SCALAR_PWM_BC_InverterDisable();
#endif

  NVIC_ClearPendingIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);
  /* ISR disable for wrong hall event and correct hall event handler*/
  NVIC_DisableIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);

  NVIC_DisableIRQ(MOTOR0_BLDC_SCALAR_PATTERN_UPDATE_NODE);
  NVIC_DisableIRQ(MOTOR0_BLDC_SCALAR_CTRL_LOOP_NODE);

  Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_IDLE;

}

/*
 * IDLE state:
 * Potentiometer measurement to update the ref
 * Ramp to update the ref
 */
static void Motor0_BLDC_SCALAR_MSM_IDLE_Func(void)
{
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
  int32_t setval_diff;          /* difference between ramp input and output value */
#endif
  Motor0_BLDC_SCALAR.motor_speed = 0;
  Motor0_BLDC_SCALAR.motor_current = 0;
  Motor0_BLDC_SCALAR.motor_average_current = 0;
  Motor0_BLDC_SCALAR.amplitude = 0U;

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_AnalogIpMeasurement();
#endif

  /************************** Ramp start**************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
  Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_Ramp.set_value;
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR.analogip_val;
#else  /* potentiometer disabled */
  #if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  /* Speed control */
    Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
  #elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
    /* Current control */
    Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR_CurrentControl.user_current_set;
  #else
    /* Voltage control */
    Motor0_BLDC_SCALAR_Ramp.input_value = Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set;
  #endif

#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) */

  setval_diff =  ((Motor0_BLDC_SCALAR_Ramp.input_value) - Motor0_BLDC_SCALAR_Ramp.set_value) * Motor0_BLDC_SCALAR.motor_set_direction;

  /* Find whether ramp up or down is required based on set value */
  if (setval_diff < 0)
  {
    Motor0_BLDC_SCALAR_Ramp.ramp_rate = Motor0_BLDC_SCALAR_Ramp.ramp_down_rate;
  }
  else
  {
    Motor0_BLDC_SCALAR_Ramp.ramp_rate = Motor0_BLDC_SCALAR_Ramp.ramp_up_rate;
  }

  #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U) && (MOTOR0_BLDC_SCALAR_ENABLE_RAMP_DOWN_VOLTAGE_CLAMPING == 1U))
  if (setval_diff < 0)
  {
    /* Ramp down - If DC Link voltage within threshold limit then only ramp down */
    if (Motor0_BLDC_SCALAR.dclink_voltage < Motor0_BLDC_SCALAR.max_dc_link_voltage)
    {
      Motor0_BLDC_SCALAR_Ramp_Linear();
    }
  }
  else
  {
    Motor0_BLDC_SCALAR_Ramp_Linear();
  }
  #else /* #if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U) */
  Motor0_BLDC_SCALAR_Ramp_Linear();
  #endif
#else /*#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR.analogip_val;
#else  /* potentiometer disabled */
  #if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  /* Speed control */
    Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_SpeedControl.user_speed_set;
  #elif ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL))
    /* Current control */
    Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_CurrentControl.user_current_set;
  #else
    /* Voltage control */
    Motor0_BLDC_SCALAR.set_val = Motor0_BLDC_SCALAR_VoltageControl.user_voltage_set;
  #endif

#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U) */
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U) */
  /************************** Ramp end**************************/

  if ((Motor0_BLDC_SCALAR.set_val > 0) || (Motor0_BLDC_SCALAR.set_val < 0))
  {
    Motor0_BLDC_SCALAR_MSM_IDLE_Exit_Func();
  }

}

/*
 * IDLE exit:
 * Reset speed calculation related variables
 * Reset PI buffer
 * Next state:
 * NORMAL_OPERATION
 */
static void Motor0_BLDC_SCALAR_MSM_IDLE_Exit_Func(void)
{
  /* Reset speed calculation related variables */
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearSpeedFilter();

  /* Reset the PI integral buffer */
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  Motor0_BLDC_SCALAR_SpeedControl_PI.ik = 0;
  Motor0_BLDC_SCALAR_SpeedControl_PI.sat_state = 1U;
#endif

#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
  Motor0_BLDC_SCALAR_CurrentControl_PI.ik = 0;
  Motor0_BLDC_SCALAR_CurrentControl_PI.sat_state = 1U;
#endif

#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
  /*Enable inverter*/
    Motor0_BLDC_SCALAR_PWM_BC_InverterEnable();
#endif

  /* Change the state to NORMAL_OPERATION */
  Motor0_BLDC_SCALAR_MSM_NORMAL_OPERATION_Entry_Func();
}

#endif

/****************************end: BLDC_SCALAR_MSM_IDLE****************/
