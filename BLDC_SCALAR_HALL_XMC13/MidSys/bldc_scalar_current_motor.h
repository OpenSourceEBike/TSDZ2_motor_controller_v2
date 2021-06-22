/**
 * @file bldc_scalar_current_motor.h
 * @brief DC link current measurement and Average DC link current measurement
 * @date 2016-09-08
 *
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
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup MidSys
 * @brief  Middle level interface to read values from VADC (current, voltage) and position sensor and
 * to drive inverter using PWM <br>
 * @{
 */
#ifndef BLDC_SCALAR_CURRENT_MOTOR_H_
#define BLDC_SCALAR_CURRENT_MOTOR_H_
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "../MCUInit/vadc.h"
#include "../ControlModule/bldc_scalar_pt1_filter.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
/** Use for amplifier bias calibration*/
#define BLDC_SCALAR_ADCCAL_COUNT    (16U)
/** Use for calculate offset value after accumulation of 16 samples*/
#define BLDC_SCALAR_ADCCAL_SHIFT_4  (4U)
/** Shift by 14 */
#define BLDC_SCALAR_SHIFT_14        (14)
/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
/**
 *  @brief Structure for motor current measurement
 */
typedef struct BLDC_SCALAR_CURRENT_MEASUREMENT
{
  int32_t    direct_dc_amplifier_offset;            /*!< external amplifier offset for direct DC link current*/
  int32_t    avg_dc_amplifier_offset;               /*!< external amplifier offset for average current*/
  uint32_t   current_adc_scale;                     /*!< Scale to convert ADC current reading to target current in Q14 */
  int32_t    short_circuit_current;                 /*!< short circuit current limit in Q14 */
  int32_t    prev_current;                          /*!< During de-magnetization time blanking current previous measured current will be returned */
  uint32_t * amplitude;                             /*!< amplitude information for filtering DC link instantaneous current */
  uint32_t   demagnetization_blanking_count;        /*!< Blanking time to avoid wrong current reading during de-magnetization spike. */
  uint32_t   demagnetization_blanking_counter;      /*!< Blanking time counter */
  uint8_t    demagnetization_blanking_enable;       /*!< New commutation time flag will be set to avoid de-magnetization spike */

} BLDC_SCALAR_CURRENT_MEASUREMENT_t;



/***********************************************************************************************************************
 * EXTERN
 **********************************************************************************************************************/
extern BLDC_SCALAR_CURRENT_MEASUREMENT_t Motor0_BLDC_SCALAR_CurrentMeasurement;

#ifdef __cplusplus
   extern "C" {
#endif
/*********************************************************************************************************************
 * API Prototypes
 ********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Calibrates the amplifier bias voltage. It is advised to enable this calibration
 * for accurate current measurement.
 */
void Motor0_BLDC_SCALAR_AmpBiasVoltCalibration(void);
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * initializes VADC group, channel, result for DC link current measurement.
 */
void Motor0_BLDC_SCALAR_Current_Measurment_Init(void);

/**
 * @param dclink_current Motor DC link current value in Q14 format
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with VADC conversion result for DC link current measurement.
 * DC link current measurement is skipped for MOTOR0_BLDC_SCALAR_DEMAGNETIZATION_TIME_COUNT to avoid wrong readings at the commutation point.
 *
 * \par<b>Execution Time:</b><br>
 * using O3 optimization level \n
 * without PT1 filter:                                    <b>0.78 uSec </b>\n
 * with PT1 filter:                                       <b>1.46 uSec </b>\n
 * with filter and with demagnetization blanking enabled: <b>1.6 uSec </b>\n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetCurrentValue(int32_t *dclink_current)
{
  int32_t current_value;
  current_value = (int32_t)VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP,MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_RES_REG_NUM);
  current_value = (int32_t)(((current_value - Motor0_BLDC_SCALAR_CurrentMeasurement.direct_dc_amplifier_offset) * (int32_t)Motor0_BLDC_SCALAR_CurrentMeasurement.current_adc_scale) >> BLDC_SCALAR_SHIFT_14);

  #if(MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U)
  /* PT1 filter   */
  Motor0_BLDC_SCALAR_PT1_Filter(&Motor0_BLDC_SCALAR_PT1_DirectCurrent,(int32_t)current_value);
  current_value = ((Motor0_BLDC_SCALAR_PT1_DirectCurrent.pt1_out_val));
  #endif /*#if(MOTOR0_BLDC_SCALAR_ENABLE_IDC_LINK_CURRENT_FILTER == 1U)*/

  /*
   * Skip the direct DC link current measurement at commutation point based on de-magnetization count
   * This is required only if the SW filter is disabled
   */
#if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U)
  if (Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_enable == 1U)
  {
    Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_counter++;
    if (Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_counter >
        Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_count)
    {
      /* De-magnetization blanking time over. Read current and reset the De-magnetization counter */
     *dclink_current = current_value;
     Motor0_BLDC_SCALAR_CurrentMeasurement.prev_current = current_value;
     Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_counter = 0U;
     Motor0_BLDC_SCALAR_CurrentMeasurement.demagnetization_blanking_enable = 0U;
    }
    *dclink_current = Motor0_BLDC_SCALAR_CurrentMeasurement.prev_current;
  }
  else
  {
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U) */
    *dclink_current = current_value;
    Motor0_BLDC_SCALAR_CurrentMeasurement.prev_current =  current_value;
#if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U)
  }
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_DEMAGNET_BLANKING == 1U) */
}
#endif /*end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)*/

