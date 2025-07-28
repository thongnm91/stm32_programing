/*
 * Alternative function TIM2
 * */

#include "include.h"

void tim3_input_capture_init(void){
	//Enable clock access to GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//Set PA6 alternate function type to TIM3_CH1 (AF02) (p.47/136)
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	GPIOA->AFR[0] |= 2U << GPIO_AFRL_AFRL6_Pos;

	//Enable clock access to tim3 - PA6
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	//Set prescale value max 2^16 (p.383/911)
	TIM3->PSC = 32000; // 32.000 x 1.000 = 32.000.000 x 1s

	//Set CH1 to input capture
	TIM3->CCMR1 = TIM_CCMR1_CC1S_0;

	//Set CH1 to capture at rising edge
	TIM3->CCER = TIM_CCER_CC1E;

	//Enable tim3
	TIM3->CR1 |= TIM_CR1_CEN;

}
