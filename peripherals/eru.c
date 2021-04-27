#include "xmc1100.h"
#include "eru.h"
#include "nvic.h"

unsigned int eruEnable() {
	// ERU does not require clock enable.

	// Enable ERU interrupt node 3-6 at priority 65-68
	enableInterrupt(3, 65);
	enableInterrupt(4, 66);
	enableInterrupt(5, 67);
	enableInterrupt(6, 68);

	return 0;
}

unsigned int eruDisable() {
	return 0;
}

unsigned int  eruConfigureETL0(unsigned int exs_a_input,  // EXISEL_EXS_INx
                               unsigned int exs_b_input,  // EXISEL_EXS_INx
                               unsigned int exicon) {     // EXICON values
	unsigned int exisel = EXISEL;

	// Configure input selector.
	exisel &= !((EXISEL_EXS_MASK << EXISEL_EXS0A_SHIFT) |
	            (EXISEL_EXS_MASK << EXISEL_EXS0B_SHIFT));
	exisel |= ((exs_a_input << EXISEL_EXS0A_SHIFT) |
	           (exs_b_input << EXISEL_EXS0B_SHIFT));
	EXISEL = exisel;
	EXICON0 = exicon;
	return 0;
}

unsigned int  eruConfigureETL1(unsigned int exs_a_input,  // EXISEL_EXS_INx
                               unsigned int exs_b_input,  // EXISEL_EXS_INx
                               unsigned int exicon) {     // EXICON values
	unsigned int exisel = EXISEL;

	// Configure input selector.
	exisel &= !((EXISEL_EXS_MASK << EXISEL_EXS1A_SHIFT) |
	            (EXISEL_EXS_MASK << EXISEL_EXS1B_SHIFT));
	exisel |= ((exs_a_input << EXISEL_EXS1A_SHIFT) |
	           (exs_b_input << EXISEL_EXS1B_SHIFT));
	EXISEL = exisel;
	EXICON1 = exicon;
	return 0;
}

unsigned int  eruConfigureETL2(unsigned int exs_a_input,  // EXISEL_EXS_INx
                               unsigned int exs_b_input,  // EXISEL_EXS_INx
                               unsigned int exicon) {     // EXICON values
	unsigned int exisel = EXISEL;

	// Configure input selector.
	exisel &= !((EXISEL_EXS_MASK << EXISEL_EXS2A_SHIFT) |
	            (EXISEL_EXS_MASK << EXISEL_EXS2B_SHIFT));
	exisel |= ((exs_a_input << EXISEL_EXS2A_SHIFT) |
	           (exs_b_input << EXISEL_EXS2B_SHIFT));
	EXISEL = exisel;
	EXICON2 = exicon;
	return 0;
}

unsigned int  eruConfigureETL3(unsigned int exs_a_input,  // EXISEL_EXS_INx
                               unsigned int exs_b_input,  // EXISEL_EXS_INx
                               unsigned int exicon) {     // EXICON values
	unsigned int exisel = EXISEL;

	// Configure input selector.
	exisel &= !((EXISEL_EXS_MASK << EXISEL_EXS3A_SHIFT) |
	            (EXISEL_EXS_MASK << EXISEL_EXS3B_SHIFT));
	exisel |= ((exs_a_input << EXISEL_EXS3A_SHIFT) |
	           (exs_b_input << EXISEL_EXS3B_SHIFT));
	EXISEL = exisel;
	EXICON3 = exicon;
	return 0;
}

unsigned int eruConfigureOGU0(unsigned int exocon) {
	EXOCON0 = exocon;
	return 0;
}

unsigned int eruConfigureOGU1(unsigned int exocon) {
	EXOCON1 = exocon;
	return 0;
}

unsigned int eruConfigureOGU2(unsigned int exocon) {
	EXOCON2 = exocon;
	return 0;
}

unsigned int eruConfigureOGU3(unsigned int exocon) {
	EXOCON3 = exocon;
	return 0;
}

