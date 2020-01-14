
#include "stm32f0xx.h"
#include "tsc.h"

/*************************	VARIABLE	******************************/
volatile TSC_CHANNEL_Typedef touchAlert = TSC_CHANNEL_EMPTY;

static uint32_t channelBase = 0;

/*************************	FUNCTIONS PROTOTYPE	******************************/
static void calibratingTSC(void);

/*************************	FUNCTION	******************************/

/**********************************************************************
*	function name	:	initTSC
*	Description		:	touch sensing controller initialization
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void initTSC(void)
{
	//	TSC
	//	Sample pin - PB3 (TS_G5_IO1)
	//	Sensor pin - PB4 (TS_G5_IO2)
	//	enable port B bus
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	//	PORTB4
	//	MODER4[1:0] = 10 - Alternate function mode
	GPIOB->MODER &= ~GPIO_MODER_MODER4;
	GPIOB->MODER |= GPIO_MODER_MODER4_1;

	//	AFRL4[3:0] = 0011 - alternate function 3
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL4);
	GPIOB->AFR[0] |= (0x03 << GPIO_AFRL_AFSEL4_Pos);

	//	OTYPER4 = 0 - Output push-pull for channel IOs
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;

	//	OSPEEDR4[1:0] = 01 - Medium speed
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR4;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR4_0;

	//	PUPDR4[1:0] = 00 - No pull-up, pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4;

	//	BSRR4 = 1 - reset bit
	GPIOB->BSRR = GPIO_BSRR_BR_4;

	//	PORTB3
	//	MODER3[1:0] = 10 - Alternate function mode
	GPIOB->MODER &= ~GPIO_MODER_MODER3;
	GPIOB->MODER |= GPIO_MODER_MODER3_1;

	//	AFRL3[3:0] = 0011 - alternate function 3
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL3);
	GPIOB->AFR[0] |= (0x03 << GPIO_AFRL_AFSEL3_Pos);

	//	OTYPER3 = 1 - Output open-drain for sampling capacitor IOs
	GPIOB->OTYPER |= GPIO_OTYPER_OT_3;

	//	OSPEEDR3[1:0] = 01 - Medium speed
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR3;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR3_0;

	//	PUPDR3[1:0] = 00 - No pull-up, pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR3;

	//	BSRR3 = 1 - reset bit
	GPIOB->BSRR |= GPIO_BSRR_BR_3;


	//	Enable TSC clock
	RCC->AHBENR |= RCC_AHBENR_TSCEN;

	//	Enable TSC
	TSC->CR |= TSC_CR_TSCE;

	//	Acquisition mode - Normal acquisition mode
	TSC->CR &= ~TSC_CR_AM;

	//	I/O Default mode - I/Os are forced to output push-pull low
	TSC->CR &= ~TSC_CR_IODEF;

	//	Max count value - 16383
	TSC->CR &= ~TSC_CR_MCV;
	TSC->CR |= TSC_CR_MCV_1 | TSC_CR_MCV_2;

	//	Pulse generator prescaler - fhclk/8
	TSC->CR &= ~(TSC_CR_PGPSC);
	TSC->CR |= TSC_CR_PGPSC_0 | TSC_CR_PGPSC_1;

	//	Spread spectrum disable
	TSC->CR &= ~TSC_CR_SSE;

	//	Charge transfer pulse low - 8x tpgclk
	TSC->CR &= ~TSC_CR_CTPL;
	TSC->CR |= TSC_CR_CTPL_0 | TSC_CR_CTPL_1 | TSC_CR_CTPL_2;

	//	Charge transfer pulse high - 8x tpgclk
	TSC->CR &= ~TSC_CR_CTPH;
	TSC->CR |= TSC_CR_CTPH_0 | TSC_CR_CTPH_1 | TSC_CR_CTPH_2;

	//	Disable Schmitt trigger hysteresis mode
	TSC->IOHCR &= ~(TSC_IOHCR_G5_IO1 | TSC_IOHCR_G5_IO2);

	//	Set pin sampling mode
	TSC->IOSCR |= TSC_IOSCR_G5_IO1;

	//	Set pin channel mode
	TSC->IOCCR |= TSC_IOCCR_G5_IO2;

	//	Enable analog group
	TSC->IOGCSR |= TSC_IOGCSR_G5E;

	//	Calibrating sensors
	calibratingTSC();

	//	Clear interrupt flag
	TSC->ICR |= TSC_ICR_EOAIC | TSC_ICR_MCEIC;

	//	Enable interrupt
	TSC->IER |= TSC_IER_EOAIE | TSC_IER_MCEIE;

	//	NVIC touch sensing interrupt set
	NVIC_EnableIRQ(TSC_IRQn);
	NVIC_SetPriority(TSC_IRQn, 11);

	//	Start acquisition
	TSC->CR |= TSC_CR_START;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	calibratingTSC
*	Description		:	touch sensing controller calibration
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
static void calibratingTSC(void)
{
	for(uint16_t i = 0; i < TSC_CALIBRATION_COUNT; i++) {
		//	start acquisition
		TSC->CR |= TSC_CR_START;

		//	wait until acquisition ends
		while((TSC->ISR & TSC_ISR_EOAF) == 0);

		channelBase += TSC->IOGXCR[4];

		//	clear acquisition end interrupt flag
		TSC->ICR |= TSC_ICR_EOAIC;
	}

	//	calculate base channel value
	channelBase /= TSC_CALIBRATION_COUNT;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	TSC_IRQHandler
*	Description		:	Touch sensing interrupt handle
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void TSC_IRQHandler(void)
{
	if(TSC->IOGXCR[4] < (channelBase - TSC_DETECT_EDGE)) {
		touchAlert = TSC_CHANNEL_DETECT;
	}
	else {
		touchAlert = TSC_CHANNEL_EMPTY;
	}

	//	Clear interrupt flag
	TSC->ICR |= TSC_ICR_EOAIC | TSC_ICR_MCEIC;

	//	start acquisition
	TSC->CR |= TSC_CR_START;
}
/*********************************************************************/







