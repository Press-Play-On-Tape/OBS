#include "src/utils/Arduboy2Ext.h"

const uint8_t textLengths[] = { 50, 51, 54, 61 };

const uint8_t PROGMEM IntroText_00[] = {    
    4,'Y','o','u','r',' ','s','h','i','p',' ','h','a','s',' ','b','e','e','n',
    10,'d','a','m','a','g','e','d',' ','b','y',' ','s','o','m','e',
    15,'s','p','a','c','e',' ','d','e','b','r','i','s','.','.',
    };

const uint8_t PROGMEM IntroText_01[] = {
    6,'.','.','t','h','e',' ','s','t','e','e','r','i','n','g',' ','i','s',
    4,'b','r','o','k','e','n',' ','a','n','d',' ','y','o','u',' ','c','a','n',
    16,'n','o','t',' ','n','a','v','i','g','a','t','e','.',
};

const uint8_t PROGMEM IntroText_02[] = {
    5,'Y','o','u',' ','d','i','s','c','o','v','e','r',' ','t','h','a','t',
    0,'b','y',' ','f','i','r','i','n','g',' ','t','h','e',' ','l','a','s','e','r',
    12,'y','o','u',' ','c','a','n',' ','s','t','e','e','r','.','.',
};

const uint8_t PROGMEM IntroText_03[] = {
    0,'.','.','s','o','r','t',' ','o','f','!',' ','A','v','o','i','d',' ','t','h','e',
    2,'a','s','t','e','r','o','i','d','s',' ','a','n','d',' ','e','n','e','m','y',
    4,'s','h','i','p','s',' ','a','n','d',' ','f','l','y',' ','h','o','m','e','.',
};

const uint8_t * const IntroTexts[] = { IntroText_00, IntroText_01, IntroText_02, IntroText_03 }; 

void title_Init() {

    gameState = GameState::Title;

    for (Point &star : starfield) {

        star.x = random(0, 128);
        star.y = random(0, 64);
        
    }

    titleScreenVars.reset();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void title() { 

    if (arduboy.justPressed(A_BUTTON)) {

        switch (titleScreenVars.mode) {

            case TitleMode::OBS:
                titleScreenVars.mode = TitleMode::Scroll_One;
                titleScreenVars.counter = 64;
                break;

            case TitleMode::Scroll_One:
                titleScreenVars.mode = TitleMode::Scenario;
                titleScreenVars.counter = 64;
                break;

            case TitleMode::Scroll_Two:
                gameState = GameState::Game_Init; 
                break;

            default:
                break;

        }

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

    switch (titleScreenVars.mode) {

        case TitleMode::OBS:

            Sprites::drawExternalMask(28, 11, Images::Title, Images::Title_Mask, 0, 0);

            break;

        case TitleMode::Scroll_One:

            titleScreenVars.counter--;
            Sprites::drawExternalMask(28, 11 - (64 - titleScreenVars.counter), Images::Title, Images::Title_Mask, 0, 0);
            arduboy.fillRect(6, 72 - (64 - titleScreenVars.counter), 118, 50, BLACK);
            Sprites::drawOverwrite(6, 72 - (64 - titleScreenVars.counter), Images::Border_TL, 0);
            Sprites::drawOverwrite(104, 102 - (64 - titleScreenVars.counter), Images::Border_BR, 0);

            if (titleScreenVars.counter == 0) {

                titleScreenVars.mode = TitleMode::Scenario;

            }

            break;

        case TitleMode::Scenario:

            arduboy.fillRect(6, 8, 118, 50, BLACK);
            Sprites::drawOverwrite(6, 8, Images::Border_TL, 0);
            Sprites::drawOverwrite(104, 38, Images::Border_BR, 0);
            introText();

            break;


        case TitleMode::Scroll_Two:

            titleScreenVars.counter--;
            arduboy.fillRect(6, 8 - (64 - titleScreenVars.counter), 118, 50, BLACK);
            Sprites::drawOverwrite(6, 8 - (64 - titleScreenVars.counter), Images::Border_TL, 0);
            Sprites::drawOverwrite(104, 38 - (64 - titleScreenVars.counter), Images::Border_BR, 0);

            font4x6.setCursor(18, 19 - (64 - titleScreenVars.counter));
            font4x6.print("..sort of! Avoid the");
            font4x6.setCursor(20, 29 - (64 - titleScreenVars.counter));
            font4x6.print("asteroids and enemy");
            font4x6.setCursor(22, 39 - (64 - titleScreenVars.counter));
            font4x6.print("ships and fly home.");

            if (titleScreenVars.counter == 0) {

                titleScreenVars.mode = TitleMode::Entrance;
                titleScreenVars.counter = 0;

            }

            break;

        case TitleMode::Entrance:

            titleScreenVars.counter++;
            Sprites::drawExternalMask(-16 + titleScreenVars.counter, player.y, Images::PlayerShip, Images::PlayerShip_Mask, 0, 0);
            Sprites::drawExternalMask(-25 + titleScreenVars.counter, player.y + 3, Images::ShipParticle, Images::ShipParticle_Mask, arduboy.getFrameCountHalf(8), arduboy.getFrameCountHalf(8));

            if (titleScreenVars.counter == 25) {

                gameState = GameState::Game_Init;

            }

            break;

    }

}


void introText() {

    uint8_t line = 0;
    uint8_t x = 0;
    
    for (uint8_t i = 0; i < titleScreenVars.index; i++) {

        uint8_t c = pgm_read_byte(&IntroTexts[titleScreenVars.panel][i]);

        switch (c) {

            case 0 ... 31:
                line++;
                x = 0 + c;
                break;

            case ' ':
                x = x + 3;
                break;
            
            default:
                font4x6.setCursor(18 + x, 9 + (line * 10));
                font4x6.print(static_cast<char>(c));
                x = x + 5;
                break;

        }
        
    }


    if (titleScreenVars.index < textLengths[titleScreenVars.panel] && arduboy.getFrameCount(2)) {

        titleScreenVars.index++;

    }


    uint8_t justPressed = arduboy.justPressedButtons();

    if (justPressed & A_BUTTON || justPressed & B_BUTTON) {
        
        if (titleScreenVars.index == textLengths[titleScreenVars.panel] && titleScreenVars.skipTypewriter == false) {
            titleScreenVars.panel++;
            titleScreenVars.index = 0;
        }
        else {
            if (titleScreenVars.skipTypewriter) titleScreenVars.panel++;
            titleScreenVars.skipTypewriter = true;
            titleScreenVars.index = textLengths[titleScreenVars.panel];
        }

        if (titleScreenVars.panel == 4) {
            titleScreenVars.mode = TitleMode::Scroll_Two;
            titleScreenVars.counter = 64;
        }

    }

}


