
#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"

void (*pRollDigit[10])(DISP_RANK_typedef, LED_STEP_typedef, FlagStatus);

/*************************	FUNCTIONS PROTOTYPE	******************************/

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

	resetDisp();

	pRollDigit[0] = letsRollZero;
	pRollDigit[1] = letsRollOne;
	pRollDigit[2] = letsRollTwo;
	pRollDigit[3] = letsRollThree;
	pRollDigit[4] = letsRollFour;
	pRollDigit[5] = letsRollFive;
	pRollDigit[6] = letsRollSix;
	pRollDigit[7] = letsRollSeven;
	pRollDigit[8] = letsRollEight;
	pRollDigit[9] = letsRollNine;
}
/*********************************************************************/

/**********************************************************************
*	function name	:	resetDispOne
*	Description		:	turn off first digit on LED display (one)
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void resetDispOne(void)
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
void resetDispTen(void)
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
*	function name	:	setZero
*	Description		:	set zero digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setZero(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_B;
		SET_DIG_ONE_C;
		SET_DIG_ONE_D;
		SET_DIG_ONE_E;
		SET_DIG_ONE_F;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_B;
		SET_DIG_TEN_C;
		SET_DIG_TEN_D;
		SET_DIG_TEN_E;
		SET_DIG_TEN_F;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setOne
*	Description		:	set one digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setOne(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_B;
		SET_DIG_ONE_C;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_B;
		SET_DIG_TEN_C;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setTwo
*	Description		:	set two digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setTwo(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_B;
		SET_DIG_ONE_D;
		SET_DIG_ONE_E;
		SET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_B;
		SET_DIG_TEN_D;
		SET_DIG_TEN_E;
		SET_DIG_TEN_G;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setThree
*	Description		:	set three digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setThree(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_B;
		SET_DIG_ONE_C;
		SET_DIG_ONE_D;
		SET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_B;
		SET_DIG_TEN_C;
		SET_DIG_TEN_D;
		SET_DIG_TEN_G;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setFour
*	Description		:	set four digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setFour(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_B;
		SET_DIG_ONE_C;
		SET_DIG_ONE_F;
		SET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_B;
		SET_DIG_TEN_C;
		SET_DIG_TEN_F;
		SET_DIG_TEN_G;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setFive
*	Description		:	set five digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setFive(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_C;
		SET_DIG_ONE_D;
		SET_DIG_ONE_F;
		SET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_C;
		SET_DIG_TEN_D;
		SET_DIG_TEN_F;
		SET_DIG_TEN_G;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setSix
*	Description		:	set six digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setSix(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_C;
		SET_DIG_ONE_D;
		SET_DIG_ONE_E;
		SET_DIG_ONE_F;
		SET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_C;
		SET_DIG_TEN_D;
		SET_DIG_TEN_E;
		SET_DIG_TEN_F;
		SET_DIG_TEN_G;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setSeven
*	Description		:	set seven digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setSeven(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_B;
		SET_DIG_ONE_C;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_B;
		SET_DIG_TEN_C;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setEight
*	Description		:	set eight digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setEight(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_B;
		SET_DIG_ONE_C;
		SET_DIG_ONE_D;
		SET_DIG_ONE_E;
		SET_DIG_ONE_F;
		SET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_B;
		SET_DIG_TEN_C;
		SET_DIG_TEN_D;
		SET_DIG_TEN_E;
		SET_DIG_TEN_F;
		SET_DIG_TEN_G;

		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setNine
*	Description		:	set nine digit
*	Arguments		:	rank - one/ten display character
*	Return value	:	none
**********************************************************************/
void setNine(DISP_RANK_typedef rank)
{
	switch(rank) {
	case DISP_RANK_ONE:
		resetDispOne();

		SET_DIG_ONE_A;
		SET_DIG_ONE_B;
		SET_DIG_ONE_C;
		SET_DIG_ONE_D;
		SET_DIG_ONE_F;
		SET_DIG_ONE_G;

		break;
	case DISP_RANK_TEN:
		resetDispTen();

		SET_DIG_TEN_A;
		SET_DIG_TEN_B;
		SET_DIG_TEN_C;
		SET_DIG_TEN_D;
		SET_DIG_TEN_F;
		SET_DIG_TEN_G;

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
void setDispNum(uint8_t num)
{
	//	only two digits can be displayed
	if(num > 99) {
		num %= 100;
	}

	//	show digits on display

	//	show one digit sector
	switch(num % 10) {
	case 0:
		setZero(DISP_RANK_ONE);
		break;
	case 1:
		setOne(DISP_RANK_ONE);
		break;
	case 2:
		setTwo(DISP_RANK_ONE);
		break;
	case 3:
		setThree(DISP_RANK_ONE);
		break;
	case 4:
		setFour(DISP_RANK_ONE);
		break;
	case 5:
		setFive(DISP_RANK_ONE);
		break;
	case 6:
		setSix(DISP_RANK_ONE);
		break;
	case 7:
		setSeven(DISP_RANK_ONE);
		break;
	case 8:
		setEight(DISP_RANK_ONE);
		break;
	case 9:
		setNine(DISP_RANK_ONE);
		break;
	default:
		break;
	}

	//	show ten digit sector
	switch(num / 10) {
	case 0:
		setZero(DISP_RANK_TEN);
		break;
	case 1:
		setOne(DISP_RANK_TEN);
		break;
	case 2:
		setTwo(DISP_RANK_TEN);
		break;
	case 3:
		setThree(DISP_RANK_TEN);
		break;
	case 4:
		setFour(DISP_RANK_TEN);
		break;
	case 5:
		setFive(DISP_RANK_TEN);
		break;
	case 6:
		setSix(DISP_RANK_TEN);
		break;
	case 7:
		setSeven(DISP_RANK_TEN);
		break;
	case 8:
		setEight(DISP_RANK_TEN);
		break;
	case 9:
		setNine(DISP_RANK_TEN);
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
		if(act == LED_ON) SET_LED_TEMP;
		else if(act == LED_OFF) RESET_LED_TEMP;
		break;
	case LED_HUM:
		if(act == LED_ON) GPIOB->BSRR = SET_LED_HUM;
		else if(act == LED_OFF) GPIOB->BSRR = RESET_LED_HUM;
		break;
	case LED_BAR:
		if(act == LED_ON) GPIOB->BSRR = SET_LED_BAR;
		else if(act == LED_OFF) GPIOB->BSRR = RESET_LED_BAR;
		break;
	default:
		break;
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollOne
*	Description		:	rolling "1" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollOne(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2) stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_3)	stepLED(rank, RESET, SET, RESET, RESET, RESET, RESET, RESET);		//	B
		else if(step == LED_STEP_4)	stepLED(rank, RESET, SET, RESET, RESET, RESET, RESET, RESET);		//	B
		else if(step == LED_STEP_5)	stepLED(rank, RESET, SET, SET, RESET, RESET, RESET, RESET);			//	B C
		else if(step == LED_STEP_6)	stepLED(rank, RESET, SET, SET, RESET, RESET, RESET, RESET);			//	B C
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, SET, SET, RESET, RESET, RESET, RESET);			//	B C
		else if(step == LED_STEP_2) stepLED(rank, RESET, SET, SET, RESET, RESET, RESET, RESET);			//	B C
		else if(step == LED_STEP_3) stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, RESET);		//	C
		else if(step == LED_STEP_4) stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, RESET);		//	C
		else if(step == LED_STEP_5) stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_6) stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollTwo
