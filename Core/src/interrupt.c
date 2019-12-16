#include "stm32f0xx.h"
#include "delay.h"
#include "main.h"
#include "interrupt.h"


//	SysTick interrupt handle
void SysTick_Handler(void)
{
	delayTimerValue--;
}

