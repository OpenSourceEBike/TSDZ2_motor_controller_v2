/**
 * @file bldc_scalar_ramp_generator.c
 * @brief Linear ramp generator
 * @date 2016-09-08
 *
 * @cond
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
 *     - Initial version
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "bldc_scalar_ramp_generator.h"
/**********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_RAMP_POW_16   (0xFFFF)
#define BLDC_SCALAR_RAMP_SHIFT_16 (16U)
/**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_RAMP == 1U)
/* This generates the linear ramp as per configured slew rate */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_Ramp_Linear(void)
{
  static int32_t sum;     /* to find the increment/decrement value */
  int32_t setval_diff;   /* difference between ramp input and output value */
  int32_t ramp_val;      /* value by which set value is incremented or decremented */

  /* ramp up - if target end value is greater than the ramp output set_value */
  if ((Motor0_BLDC_SCALAR_Ramp.input_value) >= Motor0_BLDC_SCALAR_Ramp.set_value)
  {
    /* Find increment value using fixed point representation */
    setval_diff = (Motor0_BLDC_SCALAR_Ramp.input_value) - Motor0_BLDC_SCALAR_Ramp.set_value;
    sum = (int32_t)(sum + (int32_t)Motor0_BLDC_SCALAR_Ramp.ramp_rate);
    ramp_val = (int32_t)(sum >> BLDC_SCALAR_RAMP_SHIFT_16);
    sum = (int32_t)(sum & BLDC_SCALAR_RAMP_POW_16);

    /* Set value reached the end point */
    if (setval_diff <= ramp_val)
    {
      Motor0_BLDC_SCALAR_Ramp.set_value = (Motor0_BLDC_SCALAR_Ramp.input_value);
      sum = 0;
    }
    else
    {
      Motor0_BLDC_SCALAR_Ramp.set_value += ramp_val;
    }
  }

  /* ramp down - if target end value is less than the ramp output set_value */
  else if ((Motor0_BLDC_SCALAR_Ramp.input_value) < Motor0_BLDC_SCALAR_Ramp.set_value)
  {
    /* Find decrement value using fixed point representation */
    setval_diff =  Motor0_BLDC_SCALAR_Ramp.set_value - (Motor0_BLDC_SCALAR_Ramp.input_value);
    sum = (int32_t)(sum + (int32_t)Motor0_BLDC_SCALAR_Ramp.ramp_rate);
    ramp_val = (int32_t)(sum >> BLDC_SCALAR_RAMP_SHIFT_16);
    sum = (int32_t)(sum & BLDC_SCALAR_RAMP_POW_16);

    /* Set value reached the end point */
    if (setval_diff <= ramp_val)
    {
      Motor0_BLDC_SCALAR_Ramp.set_value = (Motor0_BLDC_SCALAR_Ramp.input_value);
      sum = 0;
    }
    else
    {
      Motor0_BLDC_SCALAR_Ramp.set_value -= ramp_val;
    }
  }
  else
  {

  }
}
#endif
