
#include "delay.h"

volatile uint32_t delayTimerValue = 0;


//	set delay in miliseconds using sysTick timer
void delayMs(uint32_t delay)
{
	delayTimerValue = delay;

	while(delayTimerValue);
}
