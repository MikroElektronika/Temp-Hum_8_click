/*
    __temphum8_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__temphum8_driver.h"
#include "__temphum8_hal.c"

/* ------------------------------------------------------------------- MACROS */

/* Commands */
const uint8_t _TEMPHUM8_TEMP_MEASUREMENT_HOLD_MODE    = 0xE3;
const uint8_t _TEMPHUM8_HUM_MEASUREMENT_HOLD_MODE     = 0xE5;
const uint8_t _TEMPHUM8_TEMP_MEASUREMENT_NO_HOLD_MODE = 0xF3;
const uint8_t _TEMPHUM8_HUM_MEASUREMENT_NO_HOLD_MODE  = 0xF5;
const uint8_t _TEMPHUM8_USER_REGISTER_WRITE           = 0xE6;
const uint8_t _TEMPHUM8_USER_REGISTER_READ            = 0xE7;
const uint8_t _TEMPHUM8_SOFT_RESET                    = 0xFE;

/* user register */
const uint8_t _TEMPHUM8_CFG_RESOLUTION_H12_T14               = 0x00;
const uint8_t _TEMPHUM8_CFG_RESOLUTION_H8_T12                = 0x01;
const uint8_t _TEMPHUM8_CFG_RESOLUTION_H10_T13               = 0x80;
const uint8_t _TEMPHUM8_CFG_RESOLUTION_H11_T11               = 0x81;
const uint8_t _TEMPHUM8_CFG_END_OF_BATTERY_LESS_THAN_2_25V   = 0x40;
const uint8_t _TEMPHUM8_CFG_END_OF_BATTERY_BIGGER_THAN_2_25V = 0x00;
const uint8_t _TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER            = 0x00;
const uint8_t _TEMPHUM8_CFG_DISABLE_OTP_RELOAD               = 0x02;

const uint8_t _TEMPHUM8_DEVICE_SLAVE_ADDRESS = 0x40;

/* Temperature data in ... */
const uint8_t _TEMPHUM8_TEMPERATURE_IN_CELSIUS   = 0x00;
const uint8_t _TEMPHUM8_TEMPERATURE_IN_KELVIN    = 0x01;
const uint8_t _TEMPHUM8_TEMPERATURE_IN_FARENHAJT = 0x02;

/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __TEMPHUM8_DRV_I2C__
static uint8_t _slaveAddress;
#endif

static const uint16_t _ON_8  = 256  ;
static const uint16_t _ON_10 = 1024 ;
static const uint16_t _ON_11 = 2048 ;
static const uint16_t _ON_12 = 4096 ;
static const uint16_t _ON_13 = 8192 ;
static const uint16_t _ON_14 = 16384;

static uint16_t POLYNOMIAL = 0x131;  // P(x)=x^8+x^5+x^4+1 = 100110001
static uint8_t _dataResolution = 0;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint8_t _CRC8 (uint8_t *inData, uint8_t nBytes, uint8_t checksum);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint8_t _CRC8 (uint8_t *inData, uint8_t nBytes, uint8_t checksum)
{
    uint8_t crc = 0;
    uint8_t byteCtr;
    uint8_t nBit;

    for (byteCtr = 0; byteCtr < nBytes; ++byteCtr)
    {
        crc ^= (inData[byteCtr]);
        for ( nBit = 8; nBit > 0; --nBit)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ POLYNOMIAL;
            }
            else
            {
                crc = (crc << 1);
            }
        }
    }
    if (crc != checksum)
    {
        return 1;
    }
    return 0;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __TEMPHUM8_DRV_SPI__

