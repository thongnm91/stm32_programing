#include "bmp085.h"

// Function to calculate true pressure (in Pa)
int32_t bmp085_calculate_pressure(uint32_t up, int32_t ut, uint8_t oss, const  bmp085_calibration_param *cal) {
    int32_t B5 = bmp085_calculate_B5(ut, cal);
    int32_t B6 = B5 - 4000;

    int32_t X1 = (cal->b2 * ((B6 * B6) >> 12)) >> 11;
    int32_t X2 = (cal->ac2 * B6) >> 11;
    int32_t X3 = X1 + X2;

    int32_t B3 = ((((int32_t)cal->ac1 * 4 + X3) << oss) + 2) >> 2;

    X1 = (cal->ac3 * B6) >> 13;
    X2 = (cal->b1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;

    uint32_t B4 = (cal->ac4 * (uint32_t)(X3 + 32768)) >> 15;

    uint32_t B7 = ((uint32_t)up - B3) * (50000 >> oss);

    int32_t p;
    if (B7 < 0x80000000) {
        p = (B7 << 1) / B4;
    } else {
        p = (B7 / B4) << 1;
    }

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;

    p = p + ((X1 + X2 + 3791) >> 4);

    return p;  // Pressure in Pa
}
