/**
 * @file bldc_scalar_pwm_bc.c
 * @brief Block commutation PWM generation. This supports high side, low side and high side with synchronous rectification modulation
 * @date 2016-09-08

 ***********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2016-05-25:
 *     - Initial version
 * 2016-09-08:
 *     - Updated for sensorless support
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "bldc_scalar_pwm_bc.h"

/**********************************************************************************************************************
* MACROS
**********************************************************************************************************************/
#define BLDC_SCALAR_PWM_BC_CH_MASK (0xDU)  /* CCU8 channel mask */
/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/
/*
 * PWM_BC_Init initializes
 * -all three ccu8 slice
 * -PWM output pins
 * -Trap pin and
 * -Inverter pin as per user configurations.
 * Initialize the variable ph_cmpval[1] with (period value + 1), Used for 0% duty cycle
 */
void Motor0_BLDC_SCALAR_PWM_BC_Init(void)
{
  /*initialize PWM timer slices*/
  Motor0_BLDC_SCALAR_CCU8_PWM_Init();
  /*initialize PWM output pins*/
  Motor0_BLDC_SCALAR_GPIO_PWM_Init();
#if(MOTOR0_BLDC_SCALAR_ENABLE_CTRAP == 1U)
  /*initialize Trap pin*/
  Motor0_BLDC_SCALAR_GPIO_Trap_Init();
#endif
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
  /*initialize Inverter pin*/
  Motor0_BLDC_SCALAR_GPIO_Inverter_Init();
#endif

  /*configure variable ph_cmpval[1] with 0% duty*/
  Motor0_BLDC_SCALAR_PWM_BC.ph_cmpval[1] = Motor0_BLDC_SCALAR_CCU8_PWM_Config.period + (uint16_t)1;
}

/*
 * This function configure the inverter pin output level and
 * starts the CCU8 slices to generate the PWM.
 */
void Motor0_BLDC_SCALAR_PWM_BC_Start(void)
{
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
  /*Enable inverter*/
  Motor0_BLDC_SCALAR_PWM_BC_InverterEnable();
#endif

  /*Start PWM timers*/
  Motor0_BLDC_SCALAR_CCU8_PWM_Start();
}

/*
 * This function reset the inverter pin output level and
 * stop the CCU8 slices.
 */
void  Motor0_BLDC_SCALAR_PWM_BC_Stop(void)
{
  /*Disable Inverter*/
#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
  Motor0_BLDC_SCALAR_PWM_BC_InverterDisable();
#endif
  /* Stop pwm timers*/
  Motor0_BLDC_SCALAR_CCU8_PWM_Stop();
}

#if (MOTOR0_BLDC_SCALAR_INVERTER_ENABLE_CONF != BLDC_SCALAR_INV_DISABLED)
/*
 * This function set the inverter pin output level low and high
 * Based on inverter_pin configuration.
 */
void Motor0_BLDC_SCALAR_PWM_BC_InverterEnable(void)
{
  if (PWM_BC_IPIN_HIGH == Motor0_BLDC_SCALAR_PWM_BC.inverter_pin)
  {
    XMC_GPIO_SetOutputHigh(MOTOR0_BLDC_SCALAR_GPIO_INV_ENABLE);
  }
  if (PWM_BC_IPIN_LOW == Motor0_BLDC_SCALAR_PWM_BC.inverter_pin)
  {
    XMC_GPIO_SetOutputLow(MOTOR0_BLDC_SCALAR_GPIO_INV_ENABLE);
  }
}

/*
 * This function set the inverter pin output level low
 * if inverter_pin is high and vice versa.
 */
void Motor0_BLDC_SCALAR_PWM_BC_InverterDisable(void)
{
  if (PWM_BC_IPIN_HIGH == Motor0_BLDC_SCALAR_PWM_BC.inverter_pin)
  {
    XMC_GPIO_SetOutputLow(MOTOR0_BLDC_SCALAR_GPIO_INV_ENABLE);
  }
  if (PWM_BC_IPIN_LOW == Motor0_BLDC_SCALAR_PWM_BC.inverter_pin)
  {
    XMC_GPIO_SetOutputHigh(MOTOR0_BLDC_SCALAR_GPIO_INV_ENABLE);
  }
}
#endif
/*
 * This function check the actual MCM register and modulate high side PWM output and
 * complementary PWM output for same leg. And keep other low side output is either high or low.
 */
void Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod_SyncRect(uint16_t mcm_val)
{
  uint8_t count;

  for (count = (uint8_t)0; count < CCU8_MAXPHASE_COUNT; count++)
  {
    /* If high side switch is ON */
    if (Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] == (mcm_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count]))
    {
      /*
       * Dead Time Enable for Channel 1
       * Dead Time Enable for CC8yST1
       * Dead Time Enable for inverted CC8yST1
       */
      Motor0_BLDC_SCALAR_CCU8_EnableDeadTime(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[count],(uint8_t)BLDC_SCALAR_PWM_BC_CH_MASK);

      /*Set the compare flag to set the inverse duty*/
       Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_INVERSE_DUTY;
    } /* End of high side switch is ON */

    /* if low side switch is ON */
    else if (((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1) ==
                (mcm_val & ((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1)))
    {
      /* Disable dead time */
      Motor0_BLDC_SCALAR_CCU8_DisableDeadTime(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[count],(uint8_t)BLDC_SCALAR_PWM_BC_CH_MASK);

      /*Set the compare flag to switch on completely*/
      Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_PERIOD;
    }
    else
    {
      /*do nothing*/
    }
  }

}

