#include "../include/Laser.h"
#include "../include/LaserAssets.h"
#include "../include/PlayerAssets.h"
#include "../include/GameAssets.h"

Laser::Laser(float speed, float acceleration) {
    this->speed = speed;
    this->acceleration = acceleration;
}

using namespace LaserAssets;
using namespace LaserTextures;
using namespace LaserVariables;

using namespace GameAssets;

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

void Laser::update() {

    Laser::setScale(laserScale * currentWindowRatio, laserScale * currentWindowRatio);

    if (isPowerUp) laserScale += (laserScaleIncreaseFactor * deltaTime) * 1.6;
    
    if (isPlayerShooting) {
        if (isShotInstant) {
            isPlayerReverse ? Laser::setIsReverse(true) : Laser::setIsReverse(false);
            laserOrigin_X = isPlayerReverse ? laserPlaceholder_X : laserPlaceholderReverse_X;
            laserOrigin_Y = laserPlaceholder_Y;
            Laser::setPosition(Vector2f(laserOrigin_X, laserOrigin_Y));
            laserClock.restart();
            isShotInstant = false;
        }
        
        elapsedTimeSinceShot = Time::Zero;
        elapsedTimeSinceShot = laserClock.getElapsedTime();

        Laser::getIsReverse() ? Laser::move(-(laserOriginalSpeed_X * deltaTime), 0) : Laser::move(laserOriginalSpeed_X * deltaTime, 0);
        if (elapsedTimeSinceShot > laserCooldown) {
            isPlayerShooting = false;
            elapsedTimeSinceShot = laserCooldown;
            Laser::setPosition(-Laser::getWidth(), laserOrigin_Y);
        }
    }

    Laser::getIsBig() ? Laser::setTexture(Laser::getIsReverse() ? laserRed_reverse : laserRed) :
                        Laser::setTexture(Laser::getIsReverse() ? laserBlue_reverse : laserBlue);
}