
#include "delay.h"

/*********************************************************************/

/*************************	VARIABLE	******************************/
volatile uint32_t delayTimerValue = 0;


/*************************	FUNCTION	******************************/

/**********************************************************************
* Function name : delayMs
* Description   : set delay in milliseconds using sysTick timer
* Arguments     : delay - delay in milliseconds
* Return Value  : none
**********************************************************************/
void delayMs(uint32_t delay)
{
	delayTimerValue = delay;

	//	wait until sysTick timer counts down delay value
	while((delayTimerValue != 0) && (delayTimerValue <= delay));
}
/*********************************************************************/
