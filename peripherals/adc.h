// Support for the XMC1100 ADC (untested).

#ifndef PERIPHERALS_ADC_H
#define PERIPHERALS_ADC_H

unsigned int enableADCPin(const unsigned int port, const unsigned int pin,
                          const unsigned int mode);
unsigned int disableADCPin(const unsigned int port, const unsigned int pin);
void adcCalibrate(int wait);
unsigned int adcEnable(const unsigned int sample_time,
                       const unsigned int conversion_mode,
                       const unsigned int data_reduction,
                       const unsigned int result_interrupt,
                       const unsigned int result_node,
                       const unsigned int source_interrupt,
                       const unsigned int source_node,
                       const unsigned int trigger_level,
                       const unsigned int trigger_input,
                       const unsigned int gate_enable,
                       const unsigned int gate_input);
unsigned int adcDisable(void);
void adcRequest(unsigned int group_channel);
unsigned int adcGetResult(unsigned int wait);

// VADC0_GLOBICLASSx STCS sample time values
#define STCS_2 0x00
#define STCS_3 0x01
#define STCS_4 0x02
#define STCS_5 0x03
#define STCS_6 0x04
#define STCS_7 0x05
#define STCS_8 0x06
#define STCS_9 0x07
#define STCS_10 0x08
#define STCS_11 0x09
#define STCS_12 0x0a
#define STCS_13 0x0b
#define STCS_14 0x0c
#define STCS_15 0x0d
#define STCS_16 0x0e
#define STCS_17 0x0f
#define STCS_18 0x10
#define STCS_34 0x11
#define STCS_242 0x1e
#define STCS_258 0x1f
// VADC0_GLOBICLASSx CMS conversion modes
#define CMS_12_BIT (0x00 << 8)
#define CMS_10_BIT (0x01 << 8)
#define CMS_8_BIT (0x02 << 8)
#define CMS_10_BIT_COMPARE (0x05 << 8)
// VADC0_GLOBRCR DRCTR data reduction values
#define DRCTR_DISABLED (0x00 << 16)
#define DRCTR_ACC_1 (0x01 << 16)
#define DRCTR_ACC_2 (0x02 << 16)
#define DRCTR_ACC_3 (0x03 << 16)
// VADC0_GLOBCR SRGEN values
#define SRGEN_ON BIT31
#define SRGEN_OFF 0x00
// VADC0_BRSMR ENSI values
#define ENSI_ON BIT3
#define ENSI_OFF 0x00
// VADC0_BRSMR ENGT gate enable values
#define ENGT_NONE (0x00 << 0)
#define ENGT_PENDING (0x01 << 0)
#define ENGT_REQGT1 (0x02 << 0)
#define ENGT_REQGT0 (0x03 << 0)
// ADC pin configuration request sources (table 15-5, page 15-40)
// VADC0_BRSCTRL Gate inputs
#define BGREQGTA_CCU40_ST3 (0x00 << 16)
#define BGREQGTB_CCU40_ST2 (0x01 << 16)
#define BGREQGTC_CCU40_ST1 (0x02 << 16)
#define BGREQGTD_CCU40_ST0 (0x03 << 16)
#define BGREQGTE (0x04 << 16)
#define BGREQGTF (0x05 << 16)
#define BGREQGTG (0x06 << 16)
#define BGREQGTH (0x07 << 16)
#define BGREQGTI (0x08 << 16)
#define BGREQGTJ (0x09 << 16)
#define BGREQGTK_ERU0_PDOUT2 (0x0a << 16)
#define BGREQGTL_ERU0_PDOUT3 (0x0b << 16)
#define BGREQGTM (0x0c << 16)
#define BGREQGTN (0x0d << 16)
#define BGREQGTO_ERU0_PDOUT0 (0x0e << 16)
#define BGREQGTP_ERU0_PDOUT1 (0x0f << 16)
// VADC0_BRSCTRL Trigger levels
#define XTMODE_NONE (0x00 << 13)
#define XTMODE_FALLING (0x01 << 13)
#define XTMODE_RISING (0x02 << 13)
#define XTMODE_ANY (0x03 << 13)
// VADC0_BRSCTRL Trigger inputs
#define BGREQTRA_CCU40_SR2 (0x00 << 8)
#define BGREQTRB_CCU40_SR3 (0x01 << 8)
#define BGREQTRC (0x02 << 8)
#define BGREQTRD (0x03 << 8)
#define BGREQTRE (0x04 << 8)
#define BGREQTRF (0x05 << 8)
#define BGREQTRG_ERU0_IOUT2 (0x06 << 8))
#define BGREQTRH_ERU0_IOUT3 (0x07 << 8)
#define BGREQTRI (0x08 << 8)
#define BGREQTRJ (0x09 << 8)
#define BGREQTRK (0x0a << 8)
#define BGREQTRL (0x0b << 8)
#define BGREQTRM_ERU0_IOUT0 (0x0c << 8)
#define BGREQTRN_ERU0_IOUT1 (0x0d << 8)
#define BGREQTRO (0x0e << 8)
#define BGREQTRP_BGREQGTSEL (0x0f << 8)

#define G0CH0_P2_6  0x00000000
#define G0CH1_P2_8  0x00000001
#define G0CH2_P2_9  0x00000002
#define G0CH3_P2_10 0x00000003
#define G0CH4_P2_11 0x00000004
#define G0CH5_P2_0  0x00000005
#define G0CH6_P2_1  0x00000006
#define G0CH7_P2_2  0x00000007
#define G1CH1_P2_7  0x00010000
#define G1CH5_P2_3  0x00050000
#define G1CH6_P2_4  0x00060000
#define G1CH7_P2_5  0x00070000

#endif
