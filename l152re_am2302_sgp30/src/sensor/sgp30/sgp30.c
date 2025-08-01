#include "sensor/sgp30/sgp30.h"

int SGP30_Init() {
	check_pass(I2C1_Bus_Test(),"-I2C1_Bus_Test");
	check_pass(SGP30_Write_Cmd(CMD_INIT,STOP),"-SEND_CMD_INIT");
    systickDelayMs(10);
    return DONE;
}

int SGP30_Measure(uint16_t *co2, uint16_t *tvoc) {
    uint8_t data[6]={0};

    check_pass(SGP30_Write_Cmd(CMD_MEASURE,NSTOP),"-SEND_CMD_MEASURE");

    systickDelayMs(10);

    check_pass(SGP30_Read_Data(data, 6),"-READ_CMD_MEASURE");

    // CRC checks
     if (sgp30_crc(&data[0], 2) != data[2]) {
     	 uart2_write_string("CO2 CRC check failed\n\r");

     	 return -1; // CO2 CRC fail
     }
     if (sgp30_crc(&data[3], 2) != data[5]){
     	uart2_write_string("TVOC CRC check failed\n\r");
     	return -2; // TVOC CRC fail
     }

    *co2 = (data[0] << 8) | data[1];   // Skip CRC data[2]
    *tvoc = (data[3] << 8) | data[4];  // Skip CRC data[5]

    return DONE;
}
int SGP30_SET_AH(float humidity, float temperature, float* ah){
	*ah = 216.7 * (((humidity/100)*6.112*exp((17.62*temperature)/(243.12+temperature)))/(273.15+ temperature)); //page 10/19
	check_pass(SGP30_Write_Cmd(CMD_SET_ABSOLUTE_HUMIDITY,NSTOP),"-CMD_SET_ABSOLUTE_HUMIDITY");
	systickDelayMs(10);
	check_pass(SGP30_Write_Data(CMD_MEASURE,NSTOP),"-SEND_CMD_MEASURE");

	return DONE;
}