/*
 * This function check the actual MCM register and modulate high
 * side PWM output and keep low side output either high or low.
 */
void Motor0_BLDC_SCALAR_PWM_BC_HsImmediateMod(uint16_t mcm_val)
{
  uint8_t count;

  for (count = (uint8_t)0; count < CCU8_MAXPHASE_COUNT; count++)
  {
    /* If high side switch is ON */
    if (Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] == (mcm_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count]))
    {
      /*Set the compare flag to set the inverse duty*/
      Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_INVERSE_DUTY;

    } /* End of high side switch is ON */
    /* if low side switch is ON */
    else if (((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1) ==
                (mcm_val & ((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1)))
    {
      /*Set the compare flag to switch on completely*/
      Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_PERIOD;
    }
    else
    {
      /*do nothing*/
    }
  }
}

/*
 * This function check the actual MCM register and modulate low side PWM output
 * and keep high side output either high or low.
 */
void Motor0_BLDC_SCALAR_PWM_BC_LsImmediateMod(uint16_t mcm_val)
{
  uint8_t count;

  for (count = (uint8_t)0; count < CCU8_MAXPHASE_COUNT; count++)
  {
    /* If high side switch is ON */
    if (Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] == (mcm_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count]))
    {
      /*Set the compare flag to switch off completely*/
      Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_ZERO;

    } /* End of high side switch is ON */
    /* if low side switch is ON */
    else if (((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1) ==
                (mcm_val & ((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1)))
    {
     /*Set the compare flag to set the duty*/
      Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_DUTY;
    }
    else
    {
      /*do nothing*/
    }
  }

}

/*
 * This function check the non conducting phase and modulate high side PWM output and complementary
 * PWM output for same leg based on the MCMS shadow register.
 * And keep other low side output is either high or low.
 */
void Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod_SyncRect(uint16_t mcm_val, uint16_t mcms_val)
{
  uint8_t count;

  for (count = (uint8_t)0; count < CCU8_MAXPHASE_COUNT; count++)
  {
    /* if phase is not conducting in current cycle */
    if ((uint32_t)0 ==
          (mcm_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_bothside_compmask[count]))
    {
      /* If high side switch is ON */
      if (Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] ==
            (mcms_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count]))
      {
        /*
         * Dead Time Enable for Channel 1
         * Dead Time Enable for CC8yST1
         * Dead Time Enable for inverted CC8yST1
         */
        Motor0_BLDC_SCALAR_CCU8_EnableDeadTime(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[count],(uint8_t)BLDC_SCALAR_PWM_BC_CH_MASK);

        /*Set the compare flag to set the inverse duty*/
        Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_INVERSE_DUTY;
      }
      /* if low side switch is ON*/
      else
      {
        /* Disable dead time */
        Motor0_BLDC_SCALAR_CCU8_DisableDeadTime(Motor0_BLDC_SCALAR_CCU8_PWM_Config.phase_ptr[count],(uint8_t)BLDC_SCALAR_PWM_BC_CH_MASK);

        /*Set the compare flag to switch on completely*/
        Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_PERIOD;
      }
    }
  }
}

/*
 * This function check the non conducting phase and modulate high side PWM output and keep low side
 * output either high or low based on the MCMS shadow register.
 */
void Motor0_BLDC_SCALAR_PWM_BC_HsShadowMod(uint16_t mcm_val, uint16_t mcms_val)
{
  uint8_t count;

  for (count = (uint8_t)0; count < CCU8_MAXPHASE_COUNT; count++)
  {
    /* if phase is not conducting */
    if ((uint32_t)0 ==
          (mcm_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_bothside_compmask[count]))
    {
      /* If high side switch is ON */
      if (Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] ==
            (mcms_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count]))
      {
        Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_INVERSE_DUTY;
      }
      /* if low side switch is ON */
      else
      {
        Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_PERIOD;
      }
    }
  }
}

/*
 * This function check the non conducting phase and modulate low side PWM output and keep high side
 * output either high or low based on the MCMS shadow register.
 */
void Motor0_BLDC_SCALAR_PWM_BC_LsShadowMod(uint16_t mcm_val, uint16_t mcms_val)
{
  uint8_t count;

  for (count = (uint8_t)0; count < CCU8_MAXPHASE_COUNT; count++)
  {
    /* if phase is not conducting */
    if ((uint32_t)0 ==
          (mcm_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_bothside_compmask[count]))
    {
      /* If high side switch is ON */
      if (Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] ==
            (mcms_val & (uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count]))
      {
        Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_ZERO;
      }
      /* if low side switch is ON */
      else if (((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1) ==
            (mcms_val & ((uint32_t)Motor0_BLDC_SCALAR_PWM_BC.ph_mcpatt_compmask[count] << (uint32_t)1)))
      {
        Motor0_BLDC_SCALAR_PWM_BC.ph_cmpflag[count] = PWM_BC_COMPARE_DUTY;
      }
      else
      {

      }
    }
  }
}



