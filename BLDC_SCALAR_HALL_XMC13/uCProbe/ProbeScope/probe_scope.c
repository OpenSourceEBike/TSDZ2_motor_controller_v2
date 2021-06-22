/*
************************************************************************************************************************
*                                                     Oscilloscope
*
*                                    (c) Copyright 2016; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*
* File    : PROBE_SCOPE.C
* By      : JJL
* Version : V1.00.00
************************************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  "uCProbe/ProbeScope/probe_scope_cfg.h"
#include  "uCProbe/ProbeScope/probe_scope.h"

/*
*********************************************************************************************************
*                                             CONSTANTS
*********************************************************************************************************
*/


#define  PROBE_SCOPE_TRIG_NEG                  0                           // Trigger on Negative going slope
#define  PROBE_SCOPE_TRIG_POS                  1                           // Trigger on Positive going slope


#define  PROBE_SCOPE_STATE_START               0
#define  PROBE_SCOPE_STATE_SAMPLING_PRE_TRIG   1
#define  PROBE_SCOPE_STATE_SAMPLING_POST_TRIG  2
#define  PROBE_SCOPE_STATE_DATA_RDY            3


#define  PROBE_SCOPE_MODE_OFF                  0
#define  PROBE_SCOPE_MODE_SINGLE               1
#define  PROBE_SCOPE_MODE_CONTINUOUS           2
#define  PROBE_SCOPE_MODE_TRIG                 3


#define  PROBE_SCOPE_INT08U                    0                           // Supported data types
#define  PROBE_SCOPE_INT08S                    1
#define  PROBE_SCOPE_INT16U                    2
#define  PROBE_SCOPE_INT16S                    3
#define  PROBE_SCOPE_INT32U                    4
#define  PROBE_SCOPE_INT32S                    5
#define  PROBE_SCOPE_FP32                      6


#define  PROBE_SCOPE_CH1                       1
#define  PROBE_SCOPE_CH2                       2
#define  PROBE_SCOPE_CH3                       3
#define  PROBE_SCOPE_CH4                       4
#define  PROBE_SCOPE_CH5                       5
#define  PROBE_SCOPE_CH6                       6
#define  PROBE_SCOPE_CH7                       7
#define  PROBE_SCOPE_CH8                       8

/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

typedef  uint32_t                  CPU_BOOLEAN;                               //  8-bit boolean or logical 
typedef  uint8_t                   CPU_INT08U;                                //  8-bit unsigned integer   
typedef  int8_t                    CPU_INT08S;                                //  8-bit   signed integer   
typedef  uint16_t                  CPU_INT16U;                                // 16-bit unsigned integer   
typedef  int16_t                   CPU_INT16S;                                // 16-bit   signed integer   
typedef  uint32_t                  CPU_INT32U;                                // 32-bit unsigned integer   
typedef  int32_t                   CPU_INT32S;                                // 32-bit   signed integer   
typedef  uint64_t                  CPU_INT64U;                                // 64-bit unsigned integer   
typedef  int64_t                   CPU_INT64S;                                // 64-bit   signed integer   

typedef  float                     CPU_FP32;                                  // 32-bit floating point     
typedef  double                    CPU_FP64;                                  // 64-bit floating point     


typedef  struct  scope_ch          PROBE_SCOPE_CH;
typedef  union   scope_ch_sample   PROBE_SCOPE_CH_SAMPLE;


union  scope_ch_sample {                                                      // A sample can be any of these data types
    CPU_INT08U    Val08U;
    CPU_INT08S    Val08S;
#if PROBE_SCOPE_16_BIT_EN > 0                                                 // ... 16-bits only if enabled
    CPU_INT16U    Val16U;
    CPU_INT16S    Val16S;
#endif
#if PROBE_SCOPE_32_BIT_EN > 0                                                 // ... 32-bits only if enabled
    CPU_INT32U    Val32U;
    CPU_INT32S    Val32S;
    CPU_FP32      ValFP32;
#endif
};
    

