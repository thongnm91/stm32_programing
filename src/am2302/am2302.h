#ifndef AM2302_H
#define AM2302_H

#include <stdint.h>
#include <stddef.h>
#include "stm32l1xx.h"
#include "time.h"

int am2302Request(uint8_t *array);
void am2302ShowUart2(uint8_t* am2302) ;


#endif AM2302_H
