
#include <stm32f072xb.h>
#include <led.h>

/*************************	FUNCTIONS PROTOTYPE	******************************/
static void turnOffOneDigit(void);
static void turnOffTenDigit(void);

/*************************	FUNCTION	******************************/

/**********************************************************************
*	function name	:	initLED
*	Description		:	MCU GPIO initialization
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void initLED(void)
{
	//	enable PORTA/PORTB bus
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;

	//	MODERx[1:0] = 01 - general purpose output mode
	//	GPIOA
	GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 |
					  GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
	GPIOA->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
					GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;

	//	GPIOB
	GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER10 |
					  GPIO_MODER_MODER11 | GPIO_MODER_MODER12 | GPIO_MODER_MODER13 | GPIO_MODER_MODER14 |
					  GPIO_MODER_MODER15);
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER10_0 |
					GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 |
					GPIO_MODER_MODER15_0;

	//	OTYPERx = 0 - output push-pull
	//	GPIOA
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_0 | GPIO_OTYPER_OT_1 | GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_3 |
					   GPIO_OTYPER_OT_4 | GPIO_OTYPER_OT_5 | GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7);

	//	GPIOB
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_0 | GPIO_OTYPER_OT_1 | GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_10 |
					   GPIO_OTYPER_OT_11 | GPIO_OTYPER_OT_12 | GPIO_OTYPER_OT_13 | GPIO_OTYPER_OT_14 |
					   GPIO_OTYPER_OT_15);

	//	OSPEEDRx[1:0] = 00 - low speed
	//	GPIOA
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 | GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR2 | GPIO_OSPEEDER_OSPEEDR3 |
						GPIO_OSPEEDER_OSPEEDR4 | GPIO_OSPEEDER_OSPEEDR5 | GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7);

	//	GPIOB
	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 | GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR2 | GPIO_OSPEEDER_OSPEEDR10 |
						GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR12 | GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR14 |
						GPIO_OSPEEDER_OSPEEDR15);

	//	PUPDRx[1:0] = 00 - no pull-up, no pull-down
	//	GPIOA
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3 |
					  GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR5 | GPIO_PUPDR_PUPDR6 | GPIO_PUPDR_PUPDR7);

	//	GPIOB
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR10 |
					  GPIO_PUPDR_PUPDR11 | GPIO_PUPDR_PUPDR12 | GPIO_PUPDR_PUPDR13 | GPIO_PUPDR_PUPDR14 |
					  GPIO_PUPDR_PUPDR15);

	//	BRRx = 1 - reset bit
	//	GPIOA
	GPIOA->BRR = GPIO_BRR_BR_0 | GPIO_BRR_BR_1 | GPIO_BRR_BR_2 | GPIO_BRR_BR_3 |
				 GPIO_BRR_BR_4 | GPIO_BRR_BR_5 | GPIO_BRR_BR_6 | GPIO_BRR_BR_7;

	//	GPIOB
	GPIOB->BRR = GPIO_BRR_BR_0 | GPIO_BRR_BR_1 | GPIO_BRR_BR_2 | GPIO_BRR_BR_10 |
				 GPIO_BRR_BR_11 | GPIO_BRR_BR_12 | GPIO_BRR_BR_13 | GPIO_BRR_BR_14 |
				 GPIO_BRR_BR_15;
}
/*********************************************************************/

/**********************************************************************
*	function name	:	turnOffOneDigit
*	Description		:	turn off first digit on LED display
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
static void turnOffOneDigit(void)
{
	GPIOA->BSRR = GPIO_BSRR_BR_0 | GPIO_BSRR_BR_1 | GPIO_BSRR_BR_2;
	GPIOB->BSRR = GPIO_BSRR_BR_2 | GPIO_BSRR_BR_10 | GPIO_BSRR_BR_11 | GPIO_BSRR_BR_12;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	turnOffTenDigit
*	Description		:	turn off second digit on LED display
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
static void turnOffTenDigit(void)
{
	GPIOA->BSRR = GPIO_BSRR_BR_3 | GPIO_BSRR_BR_4 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6 | GPIO_BSRR_BR_7;
	GPIOB->BSRR = GPIO_BSRR_BR_0 | GPIO_BSRR_BR_1;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	turnOffDisp
*	Description		:	turn off whole LED display
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void turnOffDisp(void)
{
	turnOffTenDigit();
	turnOffOneDigit();
}
/*********************************************************************/


