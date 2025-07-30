#include "i2c.h"
//
int I2C_Read_nData(uint8_t *data, uint8_t len, uint8_t addr) {
	I2C_Start();//check_pass(I2C_Start(),"---I2C_Start");

	I2C_Write_Addr((addr << 1) | 1);//check_pass(I2C_Write_Addr((SGP30_ADDR << 1) | 1),"---I2C_Write_Addr + R");

	I2C_EN_ACK();//check_pass(I2C_EN_ACK(),"---I2C_EN_ACK");

	I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");

	for(int i=0; i<len;i++)
	{
		//Handle last byte - send NACK and STOP before read
		if(i==len-1){
			I2C_DI_ACK();//check_pass(I2C_DI_ACK(),"---I2C_DI_ACK");
			I2C_Stop();//check_pass(I2C_Stop(),"---I2C_Stop");
		}

		while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
		data[i] = I2C1->DR;
	}

    return DONE;
}
