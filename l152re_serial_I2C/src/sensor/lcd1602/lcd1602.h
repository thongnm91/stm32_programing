#include "include.h"
#include "i2c/i2c.h"
#include "timer/timer.h"

#ifndef LCD1602_H
#define LCD1602_H

#define LCD_ADDR 0x27
#define LCD_LINE_1 0x00
#define LCD_LINE_2 0x40

/* LCD prototypes  */
void DisplayOnLCD(int value, char data_line1[], char data_line2[]);
void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendChar(uint8_t c);
void LCD_SendString(char *str);
void LCD_GoToXY(uint8_t x, uint8_t y);
void LCD_ClearAll(void);
void LCD_ClearFromPos(uint8_t x, uint8_t y);
void LCD_I2C1_Write(uint8_t address, int n, uint8_t* data);
void I2C1_Write_LCD(uint8_t address, int n, uint8_t* data);

#endif
