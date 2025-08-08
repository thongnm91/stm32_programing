#include "bmp085.h"
// Function to get calibration parameters
void bmp085_get_cal_param(bmp085_calibration_param *cal) {
	cal->ac1 = bmp085_readS16(0xAA);
	cal->ac2 = bmp085_readS16(0xAC);
	cal->ac3 = bmp085_readS16(0xAE);
	cal->ac4 = bmp085_read_16(0xB0);
	cal->ac5 = bmp085_read_16(0xB2);
	cal->ac6 = bmp085_read_16(0xB4);
	cal->b1  = bmp085_readS16(0xB6);
	cal->b2  = bmp085_readS16(0xB8);
	cal->mb  = bmp085_readS16(0xBA);
	cal->mc  = bmp085_readS16(0xBC);
	cal->md  = bmp085_readS16(0xBE);
}

// Reads an unsigned 16-bit integer from the BMP085
uint16_t bmp085_read_16(uint8_t reg) {
	uint8_t cmd[1] = {reg};
	I2C_Write_Cmd(cmd,1,STOP,BMP085_ADDR_DEF);

    uint8_t data[2];
    I2C_Read_nData(data,2,BMP085_ADDR_DEF);
    return ((uint16_t)data[0] << 8) | data[1];
}

// Reads a signed 16-bit integer from the BMP085
int16_t bmp085_readS16(uint8_t reg) {
    return (int16_t)bmp085_read_16(reg);
}




