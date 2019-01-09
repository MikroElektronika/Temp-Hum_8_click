/*
    __temphum8_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __temphum8_driver.h
@brief    TempHum8 Driver
@mainpage TempHum8 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   TEMPHUM8
@brief      TempHum8 Click Driver
@{

| Global Library Prefix | **TEMPHUM8** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **nov 2018.**      |
| Developer             | **Katarina Perendic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _TEMPHUM8_H_
#define _TEMPHUM8_H_

/** 
 * @macro T_TEMPHUM8_P
 * @brief Driver Abstract type 
 */
#define T_TEMPHUM8_P    const uint8_t*

/** @defgroup TEMPHUM8_COMPILE Compilation Config */              /** @{ */

//  #define   __TEMPHUM8_DRV_SPI__                            /**<     @macro __TEMPHUM8_DRV_SPI__  @brief SPI driver selector */
   #define   __TEMPHUM8_DRV_I2C__                            /**<     @macro __TEMPHUM8_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __TEMPHUM8_DRV_UART__                           /**<     @macro __TEMPHUM8_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup TEMPHUM8_VAR Variables */                           /** @{ */

/* Commands */
extern const uint8_t _TEMPHUM8_TEMP_MEASUREMENT_HOLD_MODE    ;
extern const uint8_t _TEMPHUM8_HUM_MEASUREMENT_HOLD_MODE     ;
extern const uint8_t _TEMPHUM8_TEMP_MEASUREMENT_NO_HOLD_MODE ;
extern const uint8_t _TEMPHUM8_HUM_MEASUREMENT_NO_HOLD_MODE  ;
extern const uint8_t _TEMPHUM8_USER_REGISTER_WRITE           ;
extern const uint8_t _TEMPHUM8_USER_REGISTER_READ            ;
extern const uint8_t _TEMPHUM8_SOFT_RESET                    ;

/* user register */
extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H12_T14 ;
extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H8_T12  ;
extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H10_T13 ;
extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H11_T11 ;
extern const uint8_t _TEMPHUM8_CFG_END_OF_BATTERY_LESS_THAN_2_25V   ;
extern const uint8_t _TEMPHUM8_CFG_END_OF_BATTERY_BIGGER_THAN_2_25V ;
extern const uint8_t _TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER ;
extern const uint8_t _TEMPHUM8_CFG_DISABLE_OTP_RELOAD    ;

extern const uint8_t _TEMPHUM8_DEVICE_SLAVE_ADDRESS;

/* Temperature data in ... */
extern const uint8_t _TEMPHUM8_TEMPERATURE_IN_CELSIUS   ;
extern const uint8_t _TEMPHUM8_TEMPERATURE_IN_KELVIN    ;
extern const uint8_t _TEMPHUM8_TEMPERATURE_IN_FARENHAJT ;

                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup TEMPHUM8_INIT Driver Initialization */              /** @{ */

#ifdef   __TEMPHUM8_DRV_SPI__
void temphum8_spiDriverInit(T_TEMPHUM8_P gpioObj, T_TEMPHUM8_P spiObj);
#endif
#ifdef   __TEMPHUM8_DRV_I2C__
void temphum8_i2cDriverInit(T_TEMPHUM8_P gpioObj, T_TEMPHUM8_P i2cObj, uint8_t slave);
#endif
#ifdef   __TEMPHUM8_DRV_UART__
void temphum8_uartDriverInit(T_TEMPHUM8_P gpioObj, T_TEMPHUM8_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void temphum8_gpioDriverInit(T_TEMPHUM8_P gpioObj);
                                                                       /** @} */
/** @defgroup TEMPHUM8_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Functions for device software reset
 */
void temphum8_softReset();

/**
 * @brief Functions for read Relative Huminidy data
 *
 * @return Relative Huminidy data in [%RH]
 */
float temphum8_getHumidity();

/**
 * @brief Functions for read user register
 *
 * @return one byte data
 */
uint8_t temphum8_readUserRegister();

/**
 * @brief Functions for write data to user register
 *
 * @param[in] _data    Data to be written in user register
 */
void temphum8_writeUserRegister(uint8_t _data);

/**
 * @brief Functions for configuration device for measurement
 *
 * @param[in] cfg    Data to be written in user register
 *
 * @note - Options for sets:
        * Measurement resolution (Temp/Hum - 14bit/12bit, 12bit/8bit, 13bit/10bit or 11bit/11bit)
        * Status: End of battery (VDD > 2.25V or VDD < 2.25V)
        * Enable on-chip heater
        * Disable OTP Reload
 */
void temphum8_configuration(uint8_t cfg);

/**
 * @brief Functions for read Temperature data
 *
 * @param[in] tempIn       Temperature in ... (FAHRENHEIT, KELVIN, CELSIUS)
 * @return Temperature data
 */
float temphum8_getTemperature(uint8_t tempIn);



                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_TempHum8_STM.c
    @example Click_TempHum8_TIVA.c
    @example Click_TempHum8_CEC.c
    @example Click_TempHum8_KINETIS.c
    @example Click_TempHum8_MSP.c
    @example Click_TempHum8_PIC.c
    @example Click_TempHum8_PIC32.c
    @example Click_TempHum8_DSPIC.c
    @example Click_TempHum8_AVR.c
    @example Click_TempHum8_FT90x.c
    @example Click_TempHum8_STM.mbas
    @example Click_TempHum8_TIVA.mbas
    @example Click_TempHum8_CEC.mbas
    @example Click_TempHum8_KINETIS.mbas
    @example Click_TempHum8_MSP.mbas
    @example Click_TempHum8_PIC.mbas
    @example Click_TempHum8_PIC32.mbas
    @example Click_TempHum8_DSPIC.mbas
    @example Click_TempHum8_AVR.mbas
    @example Click_TempHum8_FT90x.mbas
    @example Click_TempHum8_STM.mpas
    @example Click_TempHum8_TIVA.mpas
    @example Click_TempHum8_CEC.mpas
    @example Click_TempHum8_KINETIS.mpas
    @example Click_TempHum8_MSP.mpas
    @example Click_TempHum8_PIC.mpas
    @example Click_TempHum8_PIC32.mpas
    @example Click_TempHum8_DSPIC.mpas
    @example Click_TempHum8_AVR.mpas
    @example Click_TempHum8_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __temphum8_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */