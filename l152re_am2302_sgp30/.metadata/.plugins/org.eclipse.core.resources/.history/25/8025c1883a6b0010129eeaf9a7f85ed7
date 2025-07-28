#include "sgp30.h"

//
// SGP30 I2C 7-bit address (from datasheet)


int Write_Cmd(uint16_t cmd,uint8_t condition) {
	I2C_Start(); //check_pass(I2C_Start(),"---I2C_Start");
	I2C_Write_Addr(SGP30_ADDR << 1);//check_pass(I2C_Write_Addr(SGP30_ADDR << 1),"---I2C_Write_Addr + W");

	I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");

	I2C_Write_Data(cmd >> 8); //check_pass(I2C_Write_Data(cmd >> 8),"---I2C_Write_Data");
	I2C_Write_Data(cmd & 0xFF);//check_pass(I2C_Write_Data(cmd & 0xFF),"---I2C_Write_Data");

    if(condition) I2C_Stop();//check_pass(I2C_Stop(),"---I2C_Stop");

    return DONE;
}

int Read_Data(uint8_t *data, uint8_t len) {
	I2C_Start();//check_pass(I2C_Start(),"---I2C_Start");

	I2C_Write_Addr((SGP30_ADDR << 1) | 1);//check_pass(I2C_Write_Addr((SGP30_ADDR << 1) | 1),"---I2C_Write_Addr + R");

	I2C_EN_ACK();//check_pass(I2C_EN_ACK(),"---I2C_EN_ACK");

	I2C_Clear_AddrFlag();//check_pass(I2C_Clear_AddrFlag(),"I2C_Clear_AddrFlag");

	for(int i=0; i<len;i++)
	{
		while(!(I2C1->SR1 & I2C_SR1_RXNE)){}

		data[i] = I2C1->DR;

		//Handle last byte - send NACK and STOP before read
		if(i==len-1){
			I2C_DI_ACK();//check_pass(I2C_DI_ACK(),"---I2C_DI_ACK");
			I2C_Stop();//check_pass(I2C_Stop(),"---I2C_Stop");
		}
	}

    return DONE;
}

// CRC8 algorithm for SGP30 (Polynomial 0x31, init 0xFF)
uint8_t crc(uint8_t *data, int count) {
    uint8_t crc = 0xFF;
    for (int i = 0; i < count; i++) {
        crc ^= data[i];
        for (int b = 0; b < 8; b++)
            crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
    }
    return crc;
}
int Write_Data(uint8_t* data, uint8_t nbyte){
	uint8_t i = 0;
	while(i>nbyte){
		I2C_Write_Data(data[i]); //check_pass(I2C_Write_Data(cmd >> 8),"---I2C_Write_Data");
		i++;
	}
	I2C_Stop();
	return DONE;
}

