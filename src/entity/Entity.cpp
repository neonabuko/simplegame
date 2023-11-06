#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Entity.h"
#include "../include/PlayerAssets.h"

using namespace sf;

Entity::Entity(
               float initial_X,
               float initial_Y,
               int lives,
               float speed_X,
               float speed_Y,
               float acceleration
               ) {
    this->lives = lives;
    this->speed_X = speed_X;
    this->speed_Y = speed_Y;
    this->acceleration = acceleration;
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
    Entity::Sprite::setPosition(initial_X, initial_Y);
}
using namespace PlayerAssets;
using namespace Variables;

int Entity::getLives() const {
    return lives;
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

float Entity::getInitial_X() const {
    return initial_X;
}

float Entity::getInitial_Y() const {
    return initial_Y;
}

float Entity::getInitialScale_X() const{
    return this->initialScale_X;
}

float Entity::getInitialScale_Y() const{
    return this->initialScale_Y;
}

void Entity::setInitialPosition(float initial_X, float initial_Y) {
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
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

void Entity::accelerate(float deltaTime) {
    speed_Y += acceleration * deltaTime;
    Entity::move(0, speed_Y);
}

float Entity::getWidth() {
    return Entity::Sprite::getLocalBounds().width *
           Entity::Sprite::getScale().x;
}

float Entity::getHeight() {
    return Entity::Sprite::getLocalBounds().height *
           Entity::Sprite::getScale().y;
}

void Entity::setScale(float scale_X, float scale_Y) {
    this->scale_X = scale_X;
    this->scale_Y = scale_Y;
    Entity::Sprite::setScale(scale_X, scale_Y);
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

void Entity::update(float deltaTime, int window_X, int window_Y) {
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        Entity::move(-Entity::getSpeed_X() * deltaTime, 0);
        setReverse(true);
    }

    if (Keyboard::isKeyPressed(Keyboard::D)) {
        Entity::move(Entity::getSpeed_X() * deltaTime, 0);
        setReverse(false);
    }

    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (!Entity::getIsJumping()) {
            setIsJumping(true);
            PlayerAssets::jumpPlayer.play();
        }
    }

    if (Entity::getPosition().y < window_X - Entity::getHeight()) {
        if (!Entity::getIsJumping()) {
            Entity::setPosition(Entity::getPosition().x, 900 - Entity::getHeight());
        }
    }

    if (Entity::getIsJumping()) {
        Entity::accelerate(deltaTime);
        if (Entity::getPosition().y >= window_Y - Entity::getHeight()) {
            Entity::setIsJumping(false);
            Entity::setSpeed_Y(-7);
            PlayerAssets::stompLightPlayer.play();
        }
    }
    
    if (Entity::getIsReverse()) {
        if (Entity::getIsShooting() && elapsedTimeSinceShot < laserCooldown) {
            Entity::setTexture(Entity::getIsPowerup() ? player_shooting_reverse_powerup : 
            (Entity::getIsBig() ? player_golden_shooting_reverse : player_shooting_reverse));
        } else {
            Entity::setTexture(Entity::getIsPowerup() ? player_reverse_powerup : 
            (Entity::getIsBig() ? player_golden_reverse : player_reverse));
        }
    } else {
        if (isShooting && elapsedTimeSinceShot < laserCooldown) {
            Entity::setTexture(Entity::getIsPowerup() ? player_shooting_powerup : 
            (Entity::getIsBig() ? player_golden_shooting : player_shooting));
        } else {
            Entity::setTexture(Entity::getIsPowerup() ? player_powerup : 
            (Entity::getIsBig() ? player_golden : player_normal));
        }
    }
}