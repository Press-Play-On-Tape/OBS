#pragma once

#include "../utils/Constants.h"

namespace Images {

    const uint8_t PROGMEM BigAsteroid_00[] = {
    19, 19,
    0x00, 0x00, 0xc0, 0xf0, 0x9c, 0x6c, 0x96, 0x96, 0x6e, 0x1e, 0x3e, 0xde, 0x2c, 0xdc, 0x38, 0x78, 0xb0, 0xc0, 0x00, 
    0x00, 0x0e, 0x1b, 0x25, 0x4a, 0xa1, 0xc0, 0x08, 0x94, 0x08, 0x80, 0x40, 0xa1, 0xd0, 0x68, 0x55, 0x2a, 0x1f, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM BigAsteroid_01[] = {
    19, 19,
    0x00, 0x80, 0xe0, 0xf8, 0xbc, 0x5c, 0xaa, 0xa6, 0x4a, 0x06, 0x0a, 0x16, 0x2a, 0x54, 0xb8, 0x60, 0xc0, 0x00, 0x00, 
    0x00, 0x1f, 0x7f, 0x67, 0xdb, 0xa5, 0xa4, 0xd8, 0xa0, 0x40, 0x84, 0x4a, 0x04, 0xa0, 0x50, 0x35, 0x0a, 0x07, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t * const BigAsteroid[] = { BigAsteroid_00, BigAsteroid_01 };

    const uint8_t PROGMEM BigAsteroid_00_Mask[] = {
    0x00, 0xc0, 0xf0, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xc0, 
    0x0e, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM BigAsteroid_01_Mask[] = {
    0x80, 0xe0, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xe0, 0xc0, 0x00, 
    0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x07, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t * const BigAsteroid_Mask[] = { BigAsteroid_00_Mask, BigAsteroid_01_Mask };

    const uint8_t PROGMEM Hit[] = {
    6, 12,
    0x00, 0x00, 0x20, 0x04, 0x20, 0x50, 
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 

    0x00, 0x20, 0x02, 0x20, 0x88, 0x00, 
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 

    0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Bullet[] = {
    9, 7,
    0x00, 0x08, 0x2a, 0x3e, 0x32, 0x3a, 0x2e, 0x1c, 0x00, 
    };

    const uint8_t PROGMEM Bullet_Mask[] = {
    0x08, 0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c, 
    };

    const uint8_t PROGMEM Enemy[] = {
    11, 13,
    0x00, 0xe0, 0x10, 0x56, 0xe6, 0x0c, 0x10, 0x48, 0xa0, 0x40, 0x00, 
    0x00, 0x00, 0x01, 0x0d, 0x0c, 0x06, 0x01, 0x02, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Enemy_Mask[] = {
    0xe0, 0xf0, 0xfe, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 0xe0, 0x40, 
    0x00, 0x01, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 
    };

    const uint8_t PROGMEM PlayerShip[] = {
    14, 10,
    0x00, 0x02, 0x06, 0xb4, 0xec, 0xa8, 0xb8, 0x78, 0xc8, 0xc8, 0xd0, 0xd0, 0x60, 0x00, 
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM PlayerShip_Mask[] = {
    0x02, 0x07, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf0, 0x60, 
    0x00, 0x01, 0x03, 0x03, 0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
    };

    const uint8_t PROGMEM ShipParticle[] = {
    9, 4,
    0x00, 0x04, 0x02, 0x00, 0x04, 0x06, 0x00, 0x04, 0x00, 
    0x00, 0x02, 0x00, 0x04, 0x06, 0x00, 0x04, 0x00, 0x00,
    };

    const uint8_t PROGMEM ShipParticle_Mask[] = {
    0x04, 0x0e, 0x07, 0x06, 0x0e, 0x0f, 0x06, 0x0e, 0x04, 
    0x02, 0x07, 0x06, 0x0e, 0x0f, 0x06, 0x0e, 0x04,  0x00,
    };

    const uint8_t PROGMEM SmallAsteroid[] = {
    9, 8,
    0x00, 0x18, 0x24, 0x52, 0x6a, 0x54, 0x2c, 0x18, 0x00, 
    };

    const uint8_t PROGMEM SmallAsteroid_Mask[] = {
    0x18, 0x3c, 0x7e, 0xff, 0xff, 0xfe, 0x7e, 0x3c, 0x18, 
    };

}