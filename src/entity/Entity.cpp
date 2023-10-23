#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../include/Entity.h"

Entity::Entity(const sf::Texture& texture,
               float scale,
               float initial_X,
               float initial_Y,
               int lives,
               float speed_X,
               float speed_Y,
               float acceleration) {
    Entity::Sprite::setTexture(texture);
    Entity::Sprite::setScale(scale, scale);
    Entity::Sprite::setPosition(initial_X, initial_Y);
    this->lives = lives;
    this->speed_X = speed_X;
    this->speed_Y = speed_Y;
    this->acceleration = acceleration;
    this->initial_X = initial_X;
    this->initial_Y = initial_Y;
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

void Entity::accelerate(int X, int Y, int Z) {
    this->speed_Y += acceleration * Z;
    Entity::move(0, Y * speed_Y);
}

float Entity::getWidth() {
    return Entity::Sprite::getLocalBounds().width *
           Entity::Sprite::getScale().x;
}

float Entity::getHeight() {
    return Entity::Sprite::getLocalBounds().height *
           Entity::Sprite::getScale().y;
}