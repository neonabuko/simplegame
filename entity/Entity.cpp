#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Entity.h"

Entity::Entity(const sf::Texture& texture,
               float scale,
               float initialPosition,
               int lives,
               float speed) {
    Entity::Sprite::setTexture(texture);
    Entity::Sprite::setScale(scale, scale);
    Entity::Sprite::setPosition(initialPosition, initialPosition);
    this->lives = lives;
    this->speed = speed;
    this->initialPosition = initialPosition;
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

float Entity::getInitialPosition() const {
    return initialPosition;
}

void Entity::setLives(int lives) {
    this->lives += lives;
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

float Entity::getWidth() {
    return Entity::Sprite::getLocalBounds().width *
           Entity::Sprite::getScale().x;
}

float Entity::getHeight() {
    return Entity::Sprite::getLocalBounds().height *
           Entity::Sprite::getScale().y;
}