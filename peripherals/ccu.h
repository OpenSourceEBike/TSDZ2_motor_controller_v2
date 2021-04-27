// Support for the XMC1100 CCU4 (Capture Compare Unit 4)

#ifndef PERIPHERALS_CCU_H
#define PERIPHERALS_CCU_H

// Enable and perform global configuration of the CCU peripheral.
//  global_control is an or of GCTRL values.
unsigned int ccuEnable(const unsigned int global_control);

// Enable requested slices.
// Once enabled slices can be started by their nominated start events.
void ccuEnableSlices(const unsigned int slices);

// Enable and start requested slices.
// Uses SCU.GSC40 to start slices simultaneously if CCU4_CC4xINS and
// CCU4_CC4xCMC have been configured to start the slices on an SCU event.
//   slices is a bit field of slices to start (0=slice 0 .. 3=slice3).
void ccuStartSlices(const unsigned int slices);

// Put requested slices into idle (clock stopped, registers not cleared).
//   slices is a bit field of slices to stop (0=slice 0 .. 3=slice3).
void ccuStopSlices(const unsigned int slices);

// GCTRL suspend configuration.
// Ignore suspend requests, module never suspends.
#define GCTRL_SUSCFG_IGNORE (0x00 << 8)
// Stop all slices immediately, does not use safe stop.
#define GCTRL_SUSCFG_HALT (0x01 << 8)
// Safe stops the block immediatele and clamps outputs to passive state.
#define GCTRL_SUSCFG_PASSIVE (0x02 << 8)
// Safe stops the block after rollover and clamps outputs to passive state.
#define GCTRL_SUSCFG_ROLLOVER (0x03 << 8)

// Helpers to build ccuCOnfigureSlice event fields.
//   is is the input selector.  It is an EVIS_INy_ value.
//   em is the edge selector.  It is an EVEM___ value.
//   lm is the active level selector.  It is an EVLM___ value.
//   lpf is the low pass filter count.  It is an LPFM__ value.
unsigned int ccuEvent0(unsigned int is, unsigned int em, unsigned int lm,
                       unsigned int lpf);
unsigned int ccuEvent1(unsigned int is, unsigned int em, unsigned int lm,
                       unsigned int lpf);
unsigned int ccuEvent2(unsigned int is, unsigned int em, unsigned int lm,
                       unsigned int lpf);

// Configure a CCU slice
//  events configures input events.  ccuEvent[0:2]() can help build it.
//  connections configures the connection matrix. Bitwise or of
//    STRTS | ENDS | CAP0S | CAP1S | CAP2S | GATES | UDS | LDS | CNTS | OFS |
//    TS | MOS | TCE
//  timer_control configures timer behaviour. See 'CCU4yTC timer control'
//    in ccu.h (there are lots of flags here).
//  prescaler: count frequency is Fccu/(2^PSC). PSC_FCCU values enumerate this.
//  period, compare: 16 bit values for timer period and compare.
//  interrupt_enable is an or of INTE_ values (eg. INTE_E0AE_ENABLE)
//  interrupt_route is an or of SRS_ values (eg. INTE_E0AE_ENABLE)
void ccuConfigureSlice(const unsigned int slice,
                       const unsigned int events,
                       const unsigned int connections,
                       const unsigned int timer_control,
                       const unsigned int prescaler,
                       const unsigned int period,
                       const unsigned int compare,
                       const unsigned int interrupt_enable,
                       const unsigned int interrupt_route,
                       const unsigned int passive_level);

void ccuSetPeriodCompare(const unsigned int slice,
                         const unsigned int period,
                         const unsigned int compare);

// TODO: A lot of the stuff below should be structs and enums.

