#include "src/utils/Arduboy2Ext.h"

void title_Init() {

    gameState = GameState::Title;

    for (Point &star : starfield) {

        star.x = random(0, 128);
        star.y = random(0, 64);
        
    }
    
}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void title() { 

    if (arduboy.justPressed(A_BUTTON)) {
        
        gameState = GameState::Game_Init; 

    }

      
    // Move and render starfield ..

    for (Point &star : starfield) {

        if (arduboy.getFrameCount(6) == 0) {

            star.x--;

            if (star.x == -1) {
                star.x = 128;
                star.y = random(0, 64);
            }

        }

        arduboy.drawPixel(star.x + xOffset, star.y + yOffset);
        
    }


    Sprites::drawSelfMasked(28, 11, Images::Title, 0);

}
