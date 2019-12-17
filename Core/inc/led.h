#pragma once

/*********************************************************************/

/*************************	DEFINE	**********************************/

/*************************	TYPEDEF	**********************************/
typedef enum {
	LED_TEMP,
	LED_HUM,
	LED_BAR,
} LED_INFO_typedef;

typedef enum {
	LED_OFF,
	LED_ON,
} LED_ACT_typedef;


/*************************	FUNCTIONS PROTOTYPE	******************************/
void initLED(void);
void turnOffDisp(void);
void showNumber(uint8_t num);
void switchInfoLed(LED_INFO_typedef led, LED_ACT_typedef act);
