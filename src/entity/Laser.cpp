#include "../include/Laser.h"
#include "../include/LaserAssets.h"
#include "../include/PlayerAssets.h"

Laser::Laser(float initial_X, float initial_Y, float speed, float acceleration) {
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
    this->speed = speed;
    this->acceleration = acceleration;
}

using namespace LaserAssets;
using namespace LaserTextures;
using namespace LaserVariables;

using namespace PlayerAssets::PlayerVariables;

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

void Laser::load() {
    loadLaserAssets();
}

void Laser::update(float deltaTime, float window_X) {

    if (isPowerUp) laserScale += (playerScaleIncreaseFactor * (window_X / 1600) * deltaTime) * 1.6;
    
    if (isPlayerShooting) {
        if (isShotInstant) {
            isPlayerReverse ? Laser::setReverse(true) : Laser::setReverse(false);
            laserOrigin_X = isPlayerReverse ? laserPlaceholder_X : laserPlaceholderReverse_X;
            laserOrigin_Y = laserPlaceholder_Y;
            Laser::setPosition(Vector2f(laserOrigin_X, laserOrigin_Y));
            laserClock.restart();
            
            isShotInstant = false;
        }
        
        elapsedTimeSinceShot = Time::Zero;
        elapsedTimeSinceShot = laserClock.getElapsedTime();

        Laser::getIsReverse() ? Laser::move(-(laserInitialSpeed_X * deltaTime), 0) : Laser::move(laserInitialSpeed_X * deltaTime, 0);
        if (elapsedTimeSinceShot > laserCooldown) {
            isPlayerShooting = false;
            elapsedTimeSinceShot = laserCooldown;
            Laser::setPosition(-window_X, laserOrigin_Y);
        }
    }

    Laser::getIsBig() ? Laser::setTexture(Laser::getIsReverse() ? laserRed_reverse : laserRed) :
                        Laser::setTexture(Laser::getIsReverse() ? laserBlue_reverse : laserBlue);
}