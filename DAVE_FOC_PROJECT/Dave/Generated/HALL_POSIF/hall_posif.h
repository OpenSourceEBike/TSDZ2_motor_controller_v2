/**
 * @file hall_posif.h
 * @date 2021-01-08
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * HALL_POSIF v4.0.10 - To get the motor position and speed using hall sensors separated at 120 degrees.
 * It supports 2-hall and 3-hall configuration.
 *
 * Copyright (c) 2015-2020, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided with the distribution.
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
 *
 * 2015-02-20:
 *     - Initial version
 *
 * 2015-06-20:
 *     - ERU initialization modified <br>
 *     - shadow_transfer_msk data type changed from uint8_t to uint32_t
 *     - help comments updated
 *
 * 2021-01-08:
 *     - Modified check for minimum XMCLib version
 *
 * @endcond
 *
 */

#ifndef HALL_POSIF_H_
#define HALL_POSIF_H_

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/


#include "xmc_gpio.h"
#include "GLOBAL_POSIF/global_posif.h"
#include "GLOBAL_CCU4/global_ccu4.h"
#include "hall_posif_conf.h"

#if (HALL_POSIF_ERU_AVALABLE == 1U)
#include "xmc_eru.h"
#endif

/**********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

#define HALL_POSIF_XMC_LIB_MAJOR_VERSION 2
#define HALL_POSIF_XMC_LIB_MINOR_VERSION 0
#define HALL_POSIF_XMC_LIB_PATCH_VERSION 0

#if !((XMC_LIB_MAJOR_VERSION > HALL_POSIF_XMC_LIB_MAJOR_VERSION) ||\
      ((XMC_LIB_MAJOR_VERSION == HALL_POSIF_XMC_LIB_MAJOR_VERSION) && (XMC_LIB_MINOR_VERSION > HALL_POSIF_XMC_LIB_MINOR_VERSION)) ||\
      ((XMC_LIB_MAJOR_VERSION == HALL_POSIF_XMC_LIB_MAJOR_VERSION) && (XMC_LIB_MINOR_VERSION == HALL_POSIF_XMC_LIB_MINOR_VERSION) && (XMC_LIB_PATCH_VERSION >= HALL_POSIF_XMC_LIB_PATCH_VERSION)))
#error "HALL_POSIF requires XMC Peripheral Library v2.0.0 or higher"
#endif

#define HALL_POSIF_SHADOWTRANSFERBITPOS    (4U)            /*!< This defines slice shadow transfer bit position*/
#define HALL_POSIF_EXPECTEDHALLBITSHIFT    (3U)            /*!< This defines number bit shift required to get expected hall pattern*/
#define HALL_POSIF_HALLTABLEMAXLIMIT       (16U)           /*!< This defines hall pattern table maximum limit*/
#define HALL_POSIF_SPEEDACCUMLIMITCHECK    (5U)            /*!< This defines speed accumulation limit value*/
#define HALL_POSIF_SIXTYDEGREE             (60U)           /*!< This defines sixty degree*/
#define HALL_POSIF_PHASEADVMINLIMIT        (10U)           /*!< This defines phase advance minimum limit*/
#define HALL_POSIF_PHASEADVMAXLIMIT        (60U)           /*!< This defines phase advance maximum limit*/
#define HALL_POSIF_BIT_POS_1               (1U)            /*!< This defines the value if only 1st bit is enable in a variable*/
#define HALL_POSIF_BIT_POS_2               (2U)            /*!< This defines the value if only 2nd bit is enable in a variable*/
#define HALL_POSIF_BIT_POS_3               (4U)            /*!< This defines the value if only 3rd bit is enable in a variable*/
#define HALL_POSIF_BIT_POS_4               (8U)            /*!< This defines the value if only 4th bit is enable in a variable*/

/**
 * This gives the current and expected hall pattern in a regsiter format. 
 */
#define  HALL_POSIF_MCM(EP,CP)          (((uint32_t)EP<< 3)|(uint32_t)CP)

/**********************************************************************************************************************
* ENUMS
**********************************************************************************************************************/
/**
 * @ingroup HALL_POSIF_enumerations
 * @{
 */
/**
 * This enumerates Status of the app. Used during initialization.
 */
