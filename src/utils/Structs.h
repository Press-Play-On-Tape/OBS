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

    Direction direction = Direction::None;
    Direction prevDirection = Direction::None;
    Motion motion = Motion::None;
    
    uint8_t count = 0;
    
};
