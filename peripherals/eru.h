// Support for the XMC1000 series ERU (Event Request Unit)

#ifndef PERIPHERALS_ERU_H
#define PERIPHERALS_ERU_H

unsigned int eruEnable(void);
unsigned int eruDisable(void);

unsigned int  eruConfigureETL0(
    unsigned int exs_a_input,  // EXISEL_EXS_INx
    unsigned int exs_b_input,  // EXISEL_EXS_INx
    unsigned int exicon);      // EXICON values

unsigned int  eruConfigureETL1(
    unsigned int exs_a_input,  // EXISEL_EXS_INx
    unsigned int exs_b_input,  // EXISEL_EXS_INx
    unsigned int exicon);      // EXICON values

unsigned int  eruConfigureETL2(
    unsigned int exs_a_input,  // EXISEL_EXS_INx
    unsigned int exs_b_input,  // EXISEL_EXS_INx
    unsigned int exicon);      // EXICON values

unsigned int  eruConfigureETL3(
    unsigned int exs_a_input,  // EXISEL_EXS_INx
    unsigned int exs_b_input,  // EXISEL_EXS_INx
    unsigned int exicon);      // EXICON values

unsigned int eruConfigureOGU0(unsigned int exocon);  // EXOCON values
unsigned int eruConfigureOGU1(unsigned int exocon);  // EXOCON values
unsigned int eruConfigureOGU2(unsigned int exocon);  // EXOCON values
unsigned int eruConfigureOGU3(unsigned int exocon);  // EXOCON values

// EXISEL register values.  eg. (EXISEL_EXS_IN1 << EXISEL_EXS0A_SHIFT) | ...
#define EXISEL_EXS_MASK 3
#define EXISEL_EXS_IN0 0
#define EXISEL_EXS_IN1 1
#define EXISEL_EXS_IN2 2
#define EXISEL_EXS_IN3 3
#define EXISEL_EXS0A_SHIFT 0
#define EXISEL_EXS0B_SHIFT 2
#define EXISEL_EXS1A_SHIFT 4
#define EXISEL_EXS1B_SHIFT 6
#define EXISEL_EXS2A_SHIFT 8
#define EXISEL_EXS2B_SHIFT 10
#define EXISEL_EXS3A_SHIFT 12
#define EXISEL_EXS3B_SHIFT 14

// EXICON[3:0] register values.
// Output trigger pulse when selected edge is detected.
#define EXICON_PE_MASK (1 << 0)
#define EXICON_PE_DISABLE (0 << 0)
#define EXICON_PE_ENABLE (1 << 0)
// Status flag rebuild level detection / sticky.
#define EXICON_LD_MASK (1 << 1)
#define EXICON_LD_STICKY (0 << 1)
#define EXICON_LD_REBUILD (1 << 1)
// Rising edge detection.
#define EXICON_RE_MASK (1 << 2)
#define EXICON_RE_DISABLE (0 << 2)
#define EXICON_RE_ENABLE (1 << 2)
// Falling edge detection.
#define EXICON_FE_MASK (1 << 3)
#define EXICON_FE_DISABLE (0 << 3)
#define EXICON_FE_ENABLE (1 << 3)
// Output channel select.
#define EXICON_OCS_MASK (7 << 4)
#define EXICON_OCS_OGU0 (0 << 4)
#define EXICON_OCS_OGU1 (1 << 4)
#define EXICON_OCS_OGU2 (2 << 4)
#define EXICON_OCS_OGU3 (3 << 4)
// Status flag value.
#define EXICON_FL_MASK (1 << 7)
// Input source select.
#define EXICON_SS_MASK (3 << 8)
#define EXICON_SS_A (0 << 8)
#define EXICON_SS_B (1 << 8)
#define EXICON_SS_A_OR_B (2 << 8)
#define EXICON_SS_A_AND_B (3 << 8)
// Input A negation.
#define EXICON_NA_MASK (1 << 10)
#define EXICON_NA_DIRECT (0 << 10)
#define EXICON_NA_INVERT (1 << 10)
// Input B negation.
#define EXICON_NB_MASK (1 << 11)
#define EXICON_NB_DIRECT (0 << 11)
#define EXICON_NB_INVERT (1 << 11)

// EXOCON[3:0] register values.
// Internal trigger source selection.
#define EXOCON_ISS_MASK (3 << 0)
#define EXOCON_ISS_DISABLE (0 << 0)
#define EXOCON_ISS_OGUY1 (1 << 0)
#define EXOCON_ISS_OGUY2 (2 << 0)
#define EXOCON_ISS_OGUY3 (3 << 0)
// Generate trigger event on pattern detection.
#define EXOCON_GEEN_MASK (1 << 2)
#define EXOCON_GEEN_DISABLE (0 << 2)
#define EXOCON_GEEN_ENABLE (1 << 2)
// Pattern detection result.
#define EXOCON_PDR_MASK (1 << 3)
// Gating selection and pattern detection result.
#define EXOCON_GP_MASK (3 << 4)
//   No interrupt
#define EXOCON_GP_GOUT_DISABLE_IOUT_DISABLE (0 << 4)
//   Interrupt for events
#define EXOCON_GP_GOUT_ENABLE_IOUT_TOUT (1 << 4)
//   Interrupt for events if PD
#define EXOCON_GP_GOUT_PDOUT_IOUT_TOUT (2 << 4)
//   Interrupt for events if not PD
#define EXOCON_GP_INV_GOUT_PDOUT_IOUT_TOUT (3 << 4)
// Pattern detection enable.
#define EXOCON_IPEN_MASK (15 << 12)
#define EXOCON_IPEN_EXICON0 (1 << 12)
#define EXOCON_IPEN_EXICON1 (1 << 13)
#define EXOCON_IPEN_EXICON2 (1 << 14)
#define EXOCON_IPEN_EXICON3 (1 << 15)



#endif  // PERIPHERALS_ERU_H