typedef enum HALL_POSIF_STATUS
{
  HALL_POSIF_STATUS_SUCCESS,              /*!< APP status success*/
  HALL_POSIF_STATUS_FAILURE,              /*!< APP status failure*/
  HALL_POSIF_STATUS_INVALID_PARAM         /*!< invalid parameters*/

} HALL_POSIF_STATUS_t;
/**
 * This enumerates state of the APP
 */
typedef enum HALL_POSIF_STATE
{

  HALL_POSIF_UNINITIALISED,  /*!< default state after power on reset*/
  HALL_POSIF_INITIALISED,    /*!< APP is in INITIALIZED state after execution of the Init function*/
  HALL_POSIF_RUNNING         /*!< This state is entered after starting of posif module*/

} HALL_POSIF_STATE_t;

/**
 * Number of hall sensors used for position and speed measurement.
 */
typedef enum HALL_POSIF_TYPE
{
  HALL_POSIF_3HALL,          /*!< 3 Hall sensor mode*/
  HALL_POSIF_2HALL           /*!< 2 Hall sensor mode*/

} HALL_POSIF_TYPE_t;

/**
 * This enumerates the phase advance enable.
 */
typedef enum HALL_POSIF_PHASEADVANCE
{

  HALL_POSIF_PHASEADVANCE_DISABLE,      /*!< phase advance disable*/
  HALL_POSIF_PHASEADVANCE_ENABLE        /*!< phase advance enable*/

} HALL_POSIF_PHASEADVANCE_t;

/**
 * This enumerates the direction of rotation. 
 */
typedef enum HALL_POSIF_DIRECTION
{

  HALL_POSIF_CLK_DIR = 0,             /*!< clockwise direction of rotation*/
  HALL_POSIF_ANTI_CLK_DIR = 8         /*!< anti-clockwise direction of rotation*/
  
}HALL_POSIF_DIRECTION_t;

/**
 * @}
 */
/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/**
 * @ingroup HALL_POSIF_datastructures
 * @{
 */

/**
 * This structure hold all the parameters related to GPIO resource.
 */
typedef struct HALL_POSIF_GPIO
{
  XMC_GPIO_PORT_t *const port;      /**< GPIO port */
  const uint8_t pin;                /**< GPIO pin */
} HALL_POSIF_GPIO_t;

/**
 *  @brief CCU4-CC4 slice identifier data
 */
typedef struct HALL_POSIF_CCU4_SLICE
{
  XMC_CCU4_SLICE_t  *slice_ptr;              /**< CCU4 CC4 pointer */
  XMC_CCU4_MODULE_t *module_ptr;             /**< Corresponding CCU4 Module Pointer */
  uint32_t          shadow_transfer_msk;     /**< CCU4 slice shadow transfer mask value*/
  uint8_t           slice_number;            /**< CCU4 slice number */
}HALL_POSIF_CCU4_SLICE_t;

#if (HALL_POSIF_ERU_AVALABLE == 1U)
typedef struct  HALL_POSIF_ERU
{
  XMC_ERU_t* const eru;                      /**< ERU module assigned(ERU0/ERU1) */
  const uint8_t ogu_channel;                 /**< ERU channel assigned(0-3) */
  const uint8_t etl_channel;                 /**< ERU channel assigned(0-3) */

}HALL_POSIF_ERU_t;
#endif
/**
 * This structure holds the parameters which change at run
 * time.
 */
