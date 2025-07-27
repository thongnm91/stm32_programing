/*
 * uart2.c
 *
 *  Created on: 29.5.2025
 *      Author: thong
 */

#include "include.h"
#define SYS_FREQ 32000000
#define UART_BAUDRATE 9600

void uart2_rx_interrupt_init(void)
{
	//Enable clock access to gpioA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//Set gpio PA3 mode alternate function
	GPIOA->MODER |= GPIO_MODER_MODER3_1;
	//Set gpio PA2 type UART_RX (AF07)
	GPIOA->AFR[0] |= 0x7U<<GPIO_AFRL_AFRL3_Pos; //0:AFRL 1:AFRH

	//Enable clock access uart2
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; //STM32L152_reference_manual.pdf p158/911
	//Configure baudrate
	uart_set_baudrate(USART2,SYS_FREQ,UART_BAUDRATE);

	//Config transfer direction
	USART2->CR1 = USART_CR1_TE | USART_CR1_RE; //TE:Transmit Enable, RE:Receive Enable

	//Enable RXNE interrupt
	USART2->CR1 |= USART_CR1_RXNEIE;

	//Enable UART2 interrupt in NVIC
	NVIC_EnableIRQ(USART2_IRQn);

	//Enable uart module
	USART2->CR1 |= USART_CR1_UE; //UE: UART Enable

}

//void USART2_IRQHandler(void){
//	//Check if RXNE is set
//	if(USART2->SR & USART_SR_RXNE){
//		uart2_write(uart2_read());
//	}
//}