// Event configuration.  ccuEvent0() - ccuEvent2() can help construct these.
// CCU4xINS event (0-2) input.
#define EV0IS_SHIFT 0
#define EV1IS_SHIFT 4
#define EV2IS_SHIFT 8
#define EVIS_INyA 0x0000
#define EVIS_INyB 0x0001
#define EVIS_INyC 0x0002
#define EVIS_INyD 0x0003
#define EVIS_INyE 0x0004
#define EVIS_INyF 0x0005
#define EVIS_INyG 0x0006
#define EVIS_INyH 0x0007
#define EVIS_INyI 0x0008
#define EVIS_INyJ 0x0009
#define EVIS_INyK 0x000a
#define EVIS_INyL 0x000b
#define EVIS_INyM 0x000c
#define EVIS_INyN 0x000d
#define EVIS_INyO 0x000e
#define EVIS_INyP 0x000f
// CCU4xINS event (0-2) edge.
#define EV0EM_SHIFT 16
#define EV1EM_SHIFT 18
#define EV2EM_SHIFT 20
#define EVEM_NONE 0x00
#define EVEM_RISING 0x01
#define EVEM_FALLING 0x02
#define EVEM_BOTH 0x03
// CCU4xINS event (0-2) active level.
#define EV0LM_SHIFT 22
#define EV1LM_SHIFT 23
#define EV2LM_SHIFT 24
#define EVLM_HIGH 0x00
#define EVLM_LOW 0x01
// CCU4xINS event (0-2) low pass filter.
#define EV0LPF_SHIFT 25
#define EV1LPF_SHIFT 27
#define EV2LPF_SHIFT 29
#define EVLPFM_0 (0x00)
#define EVLPFM_3 (0x01)
#define EVLPFM_5 (0x02)
#define EVLPFM_7 (0x03)

// CCY4yCMC connection matrix control.
// CCU4yCMC start event.
#define STRTS_EV0 (0x01 << 0)
#define STRTS_EV1 (0x02 << 0)
#define STRTS_EV2 (0x03 << 0)
// CCU4yCMC stop event.
#define ENDS_EV0 (0x01 << 2)
#define ENDS_EV1 (0x02 << 2)
#define ENDS_EV2 (0x03 << 2)
// CCU4yCMC capture event 0.
#define CAP0S_EV0 (0x01 << 4)
#define CAP0S_EV1 (0x02 << 4)
#define CAP0S_EV2 (0x03 << 4)
// CCU4yCMC capture event 1.
#define CAP1S_EV0 (0x01 << 6)
#define CAP1S_EV1 (0x02 << 6)
#define CAP1S_EV2 (0x03 << 6)
// CCU4yCMC gate event.
#define GATES_EV0 (0x01 << 8)
#define GATES_EV1 (0x02 << 8)
#define GATES_EV2 (0x03 << 8)
// CCU4yCMC up/down functionality event.
#define UDS_EV0 (0x01 << 10)
#define UDS_EV1 (0x02 << 10)
#define UDS_EV2 (0x03 << 10)
// CCU4yCMC timer load event.
#define LDS_EV0 (0x01 << 12)
#define LDS_EV1 (0x02 << 12)
#define LDS_EV2 (0x03 << 12)
// CCU4yCMC count event.
#define CNTS_EV0 (0x01 << 14)
#define CNTS_EV1 (0x02 << 14)
#define CNTS_EV2 (0x03 << 14)
// CCU4yCMC override enable (when enabled event 1 is trigger and 2 is value).
#define OFS_ENABLE BIT16
// CCU4yCMC trap enable (when enabled event 2 is trap).
#define TS_ENABLE BIT17
// CCU4yCMC modulation event.
#define MOS_EV0 (0x01 << 18)
#define MOS_EV1 (0x02 << 18)
#define MOS_EV2 (0x03 << 18)
// CCU4yCMC timer concat enable (when enabled concat from previous slice).
#define TCE_ENABLE BIT20