typedef struct HALL_POSIF_Config
{
  /**
   * This array store the service request id for ccu4 phase delay slice.\n
   * phasedelay_slice_sr[0] : Period/One match Service request selector \n
   * phasedelay_slice_sr[1] : Compare match Service request selector \n
   * phasedelay_slice_sr[2] : Event 0 Service request selector \n
   * phasedelay_slice_sr[3] : Event 1 Service request selector \n
   * phasedelay_slice_sr[4] : Event 2 Service request selector \n
   */
  XMC_CCU4_SLICE_SR_ID_t phasedelay_slice_sr[5];
  /**
   * This array store the service request id.
   * capture_slice_sr[0] : Period/One match Service request selector \n
   * capture_slice_sr[1] : Compare match(Pattern update SR) \n
   * capture_slice_sr[2] : Event 0 Service request selector \n
   * capture_slice_sr[3] : Event 1 Service request selector \n
   * capture_slice_sr[4] : Event 2 Service request selector
   */
  XMC_CCU4_SLICE_SR_ID_t capture_slice_sr[5];
  /**
   * This array store the service request id. \n
   * posif_sr[0] : Correct Hall Event Service Request Selector \n
   * posif_sr[1] : Wrong Hall Event Service Request Selector \n
   * posif_sr[2] : Hall Inputs Update Event Service Request Selector \n
   */
  XMC_POSIF_SR_ID_t posif_hsc_sr[3];
  /**
   * This variable store hall type. \n
   * 3Hall or 2Hall
   */
  HALL_POSIF_TYPE_t halltype;
  /**
   * This is the constant calculated value used for the speed calculation.
   */
  uint32_t speed_constant_avg;
  /**
    * This is the phase delay constant used for calculating the
    * period register of the PhaseDelay slice and Compare register
    * of the Capture slice.
    */
  uint16_t phase_delay_const;
  /**
    * This is the time between hall edge detection and sampling of the hall
    * patterns. This is the compare register of the phase delay slice.
    */
  uint16_t blanking_time;
  /**
   * This is the time between sampling of the hall patterns and the updating of
   * the multi channel pattern.This is the period register of the phase delay
   * slice.
   */
  uint16_t phase_delay;
  /**
   * Enable If hall inputs are connected via eru. \n
   * enable_eru[0] -> Hall Input -1 \n
   * enable_eru[1] -> Hall Input -2 \n
   * enable_eru[2] -> Hall Input -3 \n
   */
  uint8_t enable_eru[3];
  /**
   * Store the interrupt configurations.(0:Disable, 1:Enable) \n
   * Bit position 0 : Correct hall event \n
   * Bit position 1 : Wrong hall event  \n
   * Bit position 2 : Pattern update event  \n
   * Bit position 3 : Capture event \n
   */
  uint8_t interrupt_enable;
  /**
   * This is the hall3 pin status which is not connected in 2-Hall configuration
   */
  uint8_t hall3pin;

} HALL_POSIF_Config_t;

/**
 * This structure holds the configurable parameters of this app and address of 
 * sub structures associated with this app.
 */
typedef struct HALL_POSIF_Handle
{
  /**
   * This saves the captured time value between two correct hall events.
   */
  uint32_t captureval[6];
  /**
   * This saves the configured all pattern in clockwise and anti-clockwise
   * direction.
   * Each value of this hall_pattern table is equal to (expected hall << 3 | current hall)
   */
  uint8_t hall_pattern[16];
  /**
   * Pointer to the GPIO hall input.
   */
  HALL_POSIF_GPIO_t* const hallinput_ptr[3];
  
  #if (HALL_POSIF_ERU_AVALABLE == 1U)
  /**
   * Array of pointer to the ETL configuration module. 
   */
   XMC_ERU_ETL_CONFIG_t*const etl_conf_ptr[3];
  /**
   * Array of pointer to the ETL resource configuration module. 
   */
  HALL_POSIF_ERU_t*const etl_resource_ptr[3];
  /**
   * Array of pointer to the OGU resource configuration module. 
   */
  XMC_ERU_OGU_CONFIG_t*const ogu_conf_ptr[3];
  #endif
  /**
   * Pointer to the ccu4 timer init module. This slice
   * is used for phase delay.
   */
  XMC_CCU4_SLICE_COMPARE_CONFIG_t*const phasedelay_init_ptr;
  /**
    * Pointer to the ccu4 capture init module. This slice
    * is used for capture timer.
    */
  XMC_CCU4_SLICE_CAPTURE_CONFIG_t*const capture_init_ptr;
  /**
   * This is the CMSIS register structure pointer for the POSIF module.
   */
  POSIF_GLOBAL_TypeDef* const global_ptr;
  /**
   * Structure pointer which holds the dynamic data.
   */
  HALL_POSIF_Config_t* const config_ptr;
  /**
   * Pointer to the POSIF hall sensor control module
   */
  XMC_POSIF_HSC_CONFIG_t* const posifhsc_ptr;
  /**
   * Pointer to the POSIF config module
   */
  XMC_POSIF_CONFIG_t* const posifconfig_ptr;
  /**
   * CMSIS register structure pointer for the Phase Delay slice
   */
  HALL_POSIF_CCU4_SLICE_t*const phasedelay_ptr;
  /**
   * CMSIS register structure pointer for the Capture slice
   */
  HALL_POSIF_CCU4_SLICE_t* const capture_ptr;
  /**
   * Pointer to the phase delay event config module.
   */
  XMC_CCU4_SLICE_EVENT_CONFIG_t* const phdelayevent_ptr;
  /**
   * Pointer to the phase delay event config module.
   */
  XMC_CCU4_SLICE_EVENT_CONFIG_t* const captureevent_ptr;
  /**
   * Pointer to the GPIO hall configuration module.
   */
  XMC_GPIO_CONFIG_t * const hallpinconfig_ptr;
  /**
   * Pointer to the global_posif app handle.
   */
  GLOBAL_POSIF_t*const global_posif_handle_ptr;
  /**
    * This is the time between correct hall event and writing next multi channel
    * pattern to the shadow multi channel register. This is the compare register
    * of the capture slice.
    */
  uint32_t pattern_update_delay;

  /**
   * Pointer to the global_ccu4 app handle.
   */
  GLOBAL_CCU4_t*const global_ccu4_handle_ptr;
  /**
   * This saves the direction of rotation.
   */
  HALL_POSIF_DIRECTION_t direction;
  /**
   * This tells whether motor speed can be calculated.
   */
  uint32_t speedcheck;
  /**
   * This tells whether next pattern is repeated pattern in 2-hall configuration
   */
  uint32_t timercheck;
  /**
   * This saves whether phase advance feature is enabled.
   */
  HALL_POSIF_PHASEADVANCE_t phadvance;
  /**
   * This is the average speed of the motor.
   */
  uint32_t speedaccum;
  /**
   * This is the Captured time Value .
   */
  uint32_t capval;
  /**
   * This is the APP state.
   */
  HALL_POSIF_STATE_t state;
  /**
   * This saves the phase constant value as per phase delay angle or
   * phase advance angle.
   */
  uint16_t phaseconst;
  /**
   * This saves the phase constant value as per phase advance angle.
   */
  uint16_t phaseadvconst;
  /**
   * This is the index of an array of Hall Pattern and Multi-Channel output
   * pattern.
   */
  uint8_t index;
  /**
   * This is the index of an array of the speed calculation
   */
  uint8_t speedindex;

} HALL_POSIF_t;

