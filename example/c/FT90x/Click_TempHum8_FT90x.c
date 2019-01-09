/*
Example for TempHum8 Click

    Date          : nov 2018.
    Author        : Katarina Perendic

Test configuration FT90x :
    
    MCU                : FT900
    Dev. Board         : EasyFT90x v7 
    FT90x Compiler ver : v2.3.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initialization driver init, chip reset and default configuration;
- Application Task - (code snippet) - Reads Temperature and Huminidy data and this data logs to USBUART every 1sec.

*/

#include "Click_TempHum8_types.h"
#include "Click_TempHum8_config.h"

void systemInit()
{
    Delay_ms( 20 );
    
    mikrobus_i2cInit( _MIKROBUS1, &_TEMPHUM8_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART, 9600 );
    mikrobus_logWrite("--- System init ---", _LOG_LINE);
    Delay_ms( 100 );
}

void applicationInit()
{
    temphum8_i2cDriverInit( (T_TEMPHUM8_P)&_MIKROBUS1_GPIO, (T_TEMPHUM8_P)&_MIKROBUS1_I2C, 0x40 );
    temphum8_softReset();
    temphum8_configuration(_TEMPHUM8_CFG_RESOLUTION_H12_T14 | _TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER | _TEMPHUM8_CFG_DISABLE_OTP_RELOAD);
}

void applicationTask()
{
    float Temperature;
    float Humidity;
    char demoText[ 50 ];
    
    Temperature = temphum8_getTemperature(_TEMPHUM8_TEMPERATURE_IN_CELSIUS);
    FloatToStr(Temperature, demoText);
    mikrobus_logWrite(" Temperature : ", _LOG_TEXT);
    mikrobus_logWrite(demoText, _LOG_TEXT);
    mikrobus_logWrite(" C", _LOG_LINE);
    
    Humidity = temphum8_getHumidity();
    FloatToStr(Humidity, demoText);
    mikrobus_logWrite(" Humidity    : ", _LOG_TEXT);
    mikrobus_logWrite(demoText, _LOG_TEXT);
    mikrobus_logWrite(" RH", _LOG_LINE);
    
    mikrobus_logWrite(" ---------------------- ", _LOG_LINE);
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}