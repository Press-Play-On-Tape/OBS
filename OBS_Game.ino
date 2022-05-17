
#include <Arduboy2.h>     
#include "src/utils/Constants.h"

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

    #ifdef ONE_BULLET
    bullet.reset();
    #else
    bullets.reset();
    #endif

    player.reset();
    gameState = GameState::Game;

}


// -----------------------------------------------------------------------------------------------

void game() {


    // Move player ..

    switch (gameState) {
    
        case GameState::Game:
            {

                // Increase score based on distance travelled ..

                if (arduboy.getFrameCount(Constants::ScoreDistance) == 0) {

                    player.score++;

                }

                player.y = player.y + static_cast<int8_t>(player.direction);

                if (player.direction == Direction::Up && player.y == 0) {
                    player.direction = Direction::None;
                }

                if (player.direction == Direction::Down && player.y == 54) {
                    player.direction = Direction::None;
                }

                #ifdef ONE_BULLET

                    if (arduboy.justPressed(A_BUTTON) && bullet.x == -1) {

                        switch (player.direction) {

                            case Direction::Up:
                                player.direction = Direction::Down;
                                break;

                            case Direction::Down:
                                player.direction = Direction::Up;
                                break;

                            default:

                                switch (player.y) {

                                    case 0:
                                        player.direction = Direction::Down;
                                        break;

                                    case 54:
                                        player.direction = Direction::Up;
                                        break;

                                    default:
                                        if (random(0,2) == 0) {
                                            player.direction = Direction::Up;
                                        }
                                        else {
                                            player.direction = Direction::Down;
                                        }
                                        break;

                                }

                                break;
                                
                        }

                        #ifdef ORIG_BULLET
                            bullet.x = 12;
                            bullet.y = player.y + 5;
                        #else
                            bullet.x = 12;
                            bullet.y = player.y + 2;
                        #endif
                        
                        bullet.hitObject = HitObject::None;

                    }

                #else

                    if (arduboy.justPressed(A_BUTTON)) {
                        
                        uint8_t bulletIdx = bullets.getInactiveBullet();

                        if (bulletIdx != Constants::Bullet_None) {

                            Bullet &bullet = bullets.bullets[bulletIdx];

                            switch (player.direction) {

                                case Direction::Up:
                                    player.direction = Direction::Down;
                                    break;

                                case Direction::Down:
                                    player.direction = Direction::Up;
                                    break;

                                default:

                                    switch (player.y) {

                                        case 0:
                                            player.direction = Direction::Down;
                                            break;

                                        case 54:
                                            player.direction = Direction::Up;
                                            break;

                                        default:
                                            if (random(0,2) == 0) {
                                                player.direction = Direction::Up;
                                            }
                                            else {
                                                player.direction = Direction::Down;
                                            }
                                            break;

                                    }

                                    break;
                                    
                            }

                            #ifdef ORIG_BULLET
                                bullet.x = 12;
                                bullet.y = player.y + 5;
                            #else
                                bullet.x = 12;
                                bullet.y = player.y + 2;
                            #endif

                            bullet.hitObject = HitObject::None;

                        }

                    }

                #endif

                #ifdef ONE_BULLET

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

                            checkBulletCollision(bullet);

                        }

                    }

                #else

                    for (Bullet &bullet : bullets.bullets) {
                            
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

                                checkBulletCollision(bullet);

                            }

                        }

                    }

                #endif


                // Has the player hit a asteroid meteor?

                bool collision = false;

                for (Asteroid &largeAsteroid : largeAsteroids) {

                    if (collide(9, player.y, Images::PlayerShip, largeAsteroid.x, largeAsteroid.y, Images::BigAsteroid[largeAsteroid.type])) {

                        if (player.health > 0)  player.health--;
                        if (player.health == 0) player.explodeCounter = 21;
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


                    // Has the player hit an enemy ?

                    for (Enemy &enemy : enemies) {

                        if (collide(9, player.y, Images::PlayerShip, enemy.x, enemy.y, Images::Enemy)) {

                            if (player.health > 0)  player.health--;
                            if (player.health == 0) player.explodeCounter = 21;
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

                }

            }

            break;

        case GameState::Score:

            if (arduboy.justPressed(A_BUTTON)) {

                gameState = GameState::Title_Init;

            }

            break;

        default:

            break;

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

            #ifdef ONE_BULLET
                
                if (bullet.hitObject == HitObject::LargeAsteroid) {

                    bullet.x--;

                }

            #else

                for (Bullet &bullet : bullets.bullets) {
                
                    if (bullet.hitObject == HitObject::LargeAsteroid) {

                        bullet.x--;

                    }

                }

            #endif

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


    switch (gameState) {

        case GameState::Game:
            {

                // Render player bullet ..

                #ifdef ONE_BULLET
                    
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

                #else
                    
                    for (Bullet &bullet : bullets.bullets) {
                                                
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

                    }

                #endif

                // Render player ..

                if (player.health > 0 || player.explodeCounter > 16) {

                    Sprites::drawExternalMask(9 + xOffset, player.y + yOffset, Images::PlayerShip, Images::PlayerShip_Mask, 0, 0);
                    Sprites::drawExternalMask(xOffset, player.y + 3 + yOffset, Images::ShipParticle, Images::ShipParticle_Mask, arduboy.getFrameCountHalf(8), arduboy.getFrameCountHalf(8));

                }
                
                if (player.explodeCounter > 0) {

                    Sprites::drawExternalMask(6, player.y + yOffset, 
                                                pgm_read_word_near(&Images::Puffs[(21 - player.explodeCounter) / 3]), 
                                                pgm_read_word_near(&Images::Puff_Masks[(21 - player.explodeCounter) / 3]), 
                                                0, 0);

                }
                
                if (player.updateExplosion()) {
                
                    gameState = GameState::Score;

                }


                // Render the HUD ..

                arduboy.fillRect(78, 56, 64, 10, BLACK);
                arduboy.fillRect(79, 56, 1, 10, WHITE);
                arduboy.fillRect(127, 56, 1, 10, WHITE);

                uint8_t health_Bar = player.health / Constants::Health_Factor;

                font4x6.setCursor(82, 56);
                if (player.score < 1000)   font4x6.print("0");
                if (player.score < 100)    font4x6.print("0");
                if (player.score < 10)     font4x6.print("0");
                font4x6.print(player.score);


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

            break;

        case GameState::Score:
            {
                Sprites::drawExternalMask(34, 22, Images::Score, Images::Score_Mask, 0, 0);

                uint8_t health_Bar = player.health / Constants::Health_Factor;

                font4x6.setCursor(55, 29);
                if (player.score < 1000)   font4x6.print("0");
                if (player.score < 100)    font4x6.print("0");
                if (player.score < 10)     font4x6.print("0");
                font4x6.print(player.score);
            }

            break;

        default:

            break;

    }

}

void checkBulletCollision(Bullet &bullet) {

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
            player.score = player.score + 5;

            arduboy.setFrameRate(50 + (player.score / 4));

        }

    }

}