/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2021.
 *
 * Released under the GPL License, Version 3
 */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>

uint32_t adc_throttle = 0;

/*********************************************************************************************************************
 * DEFINE
 *********************************************************************************************************************/
#define VADC0_G1_0_IRQn_10					10			//VADC_G0_Result_ISR
#define VADC0_G1_1_IRQn_11					11

#define VADC_G1_Result_ISR  				VADC0_G1_0_IRQHandler		//	VADC0_G1_0_IRQn     =  19

#define VADC_HARDWARE_TRIGGER		0		// 0 = Software trigger, 1 = Hardware trigger

#define VADC_CH_MAX					(8)
#define VADC_RES_MAX				(VADC_CH_MAX)
#define VADC_QUEUE_MAX				(VADC_CH_MAX)

#define ENABLE_SOURCE_EVENT			0
#define ENABLE_CHANNEL_EVENT  	0
#define ENABLE_RESULT_EVENT 		1

XMC_VADC_RESULT_SIZE_t VADC0_G1_result[VADC_RES_MAX];

/*********************************************************************************************************************
 * GLOBAL configuration
 *********************************************************************************************************************/
/* Initialization data of VADC Global resources */
const XMC_VADC_GLOBAL_CONFIG_t g_global_handle =
{
  .disable_sleep_mode_control = false,

  .clock_config = {
    .analog_clock_divider= 3,
    .msb_conversion_clock= 0,
    .arbiter_clock_divider= 1
  },

  .class0 = {
    .conversion_mode_standard= XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv    = 3U,
    .conversion_mode_emux= XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel  = 3U
  },

  .class1 = {
    .conversion_mode_standard= XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv= 3U,
    .conversion_mode_emux= XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel= 3U
  },

  .data_reduction_control = 0,
  .wait_for_read_mode     = true,
  .event_gen_enable       = false,
  .boundary0              = 0,
  .boundary1              = 0
};


/*********************************************************************************************************************
 * VADC Group configuration
 *********************************************************************************************************************/

const XMC_VADC_GROUP_CONFIG_t g_group_handle =
{
  .class0 = {
    .conversion_mode_standard= XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv= 3U,
    .conversion_mode_emux= XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel= 3U
  },

  .class1 = {
    .conversion_mode_standard = XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv = 3U,
    .conversion_mode_emux= XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel= 3U
  },

  .arbitration_round_length = 0x0U,
  .arbiter_mode = XMC_VADC_GROUP_ARBMODE_ALWAYS,
  .boundary0 = 0, /* Boundary-0 */
  .boundary1 = 0, /* Boundary-1 */

  .emux_config = {
    .emux_mode = XMC_VADC_GROUP_EMUXMODE_SWCTRL,
    .stce_usage = 0,
    .emux_coding = XMC_VADC_GROUP_EMUXCODE_BINARY,
    .starting_external_channel = 0,
    .connected_channel = 0
  }
};

/*********************************************************************************************************************
 * Queue source configuration
 *********************************************************************************************************************/
const XMC_VADC_QUEUE_CONFIG_t g_queue_handle =
{
  .req_src_priority = (uint8_t)3, /* Highest Priority = 3, Lowest = 0 */
  .conv_start_mode= XMC_VADC_STARTMODE_WFS,
#if VADC_HARDWARE_TRIGGER
  .external_trigger = (bool) true, /* External Hardware trigger enabled*/
  .trigger_signal = XMC_CCU_40_SR2,
  .trigger_edge = XMC_VADC_TRIGGER_EDGE_RISING,
#else
  .external_trigger = (bool) false, /* software trigger enabled*/
  .trigger_signal   = 0,
  .trigger_edge     = XMC_VADC_TRIGGER_EDGE_NONE,
#endif
  .gate_signal= XMC_VADC_REQ_GT_A,
  .timer_mode = (bool) false, /* No timer mode */
};


