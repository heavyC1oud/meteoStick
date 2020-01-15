#include "stm32f0xx.h"
#include "system_stm32f0xx.h"
#include "pwm.h"

/*********************************************************************/

/*************************	VARIABLE	******************************/
volatile uint8_t PWMCount = 0;

/*************************	FUNCTION PROTOTYPE	******************************/

/*************************	FUNCTION	******************************/

/**********************************************************************
* Function name : initPWMTimer
* Description   : delay timer initialization
* Arguments     : none
* Return Value  : none
**********************************************************************/
void initPWMTimer(void)
{
	//	enable Timer7 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	//	set preload value
	TIM6->ARR = PWM_TIMER_PRELOAD_VALUE;

	//	set prescaler
	TIM6->PSC = PWM_TIMER_PRESC;

	//	auto-reload enable
	TIM6->CR1 |= TIM_CR1_ARPE;

	//	only overflow generates interrupt
	TIM6->CR1 |= TIM_CR1_URS;

	//	update event enable
	TIM6->CR1 &= ~TIM_CR1_UDIS;

	//	clear interrupt flag
	TIM6->SR &= ~TIM_SR_UIF;

	//	enable interrupt
	TIM6->DIER |= TIM_DIER_UIE;

	//	NVIC TIM6 interrupt set
	NVIC_EnableIRQ(TIM6_IRQn);
	NVIC_SetPriority(TIM6_IRQn, 12);
}
/*********************************************************************/


/**********************************************************************
* Function name : startPWMTimer
* Description   : start timer
* Arguments     : none
* Return Value  : none
**********************************************************************/
void startPWMTimer(void)
{
	//	clear interrupt flag
	TIM6->SR &= ~TIM_SR_UIF;

	//	clear counter
	TIM6->CNT = 0;

	//	reset count value
	PWMCount = 0;

	//	counter enable
	TIM6->CR1 |= TIM_CR1_CEN;
}
/*********************************************************************/


/**********************************************************************
* Function name : stopPWMTimer
* Description   : stop timer
* Arguments     : none
* Return Value  : none
**********************************************************************/
void stopPWMTimer(void)
{
	//	counter disable
	TIM6->CR1 &= ~TIM_CR1_CEN;

	//	clear interrupt flag
	TIM6->SR &= ~TIM_SR_UIF;

	//	clear counter
	TIM6->CNT = 0;

	//	reset count value
	PWMCount = 0;
}
/*********************************************************************/


/**********************************************************************
* Function name : TIM6_IRQHandler
* Description   : Timer6 interrupt handle
* Arguments     : none
* Return Value  : none
**********************************************************************/
void TIM6_IRQHandler(void)
{
	PWMCount++;

	if(PWMCount == PWM_COUNT_MAX_VALUE) {
		PWMCount = 0;
	}

	//	clear interrupt flag
	TIM6->SR &= ~TIM_SR_UIF;
}
/*********************************************************************/
