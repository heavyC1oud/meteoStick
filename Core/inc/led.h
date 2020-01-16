#pragma once

/*********************************************************************/

/*************************	DEFINE	**********************************/
//	set segment
#define SET_DIG_ONE_A (GPIOB->BSRR = GPIO_BSRR_BS_12) 		//	set segment "A" on ONE digit
#define SET_DIG_ONE_B (GPIOB->BSRR = GPIO_BSRR_BS_11) 		//	set segment "B" on ONE digit
#define SET_DIG_ONE_C (GPIOA->BSRR = GPIO_BSRR_BS_0) 		//	set segment "C" on ONE digit
#define SET_DIG_ONE_D (GPIOA->BSRR = GPIO_BSRR_BS_1) 		//	set segment "D" on ONE digit
#define SET_DIG_ONE_E (GPIOA->BSRR = GPIO_BSRR_BS_2) 		//	set segment "E" on ONE digit
#define SET_DIG_ONE_F (GPIOB->BSRR = GPIO_BSRR_BS_10) 		//	set segment "F" on ONE digit
#define SET_DIG_ONE_G (GPIOB->BSRR = GPIO_BSRR_BS_2) 		//	set segment "G" on ONE digit

#define SET_DIG_TEN_A (GPIOA->BSRR = GPIO_BSRR_BS_7) 		//	set segment "A" on TEN digit
#define SET_DIG_TEN_B (GPIOA->BSRR = GPIO_BSRR_BS_6) 		//	set segment "B" on TEN digit
#define SET_DIG_TEN_C (GPIOA->BSRR = GPIO_BSRR_BS_5) 		//	set segment "C" on TEN digit
#define SET_DIG_TEN_D (GPIOA->BSRR = GPIO_BSRR_BS_3) 		//	set segment "D" on TEN digit
#define SET_DIG_TEN_E (GPIOA->BSRR = GPIO_BSRR_BS_4) 		//	set segment "E" on TEN digit
#define SET_DIG_TEN_F (GPIOB->BSRR = GPIO_BSRR_BS_1) 		//	set segment "F" on TEN digit
#define SET_DIG_TEN_G (GPIOB->BSRR = GPIO_BSRR_BS_0) 		//	set segment "G" on TEN digit

//	reset segment
#define RESET_DIG_ONE_A (GPIOB->BSRR = GPIO_BSRR_BR_12) 	//	reset segment "A" on ONE digit
#define RESET_DIG_ONE_B (GPIOB->BSRR = GPIO_BSRR_BR_11) 	//	reset segment "B" on ONE digit
#define RESET_DIG_ONE_C (GPIOA->BSRR = GPIO_BSRR_BR_0) 	//	reset segment "C" on ONE digit
#define RESET_DIG_ONE_D (GPIOA->BSRR = GPIO_BSRR_BR_1) 		//	reset segment "D" on ONE digit
#define RESET_DIG_ONE_E (GPIOA->BSRR = GPIO_BSRR_BR_2) 		//	reset segment "E" on ONE digit
#define RESET_DIG_ONE_F (GPIOB->BSRR = GPIO_BSRR_BR_10) 	//	reset segment "F" on ONE digit
#define RESET_DIG_ONE_G (GPIOB->BSRR = GPIO_BSRR_BR_2) 		//	reset segment "G" on ONE digit

#define RESET_DIG_TEN_A (GPIOA->BSRR = GPIO_BSRR_BR_7) 		//	reset segment "A" on TEN digit
#define RESET_DIG_TEN_B (GPIOA->BSRR = GPIO_BSRR_BR_6) 		//	reset segment "B" on TEN digit
#define RESET_DIG_TEN_C (GPIOA->BSRR = GPIO_BSRR_BR_5) 		//	reset segment "C" on TEN digit
#define RESET_DIG_TEN_D (GPIOA->BSRR = GPIO_BSRR_BR_3) 		//	reset segment "D" on TEN digit
#define RESET_DIG_TEN_E (GPIOA->BSRR = GPIO_BSRR_BR_4) 		//	reset segment "E" on TEN digit
#define RESET_DIG_TEN_F (GPIOB->BSRR = GPIO_BSRR_BR_1) 		//	reset segment "F" on TEN digit
#define RESET_DIG_TEN_G (GPIOB->BSRR = GPIO_BSRR_BR_0) 		//	reset segment "G" on TEN digit

#define SET_LED_TEMP (GPIOB->BSRR = GPIO_BSRR_BS_14)		//	set temperature LED
#define SET_LED_HUM (GPIOB->BSRR = GPIO_BSRR_BS_13)			//	set humidity LED
#define SET_LED_BAR (GPIOB->BSRR = GPIO_BSRR_BS_15)			//	set pressure LED

#define RESET_LED_TEMP (GPIOB->BSRR = GPIO_BSRR_BR_14)		//	reset temperature LED
#define RESET_LED_HUM (GPIOB->BSRR = GPIO_BSRR_BR_13)		//	reset humidity LED
#define RESET_LED_BAR (GPIOB->BSRR = GPIO_BSRR_BR_15)		//	reset pressure LED

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

typedef enum {
	DISP_RANK_ONE,
	DISP_RANK_TEN,
} DISP_RANK_typedef;

typedef enum {
	DISP_DATA_ZERO = 0,
	DISP_DATA_ONE,
	DISP_DATA_TWO,
	DISP_DATA_THREE,
	DISP_DATA_FOUR,
	DISP_DATA_FIVE,
	DISP_DATA_SIX,
	DISP_DATA_SEVEN,
	DISP_DATA_EIGHT,
	DISP_DATA_NINE,
} DISP_DATA_typedef;


/*************************	FUNCTIONS PROTOTYPE	******************************/
void initLED(void);
void resetDispOne(void);
void resetDispTen(void);
void resetDisp(void);
void setZero(DISP_RANK_typedef rank);
void setOne(DISP_RANK_typedef rank);
void setTwo(DISP_RANK_typedef rank);
void setThree(DISP_RANK_typedef rank);
void setFour(DISP_RANK_typedef rank);
void setFive(DISP_RANK_typedef rank);
void setSix(DISP_RANK_typedef rank);
void setSeven(DISP_RANK_typedef rank);
void setEight(DISP_RANK_typedef rank);
void setNine(DISP_RANK_typedef rank);
void setDispNum(uint8_t num);
void setLedInfo(LED_INFO_typedef led, LED_ACT_typedef act);
