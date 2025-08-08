#include "include.h"
#include "i2c/i2c.h"
#include "timer/timer.h"
#include "debug_log/debug_logs.h"

#ifndef BMP085_H
#define BMP085_H

#define BMP085_ADDR_DEF 0x77
#define BMP085_ADDR_W 0xEE
#define BMP085_ADDR_R 0xEF
#define BMP085_CMD_TEMP 0x2E
#define BMP085_CMD_PRES 0x34
#define BMP085_REG_CONTROL 0xF4
#define BMP085_REG_MSB 0xF6
#define BMP085_REG_LSB 0xF7
#define BMP085_ID 0xD0


typedef struct  {
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;
} bmp085_calibration_param;

int16_t bmp085_readS16(uint8_t reg) ;
uint16_t bmp085_read_16(uint8_t reg);
void bmp085_get_cal_param(bmp085_calibration_param *cal) ;
uint16_t bmp085_get_ut() ;
uint32_t bmp085_get_up(uint8_t oss) ;
int32_t bmp085_calculate_B5(int32_t ut, const bmp085_calibration_param *cal) ;
int32_t bmp085_calculate_temperature(int32_t ut, const bmp085_calibration_param *cal) ;
int32_t bmp085_calculate_pressure(uint32_t up, int32_t ut, uint8_t oss, const bmp085_calibration_param *cal) ;
double bmp085_calculate_altitude(uint32_t* pressure);

#endif
