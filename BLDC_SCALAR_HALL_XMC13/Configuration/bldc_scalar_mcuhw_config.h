/**
 * @file bldc_scalar_mcuhw_config.h
 * @brief Peripheral configuration and interconnects as per selected Infineon board.
 * By default, these are configured for Infineon XMC13 low voltage motor control kit KIT_XMC1X_AK_MOTOR_001 with Maxon motor part no 267121.
 * @date 2016-08-09
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
 *2016-05-25:
 *     - Initial version
 * 2016-09-08:
 *     - Updated for sensorless support
 * @endcond
 *
 */

#ifndef BLDC_SCALAR_MCUHW_CONFIG_H_
#define BLDC_SCALAR_MCUHW_CONFIG_H_

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "xmc_ccu4.h"
#include "xmc_ccu8.h"
#include "xmc_posif.h"
#include "xmc_vadc.h"
#include "xmc_gpio.h"

#include "bldc_scalar_user_config.h"

/**
 * Contains peripheral configuration and interconnects as per selected Infineon board.
 * For Infineon low voltage and high voltage kits, peripherals are configured and control algorithm will work without any change.
 *
 * Change configurations if custom board is used and pins are different than Infineon board.
 * Refer XMC1300 reference manual for the peripheral register bit-fields and interconnects.
 */
/***********************************************************************************************************************
 * Device Related
 **********************************************************************************************************************/
#define AA_STEP (0U)
#define AB_STEP (1U)

/*!< MCU step for VADC startup calibration. */
#define UC_STEP (AB_STEP)

/* Peripheral configuration for infineon low voltage and high voltage board */
#if ((MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC1X_AK_MOTOR_001) || (MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC750WATT_MC_AK_V1))

/***********************************************************************************************************************
 * PWM Generation
 **********************************************************************************************************************/
/**
 * PWM output pins
 * For different pins than default configuration, Change the GPIO ALT mode and CCU8 module and slice numbers accordingly
 */
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_HS         P0_0
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_LS         P0_1
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_HS         P0_7
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_LS         P0_6
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_HS         P0_8
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_LS         P0_9

/** ALT mode is configured as CCU8 controlled output */
/* Refer register Px_IOCR in the reference manual */
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_HS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_LS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_HS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_LS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_HS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_LS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)

/** Three slices of the CCU8 which are connected to Phase U, V and W */
#define MOTOR0_BLDC_SCALAR_CCU8_MODULE          (CCU80)
#define MOTOR0_BLDC_SCALAR_CCU8_MODULE_NUM      (0U)

#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE      (CCU80_CC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE      (CCU80_CC81)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE      (CCU80_CC82)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM  (0U)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM  (1U)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM  (2U)

/***********************************************************************************************************************
 * CTRAP - CCU8 event 2
 **********************************************************************************************************************/
/** Trap pin and CCU8 input event 2 multiplexer configuration */
#if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
#define MOTOR0_BLDC_SCALAR_GPIO_TRAP                    P0_12

/* Refer CCU8 INS.EV2IS in reference manual */
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_CTRAP_EVT2_IN       (CCU80_IN0_P0_12)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_CTRAP_EVT2_IN       (CCU80_IN1_P0_12)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_CTRAP_EVT2_IN       (CCU80_IN2_P0_12)
#endif

/***********************************************************************************************************************
 * Synchronous start - CCU8 event 0
 **********************************************************************************************************************/