/**
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @ingroup HALL_POSIF_apidoc
 * @{
 */
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
/**
 * @brief Get HALL_POSIF APP version
 * @return DAVE_APP_VERSION_t APP version information (major, minor and patch number)
 *
 * \par<b>Description: </b><br>
 * The function can be used to check application software compatibility with a
 * specific version of the APP.
 *
 * Example Usage:
 *
 * @code
 * #include "DAVE.h"
 *
 * int main(void) {
 *   DAVE_STATUS_t init_status;
 *   DAVE_APP_VERSION_t version;
 *
 *   // HALL_POSIF_Init() is called from DAVE_Init().
 *   init_status = DAVE_Init();
 *
 *   version = HALL_POSIF_GetAppVersion();
 *
 *   // More code here
 *
 *   while(1) {
 *
 *   }
 *   return (0);
 * }
 * @endcode<BR>
 */
DAVE_APP_VERSION_t HALL_POSIF_GetAppVersion(void);
/**
 * @brief Initialize the HALL_POSIF APP as per user configured values.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return HALL_POSIF_STATUS_t: status of the operation
 * <BR>
 * \par<b>Description: </b><br>
 *  This API is called in definition of DAVE_init or top level APP, by code generation
 *  and therefore should not be explicitly called for the normal operation.
 *  Use other APIs only after DAVE_init is called successfully (returns DAVE_STATUS_SUCCESS).\n
 *
 * Example Usage:
 *
 * <BR>
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *   DAVE_STATUS_t init_status;
 *
 *   // HALL_POSIF_Init(&HALL_POSIF_0) is called from DAVE_Init().
 *   init_status = DAVE_Init();
 *
 *   // More code here
 *
 *   while(1) {
 *
 *   }
 *   return (0);
 * }
 * @endcode<BR>
 */