struct  scope_ch {
    CPU_BOOLEAN            En;                                                // Channel enabled (1) or disabled (0)
    CPU_INT08U             DataType;                                          // Source data type: 
                                                                              //    0 = CPU_INT08U
                                                                              //    1 = CPU_INT08S
                                                                              //    2 = CPU_INT16U  (only if 'PROBE_SCOPE_16_BIT_EN' is set to 1)
                                                                              //    3 = CPU_INT16S  (only if 'PROBE_SCOPE_16_BIT_EN' is set to 1)
                                                                              //    4 = CPU_INT32U  (only if 'PROBE_SCOPE_32_BIT_EN' is set to 1)
                                                                              //    5 = CPU_INT32S  (only if 'PROBE_SCOPE_32_BIT_EN' is set to 1)
                                                                              //    6 = CPU_FP32    (only if 'PROBE_SCOPE_32_BIT_EN' is set to 1)
    CPU_BOOLEAN             BitEn;                                            // Bit mode enabled (1) or disabled (0)
    CPU_INT08U              BitSel;                                           // Selected bit in bit mode (0..63)
    CPU_INT08U             *DataAddr;                                         // Address of source data (i.e. address of symbol assigned to channel) 
    PROBE_SCOPE_CH_SAMPLE   TrigLevel;                                        // Trigger level of the channel
    PROBE_SCOPE_CH_SAMPLE   Samples[PROBE_SCOPE_MAX_SAMPLES];                 // Storage for samples
};

/*
*********************************************************************************************************
*                                             LOCAL VARIABLES
*********************************************************************************************************
*/

static    PROBE_SCOPE_CH       ProbeScope_Ch1;                                // Up to 8 scope channels (minimum 1 channel)

#if PROBE_SCOPE_MAX_CH >= 2
static    PROBE_SCOPE_CH       ProbeScope_Ch2;
#endif

#if PROBE_SCOPE_MAX_CH >= 3
static    PROBE_SCOPE_CH       ProbeScope_Ch3;
#endif

#if PROBE_SCOPE_MAX_CH >= 4
static    PROBE_SCOPE_CH       ProbeScope_Ch4;
#endif

#if PROBE_SCOPE_MAX_CH >= 5
static    PROBE_SCOPE_CH       ProbeScope_Ch5;
#endif

#if PROBE_SCOPE_MAX_CH >= 6
static    PROBE_SCOPE_CH       ProbeScope_Ch6;
#endif

#if PROBE_SCOPE_MAX_CH >= 7
static    PROBE_SCOPE_CH       ProbeScope_Ch7;
#endif

#if PROBE_SCOPE_MAX_CH >= 8
static    PROBE_SCOPE_CH       ProbeScope_Ch8;
#endif

volatile  CPU_INT32U           ProbeScope_DataRdyFlag;                        // Data is ready to be read by Probe

volatile  CPU_BOOLEAN          ProbeScope_InitFlag;                           // Flag indicating MCU has reset

static    CPU_INT08U           ProbeScope_Mode;                               // Scope Mode:
                                                                              //     0 = Stop
                                                                              //     1 = Single
                                                                              //     2 = Continuous
                                                                              //     3 = Triggered (always assumes pre-triggering)
                                                                            
static    CPU_INT08U           ProbeScope_TrigChSel;                          // Channel that will be monitored for the trigger:
                                                                              //     1 = Channel #1
                                                                              //     2 = Channel #2
                                                                              //     3 = Channel #3
                                                                              //     4 = Channel #4
                                                                              //     5 = Channel #5
                                                                              //     6 = Channel #6
                                                                              //     7 = Channel #7
                                                                              //     8 = Channel #8
                                                                            

volatile  CPU_INT32U           ProbeScope_TrigDispPos;                        // Position of the trigger on the screen (in sample number):
                                                                              //     0                           = Far left,  identical to 100% post-triggering
                                                                              //     PROBE_SCOPE_MAX_SAMPLES - 1 = Far right, identical to 100% pre-triggering
volatile  CPU_BOOLEAN          ProbeScope_TrigFlag;                           // Flag indicating that we satisfied the trigger
volatile  CPU_INT32U           ProbeScope_TrigHoldOff;                        // Determines how many samples we will hold off before retriggering
static    CPU_INT32U           ProbeScope_TrigHoldOffCtr;
volatile  CPU_INT32U           ProbeScope_TrigIx;                             // Position in the sample buffer where the trigger was found
static    CPU_BOOLEAN          ProbeScope_TrigSlope;                          // Trigger Slope
                                                                              //     0 = Low  going
                                                                              //     1 = High going

static    CPU_INT32U           ProbeScope_SampleIxPrev;
static    CPU_INT32U           ProbeScope_SampleIxCur;
static    CPU_INT32U           ProbeScope_SamplesPreTrigCtr;                  // Minimum number of samples needed before we are allowed to trigger
static    CPU_INT32U           ProbeScope_SamplesPostTrigCtr;                 // Determines how many samples will be take after a trigger has been detected:
                                                                              //     In 100% post-trigger, ProbeScope_SamplesPostTrigCtr == PROBE_SCOPE_MAX_SAMPLES
                                                                              //     In 100% pre-trigger,  ProbeScope_SamplesPostTrigCtr == 0

