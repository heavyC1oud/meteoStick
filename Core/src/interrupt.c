
#include "stm32f0xx.h"
#include "delay.h"
#include "main.h"
#include "interrupt.h"

/*********************************************************************/

/*************************	FUNCTION	******************************/

/**********************************************************************
* Function name : SysTick_Handler
* Description   : SysTick interrupt handle
* Arguments     : none
* Return Value  : none
**********************************************************************/
void SysTick_Handler(void)
{
	delayTimerValue--;
}
/*********************************************************************/