HALL_POSIF_STATUS_t HALL_POSIF_Init(HALL_POSIF_t * const HandlePtr);
/**
 * @brief Initialize the current hall pattern and then start the POSIF module.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return <b>void</b>
 * <BR>
 * \par<b>Description: </b><br>
 * Invoke this API when APP state is HALL_POSIF_INITIALISED or else this API will have no effect on functionality.\n
 *
 * Example Usage:
 * <BR>
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *   DAVE_STATUS_t status;
 *   status = DAVE_Init();                 // Initialization of DAVE APPs
 *
 *   if(status == DAVE_STATUS_SUCCESS)
 *   {
 *     HALL_POSIF_Start(&HALL_POSIF_0);
 *   }
 *   while(1U)
 *   {
 *
 *   }
 * }
 * @endcode<BR>
 */
void HALL_POSIF_Start(HALL_POSIF_t * const HandlePtr);
/**
 * @brief Stop POSIF and capture CCU4 slice.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return <b>void</b>
 * <BR>
 * \par<b>Description: </b><br>
 * Invoke this API when module is running and it needs to be disabled completely.
 * Any operation on the HALL_POSIF module will have no effect after this API is called.
 * <BR>
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is HALL_POSIF_RUNNING or else it has no effect on functionality.
 * <BR>
 *
 * Example Usage:
 * <BR>
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *   DAVE_STATUS_t status;
 *   status = DAVE_Init();                 // Initialization of DAVE APPs
 *
 *   if(status == DAVE_STATUS_SUCCESS)
 *   {
 *     HALL_POSIF_Start(&HALL_POSIF_0);
 *   }
 *
 *   HALL_POSIF_Stop(&HALL_POSIF_0);  // call when HALL_POSIF_0.state == HALL_POSIF_RUNNING
 *   
 *   while(1U)
 *   {
 *
 *   }
 * }
 * @endcode<BR>
 */
void HALL_POSIF_Stop(HALL_POSIF_t * const HandlePtr);
/**
 * @brief Set the direction of rotation to clockwise or anti clockwise.\n
 * "HALL_POSIF_CLK_DIR"      : Clockwise direction<br>
 * "HALL_POSIF_ANTI_CLK_DIR" : Anti clockwise direction
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @param Dir direction of rotation
 * @return <b>void</b>
 * <BR>
 * \par<b>Description: </b><br>
 * This API update variable (direction) in the APP handle. After that hall pattern of \a Dir(direction) get applied.
 * Motor control APP call this API together with other configuration when ever there is need to change of motor direction.
 * <BR>
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".
 * <BR>
 *
 * \par<b>Related APIs:</b><BR>
 * HALL_POSIF_SetNextHallPatt(), HALL_POSIF_SetNext2HallPatt(), XMC_DAC_CH_GetRampStop(), HALL_POSIF_Start()
 *<BR>
 *
 * Example Usage:
 *
 * <BR>
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *    HALL_POSIF_SetDirection(&HALL_POSIF_0,HALL_POSIF_CLK_DIR);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 * }
 * @endcode<BR>
 */
void HALL_POSIF_SetDirection(HALL_POSIF_t * const HandlePtr,
                                                    HALL_POSIF_DIRECTION_t Dir);
/**
 * @brief Return the direction of rotation.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return <b>HALL_POSIF_DIRECTION_t</b>
 *
 *<BR>
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *   DAVE_STATUS_t init_status;
 *   HALL_POSIF_DIRECTION_t dir;
 *   init_status = DAVE_Init();
 *
 *   dir = HALL_POSIF_GetDirection(&HALL_POSIF_0);
 *
 *   while(1U)
 *   {
 *   
 *   }
 * }
 * @endcode<BR>
 */
HALL_POSIF_DIRECTION_t HALL_POSIF_GetDirection(HALL_POSIF_t * const HandlePtr);
/**
 * @brief Updates the next hall pattern in the shadow hall register
 * for 3-hall configuration.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @param index next hall index, range: 1 to 6
 * @return <b>void</b>
 * <BR>
 * \par<b>Description: </b><br>
 * This API fetches current and expected hall information from the hall_pattern table at \a index and update
 * the shadow hall register. Index is current hall value.
 * Applications can program the next hall pattern(current and expected) from hall_pattern table using index.
 * <BR>
 *
 * \par<b>Note</b><br>
 * Call this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".
 * This is applicable only to the hall sensor mode of operation.
 * Transfer from the shadow register is based on a hardware transfer trigger
 * or software trigger through API.
 *
 *<BR>
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *   DAVE_STATUS_t init_status;
 *   init_status = DAVE_Init();
 *   if(init_status == DAVE_STATUS_SUCCESS)
 *   {
 *     HALL_POSIF_Start(&HALL_POSIF_0);
 *   }
 *   while(1U)
 *   {
 *
 *   }
 * }
 *
 * //This is the hall event(correct or wrong hall) ISR
 * void HALLEvent_ISR(void)
 * {
 *   HALL_POSIF_SetNextHallPatt(&HALL_POSIF_0,3);
 * }
 *
 * @endcode<BR>
 */
