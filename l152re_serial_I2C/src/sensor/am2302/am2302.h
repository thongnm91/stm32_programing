#include <include.h>
#include "timer/timer.h"
#include "uart2/uart2.h"
#include "debug_log/debug_logs.h"

#ifndef AM2302_H
#define AM2302_H

int am2302Request(uint8_t *array);
int am2302ShowUart2(uint8_t* am2302) ;
int AM2302_Read_Data(float* humidity, float* temperature, uint8_t* data);

#endif