const XMC_VADC_QUEUE_ENTRY_t g_queue_entry[VADC_QUEUE_MAX] =
{
  //Queue 0
  {
    .channel_num		 = 0,	 /* Set Channel 0 */
    .refill_needed 	 = true, /* Refill is needed */
    .generate_interrupt = false, /* Interrupt generation is needed */
#if VADC_HARDWARE_TRIGGER
    .external_trigger 	 = true  /* External trigger is required */
#else
    .external_trigger 	 = true  /* External trigger is required */
    /*
      *  even when the trigger is not needed we need to mention it as true so that we will be able to control the execution
      *  of the queue. if WFR mode is enabled then the next conversion of the same queue entry will stall the entire
      *  execution.
      *  Since there is a small delay for inserting the entry-1, entry-0 will go for conversion again this has
      *  wait for read mode enabled in the ISR thus it will stall the ADC completely
      */
#endif
  },

  //Queue 1
  {
    .channel_num		 = 1,	 /* Set Channel 1 */
    .refill_needed 	 = true, /* Refill is needed */
    .generate_interrupt = false, /* Interrupt generation is needed */
    .external_trigger 	 = false  /* External trigger is required */
  },
  //Queue 2
  {
    .channel_num		 = 2,	 /* Set Channel 2 */
    .refill_needed 	 = true, /* Refill is needed */
    .generate_interrupt = false, /* Interrupt generation is needed */
    .external_trigger 	 = false  /* External trigger is required */
  },
  //Queue 3
  {
    .channel_num		 = 3,	 /* Set Channel 3 */
    .refill_needed 	 = true, /* Refill is needed */
    .generate_interrupt = false, /* Interrupt generation is needed */
    .external_trigger 	 = false  /* External trigger is required */
  },
  //Queue 4
  {
    .channel_num		 = 4,	 /* Set Channel 4 */
    .refill_needed 	 = true, /* Refill is needed */
    .generate_interrupt = false, /* Interrupt generation is needed */
    .external_trigger 	 = false  /* External trigger is required */
  },
  //Queue 5
  {
    .channel_num		 = 5,	 /* Set Channel 5 */
    .refill_needed 	 = true, /* Refill is needed */
    .generate_interrupt = false, /* Interrupt generation is needed */
  // .external_trigger 	 = false  /* External trigger is required */
    .external_trigger 	 = true  /* External trigger is required */				// External trigger has to be set true even for software trigger
  },
  //Queue 6
  {
    .channel_num		 = 6,	 /* Set Channel 6 */
    .refill_needed 	 = true, /* Refill is needed */
    .generate_interrupt = false, /* Interrupt generation is needed */
    .external_trigger 	 = false  /* External trigger is required */
  },
  //Queue 7
  {
    .channel_num		 = 7,	 /* Set Channel 7 */
    .refill_needed 	 = true, /* Refill is needed */
#if ENABLE_SOURCE_EVENT
    .generate_interrupt = true, /* Interrupt generation is needed */
#else
    .generate_interrupt = false, /* Interrupt generation is needed */
#endif
    .external_trigger 	 = false  /* External trigger is required */
  }
};

/*********************************************************************************************************************
 * Channel configuration
 *********************************************************************************************************************/
const XMC_VADC_CHANNEL_CONFIG_t g_channel_handle [VADC_CH_MAX] =
{
  // Channel 0
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 0,						// Store in Result register 0
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  },
  // Channel 1
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 1,								// Store in Result register 1
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  },
  // Channel 2
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 2,								// Store in Result register 2
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  },
  // Channel 3
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 3,								// Store in Result register 3
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  },
  // Channel 4
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 4,								// Store in Result register 4
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  },
  // Channel 5
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 5,								// Store in Result register 5
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  },
  // Channel 6
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 6,								// Store in Result register 6
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  },
  // Channel 7
  {
    .channel_priority              = 1U,
    .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
    .alias_channel                 = (uint8_t)-1,
    .bfl                           = 0,
    #if ENABLE_CHANNEL_EVENT
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_ALWAYS,
    #else
    .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_NEVER,
    #endif
    .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
    .result_reg_number             = (uint8_t) 7,								// Store in Result register 7
    .sync_conversion  			 = false,                          /* Sync Feature disabled*/
    .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
    .use_global_result             = false,
    .broken_wire_detect_channel    = false,
    .broken_wire_detect            = false
  }
};


/*********************************************************************************************************************
 * Result configuration
 *********************************************************************************************************************/
const XMC_VADC_RESULT_CONFIG_t g_result_handle [VADC_RES_MAX] = 
{
  // Result register 0
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
    .event_gen_enable       = false  /* No result event */
  },
  // Result register 1
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
    .event_gen_enable       = false  /* No result event */
  },
  // Result register 2
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
    .event_gen_enable       = false  /* No result event */
  },
  // Result register 3
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
    .event_gen_enable       = false  /* No result event */
  },
  // Result register 4
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
    .event_gen_enable       = false  /* No result event */
  },
  // Result register 5
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
    .event_gen_enable       = false  /* No result event */
  },
  // Result register 6
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
    .event_gen_enable       = false  /* No result event */
  },
  // Result register 7
  {
    .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
    .data_reduction_control = 0,
    .part_of_fifo           = false, /* No FIFO */
    .wait_for_read_mode     = true, /* WFS */
#if ENABLE_RESULT_EVENT
    .event_gen_enable       = true  /* No result event */
#else
    .event_gen_enable       = false  /* No result event */
#endif
  }
};

