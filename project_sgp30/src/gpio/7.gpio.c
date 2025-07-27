/*
 * GPIO mode: Input (I), Output (O), Alternate function (a), Analog (A)
 * GPIO status: On (1), Off(0)
 * */

#include "include.h"

void gpioa_init(uint8_t pin, uint8_t mode, uint8_t status){
	//Clock bus
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;


	//GPIO mode of pin
	switch (mode){
		case 0:
			GPIOA->MODER |= GPIO_MODER_MODER5_0;
			break;
		case 1:
			GPIOA->MODER &= ~GPIO_MODER_MODER5;
			break;
	}

	//GPIO status
	switch (status){
		case 1:
			GPIOA->ODR = GPIO_ODR_ODR_5;
			break;
		case 0:
			GPIOA->ODR = ~GPIO_ODR_ODR_5;
			break;
		default:
			break;
	}
}