void HALL_POSIF_SetNextHallPatt(HALL_POSIF_t * const HandlePtr, uint8_t index);
/**
 * @brief Update the next hall pattern in the shadow hall
 * register for 2-Hall configuration
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @param index next hall index, range: 0 to 3
 * @return <b>void</b>
 * <BR>
 * \par<b>Description: </b><br>
 * This API fetch current and expected hall information from the hall_pattern table at \a index and update
 * the shadow hall register. Index is current hall value.
 * Applications can program the next hall pattern(current and expected) from hall_pattern table using index.
 * <BR>
 *
 * \par<b>Note</b><br>
 * Call this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".
 * This is applicable only to the hall sensor mode of operation.
 * Transfer from the shadow register is based on a hardware transfer trigger
 * or software trigger through API.
 *
 *<BR>
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *    HALL_POSIF_Start(&HALL_POSIF_0);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 * }
 *
 * //This is the hall event(correct or wrong hall) ISR
 * void HALLEvent_ISR(void)
 * {
 *   HALL_POSIF_SetNext2HallPatt(&HALL_POSIF_0,3);
 * }
 * @endcode<BR>
 */
void HALL_POSIF_SetNext2HallPatt(HALL_POSIF_t * const HandlePtr, uint8_t index);
/**
 * @brief Calculate the speed based upon the captured time value between two correct hall events.
 * @param HandlePtr pointer to an object of HALL_POSIF module.
 * @param Speed Electrical speed of the motor
 * @return <b>void</b>
 * <BR>
 * \par<b>Description: </b><br>
 * To get the actual speed call this API in the correct or wrong hall ISR.
 *
 * <BR>
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".\n
 * Speed value will be available after 1st electrical rotation(1st 6 hall events)
 * before that speed will be zero.
 *
 *<BR>
 * Example Usage:
 *<BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *    HALL_POSIF_Start(&HALL_POSIF_0);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 * }
 *
 * //This is the correct hall event ISR
 * void HallEvent_ISR(void)
 * {
 *   uint32_t Speed;
 *   HALL_POSIF_SpeedCalculation(&HALL_POSIF_0,&Speed);
 * }
 * @endcode<BR>
 */
void HALL_POSIF_SpeedCalculation(HALL_POSIF_t * const HandlePtr, uint32_t* Speed);
/**
 * @brief Calculate period register(phase delay slice) and
 * compare register (capture slice) values based upon last captured value and
 * configured phase delay angle.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return <b>void</b>
 * <BR>
 * \par<b>Description: </b><br>
 * This function allow user to enter their desired phase delay value, that is time delay required between correct hall
 * pattern detection and application of multi-channel output pattern.
 * <BR>
 *
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".\n
 * This is not required if standalone hall sensor mode is used.
 *
 * <BR>
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *    HALL_POSIF_Start(&HALL_POSIF_0);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 * }
 *
 * //This is the pattern update ISR
 * void HALL_POSI_PatternUpdate_ISR(void)
 * {
 *   HALL_POSIF_UpdateTimerValues(&HALL_POSIF_0);
 * }
 * @endcode<BR>
 */
void HALL_POSIF_UpdateTimerValues(HALL_POSIF_t *const HandlePtr);
/**
 * @brief Retrieves the capture time between two correct hall events.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return HALL_POSIF_STATUS_t return HALL_POSIF_STATUS_SUCCESS for valid capture register value
 * <BR>
 * \par<b>Description: </b><br>
 * This function take care of the floating prescaler and gives the result in terms of the base resolution.
 * <BR>
 *
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".\n
 * In case of invalid full flag value, return status of this API is HALL_POSIF_STATUS_FAILURE.
 * <BR>
 *
 * \par<b>Related APIs:</b><BR>
 * HALL_POSIF_UpdateTimerValues()
 *<BR>

 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *   HALL_POSIF_Start(&HALL_POSIF_0);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 *   
 * }
 * //This is the pattern update interrupt handler
 * void HALL_POSI_PatternUpdate_ISR(void)
 * {
 *   status = HALL_POSIF_ReadCaptureValue(&HALL_POSIF_0);
 * }
 * @endcode<BR>
 */
