//
// Created by neo on 10/20/23.
//

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Player.h"

Player::Player(const sf::Texture& texture,
               float scale,
               float initialPosition,
               int lives) {
    Player::Sprite::setTexture(texture);
    Player::Sprite::setScale(scale, scale);
    Player::Sprite::setPosition(initialPosition, initialPosition);
    this->lives = lives;
}

int Player::getLives() const {
    return lives;
}

float Player::getSpeed() const {
    return speed;
}

bool Player::isAlive() const {
    return lives > 0;
}

float Player::getInitialPosition() const {
    return initialPosition;
}

void Player::setLives(int lives) {
    this->lives += lives;
}

void Player::setSpeed(float speed) {
    this->speed = speed;
}
