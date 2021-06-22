/**
 * @file bldc_scalar_pt1_filter.h
 * @brief Low pass first order filter
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


#ifndef CONTROLMODULE_BLDC_SCALAR_PT1_FILTER_H_
#define CONTROLMODULE_BLDC_SCALAR_PT1_FILTER_H_

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
/** Shift by 16 bits */
#define BLDC_SCALAR_PT1_SHIFT_16  (16U)
#define BLDC_SCALAR_PT1_LIMIT     (0x3FFF0000)       /*!< PT1 buffer limit */
#define BLDC_SCALAR_PT1_VOLT_COMP_MAX_LIMIT      (0x7FFFFFFF)  /*!< Maximum limit of for voltage compensation filter */
#define BLDC_SCALAR_PT1_VOLT_COMP_MIN_LIMIT      (0x80000001)  /*!< Minimum limit of for voltage compensation filter */
#define BLDC_SCALAR_PT1_VOLT_COMP_BUF_VAL        (0x3FFF0000)  /*!< Voltage compensation filter buffer value*/
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
/**
 * @param input_val Value to limit
 * @param higher_limit Maximum limit
 * @param lower_limit Minimum limit
 * @return int32_t Modified value if it is out of min and max limits <br
 *
 * \par<b>Description:</b><br>
 * Limits the input value based on higher_limit and lower_limit
 */
__STATIC_INLINE int32_t Motor0_BLDC_SCALAR_PT1_MinMaxLimiter(int32_t input_val, int32_t higher_limit, int32_t lower_limit)
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

/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/**
 *  @brief PT1 filter parameters.
 */
typedef struct BLDC_SCALAR_PT1_FILTER
{
  int32_t        z1;               /*!< Filter constant */
  int32_t        z2;               /*!< Filter constant */
  int32_t        y_max;            /*!< Maximum limit of PT1 buffer */
  int32_t        y_min;            /*!< Minimum limit of PT1 buffer */
  int32_t        pt1_buf;          /*!< Integral buffer */
  int32_t        pt1_out_val;      /*!< filter output */
} BLDC_SCALAR_PT1_FILTER_t;

/**********************************************************************************************************************
* EXTERN
**********************************************************************************************************************/
#if ((MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_VOLT_COMPENSATION_FILTER == 1U)
extern BLDC_SCALAR_PT1_FILTER_t Motor0_BLDC_SCALAR_PT1_VoltageComp;
#endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U)
extern BLDC_SCALAR_PT1_FILTER_t  Motor0_BLDC_SCALAR_PT1_DirectCurrent;
#endif
#endif

#if (((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) ||(MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U)))
#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_AVERAGE_CURRENT_FILTER == 1U)
extern BLDC_SCALAR_PT1_FILTER_t  Motor0_BLDC_SCALAR_PT1_AverageCurrent;
#endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
#if (MOTOR0_BLDC_SCALAR_POTENTIOMETER_PT1_FILTER_ENABLE == 1U)
extern BLDC_SCALAR_PT1_FILTER_t Motor0_BLDC_SCALAR_PT1_Potentiometer;
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/

/**
  * @param handle_ptr Pointer to the PT1 structure BLDC_SCALAR_PT1_FILTER_t
  * @param actual_val Value to be filtered
  * @return None <br>
  *
  * \par<b>Description:</b><br>
  * First order low pass filter implementation.\n
  * Yn[3,2,1,0] =Yn-1[3,2,1,0] +Z1*(Xn -Yn-1[3,2]) \n
  * Where Z1 is time constant.
  */

__STATIC_INLINE void Motor0_BLDC_SCALAR_PT1_Filter(BLDC_SCALAR_PT1_FILTER_t *handle_ptr, int32_t actual_val)
{
  register int32_t temp_buff;

  /* yn+1 = yn + z1*(x - yn) */
  temp_buff = handle_ptr->pt1_buf + (handle_ptr->z1*(actual_val - (handle_ptr->pt1_buf >> BLDC_SCALAR_PT1_SHIFT_16)));
  /* Checking the buffer limits in the range of Ymin to Ymax */
  handle_ptr->pt1_buf = Motor0_BLDC_SCALAR_PT1_MinMaxLimiter(temp_buff, handle_ptr->y_max, handle_ptr->y_min);
  handle_ptr->pt1_out_val = (handle_ptr->pt1_buf >> BLDC_SCALAR_PT1_SHIFT_16);
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


#endif /* CONTROLMODULE_BLDC_SCALAR_PT1_FILTER_H_ */
