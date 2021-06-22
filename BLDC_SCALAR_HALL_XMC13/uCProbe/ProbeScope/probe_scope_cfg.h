/*
************************************************************************************************************************
*                                                     Oscilloscope
*
*                                    (c) Copyright 2015; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*
* File    : PROBE_SCOPE_CFG.H
* By      : JJL
* Version : V1.00.00
************************************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              CONFIGURATION
*********************************************************************************************************
*/

#define  PROBE_SCOPE_MAX_CH                     4   /* The maximum number of channels: [1,4].             */
#define  PROBE_SCOPE_MAX_SAMPLES              500   /* The maximum number of samples per channel.         */
#define  PROBE_SCOPE_16_BIT_EN                  1   /* The maximum size of each sample is 16-bits: [0,1]. */
#define  PROBE_SCOPE_32_BIT_EN                  1   /* The maximum size of each sample is 32-bits: [0,1]. */
