#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../../include/Entity.h"

Entity::Entity(const sf::Texture& texture,
               float scale,
               float initial_X,
               float initial_Y,
               int lives,
               float speed,
               float acceleration) {
    Entity::Sprite::setTexture(texture);
    Entity::Sprite::setScale(scale, scale);
    Entity::Sprite::setPosition(initial_X, initial_Y);
    this->lives = lives;
    this->speed = speed;
    this->acceleration = acceleration;
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
}

int Entity::getLives() const {
    return lives;
}

float Entity::getSpeed() const {
    return speed;
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

void Entity::setInitialPosition(float initial_X, float initial_Y) {
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
}

void Entity::setLives(int lives) {
    this->lives += lives;
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

void Entity::accelerate(int X, int Y, int Z) {
    this->speed += acceleration * Z;
    Entity::move(X * speed, Y * speed);
}

float Entity::getWidth() {
    return Entity::Sprite::getLocalBounds().width *
           Entity::Sprite::getScale().x;
}

float Entity::getHeight() {
    return Entity::Sprite::getLocalBounds().height *
           Entity::Sprite::getScale().y;
}