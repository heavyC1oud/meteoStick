
#include <stddef.h>
#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "tsc.h"
#include "i2c.h"
#include "bme280.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"


void taskLED(void *pvParameters);
void taskGetMeas(void *pvParameters);
void taskTouchHandler(void *pvParameters);
void taskRTOS(void *pvParameters);

/*********************************************************************/

/*************************	VARIABLE	******************************/
struct bme280_dev sensor = {0};
struct bme280_data sensorData = {0};
TOUCH_STATE_typedef tKeyState = {0};


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
*	function name	:	main
*	Description		:	main function
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
int main(void)
{
	initLED();
	initDelayTimer();
	initI2C();
	initBME280();
	initTSC();

	xTaskCreate(taskGetMeas, "GET MEAS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(taskTouchHandler, "TOUCH HANDLER", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(taskRTOS, "TASK RTOS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);


//	xTaskCreate(taskLED, "LED", 128, NULL, 1, NULL);

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

void taskTouchHandler(void *pvParameters)
{
	tKeyState.curState = TSC_CHANNEL_EMPTY;
	tKeyState.prevState = TSC_CHANNEL_EMPTY;
	tKeyState.shortTouch = RESET;
	tKeyState.longTouch = RESET;
	tKeyState.longTouchTimer = 0;

	while(1) {
		tKeyState.curState = touchKey;

		if((tKeyState.curState == TSC_CHANNEL_DETECT) && (tKeyState.prevState == TSC_CHANNEL_EMPTY)) {
			tKeyState.longTouchTimer++;
		}
		else if((tKeyState.curState == TSC_CHANNEL_EMPTY) && (tKeyState.prevState == TSC_CHANNEL_DETECT)) {
			if(tKeyState.longTouchTimer <= LONG_TOUCH_MAX_TIMER) {
				tKeyState.shortTouch = SET;
			}

			tKeyState.longTouchTimer = 0;
		}
		else if((tKeyState.curState == TSC_CHANNEL_DETECT) && (tKeyState.prevState == TSC_CHANNEL_DETECT)) {
			tKeyState.longTouchTimer++;

			if(tKeyState.longTouchTimer > LONG_TOUCH_MAX_TIMER) {
				tKeyState.longTouch = SET;
			}
		}

		tKeyState.prevState = tKeyState.curState;

		vTaskDelay(TOUCH_POLL_FR);
	}
}

void taskRTOS(void *pvParameters)
{
	while(1) {
		if(tKeyState.longTouch == SET) {
			switchInfoLed(LED_BAR, LED_ON);
			vTaskDelay(1000);

			switchInfoLed(LED_BAR, LED_OFF);
			tKeyState.longTouch = RESET;
		}

		if(tKeyState.shortTouch == SET) {
			switchInfoLed(LED_TEMP, LED_ON);
			vTaskDelay(10);

			switchInfoLed(LED_TEMP, LED_OFF);
			tKeyState.shortTouch = RESET;
		}

		taskYIELD();
	}
}


//*********************************************************************
void taskLED(void *pvParameters)
{
	while(1) {
		if(touchKey == TSC_CHANNEL_DETECT) {
			bme280_get_sensor_data(BME280_ALL, &sensorData, &sensor);

			switchInfoLed(LED_TEMP, LED_ON);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_OFF);
			showNumber((uint32_t)sensorData.temperature);

			vTaskDelay(500);

			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_ON);
			switchInfoLed(LED_BAR, LED_OFF);
			showNumber((uint32_t)sensorData.humidity);

			vTaskDelay(500);

			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_ON);


			double fPressure = 0;
			fPressure = sensorData.pressure;
			fPressure /= 133.322;
			fPressure =(uint32_t)fPressure % 700;
			showNumber((uint32_t)fPressure);

			vTaskDelay(500);

			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_OFF);
			turnOffDisp();
		}
		else {
			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_OFF);
		}

		vTaskDelay(10);
	}
}
