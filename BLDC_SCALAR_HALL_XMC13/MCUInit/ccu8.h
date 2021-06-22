/**
 * @file ccu8.h
 * @brief Three CCU8 slices are used to drive three motor phases (U, V and W) with PWM signals.
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
 * @endcond
 *
 */

/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup MCUInit
 * @brief  MCU peripheral initialization <br>
 * @{
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#ifndef MCUINIT_CCU8_H_
#define MCUINIT_CCU8_H_

#include "../Configuration/bldc_scalar_derived_parameter.h"
#include "../Configuration/bldc_scalar_mcuhw_config.h"


/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
/** Synchronous start of three phases of CCU8 */
#define MOTOR0_BLDC_SCALAR_CCU8_SYNC_START      ((uint32_t)1 << (uint32_t)(8U + MOTOR0_BLDC_SCALAR_CCU8_MODULE_NUM))

/** Shadow transfer mask of the CCU8 */
#define MOTOR0_BLDC_SCALAR_CCU8_SHADOW_TRANSFER (((uint32_t)1 << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)) | \
                                                ((uint32_t)1 << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) |\
                                                ((uint32_t)1 << (uint32_t)(4U * MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)))

/** Maximum number of phase count */
#define CCU8_MAXPHASE_COUNT  (3U)

/**********************************************************************************************************************
* Data Structures
**********************************************************************************************************************/
/**
 *  @brief This structure holds, configuration structure and parameters for CCU8 slice configuration.
 * Object of this structure is used for PWM init configuration.
 */
typedef struct CCU8_PWM_INIT
{

  XMC_CCU8_SLICE_t                                 *phase_ptr[3];        /*!< CCU8 phase slice pointer */
  uint8_t                                          phase_number[3];      /*!< CCU8 slice number */
  uint16_t                                         current_trigger;      /*!< compare value for the current measurement trigger */
  uint16_t                                         period;               /*!< period register value*/

} CCU8_PWM_INIT_t;

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
 * Initializes the CCU8 global configuration.
 * Initialize CCU8 Phase-U, V and W Slice
 * Initialize Phase-U one match event and Bind Phase-U one match event SR(service request)
 * to interrupt node for control loop execution.
 * Initialize Phase-U event-2 and Bind Phase-U event-2 SR(service request)
 * to interrupt node for trap control.
 * Initialize ADC trigger for current measurement
 * Enable CCU8 shadow transfer
 */
void Motor0_BLDC_SCALAR_CCU8_PWM_Init(void);

void BLDC_SCALAR_CCU8_Event_Init(XMC_CCU8_SLICE_t* slice_ptr, XMC_CCU8_SLICE_IRQ_ID_t IrqId, XMC_CCU8_SLICE_SR_ID_t SrId);

/**
 * @return None. <br>
 *
 * \par<b>Description:</b><br>
 * Set CCUCON trigger signal to high to start all slices synchronously.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_CCU8_PWM_Start(void)
{
  XMC_SCU_SetCcuTriggerHigh((uint32_t)MOTOR0_BLDC_SCALAR_CCU8_SYNC_START);
}

/**
 * @return None. <br>
 *
 * \par<b>Description:</b><br>
 * Set CCUCON trigger signal to low to stop all slices.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_CCU8_PWM_Stop(void)
{
  /* Pull CCUCON signal to low */
  XMC_SCU_SetCcuTriggerLow((uint32_t)MOTOR0_BLDC_SCALAR_CCU8_SYNC_START);
}

/**
 * @param phase_ptr CCU8 slice pointer
 *        channel_mask channel mask to enable dead time.<br>
 * @return None. <br>
 *
 * \par<b>Description:</b><br>
 * Enable the dead time for compare channel and ST path.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_CCU8_EnableDeadTime(XMC_CCU8_SLICE_t * phase_ptr, const uint8_t channel_mask)
{
  phase_ptr->DTC |= (uint32_t)channel_mask;

}

/**
 * @param phase_ptr CCU8 slice pointer
 *        channel_mask channel mask to enable dead time.<br>
 * @return None. <br>
 *
 * \par<b>Description:</b><br>
 * Disable the dead time for compare channel and ST path.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_CCU8_DisableDeadTime(XMC_CCU8_SLICE_t * phase_ptr, const uint8_t channel_mask)
{
  phase_ptr->DTC &= ~(uint32_t)channel_mask;
}

/***********************************************************************************************************************
 * EXTERN
 **********************************************************************************************************************/
/* Making CCU8_PWM_INIT_t object as extern */
extern CCU8_PWM_INIT_t Motor0_BLDC_SCALAR_CCU8_PWM_Config;
/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif /* MCUINIT_CCU8_H_ */
