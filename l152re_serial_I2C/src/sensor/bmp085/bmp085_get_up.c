#include "bmp085.h"


// Reads uncompensated pressure value
uint32_t bmp085_get_up(uint8_t oss) {
    // 1. Write temperature measurement command to control register
	uint8_t cmd[2] = {BMP085_REG_CONTROL, BMP085_CMD_PRES + (oss << 6)};
	I2C_Write_Cmd(cmd,2,STOP,BMP085_ADDR_DEF);

    // 2. Wait for conversion time based on OSS, per datasheet:
    switch (oss) {
        case 0: systickDelayMs(5);    break;  // 4.5 ms typical
        case 1: systickDelayMs(8);    break;  // 7.5 ms typical
        case 2: systickDelayMs(14);   break;  // 13.5 ms typical
        case 3: systickDelayMs(26);   break;  // 25.5 ms typical
        default: systickDelayMs(26);  break;
    }

    // 3. Read raw uncompensated temperature from registers 0xF6 (MSB) and 0xF7 (LSB)
	uint8_t data[3]={0};
	cmd[0] = BMP085_REG_MSB;
	I2C_Write_Cmd(cmd,1,NSTOP,BMP085_ADDR_DEF);

	I2C_Read_nData(data,3,BMP085_ADDR_DEF);
	uint32_t up = ((((uint32_t)data[0] << 16) |((uint32_t)data[1] << 8) | (uint32_t)data[2])) >> (8-oss);
    return up; //p14 bmp datasheet
}
