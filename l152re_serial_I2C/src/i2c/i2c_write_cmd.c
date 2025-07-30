#include "i2c.h"


int I2C_Write_Cmd(uint16_t cmd,uint8_t condition, uint8_t addr) {
    I2C_Start();//check_pass(I2C_Start(),"---I2C_Start");
    I2C_Write_Addr(addr << 1);//check_pass(I2C_Write_Addr(SGP30_ADDR << 1),"---I2C_Write_Addr + W");
    I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");
    I2C_Write_Data(cmd >> 8);//check_pass(I2C_Write_Data(cmd >> 8),"---I2C_Write_Data");
    I2C_Write_Data(cmd & 0xFF);//check_pass(I2C_Write_Data(cmd & 0xFF),"---I2C_Write_Data");
    if(condition) I2C_Stop();//check_pass(I2C_Stop(),"---I2C_Stop");

    return DONE;
}