/**
 * Three CCU8 slices are started synchronously with CCUCON bit set
 * Refer CCU8 INS.EV0IS in reference manual
 */
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_EXTSTART_EVT0_IN   (CCU80_IN0_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_EXTSTART_EVT0_IN   (CCU80_IN1_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_EXTSTART_EVT0_IN   (CCU80_IN2_SCU_GSC80)

/***********************************************************************************************************************
 * Synchronous stop - CCU8 event 1
 **********************************************************************************************************************/
/**
 * Three CCU8 slices are stopped synchronously with CCUCON bit reset
 * Refer INS.EV1IS in reference manual
 */
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_EXTSTART_EVT1_IN   (CCU80_IN0_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_EXTSTART_EVT1_IN   (CCU80_IN1_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_EXTSTART_EVT1_IN   (CCU80_IN2_SCU_GSC80)

/***********************************************************************************************************************
 * Inverter Enable
 **********************************************************************************************************************/
/** Inverter enable pin in general purpose output mode */
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
#define MOTOR0_BLDC_SCALAR_GPIO_INV_ENABLE              P0_11
#endif

/***********************************************************************************************************************
 * HALL sensor interface
 **********************************************************************************************************************/
/** POSIF module number */
#define MOTOR0_BLDC_SCALAR_POSIF_MODULE            (POSIF0)
/**
 * Hall sensor input pins selection
 * For different pins than default configuration,
 * Change the POSIF input multiplexer configuration accordingly
 */
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
#define MOTOR0_BLDC_SCALAR_GPIO_HALL_1           P0_13
#define MOTOR0_BLDC_SCALAR_GPIO_HALL_2           P1_1
#if ((MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC1X_AK_MOTOR_001))
#define MOTOR0_BLDC_SCALAR_GPIO_HALL_3           P0_15
#elif (MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC750WATT_MC_AK_V1)
#define MOTOR0_BLDC_SCALAR_GPIO_HALL_3           P1_0
#endif
/** Input selector multiplexer */
/** Refer POSIF PCONF.INSEL0 in reference manual*/
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_0_INSEL      (XMC_POSIF_INPUT_PORT_B)
/** Refer POSIF PCONF.INSEL1 in reference manual*/
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_1_INSEL      (XMC_POSIF_INPUT_PORT_A)
/** Refer POSIF PCONF.INSEL2 in reference manual*/
#if ((MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC1X_AK_MOTOR_001))
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_2_INSEL      (XMC_POSIF_INPUT_PORT_B)
#elif (MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC750WATT_MC_AK_V1)
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_2_INSEL      (XMC_POSIF_INPUT_PORT_A)
#endif

/***********************************************************************************************************************
 * CCU4 configuration for blanking time and speed capture
 **********************************************************************************************************************/
/**
 * CCU4 module and slice numbers selection
 * For different hall pins than default configuration, Change the POSIF and CCU4 interconnects accordingly
 */
#define MOTOR0_BLDC_SCALAR_CCU4_MODULE            (CCU40)
/** Slice used for blanking time and phase delay */
#define MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE       (CCU40_CC40)
#define MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE_NUM       (0U)
/** Slice used for speed capture */
#define MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE     (CCU40_CC42)
#define MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE_NUM     (2U)

#if (MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4 == 1U)
#define MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE     (CCU40_CC41)       /*!< Slice used for multi-channel pattern synchronization */
#define MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE_NUM     (1U)
#endif

/***********************************************************************************************************************
 * CCU4 <-> POSIF interconnects
 **********************************************************************************************************************/
/**
 * blanking signal as CCU4 delay slice ST signal
 * Refer POSIF PCONF.DSEL in reference manual
 */
#define MOTOR0_BLDC_SCALAR_POSIF_BLANKING_SIGNAL_SEL  (XMC_POSIF_INPUT_PORT_A)

/**
 * multi-channel pattern update signal as CCU4 period match SR signal
 * Refer POSIF PCONF.MSETS in reference manual
 */
#define MOTOR0_BLDC_SCALAR_POSIF_PATTERN_UPDATE_SEL   (XMC_POSIF_INPUT_PORT_A)

/** multi-channel synch signal as CCU4.PS or CCU8.PS */
/* Refer POSIF PCONF.MSYNS in reference manual*/
#if (MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4 == 0U)
#define MOTOR0_BLDC_SCALAR_POSIF_PWM_SYNC_SIGNAL_SEL  (XMC_POSIF_INPUT_PORT_A)
#else
#define MOTOR0_BLDC_SCALAR_POSIF_PWM_SYNC_SIGNAL_SEL  (XMC_POSIF_INPUT_PORT_C)
#endif

/** CCU4 capture slice - Event 0 external capture signal as POSIF correct hall event */
/* Refer CCU4 INS.EV0IS in reference manual */
#define MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_EXTCAPTURE_IN   (CCU40_IN2_POSIF0_OUT1)
/** CCU4 delay slice - Event 0 external start signal as POSIF hall edge detected output */
/* Refer CCU4 INS.EV0IS in reference manual*/
#define MOTOR0_BLDC_SCALAR_CCU4_DELAY_EXTSTART_IN     (CCU40_IN0_POSIF0_OUT0)

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)*/

/***********************************************************************************************************************
 * Interrupt Configurations
 **********************************************************************************************************************/
/* NVIC nodes */
/** CCU8 one match event */
#define MOTOR0_BLDC_SCALAR_CTRL_LOOP_NODE            (CCU80_0_IRQn)
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
/** POSIF multi-channel pattern shadow transfer update event */
#define MOTOR0_BLDC_SCALAR_PATTERN_UPDATE_NODE       (POSIF0_1_IRQn)
/** POSIF correct/wrong hall event */
#define MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE           (POSIF0_0_IRQn)
#endif /*end of #if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)*/

/** CCU8 event 2 (trap) event */
#define MOTOR0_BLDC_SCALAR_CTRAP_NODE                 (CCU80_1_IRQn)


#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
/** VADC channel event for outside boundary condition */
#define MOTOR0_BLDC_SCALAR_VADC_PROTECTION_NODE      (VADC0_C0_0_IRQn)
#endif

/* Interrupt handlers */
#define Motor0_BLDC_SCALAR_ControlLoop_ISR           CCU80_0_IRQHandler
#define Motor0_BLDC_SCALAR_PatternShadowTx_ISR       (POSIF0_1_IRQHandler)
#define Motor0_BLDC_SCALAR_HallEvent_ISR             (POSIF0_0_IRQHandler)


#define Motor0_BLDC_SCALAR_Trap_PeriodMatch_ISR                  (CCU80_1_IRQHandler)


#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
#define Motor0_BLDC_SCALAR_Protection_ISR            (VADC0_C0_0_IRQHandler)
#endif

/* Service request node binding */
#define MOTOR0_BLDC_SCALAR_CCU8_ONEMATCH_SR          (XMC_CCU8_SLICE_SR_ID_0)
#define MOTOR0_BLDC_SCALAR_POSIF_MCP_SR              (XMC_POSIF_SR_ID_1)
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_SR             (XMC_POSIF_SR_ID_0)

#define MOTOR0_BLDC_SCALAR_CCU8_CTRAP_EVT2_SR         (XMC_CCU8_SLICE_SR_ID_1)

#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
#define MOTOR0_BLDC_SCALAR_VADC_CHEVT_SR             (XMC_VADC_SR_SHARED_SR0)
#endif

/** Phase V channel 2 down compare match event used for VADC queue trigger for current and voltage measurement */
#define MOTOR0_BLDC_SCALAR_CCU8_COMPMATCH_SR          (XMC_CCU8_SLICE_SR_ID_2)
/** Phase delay slice period match - used to trigger the multi-channel pattern transfer*/
#define MOTOR0_BLDC_SCALAR_CCU4_PHASE_DELAY_PM_SR    (XMC_CCU4_SLICE_SR_ID_0)

/**
 * Interrupt priority configurations
 * 0 is the highest priority and 3 is the lowest
*/
/* Control loop */
#define     MOTOR0_BLDC_SCALAR_CTRL_LOOP_NVIC_PRIO             (2U)
/* multi-channel pattern shadow transfer update */
#define     MOTOR0_BLDC_SCALAR_PATTERN_UPDATE_NVIC_PRIO        (1U)
/* Wrong hall and correct hall event */
#define     MOTOR0_BLDC_SCALAR_HALL_NVIC_PRIO                  (1U)
/* Systick */
#define     MOTOR0_BLDC_SCALAR_SYSTICK_NVIC_PRIO               (3U)

/* Ctrap */
#define     MOTOR0_BLDC_SCALAR_TRAP_NVIC_PRIO                  (0U)

#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
/* VADC channel event for current and voltage protection */
#define     MOTOR0_BLDC_SCALAR_VADC_PROTECTION_NVIC_PRIO       (0U)
#endif

/***********************************************************************************************************************
 * VADC configurations
 **********************************************************************************************************************/
/* Change VADC channel number and group  number as per the pins */

/* configure VADC on chip gain for both IDC link and IDC average current measurement*/
/** VADC on chip gain */
#define MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN               (VADC_MEASUREMENT_ONCHIP_GAIN_1)

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
/** Configuration Macros for DC link current measurement */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_CH_NUM            (1U)   /* 2.7 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP               (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP_NUM           (1U)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_RES_REG_NUM       (1U)
#endif

#if (MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC1X_AK_MOTOR_001)
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)
/** Configuration Macros for DC link average current measurement */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP              (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM          (1U)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM           (6U)    /* 2.4 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_RES_REG_NUM      (6U)
#endif
#elif  (MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC750WATT_MC_AK_V1)
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)
/** Configuration Macros for DC link average current measurement */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP              (VADC_G0)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM          (0U)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM           (6U)    /* 2.1 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_RES_REG_NUM      (6U)
#endif
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
/** Configuration Macros for DC link voltage measurement */
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP                 (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP_NUM             (1U)
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_CH_NUM              (5U)     /* 2.3 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_RES_REG_NUM         (5U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
/** Configuration Macros for Analog input - POT measurement */
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP             (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP_NUM         (1U)
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_CH_NUM          (7U)     /* 2.5 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_RES_REG_NUM     (7U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_CH_NUM             (4U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_RES_REG_NUM        (4U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_CH_NUM             (2U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_RES_REG_NUM        (2U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_CH_NUM             (3U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_RES_REG_NUM        (3U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_CH_NUM             (0U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_RES_REG_NUM        (0U)
#endif

/*
 * Queue configuration - Queue configuration will be applicable to corresponding group.
 * For Example Queue0 configuration is applicable for Group0 channels conversion.
 */
/** VADC Queue0 - Gating and trigger configuration */
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_GATE_SIGNAL       (XMC_CCU_40_ST0)
/* CCU8x compare match signal used for queue0 trigger */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)


/** VADC Queue1 - Gating and trigger configuration */
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_GATE_SIGNAL       (XMC_CCU_40_ST0)
/* CCU8x compare match signal used for queue1 trigger */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)

#if (XMC_VADC_MAXIMUM_NUM_GROUPS > 2U)
/** VADC Queue2 - Gating and trigger configuration */
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_GATE_SIGNAL       (XMC_CCU_40_ST0)
/* CCU8x compare match signal used for queue2 trigger */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)

/** VADC Queue3 - Gating and trigger configuration */
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))
/* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_GATE_SIGNAL       (XMC_CCU_40_ST0)
/* CCU8x compare match signal used for queue3 trigger */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)
#endif