// CCU4yTC timer control.
// CCU4yTCM timer counting mode
#define TCM_EDGE 0x00
#define TCM_CENTER BIT0
// CCU4yTSSM timer single shot mode
#define TSSM_ENABLE BIT1
// CCU4yCLST shadow transfer on clear
#define CLST_ENABLE BIT2
// CCU4yCMOD capture compare mode
#define CMOD_COMPARE 0x00
#define CMOD_CAPTURE (0x01 << 3)
// CCU4yECM extended capture mode
#define ECM_ENABLE BIT4
// CCU4yCAPC clear on capture
#define CAPC_CLEAR23 (0x01 << 5)
#define CAPC_CLEAR01 (0x02 << 5)
#define CAPC_CLEAR (0x03 << 5)
// CCU4yENDM extended stop function
#define ENDM_RUNBIT (0x00 << 8)
#define ENDM_TIMER (0x01 << 8)
#define ENDM_BOTH (0x02 << 8)
// CCU4ySTRM extended start function
#define STRM_RUNBIT 0x00
#define STRM_BOTH BIT10
// CCU4ySCE equal capture event enable
#define SCE_CAPT01 0x00
#define SCE_CAPT11 BIT11
// CCU4yCCS continuous capture enable
#define CCS_ENABLE BIT12
// CCU4yDITHE dither enable
#define DITHE_PERIOD (0x01 << 13)
#define DITHE_COMPARE (0x02 << 13)
#define DITHE_BOTH (0x03 << 13)
// CCU4yDIM dither input selector
#define DIM_LOCAL 0x00
#define DIM_SLICE0 BIT15
// CCU4yFPE floating prescaler enable
#define FPE_ENABLE BIT16
// CCU4yTRAPE trap enable
#define TRAPE_ENABLE BIT17
// CCU4yTRPSE trap sync enable
#define TRPSE_ENABLE BIT21
// CCU4yTRPSW trap state clear control
#define TRPSW_ENABLE BIT22
// CCU4yEMS external modulation sync
#define EMS_ENABLE BIT23
// CCU4yEMT external modulation type
#define EMT_ENABLE BIT24
// CCU4yMCME multi channel mode enable
#define MCME_ENABLE BIT25

// CCU4yPSC prescaler divisors.
#define PSC_FCCU 0x00
#define PSC_FCCU_2 0x01
#define PSC_FCCU_4 0x02
#define PSC_FCCU_8 0x03
#define PSC_FCCU_16 0x04
#define PSC_FCCU_32 0x05
#define PSC_FCCU_64 0x06
#define PSC_FCCU_128 0x07
#define PSC_FCCU_256 0x08
#define PSC_FCCU_512 0x08
#define PSC_FCCU_1024 0x0a
#define PSC_FCCU_2048 0x0b
#define PSC_FCCU_4096 0x0c
#define PSC_FCCU_8192 0x0d
#define PSC_FCCU_16384 0x0e
#define PSC_FCCU_32768 0x0f

// CCU4yINTE interrupt enable.
// PME period match while counting up generates an interrupt
#define INTE_PME_ENABLE BIT0
// OME one match while counting down generates an interrupt
#define INTE_OME_ENABLE BIT1
// CMUE compare match while counting up generates an interrupt
#define INTE_CMUE_ENABLE BIT2
// CMDE compare match while counting down generates an interrupt
#define INTE_CMDE_ENABLE BIT3
// Event 0 generates an interrupt
#define INTE_E0AE_ENABLE BIT8
#define INTE_E1AE_ENABLE BIT9
#define INTE_E2AE_ENABLE BIT10

