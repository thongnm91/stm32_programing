#ifndef I2C_H
#define I2C_H

#include "debug_log/debug_logs.h"
#include <stdint.h>
#include <stddef.h>
#include "stm32l1xx.h"

#define TIMEOUT	100000000 //100us

/*Main function*/
int I2C1_GPIO_Init();
int I2C1_Init();
int I2C_Start();
int I2C_Write_Addr(uint8_t addr);
int I2C_Write_Data(uint8_t data);
int I2C_Stop();
int I2C1_Bus_Test();
int I2C_POS_Read();
int I2C_EN_ACK();
int I2C_DI_ACK();
int I2C_Check_Overrun();
int I2C_Check_ACK_Failure();
int I2C_Read_Data(uint8_t* data);
int I2C_Clear_AddrFlag();

/*Sub function*/


#endif