/*********************************************************************************************************/

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U))
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * initializes VADC group, channel, result for user defined measurement.
 */
void Motor0_BLDC_SCALAR_AverageCurrent_Measurment_Init(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Returns VADC conversion result for DC link average current measurement
 *
 * \par<b>Execution Time:</b><br>
 * using O3 optimization level \n
 * without PT1 filter: <b>0.588 uSec </b> \n
 * with PT1 filter: <b>1.380 uSec </b>\n
 * with filter and with MOTOR0_BLDC_SCALAR_VADC_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK enabled: <b>1.508 uSec </b>\n
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetAverageCurrentValue(int32_t *dclink_average_current)
{
  int32_t current_value;

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U )
  /* Average current pin */
  current_value = (int32_t)VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP,MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_RES_REG_NUM);
  current_value = (int32_t)(((current_value - Motor0_BLDC_SCALAR_CurrentMeasurement.avg_dc_amplifier_offset) * (int32_t)Motor0_BLDC_SCALAR_CurrentMeasurement.current_adc_scale) >> BLDC_SCALAR_SHIFT_14);
#else
  /* Average current calculated from DC link current pin */
  current_value = (int32_t)VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP,MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_RES_REG_NUM);
  current_value = (int32_t)(((current_value - Motor0_BLDC_SCALAR_CurrentMeasurement.direct_dc_amplifier_offset) * (int32_t)Motor0_BLDC_SCALAR_CurrentMeasurement.current_adc_scale) >> BLDC_SCALAR_SHIFT_14);
  current_value = (current_value * ((int32_t)*Motor0_BLDC_SCALAR_CurrentMeasurement.amplitude)) >> BLDC_SCALAR_SHIFT_14;
#endif /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U ) */

#if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_AVERAGE_CURRENT_FILTER == 1U)
  /* PT1 filter is used to remove high frequency noise of average DC link current */
  Motor0_BLDC_SCALAR_PT1_Filter(&Motor0_BLDC_SCALAR_PT1_AverageCurrent,(int32_t)current_value);
  *dclink_average_current = ((Motor0_BLDC_SCALAR_PT1_AverageCurrent.pt1_out_val));
#else
  *dclink_average_current = current_value;
#endif /* end of #if (MOTOR0_BLDC_SCALAR_ENABLE_IDC_AVERAGE_CURRENT_FILTER == 1U) */
}
#endif  /* end of #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_AVERAGE_CURRENT_USING_IDC_LINK == 1U)) */


/**
 * @return uint32_t detailed result <br>
 *
 * \par<b>Description:</b><br>
 * Returns detailed dc link current result value
 */

__STATIC_INLINE uint32_t Motor0_BLDC_SCALAR_Current_Motor_GetDetailedResult(XMC_VADC_GROUP_t *const group_ptr, const uint32_t res_reg)
{
  return XMC_VADC_GROUP_GetDetailedResult(group_ptr,res_reg);
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
#endif /*BLDC_SCALAR_CURRENT_MOTOR_H_ */
