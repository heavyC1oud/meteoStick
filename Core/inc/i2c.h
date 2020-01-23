#pragma once


/*************************	FUNCTION PROTOTYPE	******************************/
void initI2C(void);
int8_t I2CWrite(uint8_t devID, uint8_t addr, uint8_t* data, uint16_t count);
int8_t I2CRead(uint8_t devID, uint8_t addr, uint8_t* data, uint16_t count);