// CCU4ySRS interrupt request selector.
// POSR period/one match service request selector
#define SRS_POSR_SR0 (0x00 << 0)
#define SRS_POSR_SR1 (0x01 << 0)
#define SRS_POSR_SR2 (0x02 << 0)
#define SRS_POSR_SR3 (0x03 << 0)
// CMSR compare match service request selector
#define SRS_CMSR_SR0 (0x00 << 2)
#define SRS_CMSR_SR1 (0x01 << 2)
#define SRS_CMSR_SR2 (0x02 << 2)
#define SRS_CMSR_SR3 (0x03 << 2)
// E0SR event 0 service request selector
#define SRS_E0SR_SR0 (0x00 << 8)
#define SRS_E0SR_SR1 (0x01 << 8)
#define SRS_E0SR_SR2 (0x02 << 8)
#define SRS_E0SR_SR3 (0x03 << 8)
#define SRS_E1SR_SR0 (0x00 << 10)
#define SRS_E1SR_SR1 (0x01 << 10)
#define SRS_E1SR_SR2 (0x02 << 10)
#define SRS_E1SR_SR3 (0x03 << 10)
#define SRS_E2SR_SR0 (0x00 << 12)
#define SRS_E2SR_SR1 (0x01 << 12)
#define SRS_E2SR_SR2 (0x02 << 12)
#define SRS_E2SR_SR3 (0x03 << 12)

// CCU40 global registers
#define CCU4_GCTRL             REGISTER_32(CCU40_BASE + 0x0000)
#define CCU4_GSTAT             REGISTER_32(CCU40_BASE + 0x0004)
#define CCU4_GIDLS             REGISTER_32(CCU40_BASE + 0x0008)
#define CCU4_GIDLC             REGISTER_32(CCU40_BASE + 0x000c)
#define CCU4_GCSS              REGISTER_32(CCU40_BASE + 0x0010)
#define CCU4_GCSC              REGISTER_32(CCU40_BASE + 0x0014)
#define CCU4_GCST              REGISTER_32(CCU40_BASE + 0x0018)
#define CCU4_MIDR              REGISTER_32(CCU40_BASE + 0x0080)

// Slice Register Offsets
#define CC40 0x100
#define CC41 0x200
#define CC42 0x300
#define CC43 0x400

// Slice Registers
#define CCU4_INS(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x00)
#define CCU4_CMC(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x04)
#define CCU4_TST(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x08)
#define CCU4_TCSET(coffset) REGISTER_32(CCU40_BASE + coffset + 0x0c)
#define CCU4_TCCLR(coffset) REGISTER_32(CCU40_BASE + coffset + 0x10)
#define CCU4_TC(coffset)    REGISTER_32(CCU40_BASE + coffset + 0x14)
#define CCU4_PSL(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x18)
#define CCU4_DIT(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x1c)
#define CCU4_DITS(coffset)  REGISTER_32(CCU40_BASE + coffset + 0x20)
#define CCU4_PSC(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x24)
#define CCU4_FPC(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x28)
#define CCU4_FPCS(coffset)  REGISTER_32(CCU40_BASE + coffset + 0x2c)
#define CCU4_PR(coffset)    REGISTER_32(CCU40_BASE + coffset + 0x30)
#define CCU4_PRS(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x34)
#define CCU4_CR(coffset)    REGISTER_32(CCU40_BASE + coffset + 0x38)
#define CCU4_CRS(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x3c)

#define CCU4_TIMER(coffset) REGISTER_32(CCU40_BASE + coffset + 0x70)
#define CCU4_C0V(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x74)
#define CCU4_C1V(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x78)
#define CCU4_C2V(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x7c)
#define CCU4_C3V(coffset)   REGISTER_32(CCU40_BASE + coffset + 0x80)

#define CCU4_INTS(coffset)  REGISTER_32(CCU40_BASE + coffset + 0xa0)
#define CCU4_INTE(coffset)  REGISTER_32(CCU40_BASE + coffset + 0xa4)
#define CCU4_SRS(coffset)   REGISTER_32(CCU40_BASE + coffset + 0xa8)
#define CCU4_SWS(coffset)   REGISTER_32(CCU40_BASE + coffset + 0xac)
#define CCU4_SWR(coffset)   REGISTER_32(CCU40_BASE + coffset + 0xb0)
#define CCU4_ECRD0(coffset) REGISTER_32(CCU40_BASE + coffset + 0xb8)
#define CCU4_ECRD1(coffset) REGISTER_32(CCU40_BASE + coffset + 0xbc)

#endif
