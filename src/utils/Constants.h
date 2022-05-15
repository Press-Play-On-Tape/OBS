#pragma once

#define _USE_BRINE
/* TEASE PRUNE DRONE CRIME BLINK and BRIEF or BRINE */

namespace Constants {

    constexpr uint8_t StarField_Size = 10;
    constexpr uint8_t SmallAsteroid_Size = 4;
    constexpr uint8_t LargeAsteroid_Size = 2;
    constexpr uint8_t Enemy_Size = 3;

    constexpr uint16_t EEPROM_Char1 = 78;
    constexpr uint16_t EEPROM_Char2 = EEPROM_Char1 + 1;

    constexpr uint8_t Enemy_Path[] = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 13, 11, 10, 9, 7, 6, 5, 4, 3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 11, 12, 14, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 38, 40, 42, 44, 45, 47, 48, 49, 50, 51, 52, 53, 53, 54, 54, 55, 55, 55, 55, 55, 55, 54, 54, 53, 53, 52, 52, 51, 50, 48, 47, 45, 44, 43, 41, 40, 38, 36, 34, 32, };


};

