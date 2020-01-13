
#include "stm32f0xx.h"
#include "delay.h"
#include "main.h"
#include "interrupt.h"

/*********************************************************************/

/*************************	FUNCTION	******************************/

/**********************************************************************
* Function name : initIT
* Description   : interrupt initialization
* Arguments     : none
* Return Value  : none
**********************************************************************/
void initIT(void)
{
	//	Touch sensing interrupt
	NVIC_EnableIRQ(TSC_IRQn);
	NVIC_SetPriority(TSC_IRQn, 11);
}
/*********************************************************************/


/**********************************************************************
* Function name : SysTick_Handler
* Description   : SysTick interrupt handle
* Arguments     : none
* Return Value  : none
**********************************************************************/
//void SysTick_Handler(void)
//{
//	delayTimerValue--;
//}
/*********************************************************************/
