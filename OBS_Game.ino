
#include <Arduboy2.h>     
#include "src/utils/Constants.h"


uint16_t score = 0;
uint8_t y = 26;
Direction direction = Direction::None;
uint16_t health = (18 * Constants::Health_Factor) - 1;

const int8_t xOffsets[] = { -2, 1, 2, 0 };
const int8_t yOffsets[] = { 0, -2, 1, 2 };

// -----------------------------------------------------------------------------------------------

void game_Init() {

    for (Asteroid &smallAsteroid : smallAsteroids) {

        smallAsteroid.x = random(128, 256);
        smallAsteroid.y = random(0, 56);
        
    }

    for (Asteroid &largeAsteroid : largeAsteroids) {

        launchLargeAsteroid(largeAsteroid);
        
    }

    for (Enemy &enemy : enemies) {

        launchEnemy(enemy);
        
    }

    bullet.reset();
    gameState = GameState::Game;

}


// -----------------------------------------------------------------------------------------------

void game() {


    // Move player ..

    y = y + static_cast<int8_t>(direction);

    if (direction == Direction::Up && y == 0) {
        direction = Direction::None;
    }

    if (direction == Direction::Down && y == 54) {
        direction = Direction::None;
    }


    if (arduboy.justPressed(A_BUTTON) && bullet.x == -1) {

        switch (direction) {

            case Direction::Up:
                direction = Direction::Down;
                break;

            case Direction::Down:
                direction = Direction::Up;
                break;

            default:

                switch (y) {

                    case 0:
                        direction = Direction::Down;
                        break;

                    case 54:
                        direction = Direction::Up;
                        break;

                    default:
                        if (random(0,2) == 0) {
                            direction = Direction::Up;
                        }
                        else {
                            direction = Direction::Down;
                        }
                        break;

                }

                break;
                
        }

        bullet.x = 12;
        bullet.y = y + 5;
        bullet.hitObject = HitObject::None;

    }

    if (bullet.hitCount > 0) {

        bullet.hitCount++;

        if (bullet.hitCount > 3) {
            bullet.reset();
        }

    }

    if (bullet.x > 0 && bullet.hitCount == 0) {

        bullet.x = bullet.x + 4;

        if (bullet.x >= 128) {
            bullet.x = -1;
        }
        else {


            // Has the bullet hit a large asteroid?

            for (Asteroid &largeAsteroid : largeAsteroids) {

                if (collide(bullet.x, bullet.y, Images::Bullet, largeAsteroid.x, largeAsteroid.y, Images::BigAsteroid[largeAsteroid.type])) {
                    bullet.hitObject = HitObject::LargeAsteroid;
                    bullet.hitCount = 1;
                    bullet.x = largeAsteroid.x - 4;
                }

            }


            // Has the bullet hit an enemy?

            for (Enemy &enemy : enemies) {

                if (collide(bullet.x, bullet.y, Images::Bullet, enemy.x, enemy.y, Images::Enemy)) {

                    bullet.hitObject = HitObject::Enemy;
                    bullet.hitCount = 1;
                    bullet.x = enemy.x - 4;

                    enemy.explodeCounter = 21;
                    enemy.active = false;
                    score++;

                }

            }

        }

    }


    // Has the player hit a asteroid meteor?

    bool collision = false;

    for (Asteroid &largeAsteroid : largeAsteroids) {

        if (collide(9, y, Images::PlayerShip, largeAsteroid.x, largeAsteroid.y, Images::BigAsteroid[largeAsteroid.type])) {

            health--;
            collision = true;
            break;

        }

    }

    if (collision) {

        offsetCount++;

        if (offsetCount > 4) {

            offsetCount = 1;

        }

        xOffset = xOffsets[offsetCount - 1];
        yOffset = yOffsets[offsetCount - 1];
        
        arduboy.invert(offsetCount % 2);

    }
    else {

        offsetCount = 0;
        xOffset = 0;
        yOffset = 0;
        arduboy.invert(false);

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


    // Move and render small asteroids ..

    for (Asteroid &smallAsteroid : smallAsteroids) {

        if (arduboy.getFrameCount(3) == 0) {

            smallAsteroid.x--;

            if (smallAsteroid.x == -9) {
                smallAsteroid.x = 128 + random(0, 96);
                smallAsteroid.y = random(0, 56);
            }

        }

        Sprites::drawExternalMask(smallAsteroid.x + xOffset, smallAsteroid.y + yOffset, Images::SmallAsteroid, Images::SmallAsteroid_Mask, 0, 0);
        
    }


    // Move and render large asteroids ..

    for (Asteroid &largeAsteroid : largeAsteroids) {

        if (arduboy.getFrameCount(2) == 0) {

            largeAsteroid.x--;

            if (largeAsteroid.x == -19) {

                launchLargeAsteroid(largeAsteroid);

            }

            if (bullet.hitObject == HitObject::LargeAsteroid) {

                bullet.x--;

            }

        }

        Sprites::drawExternalMask(largeAsteroid.x + xOffset, largeAsteroid.y + yOffset, Images::BigAsteroid[largeAsteroid.type], Images::BigAsteroid_Mask[largeAsteroid.type], 0, 0);
        
    }


    // Move and render enemies ..

    for (Enemy &enemy : enemies) {

        switch (enemy.motion) {

            case Motion::None:

                if (arduboy.getFrameCount(2) == 0) {
                    enemy.x--;
                }

                break;

            case Motion::Slow:

                if (arduboy.getFrameCount(2) == 0) {

                    switch (enemy.path) {

                        case Path::Small:

                            enemy.pathCount++;
                            if (enemy.pathCount == 70) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Small[enemy.pathCount];
                            break;

                        case Path::Large:

                            enemy.pathCount++;
                            if (enemy.pathCount == 91) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Large[enemy.pathCount] + enemy.yOffset;
                            break;

                        default:
                            break;

                    }

                }

                break;


            case Motion::Fast:

                if (arduboy.getFrameCount(3) < 2) {

                    switch (enemy.path) {

                        case Path::Small:

                            enemy.pathCount++;
                            if (enemy.pathCount == 70) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Small[enemy.pathCount] + enemy.yOffset;
                            break;

                        case Path::Large:

                            enemy.pathCount++;
                            if (enemy.pathCount == 91) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Large[enemy.pathCount];
                            break;

                        default:
                            break;

                    }

                }

                break;

        }


        if (enemy.x == -19) {

            launchEnemy(enemy);

        }

        if (enemy.getActive() || enemy.explodeCounter > 16) {

            Sprites::drawExternalMask(enemy.x + xOffset, enemy.y + yOffset, Images::Enemy, Images::Enemy_Mask, 0, 0);

        }

        if (enemy.explodeCounter > 0) {

            Sprites::drawExternalMask(enemy.x + xOffset - 3, enemy.y + yOffset, 
                                      pgm_read_word_near(&Images::Puffs[(21 - enemy.explodeCounter) / 3]), 
                                      pgm_read_word_near(&Images::Puff_Masks[(21 - enemy.explodeCounter) / 3]), 
                                      0, 0);

        }
        
        if (enemy.updateExplosion()) {
        
            launchEnemy(enemy);

        }

    }



    // Render player bullet ..

    if (bullet.x > 0) {

        switch (bullet.hitCount) {

            case 0:
                Sprites::drawExternalMask(bullet.x + xOffset, bullet.y + yOffset, Images::Bullet, Images::Bullet_Mask, 0, 0);
                break;

            default:
                Sprites::drawSelfMasked(bullet.x + xOffset, bullet.y - 5 + yOffset, Images::Hit, bullet.hitCount - 1);
                break;

        }

    }


    // Render player ..

    Sprites::drawExternalMask(9 + xOffset, y + yOffset, Images::PlayerShip, Images::PlayerShip_Mask, 0, 0);
    Sprites::drawExternalMask(xOffset, y + 3 + yOffset, Images::ShipParticle, Images::ShipParticle_Mask, arduboy.getFrameCountHalf(8), arduboy.getFrameCountHalf(8));


    // Render the HUD ..

    arduboy.fillRect(78, 56, 64, 10, BLACK);
    arduboy.fillRect(79, 56, 1, 10, WHITE);
    arduboy.fillRect(127, 56, 1, 10, WHITE);

    uint8_t health_Bar = health / Constants::Health_Factor;

    font4x6.setCursor(82, 56);
    if (score < 1000)   font4x6.print("0");
    if (score < 100)    font4x6.print("0");
    if (score < 10)     font4x6.print("0");
    font4x6.print(score);


    switch (health_Bar / 6) {

        case 0: 
            Sprites::drawSelfMasked(103, 57, Images::Shield, health_Bar % 6);
            Sprites::drawSelfMasked(111, 57, Images::Shield, 0);
            Sprites::drawSelfMasked(119, 57, Images::Shield, 0);
            break;

        case 1:
            Sprites::drawSelfMasked(103, 57, Images::Shield, 5);
            Sprites::drawSelfMasked(111, 57, Images::Shield, health_Bar % 6);
            Sprites::drawSelfMasked(119, 57, Images::Shield, 0);
            break;
            

        case 2:
            Sprites::drawSelfMasked(103, 57, Images::Shield, 5);
            Sprites::drawSelfMasked(111, 57, Images::Shield, 5);
            Sprites::drawSelfMasked(119, 57, Images::Shield, health_Bar % 6);
            break;

    }

}
