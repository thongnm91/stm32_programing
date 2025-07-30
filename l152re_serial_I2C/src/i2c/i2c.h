#include "include.h"
#include "debug_log/debug_logs.h"
#include "timer/timer.h"

#ifndef I2C_H
#define I2C_H



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
int I2C_Read_nData(uint8_t *data, uint8_t len, uint8_t addr) ;
int I2C_Write_nData(uint16_t cmd,uint8_t condition) ;
int I2C_Write_Cmd(uint16_t cmd,uint8_t condition, uint8_t addr) ;
int I2C_Clear_AddrFlag();

/*Sub function*/


#endif
