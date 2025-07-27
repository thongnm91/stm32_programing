//#include "i2c.h"



//int I2C1_Write_Command(uint8_t saddr, uint8_t* command, uint8_t nbyte, uint8_t stop){
//	check_pass(START,"I2C1_Write_Command");
//
//	/*1. Wait bus I2C free and Clear ACK*/
//	check_pass(wait_i2c_bus(),"Wait bus I2C free");
//	check_pass(clear_ack(),"Acknowledge clear");
//
//	/*Transmit START*/
//	check_pass(send_startbit(),"Send start bit");
//
//	/*Transmit slave's address with bit WRITE*/
//	check_pass(send_slave_addr_write(saddr),"Send slave's address + WRITE");
//
//	/*Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag p691*/
//	check_pass(send_clear_addr_flag(),"Clear ADDR flag");
//
//
//	/*Send command*/
//	check_pass(send_command(command, nbyte),"Send command");
//
//	/*Wait byte transfer finished*/
//	check_pass(wait_byte_transfer(),"Wait byte transfer finished");
//
//	check_pass(send_stopbit(),"Send stop bit");

//	return 0;
//}
