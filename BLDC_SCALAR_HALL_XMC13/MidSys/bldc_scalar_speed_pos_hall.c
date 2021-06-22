/**
 * @file bldc_scalar_speed_pos_hall.c
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
#include "bldc_scalar_speed_pos_hall.h"
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_SPEED_POS_HALL_MASK    (0x7U)
#define BLDC_SCALAR_SPEED_POS_HALL_2_POS   (2U)
/***********************************************************************************************************************
 * DATA
 **********************************************************************************************************************/
/**
 * Speed calculation constant used for floating prescaler values
 */
uint32_t BLDC_SCALAR_SPEED_POS_HALL_Cap_Array[16] = {
                                         0U,
                                         1U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         3U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         7U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         15U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         31U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         63U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         127U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         255U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         511U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         1023U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         2047U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         4095U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         8191U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         16383U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
                                         32767U * BLDC_SCALAR_SPEED_POS_HALL_CAP_COMP_VAL,
};


/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/*
 * Initialize POSIF and CCU4 peripherals
 * Initialize hall sensor input pins.
 */
void Motor0_BLDC_SCALAR_SPEED_POS_HALL_Init()
{
  Motor0_BLDC_SCALAR_POSIF_3Hall_Init();
  Motor0_BLDC_SCALAR_CCU4_3Hall_Init();
  Motor0_BLDC_SCALAR_GPIO_3Hall_Init();
}

/*
 * Start POSIF and CCU4 timer.
 */
void Motor0_BLDC_SCALAR_SPEED_POS_HALL_Start()
{
  Motor0_BLDC_SCALAR_SPEED_POS_HALL_ClearSpeedFilter();

  /*
   * Set RUN bit of the POSIF and
   * CC41 First slice will be started on external start trigger
   */
  XMC_POSIF_Start(MOTOR0_BLDC_SCALAR_POSIF_MODULE);

  XMC_CCU4_SLICE_ClearTimer(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE);
  XMC_CCU4_SLICE_ClearTimer(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE);

  XMC_CCU4_SLICE_StartTimer(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE);

}

/*
 * Stop POSIF and CCU4 timer.
 */
void Motor0_BLDC_SCALAR_SPEED_POS_HALL_Stop()
{
  XMC_POSIF_Stop(MOTOR0_BLDC_SCALAR_POSIF_MODULE);
  NVIC_ClearPendingIRQ(MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE);
  XMC_CCU4_SLICE_StopTimer(MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE);
  XMC_CCU4_SLICE_StopTimer(MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE);
}


/*
 * This function will return the current state of the POSIF input pins to
 * which hall sensors are connected. This information is required before
 * starting the motor to know the start position of the motor.
 */
uint32_t Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallPosition(void)
{
  uint32_t hallposition;
  uint32_t hall[3] = { 0U };

  /*Read the input pins.*/
  hall[0] = XMC_GPIO_GetInput(MOTOR0_BLDC_SCALAR_GPIO_HALL_1);
  hall[1] = XMC_GPIO_GetInput(MOTOR0_BLDC_SCALAR_GPIO_HALL_2);
  hallposition = (uint32_t)(hall[0] | ((uint32_t) hall[1] << 1U));

  hall[2] = XMC_GPIO_GetInput(MOTOR0_BLDC_SCALAR_GPIO_HALL_3);
  hallposition |= ((uint32_t)(hall[2] << BLDC_SCALAR_SPEED_POS_HALL_2_POS));


  return ((uint32_t)(hallposition & BLDC_SCALAR_SPEED_POS_HALL_MASK));
}

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)*/

