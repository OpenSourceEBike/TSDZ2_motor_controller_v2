/**
 * @file bldc_scalar_pwm_bc.h
 * @brief Block commutation PWM generation. This supports high side, low side and high side with synchronous rectification modulation
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
 * 2016-05-25:
 *     - Initial version
 * 2016-09-08:
 *     - Updated for sensorless support
 */

/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

#ifndef PWM_BC_H_
#define PWM_BC_H_
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "../MCUInit/gpio.h"
#include "../MCUInit/ccu8.h"


/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define BLDC_SCALAR_PWM_BC_SHIFT_14  (14U)

/**
 * @addtogroup MidSys
 * @{
 */
 /**********************************************************************************************************************
 * ENUMS
 **********************************************************************************************************************/

/**
 * PWM modulation type
 */
typedef enum PWM_BC_MOD
{
  PWM_BC_MOD_HIGHSIDE_SYNCRECTI  = 0U,        /*!<high side output is PWM modulated + complementary PWM for same leg low
                                                side other low side output is either high or low*/
  PWM_BC_MOD_HIGHSIDE = 1U,                   /*!<high side output is PWM modulated and low side output is either high or low */
  PWM_BC_MOD_LOWSIDE  = 2U                    /*!<low side output PWM modulated and high side output is either high or low */
} PWM_BC_MOD_t;

/**
 * Compare register update flag
 */
typedef enum PWM_BC_COMPAREFLAG
{
  PWM_BC_COMPARE_ZERO,               /*!<update compare register with value 0. Duty cycle is 100% */
  PWM_BC_COMPARE_PERIOD,             /*!<update compare register with value (period +1). Duty cycle is 0% */
  PWM_BC_COMPARE_DUTY,               /*!<update compare register with value direct duty. Duty cycle is ((period - duty)/period)% */
  PWM_BC_COMPARE_INVERSE_DUTY        /*!<update compare register with value (period - duty). Duty cycle is ((duty)/period)% */
} PWM_BC_COMPAREFLAG_t;


/**
 * inverter enable pin configurations
 */
typedef enum PWM_BC_INVERTERPINLEVEL
{
  PWM_BC_IPIN_NOTREQUIRED,           /*!<Inverter pin not required.*/
  PWM_BC_IPIN_HIGH,                  /*!<Inverter pin is active high.*/
  PWM_BC_IPIN_LOW                    /*!<Inverter pin is active low.*/
} PWM_BC_INVERTERPINLEVEL_t;


/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/**
 * This function pointer point to the address of functions:\n
 * Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod_SyncRect \n
 * Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod and \n
 * Motor0_BLDC_SCALAR_PWM_BC_LsImmediateMod \n
 * These function are used for PWM modulation based on the actual register (MCM).
 */
typedef void (*PWM_BC_MODULATION_IMMEDIATE_t)(uint16_t mcm);
/**
 * This function pointer point to the address of functions: \n
 * Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod_SyncRect \n
 * Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod and \n
 * Motor0_BLDC_SCALAR_PWM_BC_LsShadowMod \n
 * These function are used for PWM modulation based on shadow register(MCMS) and actual register (MCM).
 */
typedef void (*PWM_BC_MODULATION_SHADOW_t)(uint16_t mcm_val, uint16_t mcms_val);

/**
  *  @brief This structure holds the parameters which is used to configure PWM BC.
  */
typedef struct BLDC_SCALAR_PWM_BC
{
  CCU8_PWM_INIT_t                        *ccu8_handle_ptr;          /*!< PWM init configuration */
  PWM_BC_MODULATION_SHADOW_t             shadow_modulation_ptr;     /*!< function pointer for PWM modulation based on shadow register */
  PWM_BC_MODULATION_IMMEDIATE_t          immediate_modulation_ptr;  /*!< function pointer for PWM modulation based on actual register */
  PWM_BC_MOD_t                           modulation_type;           /*!< PWM modulation type */
  PWM_BC_INVERTERPINLEVEL_t              inverter_pin;              /*!< This saves the inverter pin level*/
  PWM_BC_COMPAREFLAG_t                   ph_cmpflag[3];             /*!< Control flag for compare value update */
  uint16_t                               ph_mcpatt_compmask[3];     /*!< Mask used for comparison whether high side or low side switch is ON based on MCMS*/
  uint16_t                               ph_bothside_compmask[3];   /*!< Mask used for comparison whether high side or low side switch is ON based on MCM*/
  uint16_t                               ph_cmpval[4];              /*!< Holds the compare values. ph_cmpval[0]: 100% duty, ph_cmpval[1]: 0% duty,
                                                                      ph_cmpval[2]: duty,ph_cmpval[3]: inverse duty*/
  uint16_t                               amplitude_scale;           /*!< Amplitude scale for duty cycle conversion */
} BLDC_SCALAR_PWM_BC_t;



