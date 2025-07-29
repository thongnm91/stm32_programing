#include "include.h"
#include  "i2c/i2c.h"
#include "timer/timer.h"

#ifndef DS1621_H
#define DS1621_H


/*Command p10/16*/
#define DS1621_ADDR 0x48	//
#define ADDR_FOR_READ 0x48  //
#define CMD_START_CONVERSATION 0xEE 	//
#define STOP_CONVERSATION 0x22 	//
#define CMD_READ_LAST_RESULT 0xAA	//
#define READ_COUNT_REMAIN 0xA8	//
#define READ_COUNT_PER_C 0xA9	//

int ds1621_read_temperature(uint8_t *data, uint8_t nbyte);
int ds1621_start();
#endif