static    CPU_INT16U           ProbeScope_SamplingClkDiv;                     // Clk source divider (1 to 1000)
static    CPU_INT16U           ProbeScope_SamplingClkDivCtr; 
volatile  CPU_INT32U           ProbeScope_SamplingClkHz;                      // Sampling Clock Frequency in Hz

static    CPU_INT08U           ProbeScope_State;                              // Scope State

/*
*********************************************************************************************************
*                                             CONSTANTS
*********************************************************************************************************
*/

static  volatile  CPU_INT16U   ProbeScopeDbg_MaxSamples     = PROBE_SCOPE_MAX_SAMPLES;
static  volatile  CPU_INT08U   ProbeScopeDbg_MaxCh          = PROBE_SCOPE_MAX_CH;
static  volatile  CPU_BOOLEAN  ProbeScopeDbg_16BitEn        = PROBE_SCOPE_16_BIT_EN;
static  volatile  CPU_BOOLEAN  ProbeScopeDbg_32BitEn        = PROBE_SCOPE_32_BIT_EN;

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/

static  void       ProbeScope_IsTrig          (void);
        
static  void       ProbeScope_ModeOff         (void);
static  void       ProbeScope_ModeContinuous  (void);
static  void       ProbeScope_ModeTrig        (void);
        
static  void       ProbeScope_SampleChAll     (void);
static  void       ProbeScope_SampleCh        (PROBE_SCOPE_CH  *p_ch);
static  void       ProbeScope_SamplePosNext   (void);

/*
************************************************************************************************************************
*                                                    INITIALIZATION
*
* Description: This function is used to initialize the internals of the Oscilloscope module
*
* Arguments  : sampling_clk_hz    The frequency of the sampling clock (Hz)
*
* Returns    : none
************************************************************************************************************************
*/

void  ProbeScope_Init (uint32_t  sampling_clk_hz)
{
    static  CPU_INT32U  temp = 0;


    ProbeScope_Ch1.En             = 0;
#if PROBE_SCOPE_MAX_CH >= 2       
    ProbeScope_Ch2.En             = 0;
#endif                            
#if PROBE_SCOPE_MAX_CH >= 3       
    ProbeScope_Ch3.En             = 0;
#endif                            
#if PROBE_SCOPE_MAX_CH >= 4       
    ProbeScope_Ch4.En             = 0;
#endif                            
#if PROBE_SCOPE_MAX_CH >= 5       
    ProbeScope_Ch5.En             = 0;
#endif                            
#if PROBE_SCOPE_MAX_CH >= 6       
    ProbeScope_Ch6.En             = 0;
#endif                            
#if PROBE_SCOPE_MAX_CH >= 7       
    ProbeScope_Ch7.En             = 0;
#endif                            
#if PROBE_SCOPE_MAX_CH >= 8       
    ProbeScope_Ch8.En             = 0;
#endif

    ProbeScope_Mode               = PROBE_SCOPE_MODE_OFF;
    ProbeScope_State              = PROBE_SCOPE_STATE_START;
    ProbeScope_TrigChSel          = PROBE_SCOPE_CH1;                         // Default trigger channel
    ProbeScope_SampleIxPrev       = 0;
    ProbeScope_SampleIxCur        = 0;
    ProbeScope_TrigFlag           = 0;
    ProbeScope_TrigDispPos        = 0;
    ProbeScope_TrigHoldOff        = 0;
    ProbeScope_TrigHoldOffCtr     = 0;
    ProbeScope_DataRdyFlag        = 0;
    ProbeScope_SamplesPreTrigCtr  = ProbeScope_TrigDispPos;
    ProbeScope_SamplesPostTrigCtr = PROBE_SCOPE_MAX_SAMPLES;
    ProbeScope_TrigSlope          = PROBE_SCOPE_TRIG_POS;                    // We assume a positive going signal by default
    temp                          = ProbeScopeDbg_MaxSamples;
    temp                         += ProbeScopeDbg_MaxCh;
    temp                         += ProbeScopeDbg_16BitEn;
    temp                         += ProbeScopeDbg_32BitEn;
    ProbeScope_SamplingClkDiv     =    1;
    ProbeScope_SamplingClkDivCtr  =    0;
    ProbeScope_SamplingClkHz      = sampling_clk_hz;
    ProbeScope_InitFlag           =    1;
}

