


#include "tsc.h"
#include "led.h"
#include "delay.h"
#include "game.h"

/**********************************************************************
*	function name	:	letsRollOne
*	Description		:	rolling "1" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollOne(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, RESET, SET, RESET, RESET, RESET, RESET, RESET, delay);			//	B
	stepLED(rank, RESET, SET, SET, RESET, RESET, RESET, RESET, delay);				//	B C

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, RESET, delay);		//	C
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollTwo
*	Description		:	rolling "2" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollTwo(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET, delay);			//	A
	stepLED(rank, SET, RESET, RESET, RESET, RESET, SET, SET, delay);				//	F G
	stepLED(rank, SET, SET, RESET, SET, SET, RESET, SET, delay);					//	A B D E G

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, SET, delay);			//	C D G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollThree
*	Description		:	rolling "3" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollThree(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET, delay);			//	A
	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, SET, delay);				//	A B G
	stepLED(rank, SET, SET, SET, SET, RESET, RESET, SET, delay);					//	A B C D G

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, SET, RESET, RESET, SET, delay);			//	C D G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollFour
*	Description		:	rolling "4" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollFour(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, RESET, SET, RESET, RESET, RESET, RESET, RESET, delay);			//	B
	stepLED(rank, RESET, SET, SET, RESET, RESET, SET, SET, delay);					//	B C F G

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, SET, SET, RESET, RESET, delay);			//	C D E
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollFive
*	Description		:	rolling "5" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollFive(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET, delay);			//	A
	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, SET, delay);				//	A B G
	stepLED(rank, SET, RESET, SET, SET, RESET, SET, SET, delay);					//	A C D F G

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, RESET, SET, SET, RESET, SET, delay);			//	D E G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollSix
*	Description		:	rolling "6" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollSix(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET, delay);			//	A
	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, SET, delay);					//	A B F G
	stepLED(rank, SET, RESET, SET, SET, SET, SET, SET, delay);						//	A C D E F G

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, RESET, SET, SET, RESET, SET, delay);			//	D E G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollSeven
*	Description		:	rolling "7" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollSeven(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, RESET, SET, RESET, RESET, RESET, RESET, RESET, delay);			//	B
	stepLED(rank, SET, SET, SET, RESET, RESET, RESET, RESET, delay);				//	A B C

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, RESET, RESET, RESET, SET, delay);			//	C G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollEight
*	Description		:	rolling "8" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollEight(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET, delay);			//	A
	stepLED(rank, SET, SET, RESET, RESET, RESET, SET, SET, delay);					//	A B F G
	stepLED(rank, SET, SET, SET, SET, SET, SET, SET, delay);						//	A B C D E F G

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, SET, SET, RESET, SET, delay);				//	C D E G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollNine
*	Description		:	rolling "9" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollNine(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET, delay);			//	A
	stepLED(rank, SET, SET, RESET, RESET, RESET, RESET, SET, delay);				//	A B G
	stepLED(rank, SET, SET, SET, SET, RESET, SET, SET, delay);						//	A B C D F G

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, SET, SET, RESET, SET, delay);				//	C D E G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
	}
}
/*********************************************************************/


/**********************************************************************
*	function name	:	letsRollZero
*	Description		:	rolling "0" numeral
*	Arguments		:	rank - ONE/TEN digit
*					:	delay - roll speed
*					:	stop - stop rolling on numeral
*	Return value	:	none
**********************************************************************/
void letsRollZero(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop)
{
	stepLED(rank, SET, RESET, RESET, RESET, RESET, RESET, RESET, delay);			//	A
	stepLED(rank, RESET, SET, RESET, RESET, RESET, SET, SET, delay);				//	B F G
	stepLED(rank, SET, SET, SET, SET, SET, SET, RESET, delay);						//	A B C D E F

	if(stop == RESET) {
		stepLED(rank, RESET, RESET, SET, RESET, SET, RESET, SET, delay);			//	C E G
		stepLED(rank, RESET, RESET, RESET, SET, RESET, RESET, RESET, delay);		//	D
		stepLED(rank, RESET, RESET, RESET, RESET, RESET, RESET, RESET, delay);		//	none
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
void stepLED(DISP_RANK_typedef rank, FlagStatus a, FlagStatus b, FlagStatus c, FlagStatus d, FlagStatus e, FlagStatus f, FlagStatus g, uint32_t delay)
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

	delayMs(delay);
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
}
/*********************************************************************/
