#include <Arduboy2.h>

#pragma once

struct SplashScreenVars {

    uint8_t delay = 0;

};

struct TitleScreenVars {

    uint8_t counter = 0;
    TitleMode mode = TitleMode::OBS;
    uint8_t panel = 0;
    uint8_t index = 0;
    bool skipTypewriter = false;

    void reset() {

        this->mode = TitleMode::OBS;
        this->counter = 0;
        this->panel = 0;
        this->index = 0;
        this->skipTypewriter = false;

    }

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
