//#include <stdio.h>
//#include <stddef.h>
//#include "stm32l1xx.h"
//
//#include "include.h"
//#include "test.h"
//
//int main(void)
//{
//	SetSysClk();
//	SystemCoreClockUpdate();
//	uart2_init();
//	I2C1_init();
//
//	uint16_t co2_eq_ppm, tvoc_ppb;
//	char buf[50];
//
//	/*Toggle button to start/stop program*/
//	//this function are developing.......
//
//
//	sprintf(buf,"--------------------------------------------\n\r");
//	uart2_write_string(buf);
//	sprintf(buf,"sgp30_iaq_init>                        START\n\r");
//    uart2_write_string(buf);
//
////    if(sgp30_iaq_init()){
////    	sprintf(buf,"sgp30_iaq_init> FAIL\n\r");
////    	uart2_write_string(buf);
////    }
////    else {
////    	sprintf(buf,"sgp30_iaq_init> PASS\n\r");
////    	uart2_write_string(buf);
////    }
//    check_pass(sgp30_iaq_init(),"sgp30_iaq_init");
//    systickDelayMs(20); // Datasheet: wait after initialization
//
//  while (1)
//  {
//		sprintf(buf,"----------------------------\n\r");
//		uart2_write_string(buf);
//		sprintf(buf,"sgp30_measure_iaq> START\n\r");
//	    uart2_write_string(buf);
//
//	  if (sgp30_measure_iaq(&co2_eq_ppm, &tvoc_ppb) == 0) {
//		  sprintf(buf, "CO2: %u, TVOC: %u\r\n", co2_eq_ppm, tvoc_ppb);
//	  } else {
//		  sprintf(buf, "SGP30 read error\r\n");
//	  }
//	  uart2_write_string(buf);
//
//	  //Delay
//	  systickDelayMs(1000);
//
//	}
//	return 0;
//}

/*v1.0*/
// Commands (from Sensirion SGP30 datasheet, Table 10)
uint8_t CMD_IAQ_INIT[2]    = {0x20, 0x03};
uint8_t CMD_MEASURE_IAQ[2] = {0x20, 0x08};

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

// SGP30 Initialization (must run once after power-up)
int sgp30_iaq_init() {
	check_pass(START, "sgp30_iaq_init");
	int check = I2C1_Write_Command(SGP30_ADDRESS, CMD_IAQ_INIT, 2,0);
	check_pass(check,"I2C1_Write_Command");

	return check? 1:0 ;
}

// SGP30 Measure IAQ Command and Data Read
// co2_eq and tvoc are output pointers (output in ppm/ppb)
int sgp30_measure_iaq(uint16_t *co2_eq, uint16_t *tvoc) {
    uint8_t data[6]={0};
    char buf[50];

    sprintf(buf,"I2C1_Read_Data> START\n\r");
	uart2_write_string(buf);

    // Send measurement command
    check_pass(I2C1_Read_Data(SGP30_ADDRESS, CMD_MEASURE_IAQ, 2, data, 6),"I2C1_Read_Data");

    // CRC checks
    if (sgp30_crc(&data[0], 2) != data[2]) {
    	 uart2_write_string("CO2 CRC check failed\n\r");

    	 return -1; // CO2 CRC fail
    }
    if (sgp30_crc(&data[3], 2) != data[5]){
    	uart2_write_string("TVOC CRC check failed\n\r");
    	return -2; // TVOC CRC fail
    }

    // Parse values (MSB first)
    *co2_eq = ((uint16_t)data[0] << 8) | data[1];
    *tvoc   = ((uint16_t)data[3] << 8) | data[4];
    return 0;
}
/*END v1.0*/