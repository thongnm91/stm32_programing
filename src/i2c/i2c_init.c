#include "i2c.h"

/*
 * PB8 -> SCL
 * PB9 -> SDA*/

/*-----------v1.0-----------*/

//int I2C1_init(){
//	/*1. Enable GPIOB and I2C1 peripheral clocks.*/
//	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; //Enable clock access to i2c1
//	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //Enable GPIOB clock PB8(D15)=SCL,PB9(D14)=SDA.
//
//	/*2. Configure PB8 and PB9 for I2C alternate function, open-drain, no pull-up.*/
//	//Set PB8 , PB9 mode alternate function
//	GPIOB->MODER |= GPIO_MODER_MODER8_1;
//	GPIOB->MODER |= GPIO_MODER_MODER9_1;
//
//	/*Set PB8, PB9 alternate function I2C AF4*/
//	GPIOB->AFR[1] |= 4U<<GPIO_AFRH_AFRH0_Pos;
//	GPIOB->AFR[1] |= 4U<<GPIO_AFRH_AFRH1_Pos;
//
//	//Set PB8, PB9 output type to open drain
//	/*Reason why output open-drain!
//	 * 1. I2C protocol uses shared lines (SCL and SDA) among multiple devices.
//	 * 2. Both Master and Slave devices can drive SCL and SDA lines at a same time.
//	 * 	It will be conflict or damaged the pin if one device drive HIGH while another pulls LOW.
//	 * 3. To avoid, when driving the line low, the device pulls it down to GND
//	 * 	When not transmitting, the line is left floating (high impedance).
//	 * 	The HIGH is maintained by using pull-up resistors, not by actively driving the line HIGH.
//	 * 	p.184
//	 * */
//	GPIOB->OTYPER |= GPIO_OTYPER_OT_8;
//	GPIOB->OTYPER |= GPIO_OTYPER_OT_9;
//
//	//Disable Pullup for PB8 and PB9
//	/*Reason why use pull-up!
//	 * 1. Without pull-ups, when no device pulls the line low, the SDA/SCL line would float
//	 * and resulting in noise or data transmission errors.
//	 * 2. If using external pull-up resistor, we must disable internal pull-up
//	 * */
//	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR8_0;
//	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR9_0;
//
//	/*3. Reset and release I2C1.*/
//	/*Reason why software reset is needed
//	 * In real-world i2c can get stuck cause Slave devices hold communication too long
//	 * Force reset I2C used to get back idle state.
//	 * */
//	//Enter software reset
//	I2C1->CR1 |= I2C_CR1_SWRST;
//	//Come out of reset mode
//	I2C1->CR1 &= ~I2C_CR1_SWRST;
//
//	/*4. Set I2C1 peripheral clock frequency (CR2).*/
//	/*Set CR2 (FREQ)
//	 * clock frequency 32Mhz FREQ = APB1 (PCLK1)
//	 * If PCLK1 = 32 MHz then FREQ = 32.
//	 * p685/911 STM32L152_reference_manual.pdf
//	 * */
//	I2C1->CR2 = I2C_CR2_FREQ_5;
//
//	/*Set clock control register (CCR) for 100kHz I2C speed.*/
//	/*how to calculate CCR
//		TPCLK1=1/32MHz=31,25ns
//		tI2C_bus=1/100kHz=10us=10000ns
//		tI2C_bus_div2=10000ns/2=5000ns
//		CCR value=tI2C_bus_div2/TPCLK1=5000ns/31,25ns=160
//	 *p692/911 datasheet.
//	 * */
//	I2C1->CCR = 160;
//
//	/*Set max rise time TRISE
//	 * What formula?
//	 * maximum rise time in sm mode = 1000ns. Equation 1000 ns/TPCK1
//	 * 1000ns/31,25ns=32
//	 * p.693
//	 * */
//	I2C1->TRISE = 33;
//
//	/*Enable I2C1 module*/
//	I2C1->CR1 |= I2C_CR1_PE;
//	return 0;
//}

/*END -----------v1.0-----------*/

/*-----------v1.1-----------*/

/*1. I2C GPIO Configuration PB8 PB9*/
int I2C1_GPIO_Init() {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;							//Bus clk AHB + GPIOB

	GPIOB->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1;	//AF mode
	GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9;		//Open drain
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_0 | GPIO_OSPEEDER_OSPEEDR9_0;//Normal speed
	//GPIOB->PUPDR &= (~GPIO_PUPDR_PUPDR8_0) & (~GPIO_PUPDR_PUPDR9_0); 	//No Pull-up
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1; 	//Pull-up
	GPIOB->AFR[1] |= (4U<<GPIO_AFRH_AFRH0_Pos) | (4U<<GPIO_AFRH_AFRH1_Pos); //AF4 = I2C1

	return DONE;
}

/*2. I2C1 Configuration*/
int I2C1_Init() {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;	// Bus clk APB1 + I2C1

    I2C1->CR1 |= I2C_CR1_SWRST;           // Reset
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 = I2C1->CR2 = I2C_CR2_FREQ_5;	// 32MHz PCLK1
    I2C1->CCR = 160;                       // 100kHz SCL
    I2C1->TRISE = I2C1->TRISE = 32;        // Max rise time

    I2C1->CR1 |= I2C_CR1_PE;              // Enable I2C

    return DONE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*4. Set I2C1 peripheral clock frequency (CR2).*/
/*Set CR2 (FREQ)
 * clock frequency 32Mhz FREQ = APB1 (PCLK1)
 * If PCLK1 = 32 MHz then FREQ = 32.
 * p685/911 STM32L152_reference_manual.pdf
 * */


/*Set clock control register (CCR) for 100kHz I2C speed.*/
/*how to calculate CCR
	TPCLK1=1/32MHz=31,25ns
	tI2C_bus=1/100kHz=10us=10000ns
	tI2C_bus_div2=10000ns/2=5000ns
	CCR value=tI2C_bus_div2/TPCLK1=5000ns/31,25ns=160
 *p692/911 datasheet.
 * */


/*Set max rise time TRISE
 * What formula?
 * maximum rise time in sm mode = 1000ns. Equation 1000 ns/TPCK1
 * 1000ns/31,25ns=32
 * p.693
 * */
/*END -----------v1.1-----------*/
