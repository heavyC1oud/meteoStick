
#include "stm32f0xx.h"
#include "delay.h"
#include "i2c.h"


/*************************	FUNCTION	******************************/

/**********************************************************************
*	function name	:	initI2C
*	Description		:	I2C initialization
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
void initI2C(void)
{
	//	I2C1
	//	SCL - PB6
	//	SDA - PB7
	//	I2C frequency 100 kHz
	//	I2C clock Mux - HSI

	//	enable port B bus
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	//	PORTB6
	//	MODER6[1:0] = 10 - alternate function mode
	GPIOB->MODER &= ~GPIO_MODER_MODER6;
	GPIOB->MODER |= GPIO_MODER_MODER6_1;

	//	AFRL6[3:0] = 0001 - alternate function 1
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL6);
	GPIOB->AFR[0] |= (0x01 << GPIO_AFRL_AFSEL6_Pos);

	//	OTYPER6 = 1 - output open-drain
	GPIOB->OTYPER |= GPIO_OTYPER_OT_6;

	//	OSPEEDR6[1:0] = 11 - High speed
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR6;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR6_0 | GPIO_OSPEEDR_OSPEEDR6_1;

	//	PUPDR6[1:0] = 01 - pull-up
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_0;

	//	PORTB7
	//	MODER7[1:0] = 10 - alternate function mode
	GPIOB->MODER &= ~GPIO_MODER_MODER7;
	GPIOB->MODER |= GPIO_MODER_MODER7_1;

	//	AFRL7[3:0] = 0001 - alternate function 1
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL7);
	GPIOB->AFR[0] |= (0x01 << GPIO_AFRL_AFSEL7_Pos);

	//	OTYPER7 = 1 - output open-drain
	GPIOB->OTYPER |= GPIO_OTYPER_OT_7;

	//	OSPEEDR7[1:0] = 11 - High speed
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR7;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7_0 | GPIO_OSPEEDR_OSPEEDR7_1;

	//	PUPDR7[1:0] = 01 - pull-up
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_0;

	//	enable I2C clock
	RCC->CFGR3 &= ~RCC_CFGR3_I2C1SW;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	//	disable Own address 1
	I2C1->OAR1 &= ~I2C_OAR1_OA1EN;

	//	disable Own address 2
	I2C1->OAR2 &= ~I2C_OAR2_OA2EN;

	//	disable general call
	I2C1->CR1 &= ~I2C_CR1_GCEN;

	//	clear NOSTRETCH bit for master mode
	I2C1->CR1 &= ~I2C_CR1_NOSTRETCH;

	//	disable peripheral for settings
	I2C1->CR1 &= ~I2C_CR1_PE;

	//	disable analog filter
	I2C1->CR1 &= ~I2C_CR1_ANFOFF;

	//	disable digital filter
	I2C1->CR1 &= ~I2C_CR1_DNF;

	//	set timings (calculate in CubeMX)
	I2C1->TIMINGR = 0x2000090E;

	//	enable peripheral
	I2C1->CR1 |= I2C_CR1_PE;

	//	disable SMBus Host address
	I2C1->CR1 &= ~I2C_CR1_SMBHEN;

	//	disable SMBus device default address
	I2C1->CR1 &= ~I2C_CR1_SMBDEN;

	//	enable autoend mode
	I2C1->CR2 |= I2C_CR2_AUTOEND;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	I2CWrite
*	Description		:	write bytes using I2C interface
*	Arguments		:	devID - slave address
*					:	addr - start address to write
*					:	data - data to write
*					:	amount of data to write
*	Return value	:	error info
**********************************************************************/
int8_t I2CWrite(uint8_t devID, uint8_t addr, uint8_t* data, uint16_t count)
{
	//	set slave address
	I2C1->CR2 &= ~I2C_CR2_SADD;
	I2C1->CR2 |=  devID << I2C_CR2_SADD_Pos;

	//	set number bytes to send
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= (count + sizeof(addr)) << I2C_CR2_NBYTES_Pos;

	//	set transfer direction to write
	I2C1->CR2 &= ~I2C_CR2_RD_WRN;

	//	generate START condition
	I2C1->CR2 |= I2C_CR2_START;

	//	send address
	I2C1->TXDR = addr;

	if(count == 0) {
		return 0;
	}

	//	wait TXE flag or NACK flag Is Set
	while((!(I2C1->ISR & I2C_ISR_TXE)) && (!(I2C1->ISR & I2C_ISR_NACKF))) {
		if(I2C1->ISR & I2C_ISR_NACKF) {
			I2C1->ISR &= ~I2C_ISR_NACKF;
			return 1;
		}
	}

	//	transmit Data
	for(uint16_t i = 0; i < count; i++)
	{
		//	write data
		I2C1->TXDR = data[i];

		if(i != (count - 1)) {
			//	wait TXE flag or NACK flag Is Set
			while((!(I2C1->ISR & I2C_ISR_TXE)) && (!(I2C1->ISR & I2C_ISR_NACKF))) {
				if(I2C1->ISR & I2C_ISR_NACKF) {
					I2C1->ISR &= ~I2C_ISR_NACKF;
					return 1;
				}
			}
		}
	}

	delayMs(1);

	return 0;
}
/*********************************************************************/


/**********************************************************************
*	function name	:	I2CRead
*	Description		:	read bytes using I2C interface
*	Arguments		:	devID - slave address
*					:	addr - start address to read
*					:	data - data to read
*					:	amount of data to read
*	Return value	:	error info
**********************************************************************/
int8_t I2CRead(uint8_t devID, uint8_t addr, uint8_t* data, uint16_t count)
{
	//	set slave address
	I2C1->CR2 &= ~I2C_CR2_SADD;
	I2C1->CR2 |=  devID << I2C_CR2_SADD_Pos;

	//	set number bytes to send
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= (sizeof(addr)) << I2C_CR2_NBYTES_Pos;

	//	set transfer direction to write
	I2C1->CR2 &= ~I2C_CR2_RD_WRN;

	//	generate START condition
	I2C1->CR2 |= I2C_CR2_START;

	//	send address
	I2C1->TXDR = addr;

	//	wait TXE flag or NACK flag Is Set
	while((!(I2C1->ISR & I2C_ISR_TXE)) && (!(I2C1->ISR & I2C_ISR_NACKF))) {
		if(I2C1->ISR & I2C_ISR_NACKF) {
			I2C1->ISR &= ~I2C_ISR_NACKF;
			return 1;
		}
	}

	//	set number bytes to send
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= count << I2C_CR2_NBYTES_Pos;

	//	set transfer direction to read
	I2C1->CR2 |= I2C_CR2_RD_WRN;

	//	generate START condition
	I2C1->CR2 |= I2C_CR2_START;

	//	receive Data
	for(uint16_t i = 0; i < count; i++)
	{
		//	wait RXNE flag Is Set
		while(!(I2C1->ISR & I2C_ISR_RXNE));

		//	read data
		data[i] = (uint8_t)I2C1->RXDR;
	}

	return 0;
}
/*********************************************************************/
