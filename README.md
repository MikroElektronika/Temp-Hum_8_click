![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# TempHum8 Click

- **CIC Prefix**  : TEMPHUM8
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : nov 2018.

---

### Software Support

We provide a library for the TempHum8 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2656/temp-hum-8-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library initializes and defines the I2C bus driver and drivers that offer a choice for writing data in register and reads data form register.
The library includes function for read Temperature and Relative Huminidy data and function for read/write data to user register.
The user also has the function for default configuration device for measurement and function for device software reset.

Key functions :

- ``` float temphum8_getTemperature(uint8_t tempIn) ``` - Functions for read Temperature data
- ``` float temphum8_getHumidity() ``` - Functions for read Relative Huminidy data
- ``` void temphum8_configuration(uint8_t cfg) ``` - Functions for configuration device for measurement

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initialization driver init, chip reset and default configuration;
- Application Task - (code snippet) - Reads Temperature and Huminidy data and this data logs to USBUART every 1sec.

```.c
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2656/temp-hum-8-click) page.

Other mikroE Libraries used in the example:

- I2C

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
