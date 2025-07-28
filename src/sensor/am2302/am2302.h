#ifndef AM2302_H
#define AM2302_H

#include <stdint.h>
#include <stddef.h>
#include "stm32l1xx.h"
#include "time.h"
#include <stdio.h>
#include "timer/timer.h"
#include "uart2/uart2.h"
#include "debug_log/debug_logs.h"

int am2302Request(uint8_t *array);
int am2302ShowUart2(uint8_t* am2302) ;
int AM2302_Read_Data(float* humidity, float* temperature, uint8_t* data);

#endif