/*
************************************************************************************************************************
*                                                  Scope Sampling API
*
* Description: This function must be called when your code needs to take a sample of all enabled channels.
*
* Arguments  : none
* Returns    : none
************************************************************************************************************************
*/

void  ProbeScope_Sampling (void)
{
    switch (ProbeScope_Mode) {
        case PROBE_SCOPE_MODE_OFF:
             ProbeScope_ModeOff();
             break;
    
        case PROBE_SCOPE_MODE_SINGLE:
             ProbeScope_ModeTrig();
             break;
    
        case PROBE_SCOPE_MODE_CONTINUOUS:
             ProbeScope_ModeContinuous();
             break;
    
        case PROBE_SCOPE_MODE_TRIG:
             ProbeScope_ModeTrig(); 
             break;
    }
}
    

/*
************************************************************************************************************************
*                                                  OFF Sampling Mode
*
* Description: This is the state machine called when we are not reading samples
*
* Arguments  : none
* Returns    : none
************************************************************************************************************************
*/

static  void  ProbeScope_ModeOff (void)
{
    ProbeScope_State = PROBE_SCOPE_STATE_START;                                // Force Triggered mode state to START
    if (ProbeScope_SamplingClkDiv == 0) {
        ProbeScope_SamplingClkDiv =  1;
    }
}
         
/*
************************************************************************************************************************
*                                                Continuous Sampling Mode
*
* Description: This is the state machine called when continuous mode is selected
*
* Arguments  : none
* Returns    : none
************************************************************************************************************************
*/

static  void  ProbeScope_ModeContinuous (void)
{
    if (ProbeScope_DataRdyFlag == 0) {                                          // Read one buffer's worth of data
        ProbeScope_TrigFlag = 0;
        if (ProbeScope_SamplingClkDivCtr > 1) {
            ProbeScope_SamplingClkDivCtr--;
        } else {
            if (ProbeScope_SamplingClkDiv == 0) {                               // Make sure clock divider is not 0
                ProbeScope_SamplingClkDiv =  1;
            }
            ProbeScope_SamplingClkDivCtr  = ProbeScope_SamplingClkDiv;
            ProbeScope_SampleChAll();                                           // Get the first sample to create a 'previous' value for triggering
            ProbeScope_SamplePosNext();                                         // Position to next sample
            if (ProbeScope_SampleIxCur == 0) {                                  // Read one buffer's worth of data
                ProbeScope_DataRdyFlag = 1;   
                ProbeScope_TrigFlag    = 1;
            }
        }
    }
    ProbeScope_State = PROBE_SCOPE_STATE_START;                                 // Force Triggered mode state to START
}

/*
************************************************************************************************************************
*                                                 Triggered Sampling
*
* Description: This is the state machine called when triggered mode is selected
*
* Arguments  : none
* Returns    : none
************************************************************************************************************************
*/

