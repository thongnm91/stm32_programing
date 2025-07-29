#include "include.h"

#ifndef TIMER_H
#define TIMER_H

void tim2_output_compare_init(void);
void tim2_1hz_init(void);
void systickDelayMs(uint32_t delay);
void systickDelayUs(uint32_t delay);

#endif
