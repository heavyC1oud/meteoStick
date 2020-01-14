#pragma once

#include <stdint.h>

/*********************************************************************/
//	set interrupt event to 1 ms
//	1 tick = 1 us = (SystemCoreClock / DELAY_TIMER_PRESC) - 1
//	interrupt event = DELAY_TIMER_PRELOAD_VALUE ticks
#define DELAY_TIMER_PRESC 1000
#define DELAY_TIMER_PRELOAD_VALUE 1000

/*************************	VARIABLE	******************************/

/*************************	FUNCTIONS PROTOTYPE	******************************/
void initDelayTimer();
void delayMs(uint32_t delay);
