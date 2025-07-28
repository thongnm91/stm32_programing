#include "include.h"
//ADC
void pa0_adc_init(void){
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //Bus_ckl APB1 enable for ADC1
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //Bus_ckl AHB enable for GPIOA
	GPIOA->MODER |= GPIO_MODER_MODER0; //GPIOA mode ADC for PA0
	//Conversion sequence start
	ADC1->SQR5 |= 0; //PA0 start first
	//Conversion sequence length
	ADC1->SQR1 |= 0; //1 conversion;
	//ADC 12bit
	ADC1->CR1 &= ~ADC_CR1_RES;
	//Enable ADC module
	ADC1->CR2 |= ADC_CR2_ADON;

}
void adc_start_conver(void){
	//Enable continuous conversion
	ADC1->CR2 |= ADC_CR2_CONT;
	//Start ADC conversion
	ADC1->CR2 |= ADC_CR2_SWSTART;
}
uint32_t adc_read(void){
	//Wait for Regular channel end of conversion to be completed
	while(!(ADC1->SR & ADC_SR_EOC)){}
	//Read conversion result
	return (ADC1->DR);
}