/* end of #if ((MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC1X_AK_MOTOR_001) || (MOTOR0_BLDC_SCALAR_BOARD == KIT_XMC750WATT_MC_AK_V1))*/

#elif ((MOTOR0_BLDC_SCALAR_BOARD == KIT_CUSTOM))

/***********************************************************************************************************************
 * PWM Generation
 **********************************************************************************************************************/
/**
 * PWM output pins
 * For different pins than default configuration, Change the GPIO ALT mode and CCU8 module and slice numbers accordingly
 */
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_HS         P0_0
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_LS         P0_1
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_HS         P0_2
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_LS         P0_3
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_HS         P0_8
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_LS         P0_9

/** ALT mode is configured as CCU8 controlled output */
/* Refer register Px_IOCR in the reference manual */
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_HS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_U_LS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_HS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_V_LS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_HS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)
#define MOTOR0_BLDC_SCALAR_GPIO_PH_W_LS_MODE     (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT5)

// // disable PWM
// #define MOTOR0_BLDC_SCALAR_GPIO_PH_U_HS_MODE     (XMC_GPIO_MODE_INPUT_PULL_DOWN)
// #define MOTOR0_BLDC_SCALAR_GPIO_PH_U_LS_MODE     (XMC_GPIO_MODE_INPUT_PULL_DOWN)
// #define MOTOR0_BLDC_SCALAR_GPIO_PH_V_HS_MODE     (XMC_GPIO_MODE_INPUT_PULL_DOWN)
// #define MOTOR0_BLDC_SCALAR_GPIO_PH_V_LS_MODE     (XMC_GPIO_MODE_INPUT_PULL_DOWN)
// #define MOTOR0_BLDC_SCALAR_GPIO_PH_W_HS_MODE     (XMC_GPIO_MODE_INPUT_PULL_DOWN)
// #define MOTOR0_BLDC_SCALAR_GPIO_PH_W_LS_MODE     (XMC_GPIO_MODE_INPUT_PULL_DOWN)

