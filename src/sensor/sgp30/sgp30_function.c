#include "sgp30.h"

//
// SGP30 I2C 7-bit address (from datasheet)


int SGP30_Write_Cmd(uint16_t cmd,uint8_t condition) {
    check_pass(I2C_Start(),"---I2C_Start");
    check_pass(I2C_Write_Addr(SGP30_ADDR << 1),"---I2C_Write_Addr + W");
    check_pass(I2C_Write_Data(cmd >> 8),"---I2C_Write_Data");
    check_pass(I2C_Write_Data(cmd & 0xFF),"---I2C_Write_Data");
    if(condition) check_pass(I2C_Stop(),"---I2C_Stop");

    return DONE;
}

int SGP30_Read_Data(uint16_t *data, uint8_t len) {
	char btf = 0;

//	uart2_write_string("\n\rBTF: ");
//	btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//	uart2_write(btf);

	check_pass(I2C_Start(),"---I2C_Start");

//	uart2_write_string("\n\rBTF: ");
//	btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//	uart2_write(btf);

	check_pass(I2C_Write_Addr((SGP30_ADDR << 1) | 1),"---I2C_Write_Addr + R");

//	uart2_write_string("\n\rBTF: ");
//	btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//	uart2_write(btf);

	check_pass(I2C_EN_ACK(),"---I2C_EN_ACK");


//	uart2_write_string("\n\rBTF: ");
//	btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//	uart2_write(btf);


		//Handle last byte - send NACK and STOP before read
//		if(i==len-1){
//			check_pass(I2C_DI_ACK(),"---I2C_DI_ACK");
//			check_pass(I2C_Stop(),"---I2C_Stop");
//
//			uart2_write_string("\n\rRXNE: ");
//			btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
//			uart2_write(btf);
//
//			uart2_write_string("\n\rACK: ");
//			btf = (I2C1->SR1 & I2C_SR1_AF)? '1' : '0';
//			uart2_write(btf);
//
//			uart2_write_string("\n\rBTF: ");
//			btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//			uart2_write(btf);
//		}
//		//Wait for RXNE flag to be set
//		uart2_write_string("\n\rRXNE: ");
//		btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
//		uart2_write(btf);
//
//		uart2_write_string("\n\rACK: ");
//		btf = (I2C1->SR1 & I2C_SR1_AF)? '1' : '0';
//		uart2_write(btf);

		while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
		for(int i=0; i<len;i++)
		{
			uart2_write_string("\n\rRXNE: ");
			btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
			uart2_write(btf);
			data[i] = I2C1->DR;

			//Handle last byte - send NACK and STOP before read
			if(i==len-1){
				check_pass(I2C_DI_ACK(),"---I2C_DI_ACK");
				check_pass(I2C_Stop(),"---I2C_Stop");

				uart2_write_string("\n\rRXNE: ");
				btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
				uart2_write(btf);

				uart2_write_string("\n\rACK: ");
				btf = (I2C1->SR1 & I2C_SR1_AF)? '1' : '0';
				uart2_write(btf);

				uart2_write_string("\n\rBTF: ");
				btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
				uart2_write(btf);
			}
		}

//		uart2_write_string("\n\rRXNE: ");
//		btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
//		uart2_write(btf);
//
//		uart2_write_string("\n\rACK: ");
//		btf = (I2C1->SR1 & I2C_SR1_AF)? '1' : '0';
//		uart2_write(btf);
//
//		uart2_write_string("\n\rBTF: ");
//		btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//		uart2_write(btf);

		//while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
//		btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//		uart2_write(btf);
//		btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
//		uart2_write(btf);



    return DONE;
}

// CRC8 algorithm for SGP30 (Polynomial 0x31, init 0xFF)
uint8_t sgp30_crc(uint8_t *data, int count) {
    uint8_t crc = 0xFF;
    for (int i = 0; i < count; i++) {
        crc ^= data[i];
        for (int b = 0; b < 8; b++)
            crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
    }
    return crc;
}

//	check_pass(I2C_EN_ACK(),"---I2C_EN_ACK");
//	for(int i=0; i<len;i++)
//	{
//		if(i==len-1)
//		{
//			check_pass(I2C_DI_ACK(),"---I2C_DI_ACK");
//			check_pass(I2C_Stop(),"---I2C_Stop");
//			while(!(I2C1->SR1 & I2C_SR1_RXNE)){} check_pass(DONE,"----I2C_SR1_RXNE");
//			data[i] = I2C1->DR;
//		}
//		else
//		{
//			char btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
//			uart2_write(btf);
//			btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
//			uart2_write(btf);
//			while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
////			btf = (I2C1->SR1 & I2C_SR1_BTF)? '1' : '0';
////			uart2_write(btf);
////			btf = (I2C1->SR1 & I2C_SR1_RXNE)? '1' : '0';
////			uart2_write(btf);
//
//			data[i] = I2C1->DR;
//
//			check_pass(I2C_EN_ACK(),"---I2C_EN_ACK");
//		}
//	}
