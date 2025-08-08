#include "include.h"
#include "uart2/uart2.h"

#ifndef DEBUG_LOGS
#define DEBUG_LOGS

#define LOG_LENGH 	100
//#include "include.h"
typedef enum{
	DONE = 0,
	NSTOP = 0,
	STOP = 1,
	FAIL = 1,
	PASS,
	START,
	TIMEOUT,
	I2C_SUCCESS = 10,
	I2C_ERROR_TIMEOUT_25MS,
    I2C_ERROR_SMBALERT,
    I2C_ERROR_NACK,
    I2C_ERROR_BUS_ERROR,
    I2C_ERROR_ARBITRATION_LOST
} Config_st;

void check_pass(int check, char* message);
void conv_int_ascii(char *buf, unsigned int d, int base);

#endif


