#include "i2c.h"


int I2C_Write_Cmd(uint8_t* cmd,uint8_t ncmd, uint8_t stop, uint8_t addr) {
    I2C_Start();//check_pass(I2C_Start(),"---I2C_Start");
    I2C_Write_Addr(addr << 1);//check_pass(I2C_Write_Addr(SGP30_ADDR << 1),"---I2C_Write_Addr + W");
    I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");
    while(ncmd--){
    	I2C_WriteData(*cmd++);
    }
    if(stop) I2C_StopWrite();//check_pass(I2C_Stop(),"---I2C_Stop");

    return DONE;
}
