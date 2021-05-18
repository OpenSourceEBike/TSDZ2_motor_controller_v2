// /*
//  * main.c
//  *
//  *  Created on: 2021 Apr 29 09:15:29
//  *  Author: gaswerke
//  */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>

#include "adc.h"

#define PWM_SLICE_USED_CCU8  1

// /**

//  * @brief main() - Application entry point
//  *
//  * <b>Details of function</b><br>
//  * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
//  * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
//  * code.
//  */

// #define LED P0_7
#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 100
// uint8_t message[] = "Hello world!!\n\r";


// const XMC_VADC_GLOBAL_CONFIG_t g_global_handle = { };
// const XMC_VADC_GROUP_CONFIG_t g_group_handle = { };
// const XMC_VADC_BACKGROUND_CONFIG_t g_bgn_handle = { };
// const XMC_VADC_CHANNEL_CONFIG_t g_g0_ch7_handle = {
// 	.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED,
// 	.result_reg_number = 7 };


// //const XMC_VADC_GROUP_CONFIG_t g_group_handle_0 = { };

// //const XMC_VADC_SCAN_CONFIG_t g_scan_handle = {
// // .trigger_signal = XMC_VADC_REQ_TR_A,
// // .trigger_edge = XMC_VADC_TRIGGER_EDGE_ANY,
// // .external_trigger = 1,
// // .req_src_interrupt = 1 };

// //const XMC_VADC_SCAN_CONFIG_t g_scan_handle_0 = {
// // .trigger_signal = XMC_VADC_REQ_TR_A,
// // .trigger_edge = XMC_VADC_TRIGGER_EDGE_ANY,
// // .external_trigger = 1,
// // .req_src_interrupt = 1 };
// //

// //// P2.3,G1CH5
// //const XMC_VADC_CHANNEL_CONFIG_t g_g1_ch5_handle = {
// // .alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED,
// // .result_reg_number = 7 };
// //
// //// P2.4, G1CH6
// //const XMC_VADC_CHANNEL_CONFIG_t g_g1_ch6_handle = {
// // .alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED,
// // .result_reg_number = 6 };
// //
// //// P2.5, G1CH7
// //const XMC_VADC_CHANNEL_CONFIG_t g_g1_ch7_handle = {
// // .alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED,
// // .result_reg_number = 7 };





// void SysTick_Handler(void)
// {
//   static uint32_t ticks = 0;
//   static int32_t TorqueOffset = 0;
//   static int32_t Torque;
//   static uint8_t buffer[100];
//   static uint8_t TorqueSensorCalibrated=0;
//   static uint8_t TorqueSensorIndex=0;
//   static uint8_t MotorDelay=0;
//   static uint32_t TorqueIndex=0;
//   static uint32_t TorqueBuffer[5];
//   static uint8_t MotorStarted=0;
//   DAVE_STATUS_t init_status;
//   static uint8_t test;

//   if (++ticks == TICKS_WAIT)
//   {
	  // if(!TorqueSensorCalibrated )
	  // {
		//   TorqueOffset += XMC_VADC_GROUP_GetResult(VADC_G0, 7);
		//   if( ++TorqueSensorIndex == 50 )
		//   {
		// 	  TorqueSensorCalibrated = 1;
		// 	  TorqueOffset /= 50;
		//   }
	  // }
// 	  else
// 	  {
// 		  TorqueBuffer[TorqueIndex] = XMC_VADC_GROUP_GetResult(VADC_G0, 7);
// 		  if( ++TorqueIndex >= 4 )
// 			  TorqueIndex = 0;
// 		  Torque = 0;
// 		  for( TorqueSensorIndex=0; TorqueSensorIndex<4; TorqueSensorIndex++ )
// 		  {
// 			  Torque += TorqueBuffer[TorqueSensorIndex];
// 		  }
// 		  Torque = Torque/4-TorqueOffset;
// 		  sprintf((char*)buffer,"Torque <%ld>\n\r",Torque);
// 		  UART_Transmit(&UART_0, buffer, strlen(buffer));

// 		  if( Torque > 20 )
// 		  {
// 			  if( !MotorStarted )
// 			  {
// 				  init_status = (DAVE_STATUS_t)PMSM_FOC_Init(&PMSM_FOC_0);
// 				  if (init_status == DAVE_STATUS_SUCCESS)
// 				  {
// 					  PMSM_FOC_MotorStart(&PMSM_FOC_0);
// 					  MotorStarted=1;
// 				  }
// 				  else
// 				  {
// 					  sprintf((char*)buffer,"PMSM_FOC_Init failed\n\r");
// 					  UART_Transmit(&UART_0, buffer, strlen(buffer));
// 				  }
// 			  }
// 			  else
// 			  {
// 				  Torque = Torque*20;
// 				  if( Torque > 10000 )
// 					  Torque = 10000;
// 				  else if( Torque < 0 )
// 					  Torque = 0;

// 				  PMSM_FOC_SetIqRef( &PMSM_FOC_0, Torque );
// 			  }
// 		  }
// 		  else
// 		  {
// 			  PMSM_FOC_SetIqRef( &PMSM_FOC_0, 0 );
// 			  if(0)//1)//--MotorDelay == 0)
// 			  {
// 				  //PWM_SVM_Stop( &PWM_SVM_0 );
// 				  PMSM_FOC_MotorStop(&PMSM_FOC_0);
// 				  MotorStarted=0;
// 			  }
// 		  }
// 	  }
	//   ticks = 0;
  // }
// }

int main(void)
{
  // DAVE_STATUS_t status;

  // status = DAVE_Init();           /* Initialization of DAVE APPs  */

//   if (status != DAVE_STATUS_SUCCESS)
//   {
//     /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
//     XMC_DEBUG("DAVE APPs initialization failed\n");

//     while(1U)
//     {

//     }
//   }

  // SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  // XMC_VADC_GLOBAL_Init(VADC, &g_global_handle);
  // XMC_VADC_GROUP_Init(VADC_G0, &g_group_handle);
  // XMC_VADC_GROUP_SetPowerMode(VADC_G0, XMC_VADC_GROUP_POWERMODE_NORMAL);
  // XMC_VADC_GLOBAL_StartupCalibration(VADC);
  // XMC_VADC_GLOBAL_BackgroundInit(VADC, &g_bgn_handle);
  // XMC_VADC_GROUP_ChannelInit(VADC_G0, 7, &g_g0_ch7_handle);
  // XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, 0, 7);
  // XMC_VADC_GLOBAL_BackgroundEnableContinuousMode(VADC);
  // XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);




//   /* Start the motor */
//   //PMSM_FOC_MotorStart(&PMSM_FOC_0);
//   //PMSM_FOC_MotorStop(&PMSM_FOC_0);
//   /* Placeholder for user application code. The while loop below can be replaced with user application code. */

	VADC_Init();

  static uint32_t throttle = 0;
  while(1U)
  {
    throttle = adc_throttle;
    // printf("ADC 7: %d\n", throttle);
  }
}