*	Description		:	rolling "2" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollTwo(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2) stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, RESET);			//	A B
		else if(step == LED_STEP_4)	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, SET);			//	A B G
		else if(step == LED_STEP_5)	stepLED(rank, SET, SET, RESET, RESET, SET, RESET, SET);				//	A B E G
		else if(step == LED_STEP_6)	stepLED(rank, SET, SET, RESET, SET, SET, RESET, SET);				//	A B D E G
	}
	else {
		if(step == LED_STEP_1)		stepLED(rank, SET, SET, RESET, SET, SET, RESET, SET);				//	A B D E G
		else if(step == LED_STEP_2)	stepLED(rank, RESET, SET, RESET, SET, SET, RESET, SET);				//	B D E G
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, RESET, SET, SET, RESET, SET);			//	D E G
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, RESET, SET, SET, RESET, RESET);			//	D E
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET);		//	D
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollThree
*	Description		:	rolling "3" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollThree(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, RESET);			//	A B
		else if(step == LED_STEP_4)	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, SET);			//	A B G
		else if(step == LED_STEP_5)	stepLED(rank, SET, SET, SET, RESET, RESET, RESET, SET);				//	A B C G
		else if(step == LED_STEP_6)	stepLED(rank, SET, SET, SET, SET, RESET, RESET, SET);				//	A B C D G
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, SET, SET, SET, SET, RESET, RESET, SET);				//	A B C D G
		else if(step == LED_STEP_2)	stepLED(rank, RESET, SET, SET, SET, RESET, RESET, SET);				//	B C D G
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, SET);			//	C D G
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, RESET);			//	C D
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET);		//	D
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollFour
*	Description		:	rolling "4" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollFour(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_3)	stepLED(rank, RESET, SET, RESET, RESET, RESET, SET, RESET);			//	B F
		else if(step == LED_STEP_4)	stepLED(rank, RESET, SET, RESET, RESET, RESET, SET, SET);			//	B F G
		else if(step == LED_STEP_5)	stepLED(rank, RESET, SET, SET, RESET, RESET, SET, SET);				//	B C F G
		else if(step == LED_STEP_6)	stepLED(rank, RESET, SET, SET, RESET, RESET, SET, SET);				//	B C F G
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, SET, SET, RESET, RESET, SET, SET);				//	B C F G
		else if(step == LED_STEP_2)	stepLED(rank, RESET, SET, SET, RESET, RESET, SET, SET);				//	B C F G
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, SET);			//	C G
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, RESET);		//	C
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollFive
*	Description		:	rolling "5" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollFive(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, RESET, RESET, RESET, RESET, SET, RESET);			//	A F
		else if(step == LED_STEP_4)	stepLED(rank, SET, RESET, RESET, RESET, RESET, SET, SET);			//	A F G
		else if(step == LED_STEP_5)	stepLED(rank, SET, RESET, SET, RESET, RESET, SET, SET);				//	A C F G
		else if(step == LED_STEP_6)	stepLED(rank, SET, RESET, SET, SET, RESET, SET, SET);				//	A C D F G
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, SET, RESET, SET, SET, RESET, SET, SET);				//	A C D F G
		else if(step == LED_STEP_2)	stepLED(rank, RESET, RESET, SET, SET, RESET, SET, SET);				//	C D F G
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, SET);			//	C D G
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, RESET);			//	C D
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET);		//	D
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollSix
*	Description		:	rolling "6" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollSix(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, RESET, RESET, RESET, RESET, SET, RESET);			//	A F
		else if(step == LED_STEP_4)	stepLED(rank, SET, RESET, RESET, RESET, RESET, SET, SET);			//	A F G
		else if(step == LED_STEP_5)	stepLED(rank, SET, RESET, SET, RESET, SET, SET, SET);				//	A C E F G
		else if(step == LED_STEP_6)	stepLED(rank, SET, RESET, SET, SET, SET, SET, SET);					//	A C D E F G
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, SET, RESET, SET, SET, SET, SET, SET);					//	A C D E F G
		else if(step == LED_STEP_2)	stepLED(rank, RESET, RESET, SET, SET, SET, SET, SET);				//	C D E F G
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, SET, SET, RESET, SET);				//	C D E G
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, SET, SET, RESET, RESET);			//	C D E
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET);		//	D
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollSeven
*	Description		:	rolling "7" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollSeven(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, RESET);			//	A B
		else if(step == LED_STEP_4)	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, RESET);			//	A B
		else if(step == LED_STEP_5)	stepLED(rank, SET, SET, SET, RESET, RESET, RESET, RESET);			//	A B C
		else if(step == LED_STEP_6)	stepLED(rank, SET, SET, SET, RESET, RESET, RESET, RESET);			//	A B C
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, SET, SET, SET, RESET, RESET, RESET, RESET);			//	A B C
		else if(step == LED_STEP_2)	stepLED(rank, RESET, SET, SET, RESET, RESET, RESET, RESET);			//	B C
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, RESET);		//	C
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, RESET);		//	C
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollEight
*	Description		:	rolling "8" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollEight(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, RESET);			//	A B F
		else if(step == LED_STEP_4)	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, SET);				//	A B F G
		else if(step == LED_STEP_5)	stepLED(rank, SET, SET, SET, RESET, SET, SET, SET);					//	A B C E F G
		else if(step == LED_STEP_6)	stepLED(rank, SET, SET, SET, SET, SET, SET, SET);					//	A B C D E F G
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, SET, SET, SET, SET, SET, SET, SET);					//	A B C D E F G
		else if(step == LED_STEP_2)	stepLED(rank, RESET, SET, SET, SET, SET, SET, SET);					//	B C D E F G
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, SET, SET, RESET, SET);				//	C D E G
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, SET, SET, RESET,RESET);			//	C D E
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET);		//	D
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollNine
*	Description		:	rolling "9" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollNine(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, RESET);			//	A B F
		else if(step == LED_STEP_4)	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, SET);				//	A B F G
		else if(step == LED_STEP_5)	stepLED(rank, SET, SET, SET, RESET, RESET, SET, SET);				//	A B C F G
		else if(step == LED_STEP_6)	stepLED(rank, SET, SET, SET, SET, RESET, SET, SET);					//	A B C D F G
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, SET, SET, SET, SET, RESET, SET, SET);					//	A B C D F G
		else if(step == LED_STEP_2)	stepLED(rank, RESET, SET, SET, SET, RESET, SET, SET);				//	B C D F G
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, SET);			//	C D G
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, RESET);			//	C D
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET);		//	D
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollZero
*	Description		:	rolling "0" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	step - current step number
*					:	show - show/hide digit
*	Return value	:	none
**********************************************************************/
void letsRollZero(DISP_RANK_typedef rank, LED_STEP_typedef step, FlagStatus show)
{
	if(show == SET) {
		if(step == LED_STEP_1) 		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
		else if(step == LED_STEP_2)	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET);		//	A
		else if(step == LED_STEP_3)	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, RESET);			//	A B F
		else if(step == LED_STEP_4)	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, RESET);			//	A B F
		else if(step == LED_STEP_5)	stepLED(rank, SET, SET, SET, RESET, SET, SET, RESET);				//	A B C E F
		else if(step == LED_STEP_6)	stepLED(rank, SET, SET, SET, SET, SET, SET, RESET);					//	A B C D E F
	}
	else {
		if(step == LED_STEP_1) 		stepLED(rank, SET, SET, SET, SET, SET, SET, RESET);					//	A B C D E F
		else if(step == LED_STEP_2)	stepLED(rank, RESET, SET, SET, SET, SET, SET, RESET);				//	B C D E F
		else if(step == LED_STEP_3)	stepLED(rank, RESET, RESET, SET, SET, SET, RESET, RESET);			//	C D E
		else if(step == LED_STEP_4)	stepLED(rank, RESET, RESET, SET, SET, SET, RESET, RESET);			//	C D E
		else if(step == LED_STEP_5)	stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET);		//	D
		else if(step == LED_STEP_6)	stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	stepLED
