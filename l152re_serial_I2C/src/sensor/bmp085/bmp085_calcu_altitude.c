#include "bmp085.h"

double bmp085_calculate_altitude(uint32_t* pressure){
	double h = 0; //altitude above sea level (m)
	double T0 = 288.15; // standard temperature at sea level (288.15K)
	double L = 0.0065; //L: temperature lapse rate (0.0065K/m)
	double p = (double)(*pressure); //p: measured pressure (Pa)
	double p0 = 101325.0;//p0 : standard pressure at sea level (101325Pa)
	double R = 8.31447;//R: universal gas constant (8.31447J/(mol·K))
	double M =  0.0289644;//M: molar mass of dry air (0.0289644kg/mol)
	double g = 9.80665; //g: gravity (9.80665m/s²)

	double exponent = (R * L) / (g * M);
	double ratio = pow((p / p0) , exponent);
	h = (T0 / L) * (1.0 - ratio);

	return h;

}