void VADC_Init(void)
{
	uint32_t i;

	/**********************************************************************
	 * Step 1: Global Initialization
	 ***********************************************************************/

	 /* Initialize the VADC global registers */
	XMC_VADC_GLOBAL_Init(VADC, &g_global_handle);

	/**********************************************************************
	 * Step 2: VADC Group Initialization
	 ***********************************************************************/

	/* Configure a conversion kernel */
	XMC_VADC_GROUP_Init(VADC_G1, &g_group_handle);

	/* Enable the analog converters */
	XMC_VADC_GROUP_SetPowerMode(VADC_G1, XMC_VADC_GROUP_POWERMODE_NORMAL);

	/**********************************************************************
	* Step 3: Source Initialization
	***********************************************************************/

	/* Configure the queue request source of the aforesaid conversion kernel */
	XMC_VADC_GROUP_QueueInit(VADC_G1, &g_queue_handle);

#if ENABLE_SOURCE_EVENT
		/* Enable event at g_queue_entry[i].generate_interrupt */
		XMC_VADC_GROUP_QueueSetReqSrcEventInterruptNode(VADC_G1, XMC_VADC_SR_GROUP_SR1);
		NVIC_SetPriority(VADC0_G1_1_IRQn, VADC0_G1_1_IRQn_11);			// Table 4-3 Interrupt Node assignment
		NVIC_EnableIRQ(VADC0_G1_1_IRQn);
#endif

	/**********************************************************************
	 * Step 4: Channel Initialization
	 ***********************************************************************/

	/* Configure a channel belonging to the aforesaid conversion kernel */
	XMC_VADC_GROUP_ChannelInit(VADC_G1,7, &g_channel_handle[7]);

#if ENABLE_CHANNEL_EVENT
		/* Enable event at g_channel_handle[i].event_gen_criteria */
		XMC_VADC_GROUP_ChannelSetEventInterruptNode(VADC_G1, 7, XMC_VADC_SR_GROUP_SR1); // For Channel 7
		NVIC_SetPriority(VADC0_G1_1_IRQn, VADC0_G1_1_IRQn_11);			// Table 4-3 Interrupt Node assignment
		NVIC_EnableIRQ(VADC0_G1_1_IRQn);
#endif
	/**********************************************************************
	 * Step 5: Result register Initialization
	 ***********************************************************************/

	/* Configure a result resource belonging to the aforesaid conversion kernel */
	XMC_VADC_GROUP_ResultInit(VADC_G1, 7, &g_result_handle[7]);
#if ENABLE_RESULT_EVENT
	/* Enable event at check g_result_handle[i].event_gen_enable */
	XMC_VADC_GROUP_SetResultInterruptNode(VADC_G1, 7, XMC_VADC_SR_GROUP_SR0);
	NVIC_SetPriority(VADC0_G1_0_IRQn, VADC0_G1_0_IRQn_10);
	NVIC_EnableIRQ(VADC0_G1_0_IRQn);
#endif

	/**********************************************************************
	 * Step 6: Calibration
	 ***********************************************************************/
	XMC_VADC_GLOBAL_StartupCalibration(VADC);

	/**********************************************************************
	 * Step 7: Adding channels to source
	 ***********************************************************************/
	XMC_VADC_GROUP_QueueInsertChannel(VADC_G1, g_queue_entry[7]);	// Queue no.7

	//Software trigger	
	XMC_VADC_GROUP_QueueTriggerConversion(VADC_G1);
}


#if ENABLE_SOURCE_EVENT || ENABLE_CHANNEL_EVENT
void VADC_G1_Source_Channel_ISR(void)
{
	uint32_t i;

	for (i=0; i<VADC_RES_MAX; i++)
	{
		// If "wait for read mode" is enabled, do a read of result register is necessary for every interrupt occurrence.
		// Otherwise interrupt will happened only once, alternatively you can disable the wait for read mode.
		VADC0_G1_result[i] = XMC_VADC_GROUP_GetResult(VADC_G1,i);
	}

#if ENABLE_SOURCE_EVENT
	XMC_VADC_GROUP_QueueClearReqSrcEvent(VADC_G1);	// Clear Source event flag
#endif

#if ENABLE_CHANNEL_EVENT
	XMC_VADC_GROUP_ChannelClearEvent(VADC_G1,7); // Clear Ch7 event flag
#endif


#if VADC_HARDWARE_TRIGGER

#else
	//Software trigger
	XMC_VADC_GROUP_QueueTriggerConversion(VADC_G1);
#endif
}
#endif

void VADC_G1_Result_ISR(void)
{
	/* Read the result register */
	VADC0_G1_result[7] = XMC_VADC_GROUP_GetResult(VADC_G1,7);
  adc_throttle = (uint32_t) VADC0_G1_result[7];

	/* Clear result event */
	XMC_VADC_GROUP_ClearResultEvent(VADC_G1, 7); // Clear Result 7 event flag

	//Software trigger	
	XMC_VADC_GROUP_QueueTriggerConversion(VADC_G1);
}