*	Description		:	set/reset LED sector
*	Arguments		:	rank - ONE/TEN digit
*					:	a - display A sector
*					:	b - display B sector
*					:	c - display C sector
*					:	d - display D sector
*					:	e - display E sector
*					:	f - display F sector
*					:	g - display G sector
*					:	delay - delay
*	Return value	:	none
**********************************************************************/
void stepLED(DISP_RANK_typedef rank, FlagStatus a, FlagStatus b, FlagStatus c, FlagStatus d, FlagStatus e, FlagStatus f, FlagStatus g)
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
*	function name	:	gameMode
*	Description		:	some game function
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void gameMode(void)
{
//	while(tKeyState.longTouch == RESET) {
//
//
//
//	}
//
//	tKeyState.longTouch = RESET;
//
//	if(tKeyState.shortTouch == SET) {
//
//		tKeyState.shortTouch = RESET;
//	}
//	else if(tKeyState.longTouch == SET) {
//		mode = MODE_GAME;
//
//		tKeyState.longTouch = RESET;
//	}

	while(1) {
		for(uint8_t i = 0; i < 100; i++) {
			setDispNum1(i);
			delayMs(200);
		}
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	setDispNum
*	Description		:	set number on LED display
*	Arguments		:	num - number to display
*	Return value	:	none
**********************************************************************/
void setDispNum1(uint8_t num)
{
	static FlagStatus firstStartFlag = SET;
	static uint8_t dispData = 0;

	uint8_t rankOne = 0;
	uint8_t rankTen = 0;


	//	only two digits can be displayed
	if(num > 99) {
		num %= 100;
	}

	if(num == dispData) return;

	//	skip hiding digits after power up
	if(firstStartFlag == RESET) {
		//	hide previous digits
		rankTen = dispData / 10;
		rankOne = dispData % 10;

		for(LED_STEP_typedef i = LED_STEP_FIRST; i <= LED_STEP_LAST; i++) {
			pRollDigit[rankOne](DISP_RANK_ONE, i, RESET);
			pRollDigit[rankTen](DISP_RANK_TEN, i, RESET);

			delayMs(ROLL_DELAY);
		}
	}
	else {
		firstStartFlag = RESET;
	}

	//	refresh current digits
	dispData = num;

	//	set current digits
	rankTen = dispData / 10;
	rankOne = dispData % 10;

	for(LED_STEP_typedef i = LED_STEP_FIRST; i <= LED_STEP_LAST; i++) {
		pRollDigit[rankOne](DISP_RANK_ONE, i, SET);
		pRollDigit[rankTen](DISP_RANK_TEN, i, SET);

		delayMs(ROLL_DELAY);
	}
}
/*********************************************************************/