/** Three slices of the CCU8 which are connected to Phase U, V and W */
#define MOTOR0_BLDC_SCALAR_CCU8_MODULE          (CCU80)
#define MOTOR0_BLDC_SCALAR_CCU8_MODULE_NUM      (0U)

#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE      (CCU80_CC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE      (CCU80_CC81)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE      (CCU80_CC82)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_SLICE_NUM  (0U)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_SLICE_NUM  (1U)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_SLICE_NUM  (2U)

/***********************************************************************************************************************
 * CTRAP - CCU8 event 2
 **********************************************************************************************************************/
/** Trap pin and CCU8 input event 2 multiplexer configuration */
#if (MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
#define MOTOR0_BLDC_SCALAR_GPIO_TRAP                    P0_12

/* Refer CCU8 INS.EV2IS in reference manual */
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_CTRAP_EVT2_IN       (CCU80_IN0_P0_12)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_CTRAP_EVT2_IN       (CCU80_IN1_P0_12)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_CTRAP_EVT2_IN       (CCU80_IN2_P0_12)
#endif

/***********************************************************************************************************************
 * Synchronous start - CCU8 event 0
 **********************************************************************************************************************/
/**
 * Three CCU8 slices are started synchronously with CCUCON bit set
 * Refer CCU8 INS.EV0IS in reference manual
 */
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_EXTSTART_EVT0_IN   (CCU80_IN0_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_EXTSTART_EVT0_IN   (CCU80_IN1_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_EXTSTART_EVT0_IN   (CCU80_IN2_SCU_GSC80)

/***********************************************************************************************************************
 * Synchronous stop - CCU8 event 1
 **********************************************************************************************************************/
/**
 * Three CCU8 slices are stopped synchronously with CCUCON bit reset
 * Refer INS.EV1IS in reference manual
 */
#define MOTOR0_BLDC_SCALAR_CCU8_PH_U_EXTSTART_EVT1_IN   (CCU80_IN0_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_V_EXTSTART_EVT1_IN   (CCU80_IN1_SCU_GSC80)
#define MOTOR0_BLDC_SCALAR_CCU8_PH_W_EXTSTART_EVT1_IN   (CCU80_IN2_SCU_GSC80)

/***********************************************************************************************************************
 * Inverter Enable
 **********************************************************************************************************************/
/** Inverter enable pin in general purpose output mode */
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
#define MOTOR0_BLDC_SCALAR_GPIO_INV_ENABLE              P0_11
#endif

/***********************************************************************************************************************
 * HALL sensor interface
 **********************************************************************************************************************/
/** POSIF module number */
#define MOTOR0_BLDC_SCALAR_POSIF_MODULE            (POSIF0)
/**
 * Hall sensor input pins selection
 * For different pins than default configuration,
 * Change the POSIF input multiplexer configuration accordingly
 */
#if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)
#define MOTOR0_BLDC_SCALAR_GPIO_HALL_1           P1_0
#define MOTOR0_BLDC_SCALAR_GPIO_HALL_2           P1_1
#define MOTOR0_BLDC_SCALAR_GPIO_HALL_3           P1_2

/** Input selector multiplexer */
/** Refer POSIF PCONF.INSEL0 in reference manual*/
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_0_INSEL      (XMC_POSIF_INPUT_PORT_A)
/** Refer POSIF PCONF.INSEL1 in reference manual*/
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_1_INSEL      (XMC_POSIF_INPUT_PORT_A)
/** Refer POSIF PCONF.INSEL2 in reference manual*/
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_2_INSEL      (XMC_POSIF_INPUT_PORT_A)

/***********************************************************************************************************************
 * CCU4 configuration for blanking time and speed capture
 **********************************************************************************************************************/
/**
 * CCU4 module and slice numbers selection
 * For different hall pins than default configuration, Change the POSIF and CCU4 interconnects accordingly
 */
#define MOTOR0_BLDC_SCALAR_CCU4_MODULE            (CCU40)
#define MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE       (CCU40_CC40)       /*!< Slice used for blanking time and phase delay */
#define MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE     (CCU40_CC42)      /*!< Slice used for speed capture */
#define MOTOR0_BLDC_SCALAR_CCU4_DELAY_SLICE_NUM       (0U)
#define MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_SLICE_NUM     (2U)

#if (MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4 == 1U)
#define MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE     (CCU40_CC41)       /*!< Slice used for multi-channel pattern synchronization */
#define MOTOR0_BLDC_SCALAR_CCU4_MCMSYNC_SLICE_NUM     (1U)
#endif

/***********************************************************************************************************************
 * CCU4 <-> POSIF interconnects
 **********************************************************************************************************************/
/**
 * blanking signal as CCU4 delay slice ST signal
 * Refer POSIF PCONF.DSEL in reference manual*/
#define MOTOR0_BLDC_SCALAR_POSIF_BLANKING_SIGNAL_SEL  (XMC_POSIF_INPUT_PORT_A)

/** multi-channel pattern update signal as CCU4 period match SR signal */
/* Refer POSIF PCONF.MSETS in reference manual*/
#define MOTOR0_BLDC_SCALAR_POSIF_PATTERN_UPDATE_SEL   (XMC_POSIF_INPUT_PORT_A)

/** multi-channel synch signal as CCU4.PS or CCU8.PS */
/* Refer POSIF PCONF.MSYNS in reference manual*/
#if (MOTOR0_BLDC_SCALAR_ENABLE_FAST_SYNCH_CCU4 == 0U)
#define MOTOR0_BLDC_SCALAR_POSIF_PWM_SYNC_SIGNAL_SEL  (XMC_POSIF_INPUT_PORT_A)
#else
#define MOTOR0_BLDC_SCALAR_POSIF_PWM_SYNC_SIGNAL_SEL  (XMC_POSIF_INPUT_PORT_C)
#endif

/** CCU4 capture slice - Event 0 external capture signal as POSIF correct hall event */
/* Refer CCU4 INS.EV0IS in reference manual */
#define MOTOR0_BLDC_SCALAR_CCU4_CAPTURE_EXTCAPTURE_IN   (CCU40_IN2_POSIF0_OUT1)
/** CCU4 delay slice - Event 0 external start signal as POSIF hall edge detected output */
/* Refer CCU4 INS.EV0IS in reference manual*/
#define MOTOR0_BLDC_SCALAR_CCU4_DELAY_EXTSTART_IN     (CCU40_IN0_POSIF0_OUT0)

#endif  /* end of #if (MOTOR0_BLDC_SCALAR_FEEDBACK == BLDC_SCALAR_3HALL)*/

/***********************************************************************************************************************
 * Interrupt Configurations
 **********************************************************************************************************************/
/* NVIC nodes */
#define MOTOR0_BLDC_SCALAR_CTRL_LOOP_NODE            (CCU80_0_IRQn)      /*!< CCU8 one match event */
#define MOTOR0_BLDC_SCALAR_PATTERN_UPDATE_NODE       (POSIF0_1_IRQn)     /*!< POSIF multi-channel pattern shadow transfer update event */
#define MOTOR0_BLDC_SCALAR_HALL_EVENT_NODE           (POSIF0_0_IRQn)     /*!< POSIF correct/wrong hall event */


#define MOTOR0_BLDC_SCALAR_CTRAP_NODE                 (CCU80_1_IRQn)     /*!< CCU8 event 2 (trap) event */


#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
#define MOTOR0_BLDC_SCALAR_VADC_PROTECTION_NODE      (VADC0_C0_0_IRQn)  /*!< VADC channel event for outside boundary condition */
#endif

/* Interrupt handlers */
#define Motor0_BLDC_SCALAR_ControlLoop_ISR           (CCU80_0_IRQHandler)
#define Motor0_BLDC_SCALAR_PatternShadowTx_ISR       (POSIF0_1_IRQHandler)
#define Motor0_BLDC_SCALAR_HallEvent_ISR             (POSIF0_0_IRQHandler)


#define Motor0_BLDC_SCALAR_Trap_PeriodMatch_ISR                  (CCU80_1_IRQHandler)


#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
#define Motor0_BLDC_SCALAR_Protection_ISR            (VADC0_C0_0_IRQHandler)
#endif

/* Service request node binding */
#define MOTOR0_BLDC_SCALAR_CCU8_ONEMATCH_SR          (XMC_CCU8_SLICE_SR_ID_0)
#define MOTOR0_BLDC_SCALAR_POSIF_MCP_SR              (XMC_POSIF_SR_ID_1)
#define MOTOR0_BLDC_SCALAR_POSIF_HALL_SR             (XMC_POSIF_SR_ID_0)

#define MOTOR0_BLDC_SCALAR_CCU8_CTRAP_EVT2_SR         (XMC_CCU8_SLICE_SR_ID_1)

#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
#define MOTOR0_BLDC_SCALAR_VADC_CHEVT_SR             (XMC_VADC_SR_SHARED_SR0)
#endif

/** Phase V channel 2 down compare match event used for VADC queue trigger for current and voltage measurement */
#define MOTOR0_BLDC_SCALAR_CCU8_COMPMATCH_SR          (XMC_CCU8_SLICE_SR_ID_2)
/** Phase delay slice period match - used to trigger the multi-channel pattern transfer*/
#define MOTOR0_BLDC_SCALAR_CCU4_PHASE_DELAY_PM_SR    (XMC_CCU4_SLICE_SR_ID_0)

/**
 * Interrupt priority configurations
0 is the highest priority and 3 is the lowest
*/
#define     MOTOR0_BLDC_SCALAR_CTRL_LOOP_NVIC_PRIO             (2U)   /* Control loop */
#define     MOTOR0_BLDC_SCALAR_PATTERN_UPDATE_NVIC_PRIO        (1U)   /* multi-channel pattern shadow transfer update */
#define     MOTOR0_BLDC_SCALAR_HALL_NVIC_PRIO                  (1U)   /* Wrong hall and correct hall event */
#define     MOTOR0_BLDC_SCALAR_SYSTICK_NVIC_PRIO               (3U)   /* Systick */

#define     MOTOR0_BLDC_SCALAR_TRAP_NVIC_PRIO                  (0U)   /* Ctrap */

#if ((MOTOR0_BLDC_SCALAR_ENABLE_OVER_CURRENT == 1U) || (MOTOR0_BLDC_SCALAR_ENABLE_UNDER_OVER_VOLTAGE == 1U))
#define     MOTOR0_BLDC_SCALAR_VADC_PROTECTION_NVIC_PRIO       (0U)   /* VADC channel event for current and voltage protection */
#endif

/***********************************************************************************************************************
 * VADC configurations
 **********************************************************************************************************************/
#define MOTOR0_BLDC_SCALAR_VADC_ON_CHIP_GAIN               (VADC_MEASUREMENT_ONCHIP_GAIN_1) /*!< VADC on chip gain */

/* Change VADC channel number and group  number as per the pins */
#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_LINK_MEASUREMENT == 1U)
/** Configuration Macros for DC link current measurement */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP               (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_GRP_NUM           (1U)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_CH_NUM            (0U)   /* 2.8 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_LINK_RES_REG_NUM       (0U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_IDC_AVERAGE_MEASUREMENT == 1U)
/** Configuration Macros for DC link average current measurement */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP              (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_GRP_NUM          (1U)
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_CH_NUM           (6U)    /* 2.4 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_IDC_AVERAGE_RES_REG_NUM      (6U)
#endif


#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_VDC_LINK_MEASUREMENT == 1U)
/** Configuration Macros for DC link voltage measurement */
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP                 (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_GRP_NUM             (1U)
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_CH_NUM              (6U)     /* 2.4 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_VDC_LINK_RES_REG_NUM         (6U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_POTENTIOMETER_MEASUREMENT == 1U)
/** Configuration Macros for Analog input - POT measurement */
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP             (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_GRP_NUM         (1U)
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_CH_NUM          (7U)     /* 2.5 VADC Pin */
#define MOTOR0_BLDC_SCALAR_VADC_ANALOG_INPUT_RES_REG_NUM     (7U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF1_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_CH_NUM             (4U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF1_RES_REG_NUM        (4U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF2_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_CH_NUM             (2U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF2_RES_REG_NUM        (2U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF3_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_CH_NUM             (3U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF3_RES_REG_NUM        (3U)
#endif

#if (MOTOR0_BLDC_SCALAR_VADC_ENABLE_USER_DEF4_MEASUREMENT == 1U)
/** Configuration Macros for VADC Channel */
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_GRP                (VADC_G1)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_GRP_NUM            (1U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_CH_NUM             (0U)
#define MOTOR0_BLDC_SCALAR_VADC_USER_DEF4_RES_REG_NUM        (0U)
#endif

/*
 * Queue configuration - Queue configuration will be applicable to corresponding group.
 * For Example Queue0 configuration is applicable for Group0 channels conversion.
 */
/** VADC Queue0 - Gating and trigger configuration */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))         /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_GATE_SIGNAL       (XMC_CCU_40_ST0)                   /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_0_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)                   /* CCU8x compare match signal used for queue0 trigger */


/** VADC Queue1 - Gating and trigger configuration */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))         /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_GATE_SIGNAL       (XMC_CCU_40_ST0)                   /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_1_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)                   /* CCU8x compare match signal used for queue1 trigger */

#if (XMC_VADC_MAXIMUM_NUM_GROUPS > 2U)
/** VADC Queue2 - Gating and trigger configuration */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))         /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_GATE_SIGNAL       (XMC_CCU_40_ST0)                   /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_2_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)                   /* CCU8x compare match signal used for queue2 trigger */

/** VADC Queue3 - Gating and trigger configuration */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_GATING            ((XMC_VADC_GATEMODE_t)(XMC_VADC_GATEMODE_IGNORE))         /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_GATE_SIGNAL       (XMC_CCU_40_ST0)                   /* Gating disabled */
#define MOTOR0_BLDC_SCALAR_VADC_QUEUE_3_TRIGGER_SIGNAL    (XMC_CCU_80_SR2)                   /* CCU8x compare match signal used for queue3 trigger */
#endif


#endif  /* end of if (MOTOR0_BLDC_SCALAR_BOARD == KIT_CUSTOM) */


#endif /* BLDC_SCALAR_MCUHW_CONFIG_H_ */
