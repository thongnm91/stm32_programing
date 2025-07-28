#include "timer.h"

/*
 * Alternative function TIM2
 * */

//#include "include.h"

void tim2_output_compare_init(void){
	//Enable clock access to GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//Set PA5 alternate function type to TIM2_CH1 (AF01)
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->AFR[0] |= 1 << GPIO_AFRL_AFRL5_Pos;

	//Enable clock access to tim2 - PA5
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//Set prescale value max 2^16 (p.383/911)
	TIM2->PSC = 32000; // 32.000 x 1.000 = 32.000.000 x 1s

	//Set auto-reload value max 2^16 (p.479/911)
	TIM2->ARR = 1000;

	//Clear counter
	TIM2->CNT = 0;

	//Set output compare toggle mode
	TIM2->CCMR1 = TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;

	//Enable tim2 ch1 in compare mode
	TIM2->CCER |= TIM_CCER_CC1E;

	//Enable timer
	TIM2->CR1 = TIM_CR1_CEN;

}
