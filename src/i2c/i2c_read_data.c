//#include "i2c.h"
//
//int I2C1_Read_Data(uint8_t saddr,uint8_t* command, uint8_t c_byte, uint8_t *data, uint8_t d_byte){
//
//
//	/*First frame*/
//	check_pass(I2C1_Write_Command(saddr,command,c_byte,1),"I2C1_Write_Command");
//
//	systickDelayMs(12);	//measurement time p11/19
//
//	/*Second frame*/
//	check_pass(send_startbit(),"Send START bit AGAIN");/*Send START bit*/
//
//	check_pass(send_addr_read(saddr),"Send slave's address + read"); /*Send slave's address + bit READ*/
//
//	check_pass(send_clear_addr_flag(),"Clears ADDR flag"); /*Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag p691*/
//
//	check_pass(send_ack(),"Enable ACK"); /* Enable ACK for all but the last byte*/
//
//	check_pass(read_data(data,d_byte),"READ DATA"); //Read data
//
//	check_pass(send_nack(),"Stop ACK");
//
//	check_pass(send_stopbit(),"Stop sending");
//
//	return 0;
//}
//
