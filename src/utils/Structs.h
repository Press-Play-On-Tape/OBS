#include <Arduboy2.h>

#pragma once

struct SplashScreenVars {

    uint8_t delay = 0;

};


struct Asteroid : public Point {

    uint8_t type = 0;
    
};

struct Bullet : public Point {

    uint8_t hitCount = 0;
    HitObject hitObject = HitObject::None;
    
    void reset() {
        this->x = -1;
        this->hitCount = 0;
        this->hitObject = HitObject::None;
    }

};

struct Enemy : public Point {

    bool active = false;
    Path path = Path::None;
    Motion motion = Motion::None;

    uint8_t pathCount = 0; 
    uint8_t yOffset = 0;         
    uint8_t explodeCounter = 0;
        
    bool updateExplosion() {

        if (this->explodeCounter > 0) {

            this->explodeCounter--;

            if (this->explodeCounter == 0) {

                this->explodeCounter = 0;
                return true;

            }

        }

        return false;

    }

    bool getActive() {

        return this->active;

    }

};
