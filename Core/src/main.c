
#include <stddef.h>
#include "stm32f0xx.h"
#include "interrupt.h"
#include "delay.h"
#include "led.h"
#include "tsc.h"
#include "i2c.h"
#include "bme280.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"


void taskLED(void *pvParameters);

/*********************************************************************/

/*************************	VARIABLE	******************************/
struct bme280_dev sensor;
struct bme280_data sensorData;


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
	sensor.delay_ms = vTaskDelay;

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
//	initI2C();
//	initBME280();
	initTSC();
	initIT();

	while(1) {
		switchInfoLed(LED_TEMP, LED_ON);
		vTaskDelay(500);
		switchInfoLed(LED_TEMP, LED_OFF);
		vTaskDelay(500);
	}

	xTaskCreate(taskLED, "LED", 128, NULL, 1, NULL);

	vTaskStartScheduler();



	while(1) {
		if(touchAlert == TSC_CHANNEL_DETECT) {
			bme280_get_sensor_data(BME280_ALL, &sensorData, &sensor);

			switchInfoLed(LED_TEMP, LED_ON);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_OFF);
			showNumber((uint32_t)sensorData.temperature);

			delayMs(2000);

			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_ON);
			switchInfoLed(LED_BAR, LED_OFF);
			showNumber((uint32_t)sensorData.humidity);

			delayMs(2000);

			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_ON);


			double fPressure = 0;
			fPressure = sensorData.pressure;
			fPressure /= 133.322;
			fPressure =(uint32_t)fPressure % 700;
			showNumber((uint32_t)fPressure);

			delayMs(2000);

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

		delayMs(10);
	}
}

//*********************************************************************
void taskLED(void *pvParameters)
{
	while(1) {
		if(touchAlert == TSC_CHANNEL_DETECT) {
			bme280_get_sensor_data(BME280_ALL, &sensorData, &sensor);

			switchInfoLed(LED_TEMP, LED_ON);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_OFF);
			showNumber((uint32_t)sensorData.temperature);

			vTaskDelay(2000);

			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_ON);
			switchInfoLed(LED_BAR, LED_OFF);
			showNumber((uint32_t)sensorData.humidity);

			vTaskDelay(2000);

			switchInfoLed(LED_TEMP, LED_OFF);
			switchInfoLed(LED_HUM, LED_OFF);
			switchInfoLed(LED_BAR, LED_ON);


			double fPressure = 0;
			fPressure = sensorData.pressure;
			fPressure /= 133.322;
			fPressure =(uint32_t)fPressure % 700;
			showNumber((uint32_t)fPressure);

			vTaskDelay(2000);

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