static  void  ProbeScope_ModeTrig (void)
{
    if (ProbeScope_SamplingClkDivCtr > 1) {
        ProbeScope_SamplingClkDivCtr--;
    } else { 
        if (ProbeScope_SamplingClkDiv == 0) {                                        // Make sure clock divider is not 0
            ProbeScope_SamplingClkDiv =  1;
        }
        ProbeScope_SamplingClkDivCtr = ProbeScope_SamplingClkDiv;
        switch (ProbeScope_State) {
            case PROBE_SCOPE_STATE_START:
                 ProbeScope_DataRdyFlag        = 0;
                 ProbeScope_TrigFlag           = 0;
                 ProbeScope_SampleIxPrev       = 0;
                 ProbeScope_SampleIxCur        = 0;
                 ProbeScope_TrigHoldOffCtr     = 0;
                 ProbeScope_SamplesPostTrigCtr = 0;
                 ProbeScope_SamplesPreTrigCtr  = ProbeScope_TrigDispPos;            // Minimum number of samples pre-trigger
                 ProbeScope_SampleChAll();                                          // Get the first sample to create a 'previous' value for triggering
                 ProbeScope_SamplePosNext();
                 ProbeScope_State              = PROBE_SCOPE_STATE_SAMPLING_PRE_TRIG;
                 break;
                 
            case PROBE_SCOPE_STATE_SAMPLING_PRE_TRIG:
                 ProbeScope_SampleChAll();                                          // Get the next sample
                 if (ProbeScope_SamplesPreTrigCtr > 0) {                            // We need a minimum number of samples before the trigger
                     ProbeScope_SamplesPreTrigCtr--;                               
                 } else {
                     ProbeScope_IsTrig();                                           // See if we detected the trigger
                 }
                 ProbeScope_SamplePosNext();
                 if (ProbeScope_TrigFlag == 1) {                                    // Remaining number of samples to collect before data available
                     ProbeScope_SamplesPostTrigCtr = PROBE_SCOPE_MAX_SAMPLES - ProbeScope_TrigDispPos - 2;  
                     ProbeScope_State              = PROBE_SCOPE_STATE_SAMPLING_POST_TRIG;
                 }
                 break;
                 
            case PROBE_SCOPE_STATE_SAMPLING_POST_TRIG:
                 ProbeScope_SampleChAll();                                          // Get the next sample
                 ProbeScope_SamplePosNext();
                 if (ProbeScope_SamplesPostTrigCtr > 0) {
                     ProbeScope_SamplesPostTrigCtr--;
                 } else {
                     if (ProbeScope_Mode == PROBE_SCOPE_MODE_SINGLE) {
                         ProbeScope_Mode           = PROBE_SCOPE_MODE_OFF;
                         ProbeScope_State          = PROBE_SCOPE_STATE_START;
                     } else {
                         ProbeScope_TrigHoldOffCtr = ProbeScope_TrigHoldOff;        // Load hold-off counter
                         ProbeScope_State          = PROBE_SCOPE_STATE_DATA_RDY;    
                     }                                                              
                     ProbeScope_DataRdyFlag = 1;                                    // Trace is available in the buffer
                 }                                                                  
                 break;                                                             
                                                                                    
            case PROBE_SCOPE_STATE_DATA_RDY:                                        
                 if (ProbeScope_TrigHoldOffCtr > 0) {                               // Hold-off before beeing able to re-trigger
                     ProbeScope_TrigHoldOffCtr--;                                   
                 } else {                                                           
                     if (ProbeScope_DataRdyFlag == 0) {                             // Give Probe time to collect and display the waveform(s)
                         ProbeScope_TrigFlag          = 0;
                         ProbeScope_SamplesPreTrigCtr = ProbeScope_TrigDispPos;     // Minimum number of samples pre-trigger
                         ProbeScope_State             = PROBE_SCOPE_STATE_SAMPLING_PRE_TRIG;
                         ProbeScope_SampleChAll();                                  // Get the first sample to create a 'previous' value for triggering
                         ProbeScope_SamplePosNext();
                     }
                 }
                 break;
                 
            default:
                 ProbeScope_State = PROBE_SCOPE_STATE_START;
                 break;
        }
    }
}

/*
************************************************************************************************************************
*                                              ProbeScope_SampleChAll()
*
* Description: This function is called to get a sample from all the enabled channels
*
* Arguments  : none
* Returns    : none
************************************************************************************************************************
*/

static  void  ProbeScope_SampleChAll (void)
{
    ProbeScope_SampleCh(&ProbeScope_Ch1);

#if PROBE_SCOPE_MAX_CH >= 2
    ProbeScope_SampleCh(&ProbeScope_Ch2);
#endif

#if PROBE_SCOPE_MAX_CH >= 3                     
    ProbeScope_SampleCh(&ProbeScope_Ch3);
#endif

#if PROBE_SCOPE_MAX_CH >= 4                     
    ProbeScope_SampleCh(&ProbeScope_Ch4);
#endif                     

#if PROBE_SCOPE_MAX_CH >= 5
    ProbeScope_SampleCh(&ProbeScope_Ch5);
#endif

#if PROBE_SCOPE_MAX_CH >= 6                     
    ProbeScope_SampleCh(&ProbeScope_Ch6);
#endif

#if PROBE_SCOPE_MAX_CH >= 7                     
    ProbeScope_SampleCh(&ProbeScope_Ch7);
#endif                     

#if PROBE_SCOPE_MAX_CH >= 8                     
    ProbeScope_SampleCh(&ProbeScope_Ch8);
#endif                     
}

/*
************************************************************************************************************************
*                                                   ProbeScope_SampleCh()
*
* Description: This function is called to read a sample from the desired channel and store it in its sample buffer.
*
* Arguments  : p_ch      is a pointer to the desired channel to sample
* Returns    : none
************************************************************************************************************************
*/

