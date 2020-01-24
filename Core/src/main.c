
#include <stddef.h>
#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "tsc.h"
#include "i2c.h"
#include "bme280.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "main.h"

//	FreeRTOS tasks
void taskGetMeas(void *pvParameters);
void taskTouchKeyHandler(void *pvParameters);
void taskDisplayData(void *pvParameters);
void taskRefreshWDT(void *pvParameters);

/*********************************************************************/

/*************************	VARIABLE	******************************/
struct bme280_dev sensor = {0};
struct bme280_data sensorData = {0};
TOUCH_STATE_typedef tKeyState = {0};
MODE_typedef mode = MODE_OFF;
TimerHandle_t sleepTimer;

/*************************	FUNCTION	******************************/

/**********************************************************************
*	function name	:	initUnusedPins
*	Description		:	set unused pins to input with pull-down
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void initUnusedPins(void)
{
	//	unused GPIO set as general purpose input with pull-down

	//	PORTA[8, 9, 10, 15]
	GPIOA->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9 | GPIO_MODER_MODER10 | GPIO_MODER_MODER15);

	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9 | GPIO_PUPDR_PUPDR10 | GPIO_PUPDR_PUPDR15);
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1 | GPIO_PUPDR_PUPDR10_1 | GPIO_PUPDR_PUPDR15_1;

	//	PORTB[5, 8, 9]
	GPIOB->MODER &= ~(GPIO_MODER_MODER5 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9);

	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR5 | GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR5_1 | GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1;

	//	PORTC[13, 14, 15]
	GPIOC->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER14 | GPIO_MODER_MODER15);

	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR13 | GPIO_PUPDR_PUPDR14 | GPIO_PUPDR_PUPDR15);
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR13_1 | GPIO_PUPDR_PUPDR14_1 | GPIO_PUPDR_PUPDR15_1;

	//	PORTF[0, 1]
	GPIOF->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);

	GPIOF->PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1);
	GPIOF->PUPDR |= GPIO_PUPDR_PUPDR0_1 | GPIO_PUPDR_PUPDR1_1;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	initWDG
*	Description		:	watch dog timer initialization
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void initWDG(void)
{
	RCC->CSR |= RCC_CSR_LSION;						//	LSI oscillator ON
	while((RCC->CSR & RCC_CSR_LSIRDY) == RESET);	//	wait until LSI oscillator is stable


	IWDG->KR = IWDG_START;							//	enable the IWDG
	IWDG->KR = IWDG_WRITE_ACCESS;					//	enable register access
	while(IWDG->SR);								//	wait to the registers to be updated


	IWDG->PR = IWDG_PRESCALER_256;					//	write IWDG prescaler
	IWDG->RLR = IWDG_COUNT_VALUE_4_S;				//	write reload register
	while(IWDG->SR);								//	wait to the registers to be updated

	IWDG->KR = IWDG_REFRESH;						//	refresh the counter value
}
/*********************************************************************/


/**********************************************************************
*	function name	:	timerCB
*	Description		:	timer callback function
*	Arguments		:	xTimer - software timer instance
*	Return value	:	none
**********************************************************************/
void timerCB(TimerHandle_t xTimer)
{
	mode = MODE_OFF;
}
/*********************************************************************/


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
	//	short touch handler
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

		//	reset sleep timer
		xTimerStart(sleepTimer, portMAX_DELAY);
	}
	//	long touch handler
	else if(tKeyState.longTouch == SET) {
		mode = MODE_OFF;

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
int main(void)
{
	//	peripheral initialization
	initUnusedPins();
	initWDG();
	initLed();
	initDelayTimer();
	initI2C();
	initBME280();
	initTSC();

	//	create FreeRTOS task
	xTaskCreate(taskGetMeas, "GET MEAS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(taskTouchKeyHandler, "TOUCH HANDLER", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(taskDisplayData, "MAIN", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(taskRefreshWDT, "REFRESH_WDT", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	//	create FreeRTOS timer
	sleepTimer = xTimerCreate("SLEEP TIMER", pdMS_TO_TICKS(TURN_OFF_TIMER_DELAY), pdFALSE, (void*)0, timerCB);

	//	start FreeRTOS scheduler
	vTaskStartScheduler();

	//	program never run here
	while(1);
}
/*********************************************************************/


/**********************************************************************
*	function name	:	taskRefreshWDT
*	Description		:	FreeRTOS task, clear IWDT
*	Arguments		:	*pvParameters - unused
*	Return value	:	none
**********************************************************************/
void taskRefreshWDT(void *pvParameters)
{
	while(1) {
		IWDG->KR = IWDG_REFRESH;						//	refresh the counter value
		vTaskDelay(IWDT_REFRESH_DELAY);
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	taskGetMeas
*	Description		:	FreeRTOS task, refresh sensor data
*	Arguments		:	*pvParameters - unused
*	Return value	:	none
**********************************************************************/
void taskGetMeas(void *pvParameters)
{
	while(1) {
		bme280_get_sensor_data(BME280_ALL, &sensorData, &sensor);
		vTaskDelay(SENSOR_POLL_FR);
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	taskTouchKeyHandler
*	Description		:	FreeRTOS task, touch button processing
*	Arguments		:	*pvParameters - unused
*	Return value	:	none
**********************************************************************/
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
/*********************************************************************/


/**********************************************************************
*	function name	:	taskDisplayData
*	Description		:	FreeRTOS task, show sensor data on display and info LED processing
*	Arguments		:	*pvParameters - unused
*	Return value	:	none
**********************************************************************/
void taskDisplayData(void *pvParameters)
{
	while(1) {
		setMode();

		switch(mode) {
		//	turn off display and info LEDs
		case MODE_OFF:
			setLedInfo(LED_TEMP, LED_OFF);
			setLedInfo(LED_HUM, LED_OFF);
			setLedInfo(LED_BAR, LED_OFF);

			resetDisp();

			break;
		//	show temperature data in Celsius on display and appropriate info LED
		case MODE_TEMP:
			setLedInfo(LED_TEMP, LED_ON);
			setLedInfo(LED_HUM, LED_OFF);
			setLedInfo(LED_BAR, LED_OFF);

			setLedNum((uint32_t)sensorData.temperature);

			break;
		//	show humidity data in percent on display and appropriate info LED
		case MODE_HUM:
			setLedInfo(LED_TEMP, LED_OFF);
			setLedInfo(LED_HUM, LED_ON);
			setLedInfo(LED_BAR, LED_OFF);

			setLedNum((uint32_t)sensorData.humidity);

			break;
		//	show pressure data in mm Hg on display and appropriate info LED
		//	7 digit is not displayed but implied
		case MODE_BAR:
			setLedInfo(LED_TEMP, LED_OFF);
			setLedInfo(LED_HUM, LED_OFF);
			setLedInfo(LED_BAR, LED_ON);

			setLedNum(((uint32_t)(sensorData.pressure / 133.322) % 700) + 1);

			break;
		default:
			break;
		}

		vTaskDelay(DISPLAY_DATA_DELAY);
	}
}
/*********************************************************************/
