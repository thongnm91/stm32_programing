
#include "lcd1602.h"
void LCD_Init(void)
{
	/*
	Datasheet for commands/instructions
	https://panda-bg.com/datasheet/2134-091834-LCD-module-TC1602D-02WA0-16x2-STN.pdf
	https://www.electronicwings.com/sensors-modules/lcd-16x2-display-module
	https://mil.ufl.edu/3744/docs/lcdmanual/commands.html
	https://www.robofun.ro/docs/rc1602b-biw-esx.pdf
	*/
	LCD_SendCommand(0x02);	// set the LCD in 4-bit mode (D4-D7)
	LCD_SendCommand(0x28);	// 2 lines, 5x8 matrix, 4-bit mode
	LCD_SendCommand(0x0C);	// Display ON, cursor off
	LCD_SendCommand(0x80);	// Force the cursor to position (0,0)
}
void LCD_SendChar(uint8_t c)
{
	uint8_t nibble_r, nibble_l;
	uint8_t data[4];
	nibble_l = c & 0xf0;
	nibble_r = (c << 4) & 0xf0;
	data[0] = nibble_l | 0x0D;
	data[1] = nibble_l | 0x09;
	data[2] = nibble_r | 0x0D;
	data[3] = nibble_r | 0x09;
	LCD_I2C1_Write(LCD_ADDR, 4,(uint8_t *)data);
}
void LCD_SendCommand(uint8_t cmd)
{
	uint8_t nibble_r, nibble_l;
	uint8_t data[4]; //I²C using a 4-bit communication protocol
	nibble_l = cmd & 0xf0;
	nibble_r = (cmd << 4) & 0xf0;
	data[0] = nibble_l | 0x0C;	//0x0C: Typically, E=1, RS=0 (command mode), and backlight on
	data[1] = nibble_l | 0x08;	//0x08: E=0, RS=0, backlight on
	data[2] = nibble_r | 0x0C;
	data[3] = nibble_r | 0x08;
	LCD_I2C1_Write(LCD_ADDR, 4,(uint8_t *)data);
}

void LCD_SendString(char *str)
{
	while (*str)
		LCD_SendChar(*str++);
}

void DisplayOnLCD(int value, char data_line1[], char data_line2[])
{
	sprintf(data_line2, "%d", value);
	LCD_ClearFromPos(0,0);
	LCD_GoToXY(0, LCD_LINE_1);
	LCD_SendString(data_line1);
	LCD_GoToXY(0, LCD_LINE_2);
	LCD_SendString(data_line2);
}

void LCD_GoToXY(uint8_t x, uint8_t y)
{
	uint8_t LCD_DDRAM_ADDR = 0x80;

	if (y == 0)
		LCD_SendCommand(LCD_DDRAM_ADDR | (LCD_LINE_1 + x));
	else
		LCD_SendCommand(LCD_DDRAM_ADDR | (LCD_LINE_2 + x));
}

void LCD_ClearAll(void)
{
	LCD_SendCommand(0x01); // 0x01 is the command to clear the LCD display
}
void LCD_ClearFromPos(uint8_t x, uint8_t y)
{
	char str[32] = "";
	LCD_GoToXY(x, y);
	LCD_SendString(str);
}
void LCD_I2C1_Write(uint8_t address, int n, uint8_t* data)
{
	I2C1_Bus_Test();//check_pass(I2C1_Bus_Test(),"I2C1_Bus_Test");

	I2C_DI_ACK();//check_pass(I2C_DI_ACK(),"I2C_DI_ACK");

	I2C_Start();//check_pass(I2C_Start(),"I2C_Start");

	I2C_Write_Addr(address<<1);//check_pass(I2C_Write_Addr(address<<1),"I2C_Write_Addr");

	I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");

	//write data
	for(int i=0;i<n;i++)
	{
		while(!(I2C1->SR1 & 0x80)){}	//wait until data register empty p.689
		I2C1->DR=*data++;				//send command
	}
	while(!(I2C1->SR1 & 4)){}		//wait until byte transfer finished p.690
	I2C_Stop();//check_pass(I2C_Stop(),"I2C_Stop");
	systickDelayMs(2);
}
void I2C1_Write_LCD(uint8_t address, int n, uint8_t* data)
{
	int i;

	while(I2C1->SR2 & 2){}			//wait until bus not busy

	I2C_DI_ACK();				//Acknowledge clear p.682
	I2C1->CR1 |= 0x100;				//generate start p.694
	while(!(I2C1->SR1&1)){}			//wait until start condition generated

	I2C1->DR=address<<1;			//transmit slave address
	while(!(I2C1->SR1 & 2)){}		//wait until end of address transmission p.690

	I2C_Clear_AddrFlag();			//Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag p691

	//write data
	for(i=0;i<n;i++)
	{
		while(!(I2C1->SR1 & 0x80)){}	//wait until data register empty p.689
		I2C1->DR=*data++;				//send command
	}

	while(!(I2C1->SR1 & 4)){}		//wait until byte transfer finished p.690
	I2C1->CR1 |= (1<<9);			//generate stop
	systickDelayMs(5);
}
