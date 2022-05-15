
#include <Arduboy2.h>     
#include "src/utils/Constants.h"


uint8_t y = 9;
Direction direction = Direction::Down;
uint16_t health = 50 * 8;

const int8_t xOffsets[] = { -2, 1, 2, 0 };
const int8_t yOffsets[] = { 0, -2, 1, 2 };

// -----------------------------------------------------------------------------------------------

void game_Init() {

    for (Point &star : starfield) {

        star.x = random(0, 128);
        star.y = random(0, 64);
        
    }

    for (Asteroid &smallAsteroid : smallAsteroids) {

        smallAsteroid.x = random(0, 192);
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

        for (Asteroid &largeAsteroid : largeAsteroids) {

            if (collide(bullet.x, bullet.y, Images::Bullet, largeAsteroid.x, largeAsteroid.y, Images::BigAsteroid[largeAsteroid.type])) {
                bullet.hitObject = HitObject::LargeAsteroid;
                bullet.hitCount = 1;
                bullet.x = largeAsteroid.x - 4;
            }

        }

    }


    // Has the player hit a large meteor?

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
            xOffset = xOffsets[offsetCount - 1];
            yOffset = yOffsets[offsetCount - 1];

        }

    }
    else {

        offsetCount = 0;
        xOffset = 0;
        yOffset = 0;

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

                    switch (enemy.direction) {

                        case Direction::Up:

                            if (canMoveEnemy(enemy, enemy.x - 1, enemy.y - 1)) {

                                enemy.x--;
                                enemy.y--;

                            }
                            else  {
                                enemy.x--;
                            }

                            break;

                        case Direction::Down:

                            if (canMoveEnemy(enemy, enemy.x - 1, enemy.y + 1)) {

                                enemy.x--;
                                enemy.y++;

                            }
                            else  {
                                enemy.x--;
                            }

                            break;

                        case Direction::None:

                            enemy.x--;
                            break;                            

                    }


                    // Change direction?

                    enemy.count--;

                    if (enemy.count == 0) {

                        enemy.count = 6 + random(0, 12);

                        switch (enemy.direction) {

                            case Direction::Up:
                            case Direction::Down:
                                enemy.prevDirection = enemy.direction;
                                enemy.direction = Direction::None;
                                break;

                            default:
                                if (enemy.prevDirection == Direction::Up) {
                                    enemy.direction = Direction::Down;
                                }
                                else {
                                    enemy.direction = Direction::Up;
                                }
                                break;

                        }

                    }

                }

                break;


            case Motion::Fast:

                switch (enemy.direction) {

                    case Direction::Up:

                        if (canMoveEnemy(enemy, enemy.x - 1, enemy.y - 1)) {

                            enemy.x--;
                            enemy.y--;

                        }
                        else if (canMoveEnemy(enemy, enemy.x - 1, enemy.y)) {
                            enemy.x--;
                        }

                        break;

                    case Direction::Down:

                        if (canMoveEnemy(enemy, enemy.x - 1, enemy.y + 1)) {

                            enemy.x--;
                            enemy.y++;

                        }
                        else if (canMoveEnemy(enemy, enemy.x - 1, enemy.y)) {
                            enemy.x--;
                        }

                        break;

                    case Direction::None:

                        enemy.x--;
                        break;                            

                }


                // Change direction?

                enemy.count--;

                if (enemy.count == 0) {

                    enemy.count = 6 + random(0, 12);

                    switch (enemy.direction) {

                        case Direction::Up:
                        case Direction::Down:
                            enemy.prevDirection = enemy.direction;
                            enemy.direction = Direction::None;
                            break;

                        default:
                            if (enemy.prevDirection == Direction::Up) {
                                enemy.direction = Direction::Down;
                            }
                            else {
                                enemy.direction = Direction::Up;
                            }
                            break;

                    }

                }

                break;

        }


        if (enemy.x == -19) {

            launchEnemy(enemy);

        }

        Sprites::drawExternalMask(enemy.x + xOffset, enemy.y + yOffset, Images::Enemy, Images::Enemy_Mask, 0, 0);

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

    arduboy.fillRect(121, 0, 8, 64, BLACK);
    arduboy.drawRect(122, 0, 6, 64, WHITE);

    uint8_t health_Bar = health / 8;

    for (uint8_t i = 0; i < health_Bar; i++) {

        if (i % 2 == 0) {

            arduboy.drawFastHLine(124, 61 - i, 2, WHITE);

        }

    }

}
