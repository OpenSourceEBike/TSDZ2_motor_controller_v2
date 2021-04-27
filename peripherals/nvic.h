// Support for the XMC1100 NVIC (nested vectored interrupt controller)

#ifndef PERIPHERALS_NVIC_H
#define PERIPHERALS_NVIC_H

void enableInterrupt(unsigned int interrupt, unsigned int priority);

void __attribute__((interrupt("IRQ"))) hardfaultHandler(void);
void __attribute__((interrupt("IRQ"))) systickHandler(void);
void __attribute__((interrupt("IRQ"))) SCU_SR0(void);
void __attribute__((interrupt("IRQ"))) SCU_SR1(void);
void __attribute__((interrupt("IRQ"))) IRQ02(void);
void __attribute__((interrupt("IRQ"))) ERU_SR0(void);
void __attribute__((interrupt("IRQ"))) ERU_SR1(void);
void __attribute__((interrupt("IRQ"))) ERU_SR2(void);
void __attribute__((interrupt("IRQ"))) ERU_SR3(void);
void __attribute__((interrupt("IRQ"))) IRQ07(void);
void __attribute__((interrupt("IRQ"))) IRQ08(void);
void __attribute__((interrupt("IRQ"))) USIC_SR0(void);
void __attribute__((interrupt("IRQ"))) USIC_SR1(void);
void __attribute__((interrupt("IRQ"))) USIC_SR2(void);
void __attribute__((interrupt("IRQ"))) USIC_SR3(void);
void __attribute__((interrupt("IRQ"))) USIC_SR4(void);
void __attribute__((interrupt("IRQ"))) USIC_SR5(void);
void __attribute__((interrupt("IRQ"))) VADC0_SR0(void);
void __attribute__((interrupt("IRQ"))) VADC0_SR1(void);
void __attribute__((interrupt("IRQ"))) IRQ17(void);
void __attribute__((interrupt("IRQ"))) IRQ18(void);
void __attribute__((interrupt("IRQ"))) IRQ19(void);
void __attribute__((interrupt("IRQ"))) IRQ20(void);
void __attribute__((interrupt("IRQ"))) CCU40_SR0(void);
void __attribute__((interrupt("IRQ"))) CCU40_SR1(void);
void __attribute__((interrupt("IRQ"))) CCU40_SR2(void);
void __attribute__((interrupt("IRQ"))) CCU40_SR3(void);
void __attribute__((interrupt("IRQ"))) IRQ25(void);
void __attribute__((interrupt("IRQ"))) IRQ26(void);
void __attribute__((interrupt("IRQ"))) IRQ27(void);
void __attribute__((interrupt("IRQ"))) IRQ28(void);
void __attribute__((interrupt("IRQ"))) IRQ29(void);
void __attribute__((interrupt("IRQ"))) IRQ30(void);
void __attribute__((interrupt("IRQ"))) IRQ31(void);

#endif
