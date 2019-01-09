_systemInit:
;Click_TempHum8_STM.c,30 :: 		void systemInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_TempHum8_STM.c,32 :: 		Delay_ms( 20 );
MOVW	R7, #43391
MOVT	R7, #3
NOP
NOP
L_systemInit0:
SUBS	R7, R7, #1
BNE	L_systemInit0
NOP
NOP
NOP
;Click_TempHum8_STM.c,34 :: 		mikrobus_i2cInit( _MIKROBUS1, &_TEMPHUM8_I2C_CFG[0] );
MOVW	R0, #lo_addr(__TEMPHUM8_I2C_CFG+0)
MOVT	R0, #hi_addr(__TEMPHUM8_I2C_CFG+0)
MOV	R1, R0
MOVS	R0, #0
BL	_mikrobus_i2cInit+0
;Click_TempHum8_STM.c,35 :: 		mikrobus_logInit( _LOG_USBUART_A, 9600 );
MOVW	R1, #9600
MOVS	R0, #32
BL	_mikrobus_logInit+0
;Click_TempHum8_STM.c,36 :: 		mikrobus_logWrite("--- System init ---", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr1_Click_TempHum8_STM+0)
MOVT	R0, #hi_addr(?lstr1_Click_TempHum8_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,37 :: 		Delay_ms( 100 );
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_systemInit2:
SUBS	R7, R7, #1
BNE	L_systemInit2
NOP
NOP
NOP
;Click_TempHum8_STM.c,38 :: 		}
L_end_systemInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _systemInit
_applicationInit:
;Click_TempHum8_STM.c,40 :: 		void applicationInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_TempHum8_STM.c,42 :: 		temphum8_i2cDriverInit( (T_TEMPHUM8_P)&_MIKROBUS1_GPIO, (T_TEMPHUM8_P)&_MIKROBUS1_I2C, 0x40 );
MOVS	R2, #64
MOVW	R1, #lo_addr(__MIKROBUS1_I2C+0)
MOVT	R1, #hi_addr(__MIKROBUS1_I2C+0)
MOVW	R0, #lo_addr(__MIKROBUS1_GPIO+0)
MOVT	R0, #hi_addr(__MIKROBUS1_GPIO+0)
BL	_temphum8_i2cDriverInit+0
;Click_TempHum8_STM.c,43 :: 		temphum8_softReset();
BL	_temphum8_softReset+0
;Click_TempHum8_STM.c,44 :: 		temphum8_configuration(_TEMPHUM8_CFG_RESOLUTION_H12_T14 | _TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER | _TEMPHUM8_CFG_DISABLE_OTP_RELOAD);
MOVS	R0, __TEMPHUM8_CFG_RESOLUTION_H12_T14
ORR	R0, R0, __TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER
UXTB	R0, R0
ORR	R0, R0, __TEMPHUM8_CFG_DISABLE_OTP_RELOAD
BL	_temphum8_configuration+0
;Click_TempHum8_STM.c,45 :: 		}
L_end_applicationInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationInit
_applicationTask:
;Click_TempHum8_STM.c,47 :: 		void applicationTask()
SUB	SP, SP, #56
STR	LR, [SP, #0]
;Click_TempHum8_STM.c,53 :: 		Temperature = temphum8_getTemperature(_TEMPHUM8_TEMPERATURE_IN_FARENHAJT);
MOVS	R0, __TEMPHUM8_TEMPERATURE_IN_FARENHAJT
BL	_temphum8_getTemperature+0
;Click_TempHum8_STM.c,54 :: 		FloatToStr(Temperature, demoText);
ADD	R1, SP, #4
BL	_FloatToStr+0
;Click_TempHum8_STM.c,55 :: 		mikrobus_logWrite(" Temperature : ", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr2_Click_TempHum8_STM+0)
MOVT	R0, #hi_addr(?lstr2_Click_TempHum8_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,56 :: 		mikrobus_logWrite(demoText, _LOG_TEXT);
ADD	R0, SP, #4
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,57 :: 		mikrobus_logWrite(" C", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr3_Click_TempHum8_STM+0)
MOVT	R0, #hi_addr(?lstr3_Click_TempHum8_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,59 :: 		Humidity = temphum8_getHumidity();
BL	_temphum8_getHumidity+0
;Click_TempHum8_STM.c,60 :: 		FloatToStr(Humidity, demoText);
ADD	R1, SP, #4
BL	_FloatToStr+0
;Click_TempHum8_STM.c,61 :: 		mikrobus_logWrite(" Humidity    : ", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr4_Click_TempHum8_STM+0)
MOVT	R0, #hi_addr(?lstr4_Click_TempHum8_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,62 :: 		mikrobus_logWrite(demoText, _LOG_TEXT);
ADD	R0, SP, #4
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,63 :: 		mikrobus_logWrite(" RH", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr5_Click_TempHum8_STM+0)
MOVT	R0, #hi_addr(?lstr5_Click_TempHum8_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,65 :: 		mikrobus_logWrite(" ---------------------- ", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr6_Click_TempHum8_STM+0)
MOVT	R0, #hi_addr(?lstr6_Click_TempHum8_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum8_STM.c,66 :: 		Delay_ms( 1000 );
MOVW	R7, #6911
MOVT	R7, #183
NOP
NOP
L_applicationTask4:
SUBS	R7, R7, #1
BNE	L_applicationTask4
NOP
NOP
NOP
;Click_TempHum8_STM.c,67 :: 		}
L_end_applicationTask:
LDR	LR, [SP, #0]
ADD	SP, SP, #56
BX	LR
; end of _applicationTask
_main:
;Click_TempHum8_STM.c,69 :: 		void main()
SUB	SP, SP, #4
;Click_TempHum8_STM.c,71 :: 		systemInit();
BL	_systemInit+0
;Click_TempHum8_STM.c,72 :: 		applicationInit();
BL	_applicationInit+0
;Click_TempHum8_STM.c,74 :: 		while (1)
L_main6:
;Click_TempHum8_STM.c,76 :: 		applicationTask();
BL	_applicationTask+0
;Click_TempHum8_STM.c,77 :: 		}
IT	AL
BAL	L_main6
;Click_TempHum8_STM.c,78 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
