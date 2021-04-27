// Support for the XMC1100 WDT (watchdog timer)

#ifndef PERIPHERALS_WDT_H
#define PERIPHERALS_WDT_H

unsigned int wdtEnable(const unsigned int lower_bound,
                       const unsigned int upper_bound,
                       const unsigned int enable_prewarning);
unsigned int wdtDisable(void);
#define wdtService() WDT_SRV = 0xabadcafe;

// Bits in WDT_WDTSTS and WDT_WDTCLR
#define WDT_ALMS BIT0

#endif
