/**
 * @file bldc_scalar_volt_userdef.h
 * @brief User defined voltage measurement
 * @date 2016-09-08
 *
 **********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2- BLDC motor control using block commutation
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

#ifndef BLDC_SCALAR_VOLT_USERDEF_H_
#define BLDC_SCALAR_VOLT_USERDEF_H_
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "../MCUInit/vadc.h"


/***********************************************************************************************************************
 * EXTERN DATA STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * initializes VADC group, channel, result for user defined measurement.
 */

void Motor0_BLDC_SCALAR_Volt_Userdef1_Init(void);

/**
 * @param user_def1_res VADC conversion result for user defined measurement as ADC count (12-bit)
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with VADC conversion result for user defined measurement
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetUserDef1_Result(uint32_t * user_def1_res)
{
  *user_def1_res = VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP, MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_RES_REG_NUM);
}
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * initializes VADC group, channel, result for user defined measurement.
 */

void Motor0_BLDC_SCALAR_Volt_Userdef2_Init(void);

/**
 * @param user_def2_res VADC conversion result for user defined measurement as ADC count (12-bit)
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with VADC conversion result for user defined measurement
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetUserDef2_Result(uint32_t * user_def2_res)
{
  *user_def2_res = VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_GRP, MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_RES_REG_NUM);
}
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * initializes VADC group, channel, result for user defined measurement.
 */

void Motor0_BLDC_SCALAR_Volt_Userdef3_Init(void);

/**
 * @param user_def3_res VADC conversion result for user defined measurement as ADC count (12-bit)
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with VADC conversion result for user defined measurement
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetUserDef3_Result(uint32_t * user_def3_res)
{
  *user_def3_res = VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_GRP, MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_RES_REG_NUM);
}
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U) */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * initializes VADC group, channel, result for user defined measurement.
 */

void Motor0_BLDC_SCALAR_Volt_Userdef4_Init(void);

/**
 * @param user_def4_res VADC conversion result for user defined measurement as ADC count (12-bit)
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the reference variable with VADC conversion result for user defined measurement
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_GetUserDef4_Result(uint32_t * user_def4_res)
{
  *user_def4_res = VADC_GetResult(MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_GRP, MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_RES_REG_NUM);
}
#endif  /* end of #if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U) */


/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif /*BLDC_SCALAR_VOLT_USERDEF_H_*/
