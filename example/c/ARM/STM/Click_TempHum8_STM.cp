#line 1 "D:/Clicks_git/T/Temp-Hum_8_Click/SW/example/c/ARM/STM/Click_TempHum8_STM.c"
#line 1 "d:/clicks_git/t/temp-hum_8_click/sw/example/c/arm/stm/click_temphum8_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "d:/clicks_git/t/temp-hum_8_click/sw/example/c/arm/stm/click_temphum8_config.h"
#line 1 "d:/clicks_git/t/temp-hum_8_click/sw/example/c/arm/stm/click_temphum8_types.h"
#line 19 "d:/clicks_git/t/temp-hum_8_click/sw/example/c/arm/stm/click_temphum8_config.h"
const uint32_t _TEMPHUM8_I2C_CFG[ 1 ] =
{
 100000
};
#line 1 "d:/clicks_git/t/temp-hum_8_click/sw/library/__temphum8_driver.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 58 "d:/clicks_git/t/temp-hum_8_click/sw/library/__temphum8_driver.h"
extern const uint8_t _TEMPHUM8_TEMP_MEASUREMENT_HOLD_MODE ;
extern const uint8_t _TEMPHUM8_HUM_MEASUREMENT_HOLD_MODE ;
extern const uint8_t _TEMPHUM8_TEMP_MEASUREMENT_NO_HOLD_MODE ;
extern const uint8_t _TEMPHUM8_HUM_MEASUREMENT_NO_HOLD_MODE ;
extern const uint8_t _TEMPHUM8_USER_REGISTER_WRITE ;
extern const uint8_t _TEMPHUM8_USER_REGISTER_READ ;
extern const uint8_t _TEMPHUM8_SOFT_RESET ;


extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H12_T14 ;
extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H8_T12 ;
extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H10_T13 ;
extern const uint8_t _TEMPHUM8_CFG_RESOLUTION_H11_T11 ;
extern const uint8_t _TEMPHUM8_CFG_END_OF_BATTERY_LESS_THAN_2_25V ;
extern const uint8_t _TEMPHUM8_CFG_END_OF_BATTERY_BIGGER_THAN_2_25V ;
extern const uint8_t _TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER ;
extern const uint8_t _TEMPHUM8_CFG_DISABLE_OTP_RELOAD ;

extern const uint8_t _TEMPHUM8_DEVICE_SLAVE_ADDRESS;


extern const uint8_t _TEMPHUM8_TEMPERATURE_IN_CELSIUS ;
extern const uint8_t _TEMPHUM8_TEMPERATURE_IN_KELVIN ;
extern const uint8_t _TEMPHUM8_TEMPERATURE_IN_FARENHAJT ;
#line 94 "d:/clicks_git/t/temp-hum_8_click/sw/library/__temphum8_driver.h"
void temphum8_i2cDriverInit( const uint8_t*  gpioObj,  const uint8_t*  i2cObj, uint8_t slave);
#line 101 "d:/clicks_git/t/temp-hum_8_click/sw/library/__temphum8_driver.h"
void temphum8_gpioDriverInit( const uint8_t*  gpioObj);




void temphum8_softReset();

float temphum8_getHumidity();

uint8_t temphum8_readUserRegister();

void temphum8_writeUserRegister(uint8_t _data);

void temphum8_configuration(uint8_t cfg);

float temphum8_getTemperature(uint8_t tempIn);
#line 30 "D:/Clicks_git/T/Temp-Hum_8_Click/SW/example/c/ARM/STM/Click_TempHum8_STM.c"
void systemInit()
{
 Delay_ms( 20 );

 mikrobus_i2cInit( _MIKROBUS1, &_TEMPHUM8_I2C_CFG[0] );
 mikrobus_logInit( _LOG_USBUART_A, 9600 );
 mikrobus_logWrite("--- System init ---", _LOG_LINE);
 Delay_ms( 100 );
}

void applicationInit()
{
 temphum8_i2cDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_I2C, 0x40 );
 temphum8_softReset();
 temphum8_configuration(_TEMPHUM8_CFG_RESOLUTION_H12_T14 | _TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER | _TEMPHUM8_CFG_DISABLE_OTP_RELOAD);
}

void applicationTask()
{
 float Temperature;
 float Humidity;
 char demoText[ 50 ];

 Temperature = temphum8_getTemperature(_TEMPHUM8_TEMPERATURE_IN_FARENHAJT);
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
