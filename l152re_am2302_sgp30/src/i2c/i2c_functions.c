#include "i2c.h"
/*----------v1.1----------*/
/*Register-Level I2C Functions*/
int I2C_Start() {
    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));	//SB: Start bit (Master mode) p690
    return DONE;
}

int I2C_Write_Addr(uint8_t addr) {
    I2C1->DR = addr;
    while(I2C1->SR1 & I2C_SR1_AF){}	//BTF: Byte transfer finished p690
    while(!(I2C1->SR1 & I2C_SR1_ADDR));	//ADDR: Address sent (master mode) p690
    return DONE;
}

int I2C_Write_Data(uint8_t data) {
    while(!(I2C1->SR1 & I2C_SR1_TXE)){}	//TxE: Data register empty (transmitters)  p689
    I2C1->DR = data;
    while(I2C1->SR1 & I2C_SR1_AF){}	//ACK
    while(I2C1->SR1 & I2C_SR1_BTF){} //BTF: Byte transfer finished p690
    return DONE;
}
int I2C_Read_Data(uint8_t* data){
	while(!(I2C1->SR1 & I2C_SR1_RXNE)){}	//RxNE: Data register not empty (receivers)  p689
	*data++ = I2C1->DR;
	return DONE;
}

int I2C_Stop() {
    I2C1->CR1 |= I2C_CR1_STOP;
    return DONE;
}

int I2C1_Bus_Test() {
    // Check for bus errors before I2C enable
    if(I2C1->SR1 & I2C_SR1_BERR) {
    	I2C1->SR1 &= ~I2C_SR1_BERR;  // Clear flag
    	return FAIL;
    }

    // Check BUSY flag - should be clear initially
    if(I2C1->SR2 & I2C_SR2_BUSY) {
        // Attempt bus recovery
        I2C1->CR1 |= I2C_CR1_SWRST;
        systickDelayMs(1);
        I2C1->CR1 &= ~I2C_CR1_SWRST;

        if(I2C1->SR2 & I2C_SR2_BUSY) return FAIL;
    }

    return PASS;
}

int I2C_POS_Read(){
	I2C1->CR1 |= I2C_CR1_POS;			//POS: Acknowledge/PEC Position (only for data reception) p.682
	return DONE;
}
int I2C_EN_ACK(){
	I2C1->CR1 |= I2C_CR1_ACK;
	return DONE;
}
int I2C_DI_ACK(){
	I2C1->CR1 &= ~I2C_CR1_ACK;	//No ACK
	return DONE;
}
int I2C_Check_ACK_Failure() {
    if(I2C1->SR1 & I2C_SR1_AF) {
        // No acknowledge received after address/data
        I2C1->SR1 &= ~I2C_SR1_AF;  // Clear flag
        return FAIL;
    }
    return PASS;
}
int I2C_Check_Overrun(void) {
    if(I2C1->SR1 & I2C_SR1_OVR) {
        // Data overrun/underrun condition
        I2C1->SR1 &= ~I2C_SR1_OVR;  // Clear flag
        return FAIL;
    }
    return PASS;
}
int I2C_Clear_AddrFlag(){
    volatile uint32_t temp = I2C1->SR2;  // Clear ADDR p691
	return DONE;
}
/* END ----------v1.1----------*/






