#include "xmc1100.h"
#include "ccu.h"
#include "nvic.h"
#include "scu.h"

const unsigned int CC4[] = {CC40, CC41, CC42, CC43};

unsigned int ccuEnable(const unsigned int global_control) {
	// CCU4 clock is SCU fPCLK.
	scuUngatePeripheralClock(CGATCLR0_CCU40);

	// Check module identification
	// This is not available before peripheral clock starts.
	if ((CCU4_MIDR >> 8) != 0x0000A6C0) {
		return 1;
	}

	// Enable interrupt node 21-24 at priority 61-64
	enableInterrupt(21, 61);
	enableInterrupt(22, 62);
	enableInterrupt(23, 63);
	enableInterrupt(24, 64);

	// Stop any slices that were previously running.
	ccuStopSlices(BIT3 | BIT2 | BIT1 | BIT0);

	// Deassert synchronised start signal.
	SCU_CCUCON = 0;

	// Configure the global CCU4 register.  17.7.1
	// Request shadow transfer of period and compare registers.
	// Module clock is prescaler clock.
	// Prescaler cleared by software only.
	CCU4_GCTRL = global_control;

	return 0;
}

void ccuEnableSlices(const unsigned int slices) {
	CCU4_GIDLS = BIT9;  // clear the prescaler and load PVAL.
	// BIT8 enables the prescaler run bit for the CCU.
	CCU4_GIDLC = BIT8 | slices;
}

void ccuStartSlices(const unsigned int slices) {
	ccuEnableSlices(slices);
	// Start CCU40 timers that have been configured (INS and CMC registers)
	// to use SCU.GSC40 as a start event.
	SCU_CCUCON = BIT0;
	// Remove idle mode from the timer slices that were not started above.
	if (slices & BIT0) {
		CCU4_TCSET(CC40) = BIT0; // set timer slice 0 run bit.
	}
	if (slices & BIT1) {
		CCU4_TCSET(CC41) = BIT0;
	}
	if (slices & BIT2) {
		CCU4_TCSET(CC42) = BIT0;
	}
	if (slices & BIT3) {
		CCU4_TCSET(CC43) = BIT0;
	}
}

void ccuStopSlices(const unsigned int slices) {
	CCU4_GIDLS = slices;  // Put requested slices into idle.
}

// Helpers to build event fields.
//   is is the input selector.  It is an EVIS_INy_ value.
//   em is the edge selector.  It is an EVEM___ value.
//   lm is the active level selector.  It is an EVLM___ value.
//   lpf is the low pass filter count.  It is an LPFM__ value.
unsigned int ccuEvent0(unsigned int is, unsigned int em, unsigned int lm,
                       unsigned int lpf) {  // An LPFM__ value.
        return ((is << EV0IS_SHIFT) | (em << EV0EM_SHIFT) |
                (lm << EV0LM_SHIFT) | (lpf << EV0LPF_SHIFT));
}

unsigned int ccuEvent1(unsigned int is, unsigned int em, unsigned int lm,
                       unsigned int lpf) {
        return ((is << EV1IS_SHIFT) | (em << EV1EM_SHIFT) |
                (lm << EV1LM_SHIFT) | (lpf << EV1LPF_SHIFT));
}

unsigned int ccuEvent2(unsigned int is, unsigned int em, unsigned int lm,
                       unsigned int lpf) {
        return ((is << EV2IS_SHIFT) | (em << EV2EM_SHIFT) |
                (lm << EV2LM_SHIFT) | (lpf << EV2LPF_SHIFT));
}

void ccuConfigureSlice(const unsigned int slice, // 0 - 3
                       const unsigned int events,
                       const unsigned int connections,
                       const unsigned int timer_control,
                       const unsigned int prescaler,  // 0x00 - 0x0f
                       const unsigned int period,     // 0x0000 - 0xffff)
                       const unsigned int compare,    // 0x0000 - 0xffff)
                       const unsigned int interrupt_enable,
                       const unsigned int interrupt_route,
                       const unsigned int passive_level) {
	const unsigned int coffset = CC4[slice];
	CCU4_PSC(coffset) = prescaler;
	CCU4_TC(coffset) = timer_control;
	CCU4_INS(coffset) = events;
	CCU4_CMC(coffset) = connections;  // Set after timer_control.
	// Set external output passive level.  output = value ^ PSL
	CCU4_PSL(coffset) = passive_level;

	ccuSetPeriodCompare(slice, period, compare);

	CCU4_INTE(coffset) = interrupt_enable;
	if (interrupt_enable) {
		CCU4_SWR(coffset) = 0x00000f0f;  // Clear interrupt flags.
		CCU4_SRS(coffset) = interrupt_route;
	}
}

void ccuSetPeriodCompare(const unsigned int slice,
                         const unsigned int period,
                         const unsigned int compare) {
	const unsigned int coffset = CC4[slice];
	// Set the period match and compare level shadow registers.
	// Request transfer of shadow registers to the normal registers.
	// Using PRS blocks out C2V and C3V capture registers.
	// Using CRS blocks out C0V and C1V capture registers.
	CCU4_PRS(coffset) = period;
	CCU4_CRS(coffset) = compare;
	CCU4_GCSS = BIT0 << (slice * 4);  // Request transfer of PRS and CRS
}