HALL_POSIF_STATUS_t HALL_POSIF_ReadCaptureValue(HALL_POSIF_t *const HandlePtr);

/**
 * @brief Return the current state of the POSIF input pins to which hall sensors are connected.
 * @param HandlePtr pointer to an object of HALL_POSIF module\n
 * @return <b>uint32_t</b>
 * <BR>
 * \par<b>Description: </b><br>
 * This is required information before starting the APP to know the start position of the motor.
 * <BR>
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".
 * <BR>
 *
 * \par<b>Related APIs:</b><BR>
 *  HALL_POSIF_Start()
 *</BR>
 *
 * Example Usage:
 * <BR>
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  uint32_t hallposition;
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *    HALL_POSIF_Start(&HALL_POSIF_0);
 *    hallposition = HALL_POSIF_GetHallPosition(&HALL_POSIF_0);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 * }
 * @endcode<BR>
 */
uint32_t HALL_POSIF_GetHallPosition(HALL_POSIF_t*const Handle);
/**
 * @brief Enable phase advancing feature at run time.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return <b>void</b>
 * <BR>
 *
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".\n
 * <BR>
 *
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *   HALL_POSIF_Start(&HALL_POSIF_0);
 *
 *   HALL_POSIF_EnablePhAdvance(&HALL_POSIF_0);
 *   
 *   }
 *   while(1U)
 *   {
 *
 *   }
 * }
 * @endcode<BR>
 */
void HALL_POSIF_EnablePhAdvance(HALL_POSIF_t*const Handle);

/**
 * @brief Disable phase advancing feature at run time.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @return <b>void</b>
 *
 * <BR>
 * \par<b>Note:</b><br>
 * Invoke this API when APP state is not equal to "HALL_POSIF_UNINITIALISED".\n
 * <BR>
 *
 * <BR>
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *    HALL_POSIF_Start(&HALL_POSIF_0);
 *    HALL_POSIF_DisablePhAdvance(&HALL_POSIF_0);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 * }
 * @endcode<BR>
 */
void HALL_POSIF_DisablePhAdvance(HALL_POSIF_t*const Handle);
/**
 * @brief Set the phase advance angle.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @param Angle Phase advance angle in degrees (10 to 60)
 * @return <b>void</b>
  * <BR>
 * \par<b>Description: </b><br>
 * Phase advance(x) = forward shift of switching pattern by 1 + phase delay(60-x)
 * This is the period register value of the phase delay slice.
 *
 * <BR>
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  init_status = DAVE_Init();
 *  if(init_status == DAVE_STATUS_SUCCESS)
 *  {
 *   HALL_POSIF_Start(&HALL_POSIF_0);
 *   HALL_POSIF_SetPhAdvanceAngle(&HALL_POSIF_0, 30);
 *  }
 *  while(1U)
 *  {
 *
 *  }
 * }
 * @endcode<BR>
 */
HALL_POSIF_STATUS_t HALL_POSIF_SetPhAdvanceAngle(HALL_POSIF_t *const HandlePtr,
                                                                uint32_t Angle);
/**
 * @brief Retrieves the phase advance angle.
 * @param HandlePtr pointer to an object of HALL_POSIF module
 * @param Angle Phase advance angle in degrees (10 to 60)
 * @return <b>uint32_t</b>
 * <BR>
 * Example Usage:
 * <BR>
 *
 * @code
 * #include "DAVE.h"
 * int main(void)
 * {
 *  DAVE_STATUS_t init_status;
 *  uint32_t Angle;
 *  init_status = DAVE_Init();
 *
 *   Angle = HALL_POSIF_GetPhAdvanceAngle(&HALL_POSIF_0);
 *
 *   while(1U)
 *   {
 *   
 *   }
 * }
 * @endcode<BR>
 */
uint32_t HALL_POSIF_GetPhAdvanceAngle(HALL_POSIF_t *const HandlePtr);

#include "hall_posif_extern.h"

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* HALL_POSIF_H_ */

