// Support for the XMC1100 SCU (system control unit)

#ifndef PERIPHERALS_SCU_H
#define PERIPHERALS_SCU_H

// Reset trigger enables.
#define RSTCON_ECCRSTEN BIT0
#define RSTCON_LOCRSTEN BIT1
#define RSTCON_SPERSTEN BIT2
#define RSTCON_U0PERSTEN BIT3
#define RSTCON_ALL (BIT0 | BIT1 | BIT2 | BIT3)

// Postreset reset reason.
#define RSTSTAT_POWER_ON BIT0
#define RSTSTAT_MASTER_RESET BIT1
#define RSTSTAT_CPU_RESET BIT2
#define RSTSTAT_CPU_LOCKUP BIT3
#define RSTSTAT_FLASH_ECC BIT4
#define RSTSTAT_WDT BIT5
#define RSTSTAT_CLOCK_LOSS BIT6
#define RSTSTAT_PARITY_ERROR BIT7

// Clock control.
// CNTADJ = 1024 clock cycles
// RTC gets clock from standby source
// PCLK = 2 * MCLK (64MHz) (fdiv=00/256, idiv=01 (32MHz))
// MCLK = 32MHz
#define CLKCR_M32_P64 0x3ff10100
#define CLKCR_M8_P8 0x3ff00400

// Peripheral clock gating controls.
#define CGATCLR0_VADC BIT0
#define CGATCLR0_CCU40 BIT2
#define CGATCLR0_USIC0 BIT3
#define CGATCLR0_WDT BIT9
#define CGATCLR0_RTC BIT10

// SCU_SRMSK and SCU_SRRAW mask values.
// Watchdog timer prewarning event.
#define SRMSK_PRWARN BIT0
// Temperature sensor done, high and low events.
#define SRMSK_TSE_DONE BIT29
#define SRMSK_TSE_HIGH BIT30
#define SRMSK_TSE_LOW BIT31

// Convenience function to get reset reason and set clock speed.
unsigned int scuPostReset(const unsigned int clkcr);

// Get reason for previous reset.
unsigned int scuResetReason(void);
// Set reset triggers.
void scuResetControl(const unsigned int rstcon);

// Set CPU and peripheral clock speeds.
void scuClockControl(const unsigned int clkcr);

// Enable specified peripheral clock.
unsigned int scuUngatePeripheralClock(const unsigned int peripheral);
// Disable specified peripheral clock.
unsigned int scuGatePeripheralClock(const unsigned int peripheral);

#endif
