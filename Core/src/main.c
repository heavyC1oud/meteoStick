
#include <stddef.h>
#include "stm32f0xx.h"
#include "delay.h"
#include "pwm.h"
#include "led.h"
#include "tsc.h"
#include "i2c.h"
#include "bme280.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "main.h"


void taskGetMeas(void *pvParameters);
void taskTouchKeyHandler(void *pvParameters);
void taskMain(void *pvParameters);

/*********************************************************************/

/*************************	VARIABLE	******************************/
struct bme280_dev sensor = {0};
struct bme280_data sensorData = {0};
TOUCH_STATE_typedef tKeyState = {0};
MODE_typedef mode = MODE_OFF;

TimerHandle_t timer;

/*************************	FUNCTION	******************************/

/**********************************************************************
*	function name	:	initBME280
*	Description		:	BME280 initialization
*	Arguments		:	none
*	Return value	:	API success code
**********************************************************************/
int initBME280(void)
{
	uint8_t measureSet = 0;
	int8_t rslt = BME280_OK;

	sensor.dev_id = (BME280_I2C_ADDR_PRIM << 1);
	sensor.intf = BME280_I2C_INTF;
	sensor.read = I2CRead;
	sensor.write = I2CWrite;
	sensor.delay_ms = delayMs;

	rslt = bme280_init(&sensor);

	//	set the temperature, pressure and humidity settings
	sensor.settings.osr_h = BME280_OVERSAMPLING_1X;
	sensor.settings.osr_p = BME280_OVERSAMPLING_16X;
	sensor.settings.osr_t = BME280_OVERSAMPLING_2X;
	sensor.settings.filter = BME280_FILTER_COEFF_16;
	sensor.settings.standby_time = BME280_STANDBY_TIME_125_MS;

	// set the required sensor settings needed
	measureSet = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

	//	set the desired sensor configuration
	rslt = bme280_set_sensor_settings(measureSet, &sensor);

	//	set sensor mode
	bme280_set_sensor_mode(BME280_NORMAL_MODE, &sensor);

	return rslt;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setMode
*	Description		:	operation mode selection
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void setMode(void)
{
	if(tKeyState.shortTouch == SET) {
		switch(mode) {
		case MODE_OFF:
			mode = MODE_TEMP;

			break;
		case MODE_TEMP:
			mode = MODE_HUM;

			break;
		case MODE_HUM:
			mode = MODE_BAR;

			break;
		case MODE_BAR:
			mode = MODE_TEMP;

			break;
		default:
			break;
		}

		tKeyState.shortTouch = RESET;
	}
	else if(tKeyState.longTouch == SET) {
		mode = MODE_GAME;

		tKeyState.longTouch = RESET;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	main
*	Description		:	main function
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
//void (*TimerCallbackFunction_t)( TimerHandle_t xTimer );


/**********************************************************************
*	function name	:	main
*	Description		:	main function
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
int main(void)
{
	initLED();
	initDelayTimer();
	initPWMTimer();
	initI2C();
	initBME280();
	initTSC();

	xTaskCreate(taskGetMeas, "GET MEAS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(taskTouchKeyHandler, "TOUCH HANDLER", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(taskMain, "MAIN", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

//	timer = xTimerCreate("SLEEP TIMER", pdMS_TO_TICKS(6000), pdFalse, (void*)0, pxCallbackFunction);


	vTaskStartScheduler();

	while(1);

}


void taskGetMeas(void *pvParameters)
{
	while(1) {
		bme280_get_sensor_data(BME280_ALL, &sensorData, &sensor);
		vTaskDelay(SENSOR_POLL_FR);
	}
}

void taskTouchKeyHandler(void *pvParameters)
{
	//	reset structure
	tKeyState.curState = TSC_CHANNEL_EMPTY;
	tKeyState.prevState = TSC_CHANNEL_EMPTY;
	tKeyState.shortTouch = RESET;
	tKeyState.longTouch = RESET;
	tKeyState.longTouchOnce = RESET;
	tKeyState.longTouchTimer = 0;

	//	touch key handling
	while(1) {
		//	read current touch key state
		tKeyState.curState = touchKey;

		//	push key detect
		if((tKeyState.curState == TSC_CHANNEL_DETECT) && (tKeyState.prevState == TSC_CHANNEL_EMPTY)) {
			tKeyState.longTouchTimer++;
		}
		//	release key detect
		else if((tKeyState.curState == TSC_CHANNEL_EMPTY) && (tKeyState.prevState == TSC_CHANNEL_DETECT)) {
			//	short touch detect
			if(tKeyState.longTouchTimer <= LONG_TOUCH_MAX_TIMER) {
				tKeyState.shortTouch = SET;
			}

			tKeyState.longTouchOnce = RESET;		//	re-triggering avoid
			tKeyState.longTouchTimer = 0;
		}
		//	hold key detect
		else if((tKeyState.curState == TSC_CHANNEL_DETECT) && (tKeyState.prevState == TSC_CHANNEL_DETECT)) {
			tKeyState.longTouchTimer++;

			//	long touch detect
			if((tKeyState.longTouchTimer > LONG_TOUCH_MAX_TIMER) && (tKeyState.longTouchOnce == RESET)) {
				tKeyState.longTouchOnce = SET;		//	re-triggering avoid
				tKeyState.longTouch = SET;
			}
		}

		tKeyState.prevState = tKeyState.curState;

		//	 possible bounce avoid
		vTaskDelay(TOUCH_POLL_FR);
	}
}

void taskMain(void *pvParameters)
{
	while(1) {
		setMode();

		switch(mode) {
		case MODE_TEMP:
			setLedInfo(LED_TEMP, LED_ON);
			setLedInfo(LED_HUM, LED_OFF);
			setLedInfo(LED_BAR, LED_OFF);

			setDispNumSmooth((uint32_t)sensorData.temperature);

			break;
		case MODE_HUM:
			setLedInfo(LED_TEMP, LED_OFF);
			setLedInfo(LED_HUM, LED_ON);
			setLedInfo(LED_BAR, LED_OFF);

			setDispNumSmooth((uint32_t)sensorData.humidity);

			break;
		case MODE_BAR:
			setLedInfo(LED_TEMP, LED_OFF);
			setLedInfo(LED_HUM, LED_OFF);
			setLedInfo(LED_BAR, LED_ON);

			setDispNumSmooth((uint32_t)sensorData.pressure);

			break;
		default:
			break;
		}
	}
}

