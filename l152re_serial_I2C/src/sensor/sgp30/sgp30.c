#include "sgp30.h"

/*write to 0x58 ack data: 0x20 0x03 */
int SGP30_Init() {
	uint8_t cmd[2] = {CMD_INIT>>8, CMD_INIT&0xFF};
	I2C1_Bus_Test();//check_pass(I2C1_Bus_Test(),"-I2C1_Bus_Test");
	I2C_Write_Cmd(cmd,2,STOP,SGP30_ADDR);//check_pass(SGP30_Write_Cmd(CMD_INIT,STOP),"-SEND_CMD_INIT");
    systickDelayMs(5);
    return DONE;
}

int SGP30_Measure(uint16_t *co2, uint16_t *tvoc) {
	uint8_t cmd[2] = {CMD_MEASURE>>8, CMD_MEASURE&0xFF};
    uint8_t data[6]={0};

    I2C_Write_Cmd(cmd,2,NSTOP,SGP30_ADDR);//check_pass(SGP30_Write_Cmd(CMD_MEASURE,NSTOP),"-SEND_CMD_MEASURE");

    systickDelayMs(10);

    I2C_Read_nData(data, 6,SGP30_ADDR);//check_pass(SGP30_Read_Data(data, 6),"-READ_CMD_MEASURE");

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
	uint8_t cmd[2] = {CMD_SET_ABSOLUTE_HUMIDITY>>8, CMD_SET_ABSOLUTE_HUMIDITY&0xFF};
	*ah = 216.7 * (((humidity/100)*6.112*exp((17.62*temperature)/(243.12+temperature)))/(273.15+ temperature)); //page 10/19
	I2C_Write_Cmd(cmd,2,NSTOP,SGP30_ADDR);//check_pass(SGP30_Write_Cmd(CMD_SET_ABSOLUTE_HUMIDITY,NSTOP),"-CMD_SET_ABSOLUTE_HUMIDITY");
	systickDelayMs(10);
	I2C_WriteData(CMD_MEASURE >> 8);//check_pass(I2C_Write_Data(cmd >> 8),"---I2C_Write_Data");
	I2C_WriteData(CMD_MEASURE & 0xFF);//check_pass(I2C_Write_Data(cmd & 0xFF),"---I2C_Write_Data");
	I2C_StopWrite();//check_pass(I2C_Stop(),"---I2C_Stop");

	return DONE;
}
