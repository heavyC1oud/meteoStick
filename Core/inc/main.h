#pragma once

/*********************************************************************/

/*************************	DEFINE	******************************/
#define IWDG_START 0xCCCC
#define IWDG_WRITE_ACCESS 0x5555
#define IWDG_REFRESH 0xAAAA
#define IWDG_PRESCALER_256 0x07				//	prescaler value 256
#define IWDG_COUNT_VALUE_4_S 0x271			//	4 seconds WDT delay value (with 256 prescaler value)
#define IWDT_REFRESH_DELAY 100

#define SENSOR_POLL_FR 125
#define TOUCH_POLL_FR 10
#define LONG_TOUCH_MAX_TIMER (2000 / TOUCH_POLL_FR)
#define TURN_OFF_TIMER_DELAY 26000

typedef enum {
	MODE_OFF = 0,
	MODE_TEMP,
	MODE_HUM,
	MODE_BAR,
	MODE_GAME,
} MODE_typedef;

typedef struct {
	TSC_CHANNEL_Typedef curState;
	TSC_CHANNEL_Typedef prevState;
	FlagStatus shortTouch;
	FlagStatus longTouch;
	FlagStatus longTouchOnce;
	uint32_t longTouchTimer;
} TOUCH_STATE_typedef;



/*************************	FUNCTIONS PROTOTYPE	******************************/
void initWDG(void);
void timerCB(TimerHandle_t xTimer);
int initBME280(void);
void setMode(void);
int main(void);
