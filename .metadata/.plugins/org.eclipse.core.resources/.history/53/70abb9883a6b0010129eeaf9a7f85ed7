#include "debug_logs.h"

/* message>  PASS/FAIL
 * PASS 0
 * FAIL 1
 * */
void check_pass(int check, char* message){
	char buf[LOG_LENGH];

	strcpy(buf,message);	//Get message

	strncat(buf,">",1);		//Add >

	uint8_t nspace = LOG_LENGH - 9 - strlen(message);	//Count number of space
    while(nspace>0){
    	strncat(buf, " ",1);
    	nspace--;
    }

    switch (check){
    case 0:
    	strncat(buf, "DONE\n\r",6);
		uart2_write_string(buf);
    	break;
    case 1:
    	strncat(buf, "FAIL\n\r",6);
		uart2_write_string(buf);
    	break;
    case 2:
    	strncat(buf, "PASS\n\r",7);
		uart2_write_string(buf);
		break;
    case 3:
		strncat(buf, "PASS\n\r",7);
		uart2_write_string(buf);
		break;
    case I2C_SUCCESS:
        printf("I2C_SUCCESS\n");
        break;
    case I2C_ERROR_TIMEOUT_25MS:
		strncat(buf, "Error: clock stretching 25ms timeout\n\r",7);
		uart2_write_string(buf);
		break;
    case I2C_ERROR_SMBALERT:
         printf("Error: SMBus alert detected\n");
         break;
     case I2C_ERROR_NACK:
         printf("Error: SGP30 not responding (NACK)\n");
         break;
    default:
    	uart2_write_string(buf);
    }

}







