#ifndef LASER_H
#define LASER_H

#include "../include/Entity.h"

class Laser : public Entity {
private:
    float initial_X{};
    float initial_Y{};
    float speed{};
    float acceleration{};
    bool isReverse{};
    bool isShot{};

public:
    Laser(float initial_X, float initial_Y, float speed, float acceleration);

    float getSpeed();
    bool getIsShot();
    void setSpeed(float speed);
    void setIsShot(bool isShot);
    void loadLaserAssets();
    void update(float deltaTime, float window_X);
};

#endif