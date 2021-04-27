// Support for the XMC1100 Systick generator.

#ifndef PERIPHERALS_SYSTICK_H
#define PERIPHERALS_SYSTICK_H

void systickEnable(const unsigned int period);
void systickDisable(void);

#endif
