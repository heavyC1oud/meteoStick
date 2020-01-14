#pragma once

/*********************************************************************/

/*************************	DEFINE	******************************/
#define SENSOR_POLL_FR 125
#define TOUCH_POLL_FR 10
#define LONG_TOUCH_MAX_TIMER (2000 / TOUCH_POLL_FR)




typedef struct {
	TSC_CHANNEL_Typedef curState;
	TSC_CHANNEL_Typedef prevState;
	FlagStatus shortTouch;
	FlagStatus longTouch;
	uint32_t longTouchTimer;
} TOUCH_STATE_typedef;

/*************************	FUNCTIONS PROTOTYPE	******************************/
int initBME280(void);
int main(void);
