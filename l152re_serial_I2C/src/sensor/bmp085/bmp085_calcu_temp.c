#include "bmp085.h"

// Function to calculate B5 and temperature in 0.1 °C
int32_t bmp085_calculate_B5(int32_t ut, const bmp085_calibration_param *cal) {
    int32_t X1 = ((ut - cal->ac6) * cal->ac5) >> 15;
    int32_t X2 = (cal->mc << 11) / (X1 + cal->md);
    return X1 + X2;
}

// Returns temperature in 0.1 degrees Celsius
int32_t bmp085_calculate_temperature(int32_t ut, const bmp085_calibration_param *cal) {
    int32_t B5 = bmp085_calculate_B5(ut, cal);
    int32_t temp = (B5 + 8) >> 4;  // same as dividing by 16
    return temp;  // temperature in 0.1°C
}
