/*******************************************************************************
 Copyright (c) 2015-2016, Infineon Technologies AG                            **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its contributors **
 may be used to endorse or promote products derived from this software without**
 specific prior written permission.                                           **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC1300 Series                                         **
**                                                                            **
** AUTHOR : Motor Control  R&D Team                                           **
**                                                                            **
** Version 1.0.0  Initial version                                             **

**                                                                            **
** MODIFICATION DATE : September 10, 2016                                     **
**                                                                            **
*******************************************************************************/

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "xmc_common.h"
#include "bldc_scalar_user_interface.h"
#include "../brake.h"


#if(MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE==1)
#include "../uCProbe/uCProbe.h"
#endif

static int32_t pot_val = 0;

/**
@brief
This example project controls 3-phase BLDC motor with 3 hall sensor feedback using block commutation control algorithm.
This is configured for Infineon low voltage motor control kit KIT_XMC1X_AK_MOTOR_001 with Maxon motor part number 267121

A list of APIs is provided to control the motor and change the configurations
 - Motor0_BLDC_SCALAR_MotorStart
 - Motor0_BLDC_SCALAR_MotorStop
 Below APIs are for speed control. Similar APIs are available for voltage control and current control.
 - BLDC_SCALAR_SetSpeedVal
 - BLDC_SCALAR_SetSpeedProportionalGain
 - BLDC_SCALAR_SetSpeedIntegralGain
 */

/* Default configuration:
 * Infineon low voltage motor control kit KIT_XMC1X_AK_MOTOR_001 with Maxon motor
 * Control scheme: BLDC_SCALAR_SPEED_CTRL
 * PWM modulation: BLDC_SCALAR_PWM_HIGHSIDE
 * PWM frequency: 20000Hz
 * Speed set: 2000 RPM
 * Ramp up and ramp down rate: 500 RPM/s
 * Over-current protection with direct DC link current measurement
 * Seamless bi-directional, Hall pattern learning and stall detection are enabled
 */

/* Change of configurations:
 * Control algorithm configurations are in the Configuration/bldc_scalar_user_config.h file.
 * MCU HW resources configurations are in the Configuration/bldc_scalar_mcuhw_config.h file.
 */

int main(void)
{
  brake_init();
  while (brake_is_set()) {
    ; // hold here while brake is pressed -- this is a protection for development
  }

  /* Initialization */
  Motor0_BLDC_SCALAR_Init();

#if (MOTOR0_BLDC_SCALAR_CTRL_UCPROBE_ENABLE == 1)
  Motor0_BLDC_SCALAR_Flash_Var_Init();

  Motor0_BLDC_SCALAR_uCProbe_Init();
#endif


  /* Start the motor */
  Motor0_BLDC_SCALAR_MotorStart();

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */

  while (1U)
  {

    Motor0_BLDC_SCALAR_GetPotentiometerVal(&pot_val);

    pot_val += 1;

  }

}

