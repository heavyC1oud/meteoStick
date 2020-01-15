#pragma once

#include <stdint.h>

/*********************************************************************/
//	set interrupt event to 10 us
//	SystemCoreClock = 48 000 000
//	interrupt event = DELAY_TIMER_PRELOAD_VALUE ticks
#define PWM_TIMER_PRESC 0
#define PWM_TIMER_PRELOAD_VALUE 480

#define PWM_COUNT_MAX_VALUE 100

/*************************	VARIABLE	******************************/
volatile uint8_t PWMCount;

/*************************	FUNCTIONS PROTOTYPE	******************************/
void initPWMTimer(void);
void startPWMTimer(void);
void stopPWMTimer(void);
