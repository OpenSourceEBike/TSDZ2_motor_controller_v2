/**
 * @file vadc.h
 * @brief VADC initialization for selected channels
 * -# DC link current
 * -# Average DC link current
 * -# DC link voltage
 * -# Potentiometer
 * -# User defined voltage
 * @date 2016-09-08

 *********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 * Copyright (c) 2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with
 * Infineon Technologies AG dave@infineon.com).
 *********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2016-01-28:
 *     - Initial version <br>
 * 2016-09-08:
 *     - Updated for sensorless support
 * @endcond
 *
 */
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */



#ifndef MCUINIT_VADC_H
#define MCUINIT_VADC_H


/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include "../Configuration/bldc_scalar_derived_parameter.h"
#include "../Configuration/bldc_scalar_mcuhw_config.h"

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
/* VADC startup calibration related MACRO's. Only applicable for xmc13 AA step micro-controllers */
#if(UC_STEP == AA_STEP)
  #define SHS0_CALOC0 ((uint32_t *)0x480340E0)
  #define SHS0_CALOC1 ((uint32_t *)0x480340E4)
  #define SHS0_CALCTR ((uint32_t *)0x480340BC)

  #define SHS_CALLOC0_CLEAR_OFFSET (0x8000U)
  #define REG_RESET (0x00U)
  #define GLOBCFG_CLEAR (0x80030000U)
  #define CLEAR_OFFSET_CALIB_VALUES         *SHS0_CALOC0 = SHS_CALLOC0_CLEAR_OFFSET;\
                                            *SHS0_CALOC1 = SHS_CALLOC0_CLEAR_OFFSET
#endif

#define BLDC_SCALAR_VADC_GROUP0 (0U)         /*!< VADC group 0 */
#define BLDC_SCALAR_VADC_GROUP1 (1U)         /*!< VADC group 1 */
#define BLDC_SCALAR_VADC_GROUP2 (2U)         /*!< VADC group 2 */
#define BLDC_SCALAR_VADC_GROUP3 (3U)         /*!< VADC group 3 */

/**
 * @addtogroup MCUInit
 * @brief  MCU peripheral initialization <br>
 * @{
 */
/*********************************************************************************************************************
 * DATA STRUCTURES
 ********************************************************************************************************************/
/**
 *  @brief Structure initializes VADC measurement for configured VADC channel.
 */
typedef struct VADC_MEASUREMENT_CONFIG
{
  const XMC_VADC_CHANNEL_CONFIG_t * channel_config;   /*!< Channel configuration */
  const XMC_VADC_RESULT_CONFIG_t *result_config;     /*!< Result register configuration */
  const XMC_VADC_QUEUE_ENTRY_t *queue_entry;         /*!< Queue entry configuration */
  XMC_VADC_GROUP_t *const group_ptr;                 /*!< Group pointer */
  const XMC_VADC_GROUP_INDEX_t group_num;            /*!< Group number */
  const uint8_t ch_num;                              /*!< Channel number */
  const uint8_t result_reg_num;                      /*!< Result register number */

} VADC_MEASUREMENT_CONFIG_t;

/**
 *  @brief Structure for Group/Global level configuration.
 */
typedef struct VADC_BOUNDARY_CONFIG
{
  XMC_VADC_GLOBAL_t *const module_ptr;               /*!< Holds the hardware VADC module pointer */
  uint32_t global_boundary0;                         /*!< Global boundary - 0 Range[0 - 4095] */
  uint32_t global_boundary1;                         /*!< Global boundary - 1 Range[0 - 4095] */
  uint32_t group_boundary0;                          /*!< Group boundary  - 0 Range[0 - 4095] */
  uint32_t group_boundary1;                          /*!< Group boundary  - 1 Range[0 - 4095] */

} VADC_BOUNDARY_CONFIG_t;
/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
/* Queue and Group enabling logic based upon user configuration */

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
      #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
      #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
      #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
      #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
      #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
      #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
      #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
      #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
       #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
       #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
       #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
       #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
      #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
      #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
      #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
      #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
       #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
       #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
       #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
       #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
       #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
       #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
       #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
       #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
       #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
       #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
       #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
       #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U)
  #ifndef VADC_ENABLE_GROUP_QUEUE_0
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP0)
       #define VADC_ENABLE_GROUP_QUEUE_0 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_1
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP1)
       #define VADC_ENABLE_GROUP_QUEUE_1 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_2
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP2)
       #define VADC_ENABLE_GROUP_QUEUE_2 (1U)
    #endif
  #endif

  #ifndef VADC_ENABLE_GROUP_QUEUE_3
    #if(MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM == BLDC_SCALAR_VADC_GROUP3)
       #define VADC_ENABLE_GROUP_QUEUE_3 (1U)
    #endif
  #endif
#endif

/* Disable Group and Queues which are not required for configured VADC conversions */
#ifndef VADC_ENABLE_GROUP_QUEUE_0
#define VADC_ENABLE_GROUP_QUEUE_0 (0U)
#endif

#ifndef VADC_ENABLE_GROUP_QUEUE_1
#define VADC_ENABLE_GROUP_QUEUE_1 (0U)
#endif

