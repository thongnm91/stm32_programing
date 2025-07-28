#ifndef TIMER_H
#define TIMER_H

#include <stddef.h>
#include "stm32l1xx.h"
#include <stdint.h>

void tim2_output_compare_init(void);
void tim2_1hz_init(void);
void systickDelayMs(uint32_t delay);
void systickDelayUs(uint32_t delay);

#endif
