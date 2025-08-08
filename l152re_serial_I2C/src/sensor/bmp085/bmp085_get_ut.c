#include "bmp085.h"

// Function to get uncompensated temperature (UT)
uint16_t bmp085_get_ut() {
    // 1. Write temperature measurement command to control register
	uint8_t cmd[2] = {BMP085_REG_CONTROL, BMP085_CMD_TEMP};
	I2C_Write_Cmd(cmd,2,STOP,BMP085_ADDR_DEF);

    // 2. Wait at least 4.5 ms for measurement to complete (datasheet)
    systickDelayMs(5);

    // 3. Read raw uncompensated temperature from registers 0xF6 (MSB) and 0xF7 (LSB)
	uint8_t data[2];
	cmd[0] = BMP085_REG_MSB;
	I2C_Write_Cmd(cmd,1,NSTOP,BMP085_ADDR_DEF);

	I2C_Read_nData(data,2,BMP085_ADDR_DEF);
    return ((uint16_t)data[0] << 8) | data[1];
}