#ifndef VADC_ENABLE_GROUP_QUEUE_2
#define VADC_ENABLE_GROUP_QUEUE_2 (0U)
#endif

#ifndef VADC_ENABLE_GROUP_QUEUE_3
#define VADC_ENABLE_GROUP_QUEUE_3 (0U)
#endif

/* ADC On chip gain configuration - register configuration values */
#if(MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN == VADC_MEASUREMENT_ONCHIP_GAIN_3)
#define MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN_T  (1U)   /*!< ADC on chip gain is 3*/
#elif(MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN == VADC_MEASUREMENT_ONCHIP_GAIN_6)
#define MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN_T  (2U)   /*!< ADC on chip gain is 6*/
#elif(MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN == VADC_MEASUREMENT_ONCHIP_GAIN_12)
#define MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN_T  (3U)   /*!< ADC on chip gain is 12*/
#else
#define MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN_T  (0U)   /*!< ADC on chip gain is 1*/
#endif


#define VADC_MODULE_PTR ((XMC_VADC_GLOBAL_t*)(void*) VADC)     /*!< Global VADC module pointer */
#define VADC_SHS_PTR    (SHS0)            /*!< SHS module pointer */


/*********************************************************************************************************************
 * EXTERN
 ********************************************************************************************************************/
/*!< Direct DC Link current measurement handle */
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_IDCLink_CH_handle;     /* VADC Channel configuration for DC link current measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_IDCLink_Res_handle;      /* Result register configuration for DC link current measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_IDCLink_queue_entry;       /* Queue entry for DC link current measurement. */

/*!< Average DC Link current measurement handle */
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_IDCAverage_CH_handle;  /* VADC Channel configuration for DC link average current measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_IDCAverage_Res_handle;   /* Result register configuration for DC link average current measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_IDCAverage_queue_entry;    /* Queue entry for DC link average current measurement. */

/*!< DC Link voltage measurement handle*/
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_VDCLink_CH_handle;     /* VADC Channel configuration for DC link voltage measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_VDCLink_Res_handle;      /* Result register configuration for DC link voltage measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_VDCLink_queue_entry;       /* Queue entry for DC link voltage measurement. */

/*!< Potentiometer measurement handle */
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_AnalogInput_CH_handle; /* VADC Channel configuration for Analog input-POT measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_AnalogInput_Res_handle;  /* Result register configuration for Analog input-POT measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_AnalogInput_queue_entry;   /* Queue entry for Analog input-POT measurement. */

/*!< User defined measurement handle 1*/
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef1_CH_handle;    /* VADC Channel configuration for User defined -1 measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef1_Res_handle;     /* Result register configuration for User defined-1 measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef1_queue_entry;      /* Queue entry for user def measurement. */

/*!< User defined measurement handle 2*/
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef2_CH_handle;    /* VADC Channel configuration for User defined -2 measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef2_Res_handle;     /* Result register configuration for User defined-2 measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef2_queue_entry;      /* Queue entry for user def measurement. */

/*!< User defined measurement handle 3*/
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef3_CH_handle;    /* VADC Channel configuration for User defined -3 measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef3_Res_handle;     /* Result register configuration for User defined-3 measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef3_queue_entry;      /* Queue entry for user def measurement. */

/*!< User defined measurement handle 4*/
extern XMC_VADC_CHANNEL_CONFIG_t  Motor0_BLDC_SCALAR_VADC_UserDef4_CH_handle;    /* VADC Channel configuration for User defined -4 measurement. */
extern XMC_VADC_RESULT_CONFIG_t Motor0_BLDC_SCALAR_VADC_UserDef4_Res_handle;     /* Result register configuration for User defined-4 measurement. */
extern XMC_VADC_QUEUE_ENTRY_t Motor0_BLDC_SCALAR_VADC_UserDef4_queue_entry;      /* Queue entry for user def measurement. */




#ifdef __cplusplus
   extern "C" {
#endif
/*********************************************************************************************************************
 * API Prototypes
 ********************************************************************************************************************/
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Initializes VADC peripheral and power on the required VADC Group and Queues.
 * Only required converters will be turned on to optimize power consumption.
 */
void Motor0_BLDC_SCALAR_VADC_Init(void);

/* This function will return the VADC result for selected result register. */
/**
 * @param group_ptr VADC Group pointer
 * @param res_reg Result register number
 * @return XMC_VADC_RESULT_SIZE_t <br>
 *
 * \par<b>Description:</b><br>
 * Returns the VADC conversion result by reading result register from selected group number.
 */
__STATIC_INLINE XMC_VADC_RESULT_SIZE_t VADC_GetResult(XMC_VADC_GROUP_t *const group_ptr, const uint32_t res_reg)
{
  XMC_VADC_RESULT_SIZE_t result;
  result = (XMC_VADC_RESULT_SIZE_t) XMC_VADC_GROUP_GetResult(group_ptr,res_reg);
  /* If xmc13 AA step then clear the offset calibration */
  #if(UC_STEP == AA_STEP)
  CLEAR_OFFSET_CALIB_VALUES;
  #endif
  return(result);
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
#endif /* MCUINIT_VADC_H */