static  void  ProbeScope_SampleCh (PROBE_SCOPE_CH  *p_ch)
{
    PROBE_SCOPE_CH_SAMPLE   msk;                                    // Mask used to select desired bit when in bit mode.
    PROBE_SCOPE_CH_SAMPLE  *p_sample;                               // Pointer to where the sample will be stored


    if (p_ch->En == 1) {
        p_sample = &p_ch->Samples[ProbeScope_SampleIxCur];          // Point to current position in sampling buffer
        switch (p_ch->DataType) {
            case PROBE_SCOPE_INT08U:
                 if (p_ch->BitEn == 0) {
                     p_sample->Val08U     = *(CPU_INT08U *)p_ch->DataAddr;
                 } else {
                     msk.Val08U           =  (CPU_INT08U)1 << p_ch->BitSel;
                     if (*(CPU_INT08U *)p_ch->DataAddr & msk.Val08U) {
                         p_sample->Val08U = 1;
                     } else {
                         p_sample->Val08U = 0;
                     }
                 }
                 break;
                                  
            case PROBE_SCOPE_INT08S:
                 if (p_ch->BitEn == 0) {
                     p_sample->Val08S     = *(CPU_INT08S *)p_ch->DataAddr;
                 } else {
                     msk.Val08S           =  (CPU_INT08S)1 << p_ch->BitSel;
                     if (*(CPU_INT08S *)p_ch->DataAddr & msk.Val08S) {
                         p_sample->Val08S = 1;
                     } else {
                         p_sample->Val08S = 0;
                     }
                 }
                 break;
                                  
#if PROBE_SCOPE_16_BIT_EN > 0                                   
            case PROBE_SCOPE_INT16U:
                 if (p_ch->BitEn == 0) {
                     p_sample->Val16U     = *(CPU_INT16U *)p_ch->DataAddr;
                 } else {
                     msk.Val16U           =  (CPU_INT16U)1 << p_ch->BitSel;
                     if (*(CPU_INT16U *)p_ch->DataAddr & msk.Val16U) {
                         p_sample->Val16U = 1;
                     } else {
                         p_sample->Val16U = 0;
                     }
                 }
                 break;
                                  
            case PROBE_SCOPE_INT16S:
                 if (p_ch->BitEn == 0) {
                     p_sample->Val16S     = *(CPU_INT16S *)p_ch->DataAddr;
                 } else {
                     msk.Val16S           =  (CPU_INT16S)1 << p_ch->BitSel;
                     if (*(CPU_INT16S *)p_ch->DataAddr & msk.Val16S) {
                         p_sample->Val16S = 1;
                     } else {
                         p_sample->Val16S = 0;
                     }
                 }
                 break;
#endif

#if PROBE_SCOPE_32_BIT_EN > 0                                   
            case PROBE_SCOPE_INT32U:
                 if (p_ch->BitEn == 0) {
                     p_sample->Val32U     = *(CPU_INT32U *)p_ch->DataAddr;
                 } else {
                     msk.Val32U           =  (CPU_INT32U)1 << p_ch->BitSel;
                     if (*(CPU_INT32U *)p_ch->DataAddr & msk.Val32U) {
                         p_sample->Val32U = 1;
                     } else {
                         p_sample->Val32U = 0;
                     }
                 }
                 break;
                                  
            case PROBE_SCOPE_INT32S:
                 if (p_ch->BitEn == 0) {
                     p_sample->Val32S     = *(CPU_INT32S *)p_ch->DataAddr;
                 } else {
                     msk.Val32S           =  (CPU_INT32S)1 << p_ch->BitSel;
                     if (*(CPU_INT32S *)p_ch->DataAddr & msk.Val32S) {
                         p_sample->Val32S = 1;
                     } else {
                         p_sample->Val32S = 0;
                     }
                 }
                 break;
                                  
            case PROBE_SCOPE_FP32:
                 p_sample->ValFP32  = *(CPU_FP32   *)p_ch->DataAddr;
                 break;
#endif
        }                          
    }
}


/*
************************************************************************************************************************
*                                         Position Sample Index for next sample
*
* Description: 
*
* Arguments  : none
* Returns    : none
************************************************************************************************************************
*/

static  void  ProbeScope_SamplePosNext (void)
{
    ProbeScope_SampleIxPrev = ProbeScope_SampleIxCur;              // Update the position of the previous sample
    ProbeScope_SampleIxCur++;                                      // Position to where next sample will be placed
    if (ProbeScope_SampleIxCur >= PROBE_SCOPE_MAX_SAMPLES) {       // See if we need to wrap around
        ProbeScope_SampleIxCur = 0;                                // yes
    }
}

