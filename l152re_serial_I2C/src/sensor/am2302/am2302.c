#include "am2302.h"
/*
 *Datasheet: https://cdn-shop.adafruit.com/datasheets/Digital+humidity+and+temperature+sensor+AM2302.pdf
 *
 * How to use function in main()?
 * uint8_t am2302[4] = {0x00};
 *   while (1)
  {
	  //If request success then read humidity and temperature and send debugger
	  if(am2302Request(am2302)){
		  am2302ShowUart2(am2302);
	  }
	  systickDelayMs(3000);
  }
 * */

/*
 * Function send request and receive data from sensor
 * User provide pointer array 5 bytes to save data.
 *
 * 1. Initial GPIO mode Output
 * 		1. Enable Clock bus for GPIO pin
 * 		2. Config GPIO pin mode output
 * 2. Start communication
 * 		1. Set Pin HIGH
 * 		2. Delay 1 ms
 * 		3. Set pin LOW
 * 		4. Delay 1 ms
 * 3. Request data
 * 		1. Set pin HIGH
 * 		2. Delay 40 us
 * 4. Change GPIO mode Input
 * 5. Wait for am2302 respond
 * 		1. Wait forever until Input Data Register Pin LOW
 * 		2. Wait forever until Input Data Register Pin HIGH
 * 		3. Wait forever until Input Data Register Pin LOW
 * 6. Get data
 * 		1. User provide pointer array uint8 array[5] to save data.
 * 		2. while(i<40)
 * 			2.1 Wait forever until Input Data Register Pin 6 HIGH
 * 			2.2 Delay 50 us
 * 			2.3 If PIN still HIGH over 45us, the vol-lengh mean data "1" else mean "0"
 * 				uint8 j = i/8;
 * 				array[j] |= 0x80 >> i
 *			2.4 i++;
 *			2.5 wait pin change HIGH to LOW to finish this bit
 *	//7. Calculate CRC
 *			//Checksum=(Byte 0 + Byte 1 + Byte 2 + Byte 3) &0xFF
 *	//8. Check CRC if correct then return data
 * */

int am2302Request(uint8_t *array){
//1. Initial GPIO mode Output
	//1. Enable Clock bus for GPIO pin PA6
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//2. Config GPIO pin mode output
	GPIOA->MODER |= GPIO_MODER_MODER6_0;
//2. Start communication
	 //1. Set Pin 6 HIGH
	GPIOA->ODR |= GPIO_ODR_ODR_6;
	//	2. Delay 1 ms
	systickDelayMs(1);

	 //3. Set pin LOW
	GPIOA->ODR &= ~GPIO_ODR_ODR_6;
	//4. Delay 1 ms
	systickDelayMs(1);
//3. Request data
	 //1. Set pin HIGH
	GPIOA->ODR |= GPIO_ODR_ODR_6;
	 //2. Delay 40 us
	systickDelayUs(40);
//4. Change GPIO mode Input
	GPIOA->MODER &= ~GPIO_MODER_MODER6;
//5. Wait for am2302 respond
	 //1. Wait forever until Input Data Register Pin LOW
	while((GPIOA->IDR & GPIO_IDR_IDR_6)){}
	//2. Wait forever until Input Data Register Pin HIGH
	while(!(GPIOA->IDR & GPIO_IDR_IDR_6)){}
	 //3. Wait forever until Input Data Register Pin LOW
	while((GPIOA->IDR & GPIO_IDR_IDR_6)){}
//6. Get data
	//1. User provide pointer array uint8 array[5] to save data.
	uint8_t ar[5]={0x00};
	//2. Read 40 bits and add each 8 bits to array
	uint8_t i = 0;
	while(i<40){
		//2.1 Wait until Input Data Register Pin HIGH
		while(!(GPIOA->IDR & GPIO_IDR_IDR_6)){}
		//2.2 Delay 50 us
		systickDelayUs(45);
		//2.3 If PIN still HIGH over 45us, the vol-lengh mean data "1" else mean "0".
		//Then add each 8bits to array.
		if(GPIOA->IDR & GPIO_IDR_IDR_6){
			ar[i/8] |= 0x80 >> (i%8);//(i/8): i increase every 8bit, (i%8): reset counting from 0->7
		}
		//2.4 i++;
		i++;
		//2.5 wait pin change HIGH to LOW to finish this bit
		while(GPIOA->IDR & GPIO_IDR_IDR_6){}
	}
//7. Calculate CRC
	//Checksum=(Byte 0 + Byte 1 + Byte 2 + Byte 3) &0xFF
	uint8_t crc = 0;
	for(i=0;i<4;i++){
		crc += ar[i];
	}
	crc &= 0xFF;
//8. Check CRC if correct then return data
	if(crc==ar[4]){
		for(i=0;i<4;i++){
			array[i]=ar[i];
		}
		return DONE;
	}
	else
		return FAIL;
}


/*
 *
 * Function format and send data to UART2
 * 1. Read humidity
 * 		1. Combine 8 bits high and 8 bit low to 16 bit humidity
 * 2. Check minus template
 * 		1. read bit[7] if 1 mean negative temperature else mean positive
 * 3. Read temperature
 * 		1. Remove bit[7]
 * 		2. Combine 8 bits high and 8 bit low to 16 bit temperature
 * 4. Write UART2
 * 		1. Format data and save in an array
 * 		2. Uart2 write string
 * */
int  am2302ShowUart2(uint8_t* am2302) {
	uint16_t h = 0x0000, t = 0x0000;
	char minus = '0';
	char buffer[20]={'\0'};

  //Read humidity
  h = ((am2302[0]&0xFFFF)<<8) | (am2302[1]&0xFFFF);

  //Check minus template
  minus = (am2302[2]>>7)? '-' : '+';
  //Read temperature
  t = ((am2302[2]&0xFF7F)<<8) | (am2302[3]&0xFFFF); //&0xFF7F to remove minus

  //Write UART2
  sprintf(buffer, "%d,%d %%RH  %c%d,%d °C\n\r", h/10,h%10,minus,t/10,t%10);
  uart2_write_string(buffer);

  return DONE;
}
int AM2302_Read_Data(float* humidity, float* temperature, uint8_t* data){
	uint16_t h = 0x0000, t = 0x0000;
	//Read humidity
	  h = ((data[0]&0xFFFF)<<8) | (data[1]&0xFFFF);

	  //Check minus template
	  int minus = (data[2]>>7)? -1 : 1;
	  //Read temperature
	  t = ((data[2]&0xFF7F)<<8) | (data[3]&0xFFFF); //&0xFF7F to remove minus

	  *humidity = h/10.0;
	  *temperature = (t/10.0) * minus;

	  return DONE;
}
