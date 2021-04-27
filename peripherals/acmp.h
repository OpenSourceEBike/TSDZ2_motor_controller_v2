// Support for the XMC1x00 ACMP (analog comparator)
//
// XMC1100 and XMC1200 ACMP pin connections:
// Analog Inputs:
//   P2.1:            ACMP2.INP
//   P2.2:  ORC0.AIN  ACMP2.INN
//   P2.3:  ORC1.AIN
//   P2.4:  ORC2.AIN
//   P2.5:  ORC3.AIN
//   P2.6:  ORC4.AIN  ACMP1.INN
//   P2.7:  ORC5.AIN  ACMP1.INP
//   P2.8:  ORC6.AIN  ACMP0.INN
//   P2.9:  ORC7.AIN  ACMP0.INP
//   P2.11:           ACMP.REF
// ACMP Outputs:
//   ACMP0.OUT: P0.10 alt4              P2.10 alt6  ERU0.0A0  BCCU0.IN5
//   ACMP1.OUT:             P1.0 alt 6  P2.5pull    ERU0.1A0  BCCU0.IN0
//   ACMP2.OUT: P0.5 alt 6  P1.2 alt 6  P2.3pull    ERU0.2A0  BCCU0.IN3
// ORC Outputs:
//   ORC0.OUT:  ERU0.0B2
//   ORC1.OUT:  ERU0.1B2
//   ORC2.OUT:  ERU0.0A2 ERU0.2B2
//   ORC3.OUT:  ERU0.1A2
//   ORC4.OUT:  ERU0.2A2
//   ORC5.OUT:  ERU0.3A2
//   ORC6.OUT:  ERU0.3B2
//   ORC7.OUT:  ERU0.3A0
//
// Interrupts are enabled through setting SCU_* bits in SCU_SRMSK

#ifndef PERIPHERALS_ACMP_H
#define PERIPHERALS_ACMP_H

#define ACMP_ORCCTRL    REGISTER_32(ORC_BASE)
#define ACMP_ANACMP(x)  REGISTER_32(ACMP_BASE + (x * 4))

// Analog comparator flags
// enable
#define ACMP_CMP_EN           BIT0
// disable filter
#define ACMP_CMP_FLT_OFF      BIT1
// invert output
#define ACMP_CMP_INV_OUT      BIT3
// select mV of hysteresis
#define ACMP_CMP_HYST_ADJ_0   0
#define ACMP_CMP_HYST_ADJ_10  BIT4
#define ACMP_CMP_HYST_ADJ_15  BIT5
#define ACMP_CMP_HYST_ADJ_20  BIT5 | BIT4
// ref voltage from resistor divider is applied to ACMP1.INP
#define ACMP_CMP1_DIV_EN      BIT6
// connect ACMP1.INP to ACMP0.INN or ACMP2.INP
// used to supply ref voltage to both pins
#define ACMP_CMP0_SEL         BIT6
#define ACMP_CMP2_SEL         BIT6
// enable low power mode for all comparators
// default is high power mode for better performance.
#define ACMP_CMP0_LPWR        BIT8
// output monitor bit (read only)
// Vminus > Vplus: 0
// Vminus < Vplus: 1
#define ACMP_CMP_OUT          BIT15

void acmpEnable(void) {}
void acmpDisable(void) {}
// Configure the out of range comparators.
//   enable is a bitwise or of the desired ORC_ENORCx + ORC_CNFx flags.
//   ORC_CNFx sets the trigger on the rising edge (falling edge is default).
void orcConfigure(unsigned int enable) { ACMP_ORCCTRL = enable; }
// Configure an analog comparator.
//   channel is the comparator channel (0 through 2).
//   flags is a bitwise or of the desired ACMP_ flags.
void acmpConfigure(unsigned int channel, unsigned int flags) {
	ACMP_ANACMP(channel) = flags;
}
// Read the analog comparator channel result.
int acmpRead(unsigned int channel) {
	return ACMP_ANACMP(channel) & ACMP_CMP_OUT;
}

// Out of range comparator enable flags
#define ORC_ENORC0 BIT0
#define ORC_ENORC1 BIT1
#define ORC_ENORC2 BIT2
#define ORC_ENORC3 BIT3
#define ORC_ENORC4 BIT4
#define ORC_ENORC5 BIT5
#define ORC_ENORC6 BIT6
#define ORC_ENORC7 BIT7
// Out of range comparator rising edge select
// (falling edge is default)
#define ORC_CNF0 BIT16
#define ORC_CNF1 BIT17
#define ORC_CNF2 BIT18
#define ORC_CNF3 BIT19
#define ORC_CNF4 BIT20
#define ORC_CNF5 BIT21
#define ORC_CNF6 BIT22
#define ORC_CNF7 BIT23

// Interrupts are enabled through setting SCU_* bits in SCU_SRMSK
#define SCU_ACMP0I  BIT4
#define SCU_ACMP1I  BIT5
#define SCU_ACMP2I  BIT6
#define SCU_ORC0I   BIT8
#define SCU_ORC1I   BIT9
#define SCU_ORC2I   BIT10
#define SCU_ORC3I   BIT11
#define SCU_ORC4I   BIT12
#define SCU_ORC5I   BIT13
#define SCU_ORC6I   BIT14
#define SCU_ORC7I   BIT15

#endif
