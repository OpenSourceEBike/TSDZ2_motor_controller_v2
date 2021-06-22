/**
 * @file bldc_scalar_ctrap_periodmatch.c
 * @brief Ctrap event of CCU8
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
 */
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup Interrupt Interrupts
 * @brief  Interrupt Service Routines  <br>
 * @{
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "../ControlModule/bldc_scalar_control_scheme.h"

#include "../bldc_scalar_user_interface.h"


/**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

/**
 * @param none
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Trap event mapped to the Phase U (CCU8) event 2 \n
 * PWM is stopped by the hardware when this event is detected.
 * This ISR, stops the motor and clears the state of the control if trap event occurs.
 *
 * This ISR is also mapped to the phase V period match to handle startup algorithm and fast control loop execution
 * rate for sensor-less configuration.
 */

RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_Trap_PeriodMatch_ISR(void)
{

#if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
  /* CTRAP event check */
  if(Motor0_BLDC_SCALAR_PWM_BC_GetEvent(Motor0_BLDC_SCALAR_PWM_BC.ccu8_handle_ptr->phase_ptr[0], XMC_CCU8_SLICE_IRQ_ID_TRAP) == true)
  {
    /* Update the error status and stop the motor in case of trap event */
    Motor0_BLDC_SCALAR.error_status |= (uint32_t)1 << (uint32_t)BLDC_SCALAR_EID_CTRAP_ERROR;
    Motor0_BLDC_SCALAR.msm_state = BLDC_SCALAR_MSM_ERROR;
    Motor0_BLDC_SCALAR_MotorStop();
  }
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U) */

  /* Check if phase V period match event is occurred to execute startup algorithm */
  if (Motor0_BLDC_SCALAR_PWM_BC_GetEvent(Motor0_BLDC_SCALAR_PWM_BC.ccu8_handle_ptr->phase_ptr[1], XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH) == true)
  {
  #if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U)
  #if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
    if(Motor0_BLDC_SCALAR.control_loop_exec_count >= Motor0_BLDC_SCALAR.control_loop_exec_rate)
    {
      Motor0_BLDC_SCALAR_PWM_BC_EnableEvent(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[0U],XMC_CCU8_SLICE_IRQ_ID_ONE_MATCH);
    }
    Motor0_BLDC_SCALAR.control_loop_exec_count++;
  #endif/* end of #if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL) */
  #endif/* end of #if(MOTOR0_BLDC_SCALAR_CONTROL_LOOP_EXECUTION_RATE > 1U) */
  } /* end of if (Motor0_BLDC_SCALAR.msm_state != BLDC_SCALAR_MSM_ERROR) */
}

/**
 * @}
 */
/**
 * @}
 */
