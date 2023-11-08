#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Entity.h"
#include "../include/PlayerAssets.h"
#include "../include/GameAssets.h"

using namespace sf;
using namespace GameAssets;

Entity::Entity() {};

Entity::Entity(
               int lives,
               float speed_X,
               float speed_Y,
               float acceleration
               ) {
    this->lives = lives;
    this->speed_X = speed_X;
    this->speed_Y = speed_Y;
    this->acceleration = acceleration;
}
using namespace PlayerAssets;
using namespace PlayerVariables;

int Entity::getLives() const {
    return lives;
}

float Entity::getAcceleration() {
    return this->acceleration;
}

float Entity::getSpeed_X() const {
    return speed_X;
}

float Entity::getSpeed_Y() const {
    return speed_Y;
}

bool Entity::getIsAlive() const {
    return lives > 0;
}

float Entity::getWidth() {
    return Entity::getGlobalBounds().width;
}

float Entity::getHeight() {
    return Entity::getGlobalBounds().height;
}

void Entity::setLives(int lives) {
    this->lives += lives;
}

void Entity::setSpeed_X(float speed_X) {
    this->speed_X = speed_X;
}

void Entity::setSpeed_Y(float speed_Y) {
    this->speed_Y = speed_Y;
}

void Entity::setAcceleration(float acceleration) {
    this->acceleration = acceleration;
}

void Entity::accelerate() {
    speed_Y += acceleration * deltaTime;
    Entity::move(0, speed_Y);
}

void Entity::setReverse(bool isReverse) {
    this->isReverse = isReverse;
}

bool Entity::getIsReverse() {
    return this->isReverse;
}

bool Entity::getIsJumping() {
    return this->isJumping;
}

void Entity::setIsJumping(bool isJumping) {
    this->isJumping = isJumping;
}

void Entity::setIsShooting(bool isShooting) {
    this->isShooting = isShooting;
}

bool Entity::getIsShooting() {
    return this->isShooting;
}

bool Entity::getIsPowerup() {
    return this->isPowerup;
}

void Entity::setIsPowerup(bool isPowerup) {
    this->isPowerup = isPowerup;
}

bool Entity::getIsBig() {
    return this->isBig;
}

void Entity::setIsBig(bool isBig) {
    this->isBig = isBig;
}

void Entity::loadPlayerAssets() {
    loadPlayerTextures();
    loadPlayerSounds();
}

void Entity::grow() {
    if (Entity::getScale().x <= (playerInitialScale * 2) * currentWindowRatio) {
        if (playerScore % 5 == 0) {
            Entity::setIsPowerup(true);
            powerUp.play();
        } else {
            Entity::setIsPowerup(false);
        }
    } else if ((int) Entity::getScale().x * 10 == (int) playerInitialScale * 20) {
        // laser.setSpeed_X(laserOriginalSpeed_X * 2);
        isPlayerBig = true;
        if (soundtrack.getStatus() == Sound::Playing) soundtrack.stop();
        if (soundtrackBig.getStatus() != Sound::Playing) soundtrackBig.play();
    }    
}

void Entity::update() {
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        Entity::move(-Entity::getSpeed_X() * deltaTime, 0);
        isPlayerReverse = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::D)) {
        Entity::move(Entity::getSpeed_X() * deltaTime, 0);
        isPlayerReverse = false;
    }

    // Border limits
    if (Entity::getPosition().x > playerMax_X) Entity::setPosition(playerMax_X, Entity::getPosition().y);
    if (Entity::getPosition().x < 0)           Entity::setPosition(0, Entity::getPosition().y);
    if (Entity::getPosition().y > playerMax_Y) Entity::setPosition(Entity::getPosition().x, playerMax_Y);
    if (Entity::getPosition().y < 0)           Entity::setPosition(Entity::getPosition().x, 0);    

    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (!Entity::getIsJumping()) {
            setIsJumping(true);
            jumpPlayer.play();
        }
    }

    if (Entity::getPosition().y < window_X - Entity::getHeight()) {
        if (!Entity::getIsJumping()) {
            Entity::setPosition(Entity::getPosition().x, 900 - Entity::getHeight());
        }
    }

    if (Entity::getIsJumping()) {
        Entity::accelerate();
        if (Entity::getPosition().y >= window_Y - Entity::getHeight()) {
            Entity::setIsJumping(false);
            Entity::setSpeed_Y(-7);
            stompLightPlayer.play();
        }
    }

    float windowRatio = window_X / 1600;
    Entity::setScale(playerInitialScale * windowRatio, playerInitialScale * windowRatio);
    playerCurrent_X = Entity::getPosition().x;

    if (isPlayerReverse) {
        if (isPlayerShooting && elapsedTimeSinceShot < shootWait) {
            Entity::setTexture(isPowerup ? player_shooting_reverse_powerup : 
            (isPlayerBig ? player_golden_shooting_reverse : player_shooting_reverse));
        } else {
            Entity::setTexture(isPowerup ? player_reverse_powerup : 
            (isPlayerBig ? player_golden_reverse : player_reverse));
        }
    } else {
        if (isPlayerShooting && elapsedTimeSinceShot < shootWait) {
            Entity::setTexture(isPowerup ? player_shooting_powerup : 
            (isPlayerBig ? player_golden_shooting : player_shooting));
        } else {
            Entity::setTexture(isPowerup ? player_powerup : 
            (isPlayerBig ? player_golden : player_normal));
        }
    }

    laserPlaceholder_X = Entity::getPosition().x - 20;
    laserPlaceholderReverse_X = Entity::getPosition().x + Entity::getWidth() / 1.5;
    laserPlaceholder_Y = Entity::getPosition().y + Entity::getHeight() / 1.65;

    // Shoot Laser
    if (Keyboard::isKeyPressed(Keyboard::Enter) && !isPlayerShooting && !isPowerUp) {
        isPlayerBig ? laserShootBig.play() : laserShoot.play();
        isPlayerShooting = true;
        isShotInstant = true;
    }

    float currentWindowRatio = (float) window_X / 1600;
    if (isPowerup) {
        playerInitialScale += playerScaleIncreaseFactor * currentWindowRatio * deltaTime;
    }
}