/**********************************************************************
*	function name	:	showNumber
*	Description		:	set number from 0 to 99 on LED display
*	Arguments		:	num - number to display
*	Return value	:	none
**********************************************************************/
void showNumber(uint8_t num)
{
	//	only two digits can be displayed
	if(num > 99) {
		num %= 100;
	}

	//	show digits on display
	//	show ten digit sector
	turnOffTenDigit();

	switch(num / 10) {
	case 0:
		GPIOA->BSRR = GPIO_BSRR_BS_3 | GPIO_BSRR_BS_4 | GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6 | GPIO_BSRR_BS_7;
		GPIOB->BSRR = GPIO_BSRR_BS_1;
		break;
	case 1:
		GPIOA->BSRR = GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6;
		break;
	case 2:
		GPIOA->BSRR = GPIO_BSRR_BS_3 | GPIO_BSRR_BS_4 | GPIO_BSRR_BS_6 | GPIO_BSRR_BS_7;
		GPIOB->BSRR = GPIO_BSRR_BS_0;
		break;
	case 3:
		GPIOA->BSRR = GPIO_BSRR_BS_3 | GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6 | GPIO_BSRR_BS_7;
		GPIOB->BSRR = GPIO_BSRR_BS_0;
		break;
	case 4:
		GPIOA->BSRR = GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6;
		GPIOB->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
		break;
	case 5:
		GPIOA->BSRR = GPIO_BSRR_BS_3 | GPIO_BSRR_BS_5 | GPIO_BSRR_BS_7;
		GPIOB->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
		break;
	case 6:
		GPIOA->BSRR = GPIO_BSRR_BS_3 | GPIO_BSRR_BS_4 | GPIO_BSRR_BS_5 | GPIO_BSRR_BS_7;
		GPIOB->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
		break;
	case 7:
		GPIOA->BSRR = GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6 | GPIO_BSRR_BS_7;
		break;
	case 8:
		GPIOA->BSRR = GPIO_BSRR_BS_3 | GPIO_BSRR_BS_4 | GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6 | GPIO_BSRR_BS_7;
		GPIOB->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
		break;
	case 9:
		GPIOA->BSRR = GPIO_BSRR_BS_3 | GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6 | GPIO_BSRR_BS_7;
		GPIOB->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
	default:
		break;
	}

	//	show one digit sector
	turnOffOneDigit();

	switch(num % 10) {
	case 0:
		GPIOA->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2;
		GPIOB->BSRR = GPIO_BSRR_BS_10 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_12;
		break;
	case 1:
		GPIOA->BSRR = GPIO_BSRR_BS_0;
		GPIOB->BSRR = GPIO_BSRR_BS_11;
		break;
	case 2:
		GPIOA->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2;
		GPIOB->BSRR = GPIO_BSRR_BS_2 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_12;
		break;
	case 3:
		GPIOA->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
		GPIOB->BSRR = GPIO_BSRR_BS_2 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_12;
		break;
	case 4:
		GPIOA->BSRR = GPIO_BSRR_BS_0;
		GPIOB->BSRR = GPIO_BSRR_BS_2 | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_11;
		break;
	case 5:
		GPIOA->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
		GPIOB->BSRR = GPIO_BSRR_BS_2 | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_12;
		break;
	case 6:
		GPIOA->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2;
		GPIOB->BSRR = GPIO_BSRR_BS_2 | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_12;
		break;
	case 7:
		GPIOA->BSRR = GPIO_BSRR_BS_0;
		GPIOB->BSRR = GPIO_BSRR_BS_11 | GPIO_BSRR_BS_12;
		break;
	case 8:
		GPIOA->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2;
		GPIOB->BSRR = GPIO_BSRR_BS_2 | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_12;
		break;
	case 9:
		GPIOA->BSRR = GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1;
		GPIOB->BSRR = GPIO_BSRR_BS_2 | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_12;
		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	switchInfoLed
*	Description		:	turn on/off temperature/humidity/pressure LEDs
*	Arguments		:	led - temperature/humidity/pressure LED
*					:	act - on/off
*	Return value	:	none
**********************************************************************/
void switchInfoLed(LED_INFO_typedef led, LED_ACT_typedef act)
{
	switch(led) {
	case LED_TEMP:
		if(act == LED_ON) GPIOB->BSRR = GPIO_BSRR_BS_14;
		else if(act == LED_OFF) GPIOB->BSRR = GPIO_BSRR_BR_14;
		break;
	case LED_HUM:
		if(act == LED_ON) GPIOB->BSRR = GPIO_BSRR_BS_13;
		else if(act == LED_OFF) GPIOB->BSRR = GPIO_BSRR_BR_13;
		break;
	case LED_BAR:
		if(act == LED_ON) GPIOB->BSRR = GPIO_BSRR_BS_15;
		else if(act == LED_OFF) GPIOB->BSRR = GPIO_BSRR_BR_15;
		break;
	default:
		break;
	}
}
/*********************************************************************/


