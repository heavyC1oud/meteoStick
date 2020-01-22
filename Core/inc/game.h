#pragma once

#include "stm32f0xx.h"
#include "led.h"


/*************************	FUNCTIONS PROTOTYPE	******************************/
void letsRollOne(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollTwo(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollThee(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollFour(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollFive(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollSix(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollSeven(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollEight(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollNine(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void letsRollZero(DISP_RANK_typedef rank, uint32_t delay, FlagStatus stop);
void stepLED(DISP_RANK_typedef rank, FlagStatus a, FlagStatus b, FlagStatus c, FlagStatus d, FlagStatus e, FlagStatus f, FlagStatus g, uint32_t delay);

void gameMode(void);
