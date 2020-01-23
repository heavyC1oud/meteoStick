#include "stm32f0xx.h"
#include "system_stm32f0xx.h"
#include "delay.h"

/*********************************************************************/

/*************************	VARIABLE	******************************/
static volatile uint32_t delayTimerValue = 0;

/*************************	FUNCTION PROTOTYPE	******************************/
static void startDelayTimer(void);
static void stopDelayTimer(void);

/*************************	FUNCTION	******************************/

/**********************************************************************
* Function name : initDelayTimer
* Description   : delay timer initialization
* Arguments     : none
* Return Value  : none
**********************************************************************/
void initDelayTimer(void)
{
	//	enable Timer7 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	//	set preload value
	TIM7->ARR = DELAY_TIMER_PRELOAD_VALUE;

	//	set prescaler
	TIM7->PSC = ((SystemCoreClock / (DELAY_TIMER_PRESC * DELAY_TIMER_PRELOAD_VALUE)) - 1);

	//	auto-reload enable
	TIM7->CR1 |= TIM_CR1_ARPE;

	//	only overflow generates interrupt
	TIM7->CR1 |= TIM_CR1_URS;

	//	update event enable
	TIM7->CR1 &= ~TIM_CR1_UDIS;

	//	clear interrupt flag
	TIM7->SR &= ~TIM_SR_UIF;

	//	enable interrupt
	TIM7->DIER |= TIM_DIER_UIE;

	//	NVIC TIM7 interrupt set
	NVIC_EnableIRQ(TIM7_IRQn);
	NVIC_SetPriority(TIM7_IRQn, 11);
}
/*********************************************************************/


/**********************************************************************
* Function name : startDelayTimer
* Description   : start timer
* Arguments     : none
* Return Value  : none
**********************************************************************/
static void startDelayTimer(void)
{
	//	clear interrupt flag
	TIM7->SR &= ~TIM_SR_UIF;

	//	clear counter
	TIM7->CNT = 0;

	//	counter enable
	TIM7->CR1 |= TIM_CR1_CEN;
}
/*********************************************************************/


/**********************************************************************
* Function name : stopDelayTimer
* Description   : stop timer
* Arguments     : none
* Return Value  : none
**********************************************************************/
static void stopDelayTimer(void)
{
	//	counter disable
	TIM7->CR1 &= ~TIM_CR1_CEN;

	//	clear interrupt flag
	TIM7->SR &= ~TIM_SR_UIF;

	//	clear counter
	TIM7->CNT = 0;
}
/*********************************************************************/


/**********************************************************************
* Function name : delayMs
* Description   : set delay in milliseconds
* Arguments     : delay - delay in milliseconds
* Return Value  : none
**********************************************************************/
void delayMs(uint32_t delay)
{
	delayTimerValue = delay;

	//	start counter
	startDelayTimer();

	//	wait until sysTick timer counts down delay value
	while((delayTimerValue != 0) && (delayTimerValue <= delay));

	//	stop counter
	stopDelayTimer();
}
/*********************************************************************/


/**********************************************************************
* Function name : TIM7_IRQHandler
* Description   : Timer7 interrupt handle
* Arguments     : none
* Return Value  : none
**********************************************************************/
void TIM7_IRQHandler(void)
{
	delayTimerValue--;

	//	clear interrupt flag
	TIM7->SR &= ~TIM_SR_UIF;
}
/*********************************************************************/
