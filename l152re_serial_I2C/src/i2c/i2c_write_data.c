#include "i2c.h"

int I2C_Write_nData(uint16_t cmd,uint8_t condition) {
    I2C_Write_Data(cmd >> 8);//check_pass(I2C_Write_Data(cmd >> 8),"---I2C_Write_Data");
    I2C_Write_Data(cmd & 0xFF);//check_pass(I2C_Write_Data(cmd & 0xFF),"---I2C_Write_Data");
    I2C_Stop();//check_pass(I2C_Stop(),"---I2C_Stop");

    return DONE;
}
