/**
 * @file bldc_scalar_defines.h
 * @brief Non-configurable defines
 * @date 2016-09-08
 *
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
 *
 * @endcond
 *
 */

/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup Configuration
 * @brief Control algorithm and MCU peripheral configurations <br>
 *
 * @{
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#ifndef BLDC_SCALAR_COMMON_H_
#define BLDC_SCALAR_COMMON_H_


/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/**
 * @addtogroup SW_Macros
 * @brief Non-configurable macros  - used to configure control algorithm parameters.  <br>
 * @{
 */
/*
 * DO NOT change macros in the "Non-configurable macros" section
 */
/**************************START: Non-configurable macros ***************************************************/
/* Motor application kit */
#define   KIT_XMC1X_AK_MOTOR_001        (0U)      /*!< Low voltage 15W kit KIT_XMC1X_AK_MOTOR_001 */
#define   KIT_XMC750WATT_MC_AK_V1       (1U)      /*!< High voltage 750W kit KIT_XMC750WATT_MC_AK_V1 */
#define   KIT_CUSTOM                    (2U)      /*!< Custom motor control kit */

/* Motor Definition */
#define   MOTOR_EC_MAXON_267121         (0U)      /*!< Maxon motor part number 267121 which is a part of KIT_XMC1X_AK_MOTOR_001 kit */
#define   MOTOR_CUSTOM                  (1U)      /*!< Custom motor */

/** Active level of the switches is low */
#define   BLDC_SCALAR_ACTIVE_LOW       (0U)
/** Active level of the switches is high */
#define   BLDC_SCALAR_ACTIVE_HIGH      (1U)

/** Inverter enable pin is not required */
#define   BLDC_SCALAR_INV_DISABLED      (0U)
/**Active level of the inverter enable pin is high */
#define   BLDC_SCALAR_INV_ACTIVE_HIGH   (1U)
/**Active level of the inverter enable pin is low */
#define   BLDC_SCALAR_INV_ACTIVE_LOW    (2U)

/** Position feedback is from 3 hall sensors*/
#define   BLDC_SCALAR_3HALL             (0U)
/** Position feedback using phase BEMF signals */
#define   BLDC_SCALAR_SENSORLESS         (1U)

/* Control scheme */
#define   BLDC_SCALAR_VOLTAGE_CTRL        (0U)    /*!< Open loop voltage control */
#define   BLDC_SCALAR_SPEED_CTRL          (1U)    /*!< Closed loop speed control - duty is controlled as per speed feedback */
#define   BLDC_SCALAR_CURRENT_CTRL        (2U)    /*!< Closed loop current control - duty is controlled as per current feedback */
#define   BLDC_SCALAR_SPEEDCURRENT_CTRL   (3U)    /*!< Closed loop current control - duty is controlled as per speed and current feedback */

/* PWM Modulation scheme */
#define   BLDC_SCALAR_PWM_HIGHSIDE_SYNCHRECTI  (0U)  /*!< High side switch is modulated along with complementary PWM to same phase low side switch
                                                        and second phase low side switch is always ON */
#define   BLDC_SCALAR_PWM_HIGHSIDE             (1U)  /*!< High side switch is modulated and low side switch is always ON */
#define   BLDC_SCALAR_PWM_LOWSIDE              (2U)  /*!< Low side switch is modulated and high side switch is always ON */

/* Motor direction */
/** Phase sequence U, V, W */
#define    BLDC_SCALAR_POSITIVE_DIR       (1)
/** Phase sequence U, W, V */
#define    BLDC_SCALAR_NEGATIVE_DIR       (-1)

/** Motor current average DC-link measurement */
#define    BLDC_SCALAR_IDC_AVG_CURRENT     (0U)
/** Motor current DC-link measurement */
#define    BLDC_SCALAR_IDC_DIRECT_CURRENT  (1U)

/** ADC on-chip gain = 1 */
#define  VADC_MEASUREMENT_ONCHIP_GAIN_1  (1U)
/** ADC on-chip gain = 3 */
#define  VADC_MEASUREMENT_ONCHIP_GAIN_3  (3U)
/** ADC on-chip gain = 6 */
#define  VADC_MEASUREMENT_ONCHIP_GAIN_6  (6U)
/** ADC on-chip gain = 12 */
#define  VADC_MEASUREMENT_ONCHIP_GAIN_12 (12U)

/* Forward direction hall sequence */
#define BLDC_SCALAR_HALL_SEQ_1           (1U)      /*!< Hall sequence is 1 -> 3 -> 2 -> 6 -> 4 -> 5 (MSB)H3 H2 H1 (LSB)*/
#define BLDC_SCALAR_HALL_SEQ_2           (2U)      /*!< Hall sequence is 1 -> 5 -> 4 -> 6 -> 2 -> 3 (MSB)H3 H2 H1 (LSB)*/


/***********************************************************************************************************************
 * Multi-channel pattern based on CCU8 slices
 **********************************************************************************************************************/
/** High side switch is ON */
#define HIGH_ON   (1U)
/** Low side switch is ON */
#define LOW_ON    (2U)
/** Both high and low side switches are OFF */
#define BOTH_OFF  (0U)

/** Ph W high side switch ON, Ph V low side switch ON, Ph U both switches OFF */
#define WH_VL_UOFF   (((uint32_t)HIGH_ON  << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)) | ((uint32_t)LOW_ON   << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) | ((uint32_t)BOTH_OFF << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)))
/** Ph W both switches OFF, Ph V low side switch ON, Ph U high side switch ON */
#define WOFF_VL_UH   (((uint32_t)BOTH_OFF << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)) | ((uint32_t)LOW_ON   << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) | ((uint32_t)HIGH_ON  << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)))
/** Ph W low side switch ON, Ph V both switches OFF, Ph U high side switch ON */
#define WL_VOFF_UH   (((uint32_t)LOW_ON   << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)) | ((uint32_t)BOTH_OFF << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) | ((uint32_t)HIGH_ON  << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)))
/** Ph W low side switch ON, Ph V high side switch ON, Ph U both switches OFF */
#define WL_VH_UOFF   (((uint32_t)LOW_ON   << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)) | ((uint32_t)HIGH_ON  << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) | ((uint32_t)BOTH_OFF << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)))
/** Ph W both switches OFF, Ph V high side switch ON, Ph U low side switch ON */
#define WOFF_VH_UL   (((uint32_t)BOTH_OFF << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)) | ((uint32_t)HIGH_ON  << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) | ((uint32_t)LOW_ON   << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)))
/** Ph W high side switch ON, Ph V both switches OFF, Ph U low side switch ON */
#define WH_VOFF_UL   (((uint32_t)HIGH_ON  << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM)) | ((uint32_t)BOTH_OFF << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM)) | ((uint32_t)LOW_ON   << (uint32_t)(4U*MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM)))
/************************************************************************************************************/

/** Position feedback */
#define   MOTOR0_BLDC_SCALAR_FEEDBACK               (BLDC_SCALAR_3HALL)

/* Version information */

#define BLDC_SCALAR_XMC13_LIB_MAJOR_VERSION (1U)
#define BLDC_SCALAR_XMC13_LIB_MINOR_VERSION (0U)
#define BLDC_SCALAR_XMC13_LIB_PATCH_VERSION (2U)

#define BLDC_SCALAR_XMC13_LIB_VERSION         ((BLDC_SCALAR_XMC13_LIB_MAJOR_VERSION << 16U) + (BLDC_SCALAR_XMC13_LIB_MINOR_VERSION << 8U) + BLDC_SCALAR_XMC13_LIB_PATCH_VERSION)

/**************************END: Non-configurable macros ***************************************************/
/**
 * @}
 */


/**
 * @}
 */
/**
 * @}
 */
#endif /* BLDC_SCALAR_COMMON_H_ */
