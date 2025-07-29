## `int main(void)`

**Short list of steps:**

1. Initialize I2C1 and USART2 peripherals.
2. Configure system clock to 32 MHz and update `SystemCoreClock`.
3. Enable GPIOA clock and set PA5 as output.
4. Send `"start"` message over USART2.
5. Send start conversion command to DS1621 sensor via I2C.
6. Delay for sensor conversion.
7. Enter infinite loop:

   * Read temperature data from DS1621 via I2C.
   * Format and adjust received data.
   * Send temperature data over USART2.
   * Toggle PA5 (LED) on and off with delays.

**Reason why it is needed:**
Sets up hardware and continuously reads temperature from the DS1621 sensor, sends it over UART, and toggles an LED for status indication.

---
`main.c`

```c
#include <stdio.h>
#include <stddef.h>
#include "stm32l1xx.h"

#include "include.h"

int main(void)
{
	SetSysClk();
	SystemCoreClockUpdate();
	uart2_init();
	I2C1_init();

    char received_data[2]="";		//data array for temperature. "char" can display negative char a = 0b11100111; result: -25
    char counter_per_c;
    char counter_remain;
    float lowtem,temperature;

//	uint16_t co2_eq_ppm, tvoc_ppb;

    //Send "start" message over USART2.
    char buf[50]="start";
    uart2_write_string(buf);

     //Send start conversion command to DS1621 sensor via I2C.
     ds1621_start();

//	sgp30_init();

  while (1)
  {
	   //Read temperature data from DS1621 via I2C.
	   //Format and adjust received data.
	   ds1621_read_temperature(received_data);

	   lowtem = (received_data[1]&0x80) ? 0.5 : 0; //LSB 0x80 = 0.5 degree

	   //Calculate the higher resolution temperature
	   ds1621_read_count_per_c(&counter_per_c);
	   ds1621_read_count_remain(&counter_remain);
	   temperature = ((received_data[0]+lowtem) - 0.25) + (((float)counter_per_c-(float)counter_remain)/(float)counter_per_c);
	   lowtem = (temperature-(int)temperature)*1000;
	   sprintf(buf,"%d.%d \n\r",received_data[0],(int)lowtem);
		
	  //Send temperature data over USART2.
	  uart2_write_string(buf);
	  systickDelayMs(3000);
	}
	return 0;
}
```