#include "src/utils/Arduboy2Ext.h"

void title_Init() {

    gameState = GameState::Title;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void title() { 

    if (arduboy.justPressed(A_BUTTON)) {
        
        gameState = GameState::Game_Init; 

    }

    Sprites::drawOverwrite(28, 11, Images::Title, 0);

}
