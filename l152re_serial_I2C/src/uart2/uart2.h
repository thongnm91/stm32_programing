#include "include.h"

#ifndef UART2_H
#define UART2_H


#define SYS_FREQ 32000000
#define UART_BAUDRATE 9600
uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart2_init();
void uart2_write(unsigned char ch);
void uart2_write_string(char* ch);
char uart2_read();


#endif