void temphum8_spiDriverInit(T_TEMPHUM8_P gpioObj, T_TEMPHUM8_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __TEMPHUM8_DRV_I2C__

void temphum8_i2cDriverInit(T_TEMPHUM8_P gpioObj, T_TEMPHUM8_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __TEMPHUM8_DRV_UART__

void temphum8_uartDriverInit(T_TEMPHUM8_P gpioObj, T_TEMPHUM8_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

void temphum8_writeUserRegister(uint8_t _data)
{
    uint8_t writeData[ 3 ];

    writeData[ 0 ] = _TEMPHUM8_USER_REGISTER_WRITE;
    writeData[ 1 ] = _data;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeData, 2, END_MODE_STOP);
}

uint8_t temphum8_readUserRegister()
{
    uint8_t error = 0;
    uint8_t writeData[ 2 ];
    uint8_t readData[ 2 ];
  
    writeData[ 0 ] = _TEMPHUM8_USER_REGISTER_READ;
  
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeData, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, readData, 2, END_MODE_STOP);
  
    error = _CRC8 (&readData[0],1,readData[1]);

    return readData[0];
}

void temphum8_softReset()
{
    uint8_t cmdReset;
    cmdReset = _TEMPHUM8_SOFT_RESET;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, &cmdReset, 1, END_MODE_STOP);
    Delay_100ms();
}

void temphum8_configuration(uint8_t cfg)
{
    uint8_t dataWrite;
    
    dataWrite = 0x3A | cfg;
    temphum8_writeUserRegister(dataWrite);
    
    if((cfg & _TEMPHUM8_CFG_RESOLUTION_H8_T12) != 0)
    {
        _dataResolution = 1;
    }
    else if ((cfg & _TEMPHUM8_CFG_RESOLUTION_H10_T13) != 0)
    {
        _dataResolution = 2;
    }
    else if ((cfg & _TEMPHUM8_CFG_RESOLUTION_H11_T11) != 0)
    {
        _dataResolution = 3;
    }
    else
    {
        _dataResolution = 0;
    }
}

float temphum8_getTemperature(uint8_t tempIn)
{
    uint16_t TempData;
    float Temperature;
    uint16_t _res;
    uint8_t command;
    uint8_t readData[ 3 ];

    command = _TEMPHUM8_TEMP_MEASUREMENT_HOLD_MODE;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, &command, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, readData, 3, END_MODE_STOP);
    
    TempData = (readData[0] << 8);
    TempData |= readData[1];

    if(_CRC8(readData,2,readData[2])) 
    {
        temphum8_softReset();
        return 1;
    }
    
    if(_dataResolution == 0)
    {
        TempData = (TempData >> 2);
        _res = _ON_14;
    }
    else if(_dataResolution == 1)
    {
        TempData = (TempData >> 4);
        _res = _ON_12;
    }
    else if (_dataResolution == 2)
    {
        TempData = (TempData >> 3);
        _res = _ON_13;
    }
    else
    {
        TempData = (TempData >> 5);
        _res = _ON_11;
    }
    
    Temperature = (-46.85 + 175.72/_res * (float)TempData);
    
    if(tempIn == _TEMPHUM8_TEMPERATURE_IN_FARENHAJT)
    {
        return Temperature * 9/5 + 32;
    }
    else if(tempIn == _TEMPHUM8_TEMPERATURE_IN_KELVIN)
    {
        return Temperature + 273.15;
    }

    return Temperature;
}

float temphum8_getHumidity()
{
    uint8_t crc;
    uint16_t HumData;
    uint16_t _res;
    uint8_t command;
    uint8_t readData[ 3 ];

    command = _TEMPHUM8_HUM_MEASUREMENT_HOLD_MODE;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, &command, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, readData, 3, END_MODE_STOP);

    HumData = (readData[0] << 8);
    HumData |= readData[1];

    if(_CRC8(readData,2,readData[2]))
    {
        temphum8_softReset();
        return 1;
    }
    
    if(_dataResolution == 0)
    {
        HumData = HumData >> 4;
        _res = _ON_12;
    }
    else if(_dataResolution == 1)
    {
        HumData = HumData >> 8;
        _res = _ON_8;
    }
    else if (_dataResolution == 2)
    {
        HumData = HumData >> 6;
        _res = _ON_10;
    }
    else
    {
        HumData = HumData >> 5;
        _res = _ON_11;
    }
        
    return (-6.0 + 125.0/_res * (float)HumData);
}

/* -------------------------------------------------------------------------- */
/*
  __temphum8_driver.c

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