/**
 * @file bldc_scalar_current_motor.c
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
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "bldc_scalar_current_motor.h"

/**********************************************************************************************************************
* MACROS
**********************************************************************************************************************/
#define BLDC_SCALAR_VADC_CONVERSION_DELAY   (0xFU)   /* VADC conversion delay time */
/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/

/*********************************************************************************************************************/
/* DC Link Current Measurement */
/*********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)


void Motor0_BLDC_SCALAR_Current_Measurment_Init(void)
{
  /* Initialize VADC channel */
  XMC_VADC_GROUP_ChannelInit(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP, MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_CH_NUM,
      &Motor0_BLDC_SCALAR_VADC_IDCLink_CH_handle);

  /* Initialize VADC result */
  XMC_VADC_GROUP_ResultInit(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP, MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_RES_REG_NUM,
      &Motor0_BLDC_SCALAR_VADC_IDCLink_Res_handle);

  /* Request the LLD to insert the channel in queue.*/
  XMC_VADC_GROUP_QueueInsertChannel(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP, Motor0_BLDC_SCALAR_VADC_IDCLink_queue_entry);

  #if((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) && (BLDC_SCALAR_IDC_DIRECT_CURRENT == MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE))

  XMC_VADC_GROUP_SetBoundaries((XMC_VADC_GROUP_t *)MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP,
                               MOTOR0_BLDC_SCALAR_OVER_CURRENT_VADC_BOUND0_T,
                               MOTOR0_BLDC_SCALAR_OVER_CURRENT_VADC_BOUND1_T);
  /* Bind the channel event to shared service request line */
  XMC_VADC_GROUP_ChannelSetEventInterruptNode(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP, MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_CH_NUM,
      MOTOR0_BLDC_SCALAR_VADC_CHEVT_SR);
  #endif

  #if (UC_SERIES == XMC13)
  /* Check if VADC on chip gain is configured */
  #if(MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN > VADC_MEASUREMENT_ONCHIP_GAIN_1)
  XMC_VADC_GLOBAL_SHS_SetGainFactor(VADC_SHS_PTR,MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN_T, BLDC_SCALAR_VADC_IDC_LINK_GRP_NUM,
      MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_CH_NUM);
  #endif

  #endif /* end of #if (UC_SERIES == XMC13) */
}
#endif

/*********************************************************************************************************************/
/* DC Link Average Current Measurement */
/*********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)

void Motor0_BLDC_SCALAR_AverageCurrent_Measurment_Init()
{

  /* Initialize VADC channel */
  XMC_VADC_GROUP_ChannelInit(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP, MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM,
      &Motor0_BLDC_SCALAR_VADC_IDCAverage_CH_handle);

  /* Initialize VADC result */
  XMC_VADC_GROUP_ResultInit(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP, MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_RES_REG_NUM,
      &Motor0_BLDC_SCALAR_VADC_IDCAverage_Res_handle);

  /* Request the LLD to insert the channel in queue.*/
  XMC_VADC_GROUP_QueueInsertChannel(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP, Motor0_BLDC_SCALAR_VADC_IDCAverage_queue_entry);

  #if((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) && (BLDC_SCALAR_IDC_AVG_CURRENT == MOTOR0_BLDC_SCALAR_OVER_CURRENT_SOURCE))
  XMC_VADC_GROUP_SetBoundaries(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP, MOTOR0_BLDC_SCALAR_OVER_CURRENT_VADC_BOUND0_T,
	 MOTOR0_BLDC_SCALAR_OVER_CURRENT_VADC_BOUND1_T);
  /* Bind the channel event to shared service request line */
  XMC_VADC_GROUP_ChannelSetEventInterruptNode(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP,
      MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM, MOTOR0_BLDC_SCALAR_VADC_CHEVT_SR);
  #endif

  #if (UC_SERIES == XMC13)
  /* Check if VADC on chip gain is configured */
  #if(MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN > VADC_MEASUREMENT_ONCHIP_GAIN_1)
  XMC_VADC_GLOBAL_SHS_SetGainFactor(VADC_SHS_PTR,MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN_T,
      BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM, MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM);
  #endif
  #endif /* end of #if (UC_SERIES == XMC13) */
}
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U) */

#if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U))
#if (MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION == 1U)

void Motor0_BLDC_SCALAR_AmpBiasVoltCalibration(void)
{
  uint32_t amp_offset = 0U;      /* current amplifier offset value */
  uint32_t count;                /* for loop count */
  volatile uint32_t delay;       /* ADC conversion delay counter */
  uint32_t vadc_conversion_time_dealy = BLDC_SCALAR_VADC_CONVERSION_DELAY;  /* ADC conversion delay */
  uint32_t temp_ampoffset;       /* current amplifier offset value */

  /* Average DC link current */
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)
  /* SW trigger for direct DC link current channel and measure the amplifier bias voltage */
  /* Calibration is done with average of 16 measurements */
  for (count = 0U; count < BLDC_SCALAR_ADCCAL_COUNT; count++)
  {
    XMC_VADC_GROUP_QueueTriggerConversion(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP);
    /* VADC queue measurements conversion time delay */
    for (delay = 0U; delay < vadc_conversion_time_dealy; delay++)
    {

    }
    temp_ampoffset = (uint32_t) (VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP, MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_RES_REG_NUM));
    amp_offset = amp_offset + temp_ampoffset;
  }
  temp_ampoffset = ((uint32_t)amp_offset >> (uint32_t)BLDC_SCALAR_ADCCAL_SHIFT_4);
  Motor0_BLDC_SCALAR_CurrentMeasurement.avg_dc_amplifier_offset = (int32_t) temp_ampoffset;
#endif  /* end of MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT */

  /* Direct DC link current */
#if(MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
  amp_offset = 0U;
  /* SW trigger for direct DC link current channel and measure the amplifier bias voltage */
  /* Calibration is done with average of 16 measurements */
  for (count = 0U; count < BLDC_SCALAR_ADCCAL_COUNT; count++)
  {
    XMC_VADC_GROUP_QueueTriggerConversion(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP);
    /* VADC queue measurements conversion time delay */
    for (delay = 0U; delay < vadc_conversion_time_dealy; delay++)
    {

    }
    temp_ampoffset = (uint32_t) (VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP, MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_RES_REG_NUM));
    amp_offset = amp_offset + temp_ampoffset;
  }
  temp_ampoffset = ((uint32_t)amp_offset >> (uint32_t)BLDC_SCALAR_ADCCAL_SHIFT_4);
  Motor0_BLDC_SCALAR_CurrentMeasurement.direct_dc_amplifier_offset = (int32_t) temp_ampoffset;
#endif /* end of MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT */


}
#endif /* end of MOTOR0_BLDC_SCALAR_ENABLE_AMPLIFIER_OFFSET_CALIBRATION */
#endif /* end of #if ((MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U) || (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)) */
