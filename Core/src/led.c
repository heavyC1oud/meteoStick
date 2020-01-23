
#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"

/*************************	FUNCTIONS PROTOTYPE	******************************/
static void resetDispOne(void);
static void resetDispTen(void);
static void setLed(DISP_RANK_typedef rank, FlagStatus a, FlagStatus b, FlagStatus c, FlagStatus d, FlagStatus e, FlagStatus f, FlagStatus g);


/*************************	FUNCTION	******************************/

/**********************************************************************
*	function name	:	initLed
*	Description		:	MCU GPIO initialization
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void initLed(void)
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

	resetDisp();
}
/*********************************************************************/

/**********************************************************************
*	function name	:	resetDispOne
*	Description		:	turn off first digit on LED display (one)
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
static void resetDispOne(void)
{
	RESET_DIG_ONE_A;
	RESET_DIG_ONE_B;
	RESET_DIG_ONE_C;
	RESET_DIG_ONE_D;
	RESET_DIG_ONE_E;
	RESET_DIG_ONE_F;
	RESET_DIG_ONE_G;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	resetDispTen
*	Description		:	turn off second digit on LED display (ten)
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
static void resetDispTen(void)
{
	RESET_DIG_TEN_A;
	RESET_DIG_TEN_B;
	RESET_DIG_TEN_C;
	RESET_DIG_TEN_D;
	RESET_DIG_TEN_E;
	RESET_DIG_TEN_F;
	RESET_DIG_TEN_G;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	resetDisp
*	Description		:	turn off LED display
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void resetDisp(void)
{
	resetDispTen();
	resetDispOne();
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setLED
*	Description		:	set/reset LED sector
*	Arguments		:	rank - ONE/TEN digit
*					:	a - display A sector
*					:	b - display B sector
*					:	c - display C sector
*					:	d - display D sector
*					:	e - display E sector
*					:	f - display F sector
*					:	g - display G sector
*	Return value	:	none
**********************************************************************/
static void setLed(DISP_RANK_typedef rank, FlagStatus a, FlagStatus b, FlagStatus c, FlagStatus d, FlagStatus e, FlagStatus f, FlagStatus g)
{
	switch(rank) {
	case DISP_RANK_ONE:
		if(a == SET) 	SET_DIG_ONE_A;
		else			RESET_DIG_ONE_A;

		if(b == SET) 	SET_DIG_ONE_B;
		else			RESET_DIG_ONE_B;

		if(c == SET) 	SET_DIG_ONE_C;
		else			RESET_DIG_ONE_C;

		if(d == SET) 	SET_DIG_ONE_D;
		else			RESET_DIG_ONE_D;

		if(e == SET) 	SET_DIG_ONE_E;
		else			RESET_DIG_ONE_E;

		if(f == SET) 	SET_DIG_ONE_F;
		else			RESET_DIG_ONE_F;

		if(g == SET) 	SET_DIG_ONE_G;
		else			RESET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		if(a == SET) 	SET_DIG_TEN_A;
		else			RESET_DIG_TEN_A;

		if(b == SET) 	SET_DIG_TEN_B;
		else			RESET_DIG_TEN_B;

		if(c == SET) 	SET_DIG_TEN_C;
		else			RESET_DIG_TEN_C;

		if(d == SET) 	SET_DIG_TEN_D;
		else			RESET_DIG_TEN_D;

		if(e == SET) 	SET_DIG_TEN_E;
		else			RESET_DIG_TEN_E;

		if(f == SET) 	SET_DIG_TEN_F;
		else			RESET_DIG_TEN_F;

		if(g == SET) 	SET_DIG_TEN_G;
		else			RESET_DIG_TEN_G;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setDispNum
*	Description		:	set number on LED display
*	Arguments		:	num - number to display
*	Return value	:	none
**********************************************************************/
void setLedNum(uint8_t num)
{
	//	only two digits can be displayed
	if(num > 99) {
		num %= 100;
	}

	//	show digits on display

	//	show one digit sector
	switch(num % 10) {
	case 0:
		setLed(DISP_RANK_ONE, SET, SET, SET, SET, SET, SET, RESET);			//	A B C D E F
		break;
	case 1:
		setLed(DISP_RANK_ONE, RESET, SET, SET, RESET, RESET, RESET, RESET);	//	B C
		break;
	case 2:
		setLed(DISP_RANK_ONE, SET, SET, RESET, SET, SET, RESET, SET);		//	A B D E G
		break;
	case 3:
		setLed(DISP_RANK_ONE, SET, SET, SET, SET, RESET, RESET, SET);		//	A B C D G
		break;
	case 4:
		setLed(DISP_RANK_ONE, RESET, SET, SET, RESET, RESET, SET, SET);		//	B C F G
		break;
	case 5:
		setLed(DISP_RANK_ONE, SET, RESET, SET, SET, RESET, SET, SET);		//	A C D F G
		break;
	case 6:
		setLed(DISP_RANK_ONE, SET, RESET, SET, SET, SET, SET, SET);			//	A C D E F G
		break;
	case 7:
		setLed(DISP_RANK_ONE, SET, SET, SET, RESET, RESET, RESET, RESET);	//	A B C
		break;
	case 8:
		setLed(DISP_RANK_ONE, SET, SET, SET, SET, SET, SET, SET);			//	A B C D E F G
		break;
	case 9:
		setLed(DISP_RANK_ONE, SET, SET, SET, SET, RESET, SET, SET);			//	A B C D F G
		break;
	default:
		break;
	}

	//	show ten digit sector
	switch(num / 10) {
	case 0:
		setLed(DISP_RANK_TEN, SET, SET, SET, SET, SET, SET, RESET);			//	A B C D E F
		break;
	case 1:
		setLed(DISP_RANK_TEN, RESET, SET, SET, RESET, RESET, RESET, RESET);	//	B C
		break;
	case 2:
		setLed(DISP_RANK_TEN, SET, SET, RESET, SET, SET, RESET, SET);		//	A B D E G
		break;
	case 3:
		setLed(DISP_RANK_TEN, SET, SET, SET, SET, RESET, RESET, SET);		//	A B C D G
		break;
	case 4:
		setLed(DISP_RANK_TEN, RESET, SET, SET, RESET, RESET, SET, SET);		//	B C F G
		break;
	case 5:
		setLed(DISP_RANK_TEN, SET, RESET, SET, SET, RESET, SET, SET);		//	A C D F G
		break;
	case 6:
		setLed(DISP_RANK_TEN, SET, RESET, SET, SET, SET, SET, SET);			//	A C D E F G
		break;
	case 7:
		setLed(DISP_RANK_TEN, SET, SET, SET, RESET, RESET, RESET, RESET);	//	A B C
		break;
	case 8:
		setLed(DISP_RANK_TEN, SET, SET, SET, SET, SET, SET, SET);			//	A B C D E F G
		break;
	case 9:
		setLed(DISP_RANK_TEN, SET, SET, SET, SET, RESET, SET, SET);			//	A B C D F G
		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setLedInfo
*	Description		:	turn on/off temperature/humidity/pressure LEDs
*	Arguments		:	led - temperature/humidity/pressure LED
*					:	act - on/off
*	Return value	:	none
**********************************************************************/
void setLedInfo(LED_INFO_typedef led, LED_ACT_typedef act)
{
	switch(led) {
	case LED_TEMP:
		if(act == LED_ON)	SET_LED_TEMP;
		else				RESET_LED_TEMP;
		break;
	case LED_HUM:
		if(act == LED_ON)	SET_LED_HUM;
		else				RESET_LED_HUM;
		break;
	case LED_BAR:
		if(act == LED_ON)	SET_LED_BAR;
		else				RESET_LED_BAR;
		break;
	default:
		break;
	}
}
/*********************************************************************/

