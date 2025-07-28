#include "include.h"

float calCelcius(uint32_t adc_raw){
	float vol = adc_raw*(3.3/4096); //Convert current voltage
	float temp = 125-(vol/0.017);
	return temp;
}
float calLux(uint32_t adc_raw){
	float vol = adc_raw*(3.3/4096); //Convert current voltage
	float lux = (3.3-vol)/0.00056; //0.00056V per 1lux.
	return lux;
}

/*
 * Sensor KY-013 Analog temperature
 * Vin 5V
 * Vout : Max 3.8V, Min 0.5V -> range ~3.35
 * Temperature range: -40 -> 125 oC
 * ADC = 0->4096
 * Decrease 0.02V = Increase 1 oC
 * */
