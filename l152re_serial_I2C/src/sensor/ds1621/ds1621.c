//#include "include.h"

/*Command p10/16*/
#define ADDR_FOR_WRITE 0x48	//
#define ADDR_FOR_READ 0x48  //
#define START_CONVERSATION 0xEE 	//
#define STOP_CONVERSATION 0x22 	//
#define READ_LAST_RESULT 0xAA	//
#define READ_COUNT_REMAIN 0xA8	//
#define READ_COUNT_PER_C 0xA9	//

void ds1621_start(void){
	//Send start conversion command to DS1621 sensor via I2C.
	I2C1_ByteWrite(ADDR_FOR_WRITE,START_CONVERSATION); 			//start conversion
	systickDelayMs(100);
}

void ds1621_read_temperature(char *data){
	I2C1_bursRead(ADDR_FOR_READ,READ_LAST_RESULT,2,data);
}
void ds1621_read_count_per_c(char *data){
	I2C1_byteRead(ADDR_FOR_READ,READ_COUNT_PER_C,data);
}
void ds1621_read_count_remain(char *data){
	 I2C1_byteRead(ADDR_FOR_READ,READ_COUNT_REMAIN,data);
}
