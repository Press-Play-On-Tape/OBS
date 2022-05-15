
#include "src/utils/Arduboy2Ext.h"
#include <ArduboyFX.h>

#include "src/images/Images.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "src/utils/EEPROM_Utils.h"
#include "src/utils/Structs.h"

Arduboy2Ext arduboy;

SplashScreenVars splashScreenVars;

GameState gameState = GameState::SplashScreen_Init;

Point starfield[Constants::StarField_Size];
Asteroid smallAsteroids[Constants::SmallAsteroid_Size];
Asteroid largeAsteroids[Constants::LargeAsteroid_Size];
Enemy enemies[Constants::Enemy_Size];
Bullet bullet;

int8_t xOffset = 0;
int8_t yOffset = 0;
uint8_t offsetCount = 0;

const uint8_t PROGMEM lookup[] { 0xFF >> 8, 0xFF >> 7, 0xFF >> 6, 0xFF >> 5, 0xFF >> 4, 0xFF >> 3, 0xFF >> 2, 0xFF >> 1 };


void setup() {

    arduboy.boot();
    arduboy.flashlight();
    arduboy.systemButtons();
    arduboy.setFrameRate(60);
    arduboy.initRandomSeed();

//    EEPROM_Utils::initEEPROM(false, GameMode::English, true);
//    gamePlayVars.mode = EEPROM_Utils::getMode();

}

void loop() {
   
    if (!arduboy.nextFrame()) return; 
    arduboy.pollButtons();

    switch (gameState) {

        case GameState::SplashScreen_Init:

            splashScreen_Init();
            splashScreen();
            break;

        case GameState::SplashScreen:

            splashScreen();
            break;

        case GameState::Title_Init:

            gameState = GameState::Title;
            title_Init();
            title();
            break;

        case GameState::Title:

            title();
            break;

        case GameState::Game_Init:

            game_Init();
            game();
            break;

        case GameState::Game:

            game();
            break;

    }

    arduboy.display(CLEAR_BUFFER); 

}
