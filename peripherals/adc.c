#include "xmc1100.h"
#include "adc.h"
#include "gpio.h"
#include "scu.h"

unsigned int enableADCPin(const unsigned int port, const unsigned int pin,
                          const unsigned int mode) {
	if (port != 2) {
		// Only port 2 of the XMC1100 has A/D functionality.
		return 1;
	}

	return enablePin(port, pin, mode);
}

unsigned int disableADCPin(const unsigned int port, const unsigned int pin) {
	if (port != 2) {
		// Only port 2 of the XMC1100 has A/D functionality.
		return 1;
	}
	return disablePin(port, pin);
}

void adcCalibrate(int wait) {
	VADC0_GLOBCFG |= BIT31;
	while (wait) {
		unsigned int state = (SHS0_CFG >> 28) & 0x0F;
		switch (state) {
		case 1:	// offset calibration active.
			break;
		case 2:	// gain calibration active.
			break;
		case 3:	// startup calibration active.
			break;
		default:
			wait = 0;
		}
	}
}

// Configure and enable the ADC.
//   sample_time is a STCS (eg. STCS_18)
//   conversion_mode is a CMS (eg. CMS_12_BIT)
//   data_reduction is a DRCTR (eg. DRCTR_DISABLED))
//   result_interrupt is a SRGEN (eg. SRGEN_ON)
//   result_node is the service request node pointer (C0SRx in table 15-5)
//   source_interrupt is a ENSI (eg. ENSI_ON)
//   source_node is the service request node pointer (C0SRx in table 15-5)
//   trigger_level is a XTMODE (eg. XTMODE_NONE)
//   trigger_input is a BGREQTRx. (eg. BGREQTRC)
//   gate_enable is a ENGT (eg. ENGT_PENDING)
//   gate_input is a BGREQGTx (eg. BGREQGTE)
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
                       const unsigned int gate_input) {
	// Clear gating of ADC in SCU_CGATCLR0
	scuUngatePeripheralClock(CGATCLR0_VADC);

	// Check the module ID
	if (SHS0_ID  >> 8 != 0x000099c0) {
		return 1;
	}

	// Configure analog settings in SHS.
	// AREF = internal reference, upper supply range (BIT1)
	// ANOFF = convertor controlled by ANONS
	// SCWC = enable AREF/ANOFF write (BIT15)
	SHS0_CFG = BIT15 | BIT1;
	// Wait for convertor to become operable.
	while (SHS0_CFG & BIT14) { }

	// DISR: 0 Module clock is not disabled (BIT0)
	// EDIS: 1 Module active during sleep (BIT3)
	VADC0_CLC = BIT3;

	// Configure trigger and gating.
	// BIT15 is trigger write control.
	// BIT23 is gate write control.
	unsigned int brsctrl = (BIT23 | gate_input |
	                        BIT15 | trigger_level | trigger_input);
	VADC0_BRSCTRL = brsctrl;

	// TODO: Support autoscan.  It uses BRSMR and the channel select
	// registers VADC0_BRSSEL0, VADC0_BRSSEL1. BRSSELx and the load
	// bit can be updated by writing BRSPNDx.
	// CLRPND: 1 (BIT8) clear pending bits.
	unsigned int brsmr = (BIT8 | source_interrupt | gate_enable);
	if (trigger_level != XTMODE_NONE) {
		brsmr |= BIT2;  // ENTR external trigger enable
	}
	VADC0_BRSMR = brsmr;
	// Result control register
	VADC0_GLOBRCR = data_reduction | result_interrupt;
	VADC0_GLOBEVNP = (result_node << 16) | source_node;

	// TODO: Enable groups to be configured separately.
	unsigned int globiclass = conversion_mode | sample_time;
	VADC0_GLOBICLASS0 = globiclass;
	VADC0_GLOBICLASS1 = globiclass;


	// Trigger calibration (60us)
	adcCalibrate(1);

	return 0;
}

unsigned int adcDisable(void) {
	// DISR: 1 Module clock is disabled (BIT0)
	// EDIS: 0 Module inactive during sleep (BIT3)
	VADC0_CLC = BIT0;

	// Configure analog settings in SHS.
	// AREF = external reference.
	// ANOFF = convertor off (BIT12)
	// SCWC = enable AREF/ANOFF write (BIT15)
	SHS0_CFG = BIT15 | BIT12;

	// Gate the ADC in SCU_CGATCLR0
	scuGatePeripheralClock(CGATCLR0_VADC);

	return 0;
}

// group_channel is a GxCHy group/channel selection
void adcRequest(unsigned int group_channel) {
	if (group_channel > 0xffff) {
		VADC0_BRSPND1 = (group_channel >> 16) & 0xffff;
	} else {
		VADC0_BRSPND0 = group_channel;
	}
}

unsigned int adcGetResult(unsigned int wait) {
	unsigned int result = VADC0_GLOBRES;
	// Check the result valid flag
	while (wait && !(result & BIT31)) {
		result = VADC0_GLOBRES;
	}
	return result;
}

void __attribute__((interrupt("IRQ"))) VADC0_SR0(void) {
	unsigned int globeflag = VADC0_GLOBEFLAG;
	if (globeflag & BIT0) {
		// Source event
		// adcRequest(...);
	}
	if (globeflag & BIT8) {
		// Result event
		adcGetResult(0);
		// TODO: Use result.
	}
	// Clear flags
	VADC0_GLOBEFLAG = BIT16 | BIT24;
}

void __attribute__((alias("VADC0_SR0"))) VADC0_SR1(void);

