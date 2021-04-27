// Support for the XMC1100 General Purpose IOs.

#ifndef PERIPHERALS_GPIO_H
#define PERIPHERALS_GPIO_H

#define togglePinP0(pin) P0_OMR = 0x00010001 << pin;
#define togglePinP1(pin) P1_OMR = 0x00010001 << pin;
#define togglePinP2(pin) P2_OMR = 0x00010001 << pin;
void setPin(const unsigned int port, const unsigned int pin);
void clearPin(const unsigned int port, const unsigned int pin);
int enablePin(const unsigned int port, const unsigned int pin,
              const unsigned int mode);
int disablePin(const unsigned int port, const unsigned int pin);

// Modes for enablePin
// Mode: Input
#define GPIO_IN_FLOAT		0x00
#define GPIO_IN_PD		0x08
#define GPIO_IN_PU		0x10
#define GPIO_IN_LOOP		0x18
// Mode: Inverted input
#define GPIO_IN_INV_FLOAT	0x20
#define GPIO_IN_INV_PD		0x28
#define GPIO_IN_INV_PU		0x30
#define GPIO_IN_INV_LOOP	0x38
// Mode: Push pull output
// Alt functions are listed at the end of chapter 18.
#define GPIO_OUT_PP		0x80
#define GPIO_OUT_PP_ALT1	0x88
#define GPIO_OUT_PP_ALT2	0x90
#define GPIO_OUT_PP_ALT3	0x98
#define GPIO_OUT_PP_ALT4	0xa0
#define GPIO_OUT_PP_ALT5	0xa8
#define GPIO_OUT_PP_ALT6	0xb0
#define GPIO_OUT_PP_ALT7	0xb8
// Mode: Open Drain output
#define GPIO_OUT_OD		0xc0
#define GPIO_OUT_OD_ALT1	0xc8
#define GPIO_OUT_OD_ALT2	0xd0
#define GPIO_OUT_OD_ALT3	0xd8
#define GPIO_OUT_OD_ALT4	0xe0
#define GPIO_OUT_OD_ALT5	0xe8
#define GPIO_OUT_OD_ALT6	0xf0
#define GPIO_OUT_OD_ALT7	0xf8

#endif
