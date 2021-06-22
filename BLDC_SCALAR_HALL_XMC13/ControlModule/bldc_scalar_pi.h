/**
 * @file bldc_scalar_pi.h
 * @brief PI controller
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


#ifndef CONTROLMODULE_BLDC_SCALAR_PI_H_
#define CONTROLMODULE_BLDC_SCALAR_PI_H_

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
#include "../Configuration/bldc_scalar_derived_parameter.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
/**
 * @param input_val Value to limit
 * @param higher_limit Maximum limit
 * @param lower_limit Minimum limit
 * @return int32_t Modified value if it is out of min and max limits <br>
 *
 * \par<b>Description:</b><br>
 * Limits the input value based on higher_limit and lower_limit
 */
__STATIC_INLINE int32_t Motor0_BLDC_SCALAR_PI_MIN_MAX_LIMIT(int32_t input_val, int32_t higher_limit, int32_t lower_limit)
{
  int32_t return_val;
  if ( input_val > higher_limit )
  {
    return_val = higher_limit;
  }
  else if ( input_val < lower_limit )
  {
    return_val = lower_limit;
  }
  else
  {
    return_val = input_val;
  }
  return return_val;
}

/**
 * @param input1 input value 1
 * @param input2 input value 2
 * @return uint8_t PI saturation flag. \n
 * 0: when two inputs are equal \n
 * 1: when two inputs are different \n <br>
 *
 * \par<b>Description:</b><br>
 * Checks if PI saturation flag is set
 */
__STATIC_INLINE uint8_t Motor0_BLDC_SCALAR_PI_SAT_STATE(int32_t input1, int32_t input2)
{
  uint8_t return_val;
  if (input1 == input2)
  {
    return_val = 1U;
  }
  else
  {
    return_val = 0U;
  }
  return (return_val);
}

/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/**
 *  @brief PI parameters
 */
typedef struct BLDC_SCALAR_PI_CONTROLLER
{
  int32_t uk;                     /*!< PI output U[k] */
  int32_t ik;                     /*!< Integral result I[k] */
  int32_t uk_limit_min;           /*!< Minimum value of the PI output */
  int32_t uk_limit_max;           /*!< Maximum value of the PI output */
  uint16_t kp;                    /*!< Proportional gain Kp */
  uint16_t ki;                    /*!< Integral gain Ki */
  uint8_t scale_kpki;             /*!< Scale-up Kp and Ki by 2^Scale_KpKi */
  uint8_t sat_state;              /*!< Switch to represent saturation of PI output */
} BLDC_SCALAR_PI_CONTROLLER_t;

/**********************************************************************************************************************
* EXTERN
**********************************************************************************************************************/
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEED_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
extern BLDC_SCALAR_PI_CONTROLLER_t Motor0_BLDC_SCALAR_SpeedControl_PI;
#endif
#if ((MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_CURRENT_CTRL) || (MOTOR0_BLDC_SCALAR_CTRL_SCHEME == BLDC_SCALAR_SPEEDCURRENT_CTRL))
extern BLDC_SCALAR_PI_CONTROLLER_t Motor0_BLDC_SCALAR_CurrentControl_PI;
#endif


#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/

/**
  * @param handle_ptr Pointer to PI strcuture of type BLDC_SCALAR_PI_CONTROLLER_t
  * @param error_val Error value for PI controller
  * @return None <br>
  *
  * \par<b>Description:</b><br>
  * PI controller with simple anti-windup. Stops integration when PI output reaches saturation \n
  * PI Output = (kp*error) + (Ki * integral of error)
  */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PI_Controller
(
    BLDC_SCALAR_PI_CONTROLLER_t *handle_ptr,
    int32_t error_val
)
{
  register int32_t u_k;
  register int32_t error = error_val;

  handle_ptr->ik = (int32_t)(error * (int32_t)handle_ptr->ki * (int32_t)handle_ptr->sat_state) + handle_ptr->ik;              /*Integral output I[k] = I[k-1] + Ki * error[k] */
  u_k = (( error * (int32_t)handle_ptr->kp) + handle_ptr->ik) >> handle_ptr->scale_kpki;         /*PI output U[k] = Kp * error[k] + I[k]. */
  handle_ptr->uk = Motor0_BLDC_SCALAR_PI_MIN_MAX_LIMIT(u_k, handle_ptr->uk_limit_max, handle_ptr->uk_limit_min);  /* Check U[k] output limit. Vq = handle_ptr->Uk. */
  handle_ptr->sat_state = (uint8_t)Motor0_BLDC_SCALAR_PI_SAT_STATE(u_k, handle_ptr->uk);                                   /* Update saturation flag */
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

#endif /* CONTROLMODULE_BLDC_SCALAR_PI_H_ */
