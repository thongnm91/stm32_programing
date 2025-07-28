#ifndef SGP30_H
#define SGP30_H
//#include "include.h"
#include "debug_log/debug_logs.h"
#include "i2c/i2c.h"
#include <stddef.h>
#include "stm32l1xx.h"

#define SGP30_ADDR     0x58
#define CMD_RESET	0x0006
#define CMD_INIT  (0x2003)
#define CMD_MEASURE  (0x2008)
#define CMD_GET_BASELINE  (0x2015)
#define SGP30_SET_IAQ_BASELINE  (0x201e)
#define SGP30_SET_ABSOLUTE_HUMIDITY  (0x2061)
#define SGP30_MEASURE_TEST  (0x2032)
#define SGP30_GETFEATURE_SET  (0x202f)
#define SGP30_MEASURE_RAW  (0x2050)
#define SGP30_GET_TVOC_INCEPTIVE_BASELINE  (0x20b3)
#define SGP30_SET_TVOC_BASELINE  (0x2077)

int SGP30_Write_Cmd(uint16_t cmd,uint8_t condition);
int SGP30_Read_Data(uint16_t *data, uint8_t len);
int SGP30_Init();
int SGP30_Measure(uint16_t *co2, uint16_t *tvoc);
uint8_t sgp30_crc(uint8_t *data, int count);

typedef enum{
	NSTOP=0,
	STOP,
} Config_Write_Cmd;
#endif
