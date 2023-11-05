#include <SFML/Graphics.hpp>
#include "../include/Entity.h"

using namespace sf;

Entity::Entity(const Texture& texture,
               float initial_X,
               float initial_Y,
               int lives,
               float speed_X,
               float speed_Y,
               float acceleration) {
    this->lives = lives;
    this->speed_X = speed_X;
    this->speed_Y = speed_Y;
    this->acceleration = acceleration;
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
    Entity::Sprite::setTexture(texture);
    Entity::Sprite::setPosition(initial_X, initial_Y);
}

int Entity::getLives() const {
    return lives;
}

float Entity::getSpeed_X() const {
    return speed_X;
}

float Entity::getSpeed_Y() const {
    return speed_Y;
}

bool Entity::isAlive() const {
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

void Entity::update(float deltaTime, int window_X, int window_Y) {
    // Move Left
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        Entity::move(-Entity::getSpeed_X() * deltaTime, 0);
        setReverse(true);
    }
    // Move Right
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        Entity::move(Entity::getSpeed_X() * deltaTime, 0);
        setReverse(false);
    }
    // Jump
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (!Entity::getIsJumping()) {
            setIsJumping(true);
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
        }
    }    
}