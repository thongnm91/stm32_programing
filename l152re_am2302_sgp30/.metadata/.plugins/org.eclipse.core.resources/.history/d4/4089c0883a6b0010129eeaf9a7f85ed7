#include "sgp30.h"

int SGP30_Init() {
	I2C1_Bus_Test();//check_pass(I2C1_Bus_Test(),"-I2C1_Bus_Test");

	Write_Cmd(CMD_INIT,STOP);//check_pass(Write_Cmd(CMD_INIT,STOP),"-SEND_CMD_INIT");

	systickDelayMs(10);

	return DONE;
}

int SGP30_Measure(uint16_t *co2, uint16_t *tvoc) {
    uint8_t data[6]={0};

    Write_Cmd(CMD_MEASURE,NSTOP);//check_pass(Write_Cmd(CMD_MEASURE,NSTOP),"-SEND_CMD_MEASURE");

    systickDelayMs(10);

    Read_Data(data, 6);//check_pass(Read_Data(data, 6),"-READ_CMD_MEASURE");

    // CRC checks
     if (crc(&data[0], 2) != data[2]) {
     	 uart2_write_string("CO2 CRC check failed\n\r");

     	 return -1; // CO2 CRC fail
     }
     if (crc(&data[3], 2) != data[5]){
     	uart2_write_string("TVOC CRC check failed\n\r");
     	return -2; // TVOC CRC fail
     }

    *co2 = (data[0] << 8) | data[1];   // Skip CRC data[2]
    *tvoc = (data[3] << 8) | data[4];  // Skip CRC data[5]

    return DONE;
}

int SGP30_Get_Baseline(uint16_t *co2, uint16_t *tvoc)
{
	uint8_t data[6]={0};
	Write_Cmd(CMD_GET_BASELINE,NSTOP); //check_pass(Write_Cmd(CMD_GET_BASELINE,NSTOP),"CMD_GET_BASELINE");
	systickDelayMs(10);
	Read_Data(data, 6);//check_pass(Read_Data(data, 6),"-READ_CMD_MEASURE");
	// CRC checks
     if (crc(&data[0], 2) != data[2]) {
     	 uart2_write_string("CO2 CRC check failed\n\r");

     	 return -1; // CO2 CRC fail
     }
     if (crc(&data[3], 2) != data[5]){
     	uart2_write_string("TVOC CRC check failed\n\r");
     	return -2; // TVOC CRC fail
     }

    *co2 = (data[0] << 8) | data[1];   // Skip CRC data[2]
    *tvoc = (data[3] << 8) | data[4];  // Skip CRC data[5]

	return DONE;
}
int SGP30_Get_Feature_Ver(uint8_t* prod_type, uint8_t* ver_num){
	uint8_t data[3]={0};
	Write_Cmd(CMD_GET_FEATURE_SET,NSTOP);//check_pass(Write_Cmd(CMD_GET_FEATURE_SET,NSTOP),"CMD_GET_BASELINE");
	systickDelayMs(10);

	//check_pass(Read_Data(data, 3),"-READ_CMD_MEASURE");
	Read_Data(data, 3);

	// CRC checks
     if (crc(&data[0], 2) != data[2]) {
     	 uart2_write_string("CRC check failed\n\r");
     	 return -1; // CRC fail
     }


    *prod_type = data[0];
    *ver_num = data[1];

	return DONE;
}
int SGP30_Set_Humidity(double* absolute_humidity){
	uint8_t data[3] = {0};
	Write_Cmd(CMD_SET_ABSOLUTE_HUMIDITY,NSTOP);// check_pass(Write_Cmd(CMD_SET_ABSOLUTE_HUMIDITY,NSTOP),"CMD_SET_ABSOLUTE_HUMIDITY");
	systickDelayMs(10);
	data[1]=*absolute_humidity;
	data[2]= crc(&data[0], 2);
	Write_Data(data,3);// check_pass(Write_Data(data,3),"-Write_Data");
	return DONE;
}
