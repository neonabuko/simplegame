//
// Created by neo on 10/20/23.
//

#include "Player.h"

Player::Player(float position_X, float position_Y) {
    this->position_X = position_X;
    this->position_Y = position_Y;
}

void Player::moveLeft(float speed) {
    this->position_X -= speed;
}

void Player::moveRight(float speed) {
    this->position_X += speed;
}

void Player::moveUp(float speed) {
    this->position_Y -= speed;
}

void Player::moveDown(float speed) {
    this->position_Y += speed;
}
