#ifndef LASER_H
#define LASER_H

#include "../include/Entity.h"

class Laser : public Entity {
private:
    float speed{};
    float acceleration{};
    bool isReverse{};
    bool isShot{};

public:
    Laser(float speed, float acceleration);

    float getSpeed();
    bool getIsShot();
    void setSpeed(float speed);
    void setIsShot(bool isShot);
    void update();
};

#endif