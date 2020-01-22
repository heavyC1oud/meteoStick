#pragma once

#include "stm32f0xx.h"
#include "led.h"


#define ROLL_DELAY 50


/*************************	FUNCTIONS PROTOTYPE	******************************/
void letsRollOne(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollTwo(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollThree(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollFour(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollFive(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollSix(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollSeven(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollEight(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollNine(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void letsRollZero(DISP_RANK_typedef rank, uint32_t delay, FlagStatus show);
void stepLED(DISP_RANK_typedef rank, FlagStatus a, FlagStatus b, FlagStatus c, FlagStatus d, FlagStatus e, FlagStatus f, FlagStatus g, uint32_t delay);

void gameMode(void);
