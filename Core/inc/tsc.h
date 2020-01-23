#pragma once

/*************************	DEFINE	******************************/
#define TSC_CALIBRATION_COUNT 11
#define TSC_DETECT_EDGE 100

/*************************	TYPEDEF	******************************/
typedef enum {
	TSC_CHANNEL_EMPTY,
	TSC_CHANNEL_DETECT,
	TSC_CHANNEL_ERROR,
} TSC_CHANNEL_Typedef;

/*************************	VARIABLE	******************************/
extern volatile TSC_CHANNEL_Typedef touchKey;

/*************************	FUNCTION PROTOTYPE	******************************/
void initTSC(void);