/*
************************************************************************************************************************
*                                                    ProbeScope_IsTrig()
*
* Description: This function is called to detect whether the trigger channel sees the trigger conditions.
*              The channel needs to be enabled as well.
*              To trigger the sampling, we must see the proper slope and the trigger level must be reached.
*
* Arguments  : ch      is the channel number that will be used as the trigger channel.
* Returns    : Sets ProbeScope_TrigFlag to 1 when a  trigger is detected
*              Sets ProbeScope_TrigFlag to 0 when no trigger is detected
************************************************************************************************************************
*/

static  void  ProbeScope_IsTrig (void)
{
    PROBE_SCOPE_CH          *p_ch;
    PROBE_SCOPE_CH_SAMPLE   *p_sample_prev;
    PROBE_SCOPE_CH_SAMPLE   *p_sample_cur;
    

    switch (ProbeScope_TrigChSel) {
        case PROBE_SCOPE_CH1:
             p_ch = &ProbeScope_Ch1;
             break;
             
#if PROBE_SCOPE_MAX_CH >= 2
        case PROBE_SCOPE_CH2:
             p_ch = &ProbeScope_Ch2;
             break;
#endif
             
#if PROBE_SCOPE_MAX_CH >= 3
        case PROBE_SCOPE_CH3:
             p_ch = &ProbeScope_Ch3;
             break;
#endif             
             
#if PROBE_SCOPE_MAX_CH >= 4
        case PROBE_SCOPE_CH4:
             p_ch = &ProbeScope_Ch4;
             break;
#endif
             
#if PROBE_SCOPE_MAX_CH >= 5
        case PROBE_SCOPE_CH5:
             p_ch = &ProbeScope_Ch5;
             break;
#endif
             
#if PROBE_SCOPE_MAX_CH >= 6
        case PROBE_SCOPE_CH6:
             p_ch = &ProbeScope_Ch6;
             break;
#endif             
             
#if PROBE_SCOPE_MAX_CH >= 7
        case PROBE_SCOPE_CH7:
             p_ch = &ProbeScope_Ch7;
             break;
#endif
             
#if PROBE_SCOPE_MAX_CH >= 8
        case PROBE_SCOPE_CH8:
             p_ch = &ProbeScope_Ch8;
             break;
#endif
             
        default:
             p_ch                 = &ProbeScope_Ch1;
             ProbeScope_TrigChSel = PROBE_SCOPE_CH1;
             break;
    }         
    ProbeScope_TrigFlag = 0;
    if (p_ch->En == 1) {
        p_sample_prev = &p_ch->Samples[ProbeScope_SampleIxPrev];          // Point to previous position in sampling buffer
        p_sample_cur  = &p_ch->Samples[ProbeScope_SampleIxCur];           // Point to current  position in sampling buffer
        if (ProbeScope_TrigSlope == PROBE_SCOPE_TRIG_POS) {
            switch (p_ch->DataType) {
                case PROBE_SCOPE_INT08U:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val08U < p_sample_cur->Val08U) {
                             if (p_sample_prev->Val08U <= p_ch->TrigLevel.Val08U) {
                                 if (p_sample_cur->Val08U >= p_ch->TrigLevel.Val08U) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val08U == 0) {
                             if (p_sample_cur->Val08U != 0) { 
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                     
                case PROBE_SCOPE_INT08S:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val08S < p_sample_cur->Val08S) {
                             if (p_sample_prev->Val08S <= p_ch->TrigLevel.Val08S) {
                                 if (p_sample_cur->Val08S >= p_ch->TrigLevel.Val08S) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val08S == 0) {
                             if (p_sample_cur->Val08S != 0) { 
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;

#if PROBE_SCOPE_16_BIT_EN > 0                                    
                case PROBE_SCOPE_INT16U:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val16U < p_sample_cur->Val16U) {
                             if (p_sample_prev->Val16U <= p_ch->TrigLevel.Val16U) {
                                 if (p_sample_cur->Val16U >= p_ch->TrigLevel.Val16U) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val16U == 0) {
                             if (p_sample_cur->Val16U != 0) { 
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                     
                case PROBE_SCOPE_INT16S:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val16S < p_sample_cur->Val16S) {
                             if (p_sample_prev->Val16S <= p_ch->TrigLevel.Val16S) {
                                 if (p_sample_cur->Val16S >= p_ch->TrigLevel.Val16S) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val16S == 0) {
                             if (p_sample_cur->Val16S != 0) { 
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
#endif

#if PROBE_SCOPE_32_BIT_EN > 0                                   
                case PROBE_SCOPE_INT32U:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val32U < p_sample_cur->Val32U) {
                             if (p_sample_prev->Val32U <= p_ch->TrigLevel.Val32U) {
                                 if (p_sample_cur->Val32U >= p_ch->TrigLevel.Val32U) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val32U == 0) {
                             if (p_sample_cur->Val32U != 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                     
                case PROBE_SCOPE_INT32S:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val32S < p_sample_cur->Val32S) {
                             if (p_sample_prev->Val32S <= p_ch->TrigLevel.Val32S) {
                                 if (p_sample_cur->Val32S >= p_ch->TrigLevel.Val32S) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val32S == 0) {
                             if (p_sample_cur->Val32S != 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                                    
                case PROBE_SCOPE_FP32:
                     if (p_sample_prev->ValFP32 < p_sample_cur->ValFP32) {
                         if (p_sample_prev->ValFP32 <= p_ch->TrigLevel.ValFP32) {
                             if (p_sample_cur->ValFP32 >= p_ch->TrigLevel.ValFP32) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
#endif
            }
        } else {
            switch (p_ch->DataType) {
                case PROBE_SCOPE_INT08U:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val08U > p_sample_cur->Val08U) {
                             if (p_sample_prev->Val08U >= p_ch->TrigLevel.Val08U) {
                                 if (p_sample_cur->Val08U <= p_ch->TrigLevel.Val08U) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val08U != 0) {
                             if (p_sample_cur->Val08U == 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                     
                case PROBE_SCOPE_INT08S:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val08S > p_sample_cur->Val08S) {
                             if (p_sample_prev->Val08S >= p_ch->TrigLevel.Val08S) {
                                 if (p_sample_cur->Val08S <= p_ch->TrigLevel.Val08S) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val08S != 0) {
                             if (p_sample_cur->Val08S == 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                                    
#if PROBE_SCOPE_16_BIT_EN > 0                                   
                case PROBE_SCOPE_INT16U:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val16U > p_sample_cur->Val16U) {
                             if (p_sample_prev->Val16U >= p_ch->TrigLevel.Val16U) {
                                 if (p_sample_cur->Val16U <= p_ch->TrigLevel.Val16U) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val16U != 0) {
                             if (p_sample_cur->Val16U == 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                     
                case PROBE_SCOPE_INT16S:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val16S > p_sample_cur->Val16S) {
                             if (p_sample_prev->Val16S >= p_ch->TrigLevel.Val16S) {
                                 if (p_sample_cur->Val16S <= p_ch->TrigLevel.Val16S) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val16S != 0) {
                             if (p_sample_cur->Val16S == 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
#endif

#if PROBE_SCOPE_32_BIT_EN > 0                                                                     
                case PROBE_SCOPE_INT32U:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val32U > p_sample_cur->Val32U) {                  
                             if (p_sample_prev->Val32U >= p_ch->TrigLevel.Val32U) {
                                 if (p_sample_cur->Val32U <= p_ch->TrigLevel.Val32U) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val32U != 0) {
                             if (p_sample_cur->Val32U == 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                     
                case PROBE_SCOPE_INT32S:
                     if (p_ch->BitEn == 0) {
                         if (p_sample_prev->Val32S > p_sample_cur->Val32S) {
                             if (p_sample_prev->Val32S >= p_ch->TrigLevel.Val32S) {
                                 if (p_sample_cur->Val32S <= p_ch->TrigLevel.Val32S) {
                                     ProbeScope_TrigFlag = 1;
                                     ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                                 }
                             }
                         }
                     } else {
                         if (p_sample_prev->Val32S != 0) {
                             if (p_sample_cur->Val32S == 0) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
                                    
                case PROBE_SCOPE_FP32:
                     if (p_sample_prev->ValFP32 > p_sample_cur->ValFP32) {
                         if (p_sample_prev->ValFP32 >= p_ch->TrigLevel.ValFP32) {
                             if (p_sample_cur->ValFP32 <= p_ch->TrigLevel.ValFP32) {
                                 ProbeScope_TrigFlag = 1;
                                 ProbeScope_TrigIx   = ProbeScope_SampleIxCur; 
                             }
                         }
                     }
                     break;
#endif                     
            }                          
        }
    }
}
             