#ifdef __cplusplus
extern "C" {
#endif


extern BLDC_SCALAR_PWM_BC_t Motor0_BLDC_SCALAR_PWM_BC;

/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes CCU8 and GPIO peripherals for PWM generation.
 */
void Motor0_BLDC_SCALAR_PWM_BC_Init(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Starts three CCU8 slices synchronously with the SCU CCUCON trigger.
 * This also sets the inverter enable pin.
 */
void Motor0_BLDC_SCALAR_PWM_BC_Start(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Stops three CCU8 slices synchronously with the SCU CCUCON trigger.
 * This also clears the inverter enable pin.
 */
void Motor0_BLDC_SCALAR_PWM_BC_Stop(void);
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * This disables the driver by changing the inverter enable pin to passive level.
 */
void Motor0_BLDC_SCALAR_PWM_BC_InverterDisable(void);

/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * This enables the driver by changing the inverter enable pin to active level.
 */
void Motor0_BLDC_SCALAR_PWM_BC_InverterEnable(void);
#endif
/**
 * @param mcm_val multi-channel pattern
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Checks the actual MCM register and modulate high side PWM output and
 * complementary PWM output for same leg. And keep other low side output is either high or low.
 *
 * \par<b>Execution Time:</b><br>
 * <b>2.6 uSec </b> using O3 optimization level
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod_SyncRect(uint16_t mcm_val);
/**
 * @param mcm_val multi-channel pattern
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Checks the actual MCM register and modulate high
 * side PWM output and keep low side output either high or low.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.84 uSec </b>using O3 optimization level
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod(uint16_t mcm_val);
/**
 * @param mcm_val multi-channel pattern
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Checks the actual MCM register and modulate low side PWM output
 * and keep high side output either high or low.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.84 uSec </b>using O3 optimization level
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PWM_BC_LsImmediateMod(uint16_t mcm_val);

/**
 * @param mcm_val multi-channel pattern
 * @param mcms_val shadow multi-channel pattern
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Checks the non conducting phase and modulate high side PWM output and complementary
 * PWM output for same leg based on the MCMS shadow register.
 * And keep other low side output is either high or low.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.48 uSec </b>using O3 optimization level
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod_SyncRect(uint16_t mcm_val, uint16_t mcms_val);

/**
 * @param mcm_val multi-channel pattern
 * @param mcms_val shadow multi-channel pattern
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Checks the non conducting phase and modulate high side PWM output and keep low side
 * output either high or low based on the MCMS shadow register.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.91 uSec </b>using O3 optimization level
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod(uint16_t mcm_val, uint16_t mcms_val);

/**
 * @param mcm_val multi-channel pattern
 * @param mcms_val shadow multi-channel pattern
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Checks the non conducting phase and modulate low side PWM output and keep high side
 * output either high or low based on the MCMS shadow register.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.76 uSec </b>using O3 optimization level
 */
RAM_ATTRIBUTE void Motor0_BLDC_SCALAR_PWM_BC_LsShadowMod(uint16_t mcm_val, uint16_t mcms_val);


/**
 * @param dutycycle Duty cycle of the CCU8 in Q14
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Updates the compare value of the phases as dutycycle.
 *
 * \par<b>Execution Time:</b><br>
 * <b>1.9 uSec </b>using O3 optimization level
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_DutyCycleUpdate
(
  uint16_t dutycycle
)
{
  uint16_t duty = (dutycycle * Motor0_BLDC_SCALAR_PWM_BC.amplitude_scale) >> BLDC_SCALAR_PWM_BC_SHIFT_14;
  /* Update compare value for inverted switch*/
  Motor0_BLDC_SCALAR_PWM_BC.ph_cmpval[3] = Motor0_BLDC_SCALAR_PWM_BC.ccu8_handle_ptr->period - duty;
  /* Update compare value for direct switch */
  Motor0_BLDC_SCALAR_PWM_BC.ph_cmpval[2] = duty;

  /*Load the duty cycle to the channel compare shadow register*/
  (MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE)->CR1S = (uint32_t) Motor0_BLDC_SCALAR_PWM_BC.ph_cmpval[Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[0U]];
  (MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE)->CR1S = (uint32_t) Motor0_BLDC_SCALAR_PWM_BC.ph_cmpval[Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[1U]];
  (MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE)->CR1S = (uint32_t) Motor0_BLDC_SCALAR_PWM_BC.ph_cmpval[Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[2U]];

  /*Enable the shadow transfer*/
  XMC_CCU8_EnableShadowTransfer(MOTOR0_BLDC_SCALAR_CCU8_MODULE, MOTOR0_BLDC_SCALAR_CCU8_SHADOW_TRANSFER);
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * enable trap for all the three phases (Phase U, V and W) CCU8 slices.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_EnableTrap(void)
{
  XMC_CCU8_SLICE_EnableTrap(MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE,(XMC_CCU8_SLICE_OUTPUT_0|XMC_CCU8_SLICE_OUTPUT_1));
  XMC_CCU8_SLICE_EnableTrap(MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE,(XMC_CCU8_SLICE_OUTPUT_0|XMC_CCU8_SLICE_OUTPUT_1));
  XMC_CCU8_SLICE_EnableTrap(MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE,(XMC_CCU8_SLICE_OUTPUT_0|XMC_CCU8_SLICE_OUTPUT_1));
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * enable multi channel mode for Phase U CCU8 slice.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseU(void)
{
  XMC_CCU8_SLICE_EnableMultiChannelMode(MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE, XMC_CCU8_SLICE_COMPARE_CHANNEL_1);
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * enable multi channel mode for Phase V CCU8 slice.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseV(void)
{
  XMC_CCU8_SLICE_EnableMultiChannelMode(MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE, XMC_CCU8_SLICE_COMPARE_CHANNEL_1);
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * enable multi channel mode for Phase U CCU8 slice.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_EnableMCMPhaseW(void)
{
  XMC_CCU8_SLICE_EnableMultiChannelMode(MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE, XMC_CCU8_SLICE_COMPARE_CHANNEL_1);
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * disable  multi channel mode for Phase U CCU8 slice.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_DisableMCMPhaseU(void)
{
  XMC_CCU8_SLICE_DisableMultiChannelMode(MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE, XMC_CCU8_SLICE_COMPARE_CHANNEL_1);
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * disable  multi channel mode for Phase U CCU8 slice.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_DisableMCMPhaseV(void)
{
  XMC_CCU8_SLICE_DisableMultiChannelMode(MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE, XMC_CCU8_SLICE_COMPARE_CHANNEL_1);
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * disable  multi channel mode for Phase U CCU8 slice.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_DisableMCMPhaseW(void)
{
  XMC_CCU8_SLICE_DisableMultiChannelMode(MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE, XMC_CCU8_SLICE_COMPARE_CHANNEL_1);
}
/**
 * @param comp_val Timer compare value
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * update compare value for Phase U CCU8 slice.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseU(uint16_t comp_val)
{

  XMC_CCU8_SLICE_SetTimerCompareMatchChannel1(MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE, (uint16_t) comp_val);
}
/**
 * @param comp_val Timer compare value
* @return None <br>
*
* \par<b>Description:</b><br>
* update compare value for Phase V CCU8 slice.
*/
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseV(uint16_t comp_val)
{
  XMC_CCU8_SLICE_SetTimerCompareMatchChannel1(MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE, (uint16_t) comp_val);
}
/**
 * @param comp_val Timer compare value
* @return None <br>
*
* \par<b>Description:</b><br>
* update compare value for Phase W CCU8 slice.
*/
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_SetCompareValPhaseW(uint16_t comp_val)
{
  XMC_CCU8_SLICE_SetTimerCompareMatchChannel1(MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE, (uint16_t) comp_val);
}
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * enable shadow transfer for all Phase CCU8 slices.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_EnableShadowTransfer(void)
{
  XMC_CCU8_EnableShadowTransfer(MOTOR0_BLDC_SCALAR_CCU8_MODULE, MOTOR0_BLDC_SCALAR_CCU8_SHADOW_TRANSFER);
}
/**
 * @return evt_status <br>
 *
 * \par<b>Description:</b><br>
 * Gets event status for CCU8 slices.
 */
__STATIC_INLINE uint8_t Motor0_BLDC_SCALAR_PWM_BC_GetEvent(const XMC_CCU8_SLICE_t *const slice, const XMC_CCU8_SLICE_IRQ_ID_t event)
{
  uint8_t evt_status;
  evt_status = (uint8_t)XMC_CCU8_SLICE_GetEvent(slice, event);
  return (evt_status);
}


/**
 * @return None. <br>
 *
 * \par<b>Description:</b><br>
 * Enables ccu8 event.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_EnableEvent(XMC_CCU8_SLICE_t *const slice, const XMC_CCU8_SLICE_IRQ_ID_t event)
{
  /* Pull CCUCON signal to low */
  XMC_CCU8_SLICE_EnableEvent(slice,event);
}

/**
 * @return None. <br>
 *
 * \par<b>Description:</b><br>
 * Clears trap event.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_ClearTrapEvent(void)
{
  XMC_CCU8_SLICE_ClearEvent(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[0],XMC_CCU8_SLICE_IRQ_ID_TRAP);
  XMC_CCU8_SLICE_ClearEvent(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[1],XMC_CCU8_SLICE_IRQ_ID_TRAP);
  XMC_CCU8_SLICE_ClearEvent(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[2],XMC_CCU8_SLICE_IRQ_ID_TRAP);
}

/**
 * @return None. <br>
 *
 * \par<b>Description:</b><br>
 * Disables ccu8 event.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_DisableEvent(XMC_CCU8_SLICE_t *const slice, const XMC_CCU8_SLICE_IRQ_ID_t event)
{
  /* Pull CCUCON signal to low */
  XMC_CCU8_SLICE_DisableEvent(slice,event);
}



/**
 * @param slice pointer and period value
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Set period value for CCU8 slices.
 */
__STATIC_INLINE void Motor0_BLDC_SCALAR_PWM_BC_SetTimerPeriodMatch(XMC_CCU8_SLICE_t *const slice, const uint16_t period_val)
{
  XMC_CCU8_SLICE_SetTimerPeriodMatch(slice,period_val);
}
/***********************************************************************************************************************
 * EXTERN
 **********************************************************************************************************************/
extern BLDC_SCALAR_PWM_BC_t Motor0_BLDC_SCALAR_PWM_BC;


/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* PWM_BC_H_ */
