#include "../include/Laser.h"
#include "../include/LaserAssets.h"

Laser::Laser(float initial_X, float initial_Y, float speed, float acceleration) {
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
    this->speed = speed;
    this->acceleration = acceleration;
}

using namespace LaserAssets;
using namespace LaserTextures;
using namespace LaserVariables;

float Laser::getSpeed() {
    return this->speed;
}

void Laser::setSpeed(float speed) {
    this->speed = speed;
}

bool Laser::getIsShot() {
    return this->isShot;
}

void Laser::setIsShot(bool isShot) {
    this->isShot = isShot;
}

void Laser::loadLaserAssets() {
    loadLaserAssets();
}

void Laser::update(float deltaTime, float window_X) {

    if (Laser::getIsShot()) {
        elapsedTimeSinceShot = Time::Zero;
        elapsedTimeSinceShot = laserClock.getElapsedTime();
        Laser::getIsReverse() ? Laser::move(-(laserInitialSpeed_X * deltaTime), 0) : Laser::move(laserInitialSpeed_X * deltaTime, 0);
        if (elapsedTimeSinceShot > laserCooldown) {
            Laser::setIsShot(false);
            elapsedTimeSinceShot = laserCooldown;
            Laser::setPosition(-window_X, laserOrigin_Y);
        }
    }
    // Laser textures
    Laser::getIsBig() ? Laser::setTexture(Laser::getIsReverse() ? laserRed_reverse : laserRed) :
                        Laser::setTexture(Laser::getIsReverse() ? laserBlue_reverse : laserBlue);    
}