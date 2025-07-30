#include "sgp30.h"

//
// SGP30 I2C 7-bit address (from datasheet)

// CRC8 algorithm for SGP30 (Polynomial 0x31, init 0xFF)
int sgp30_crc(uint8_t *data, int count) {
    uint8_t crc = 0xFF;
    for (int i = 0; i < count; i++) {
        crc ^= data[i];
        for (int b = 0; b < 8; b++)
            crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
    }
    return crc;
}
