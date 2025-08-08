#include "ds1621.h"



int ds1621_start(){
	//Send start conversion command to DS1621 sensor via I2C.
	I2C_Start();//check_pass(I2C_Start(),"---I2C_Start");
	I2C_Write_Addr(DS1621_ADDR << 1);//check_pass(I2C_Write_Addr(DS1621_ADDR << 1),"---I2C_Write_Addr + W");
	I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");
	I2C_WriteData(CMD_START_CONVERSATION);//check_pass(I2C_Write_Data(CMD_START_CONVERSATION),"---CMD_START_CONVERSATION");
	I2C_StopWrite();//check_pass(I2C_Stop(),"---I2C_Stop");
	systickDelayMs(100);
	return DONE;
}

int ds1621_read_temperature(uint8_t *data, uint8_t nbyte){
	I2C_Start();//check_pass(I2C_Start(),"---I2C_Start");
	I2C_Write_Addr(DS1621_ADDR << 1);//check_pass(I2C_Write_Addr(DS1621_ADDR << 1),"---I2C_Write_Addr + W");
	I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");
	I2C_WriteData(CMD_READ_LAST_RESULT);//check_pass(I2C_Write_Data(CMD_READ_LAST_RESULT),"---CMD_START_CONVERSATION");
	systickDelayMs(10);

	I2C_Start();//check_pass(I2C_Start(),"---I2C_Start");
	I2C_Write_Addr((DS1621_ADDR << 1) | 1);//check_pass(I2C_Write_Addr((DS1621_ADDR << 1) | 1),"---I2C_Write_Addr + R");
	I2C_EN_ACK();//check_pass(I2C_EN_ACK(),"---I2C_EN_ACK");
	I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");
	for(int i=0; i<nbyte;i++)
	{
		//Handle last byte - send NACK and STOP before read
		if(i==nbyte-1){
			I2C_DI_ACK();//check_pass(I2C_DI_ACK(),"---I2C_DI_ACK");
			I2C_StopRead();//check_pass(I2C_Stop(),"---I2C_Stop");
		}
		while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
		data[i] = I2C1->DR;
	}

	  data[1] = data[1]==128 ? 5:0 ;


	return DONE;
}

void ds1621_read_count_per_c(char *data){
	//I2C1_byteRead(ADDR_FOR_READ,READ_COUNT_PER_C,data);
}
void ds1621_read_count_remain(char *data){
	 //I2C1_byteRead(ADDR_FOR_READ,READ_COUNT_REMAIN,data);
}
