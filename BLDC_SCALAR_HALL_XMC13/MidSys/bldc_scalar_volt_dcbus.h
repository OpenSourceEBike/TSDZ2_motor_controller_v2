/**
 * @file bldc_scalar_volt_dcbus.h
 * @brief DC link voltage measurement
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
 * @{
 */

#ifndef BLDC_SCALAR_VOLT_DCBUS_H_
#define BLDC_SCALAR_VOLT_DCBUS_H_
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "../MCUInit/vadc.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_MEASUREMENT_SHIFT_14 (14U)       /*!< Shift by 14 bits */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
/***********************************************************************************************************************
 * EXTERN DATA STRUCTURES
 **********************************************************************************************************************/
extern uint32_t  motor0_dcbus_voltage_adc_scale;

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * initializes VADC group, channel, result for DC link voltage measurement.
 */
void Motor0_BLDC_SCALAR_Volt_DCBus_Measurement_Init(void);

/**
 * @param dc_bus_voltage VADC conversion result for DC link voltage measurement in Q14 format
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with VADC conversion result for DC link voltage measurement
 *
 * \par<b>Execution Time:</b><br>
 * <b>0.67 uSec </b>using O3 optimization level
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_VOLT_DCBUS_GetDCLinkVoltage(uint32_t* dc_bus_voltage)
{
  uint32_t dcvoltage;
  dcvoltage = VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP, MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_RES_REG_NUM);
  *dc_bus_voltage = (uint32_t)((dcvoltage * motor0_dcbus_voltage_adc_scale) >> BLDC_SCALAR_MEASUREMENT_SHIFT_14);
}

/**
 * @param dc_bus_voltage VADC conversion result for DC link voltage measurement
 * @return uint32_t raw_dcvoltage <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with VADC conversion result for DC link voltage measurement
 *
 * \par<b>Execution Time:</b><br>
 */
__STATIC_INLINE uint16_t Motor0_BLDC_SCALAR_VOLT_DCBUS_GetRawDCLinkVoltage(void)
{
  uint16_t raw_dcvoltage;
  raw_dcvoltage = VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP, MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_RES_REG_NUM);
  return (raw_dcvoltage);
}
#endif
/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif /*BLDC_SCALAR_VOLT_DCBUS_H_*/
