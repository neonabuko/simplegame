#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Entity.h"
#include "../include/PlayerAssets.h"
#include "../include/GameAssets.h"
#include "../include/EnemyAssets.h"

using namespace sf;
using namespace GameAssets;
using namespace PlayerAssets;
using namespace PlayerVariables;
using namespace PlayerControls;

Entity::Entity() {};

Entity::Entity(int lives, float speed_X, float speed_Y, float acceleration) {
    this->lives = lives;
    this->speed_X = speed_X;
    this->speed_Y = speed_Y;
    this->acceleration = acceleration;
}

int Entity::getLives() {
    return lives;
}

float Entity::getAcceleration() {
    return this->acceleration;
}

float Entity::getSpeed_X() {
    return speed_X;
}

float Entity::getSpeed_Y() {
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

bool Entity::getIsReverse() {
    return this->isReverse;
}

bool Entity::getIsJumping() {
    return this->isJumping;
}

bool Entity::getIsShooting() {
    return this->isShooting;
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

void Entity::setIsJumping(bool isJumping) {
    this->isJumping = isJumping;
}

void Entity::setIsShooting(bool isShooting) {
    this->isShooting = isShooting;
}

void Entity::setIsReverse(bool isReverse) {
    this->isReverse = isReverse;
}

void Entity::accelerate() {
    speed_Y += acceleration * deltaTime;
    Entity::move(0, speed_Y);
}

void Entity::incrementLives(int lives) {
    this->lives += lives;
}

void Entity::grow() {
    if (Entity::getScale().x <= (playerInitialScale * 2) * currentWindowRatio) {
        playerInitialScale += playerScaleIncreaseFactor * currentWindowRatio * deltaTime;
    } else if ((int) Entity::getScale().x * 10 == (int) playerInitialScale * 20) {
        isPlayerBig = true;
    }
}

void Entity::update() {
    playerMax_X = window_X - Entity::getWidth();
    playerMax_Y = window_Y - Entity::getHeight();

    if (isKey_A_pressed) {
        Entity::move(-Entity::getSpeed_X() * deltaTime, 0);
        isPlayerReverse = true;
    }

    if (isKey_D_pressed) {
        Entity::move(Entity::getSpeed_X() * deltaTime, 0);
        isPlayerReverse = false;
    }

    float entity_X = Entity::getPosition().x;
    float entity_Y = Entity::getPosition().y;

    // Background Movement
    bool is_at_background_movement_trigger = entity_X > playerMax_X / 1.8;
    float background_X = backgroundSprite.getPosition().x;
    float backgroundWidth = backgroundSprite.getGlobalBounds().width;
    if (is_at_background_movement_trigger && isKey_D_pressed && background_X + backgroundWidth > window_X) {
        backgroundSprite.move(-250 * deltaTime, 0);
        Entity::setSpeed_X(0);
        for (Enemy& enemy : enemies) {
            enemy.move(-250 * deltaTime, 0);
        }
    } else if (entity_X <= 0 && isKey_A_pressed && background_X < 0) {
        backgroundSprite.move(250 * deltaTime, 0);
        for (Enemy& enemy : enemies) {
            enemy.move(250 * deltaTime, 0);
        }
    } else {
        Entity::setSpeed_X(playerInitialSpeed_X);
    }

    // Border limits
    if (entity_X > playerMax_X) Entity::setPosition(playerMax_X, entity_Y);
    if (entity_X < 0)           Entity::setPosition(0, entity_Y);
    if (entity_Y > playerMax_Y) Entity::setPosition(entity_X, playerMax_Y);
    if (entity_Y < 0)           Entity::setPosition(entity_X, 0);

    if (isKey_Space_pressed) {
        if (!Entity::getIsJumping()) {
            setIsJumping(true);
        }
    }

    if (Entity::getIsJumping()) {
        Entity::accelerate();
        if (entity_Y > window_Y - Entity::getHeight()) {
            Entity::setIsJumping(false);
            Entity::setSpeed_Y(playerInitialSpeed_Y);
            stompLightPlayer.play();
        }
    }

    bool isShotAvailable = elapsedTimeSinceShot < shootWait;
    if (isPlayerReverse) {
        if (isShotAvailable) Entity::setTexture(isPowerup ? player_powerup_shooting_reverse : (isPlayerBig ? player_golden_shooting_reverse : player_shooting_reverse));
        else Entity::setTexture(isPowerup ? player_powerup_reverse : (isPlayerBig ? player_golden_reverse : player_reverse));
    } else {
        if (isShotAvailable) Entity::setTexture(isPowerup ? player_powerup_shooting : (isPlayerBig ? player_golden_shooting : player_shooting));
        else Entity::setTexture(isPowerup ? player_powerup : (isPlayerBig ? player_golden : player_normal));
    }

    laserPlaceholder_X = entity_X - 20;
    laserPlaceholderReverse_X = entity_X + Entity::getWidth() / 1.5;
    laserPlaceholder_Y = entity_Y + Entity::getHeight() / 1.65;

    if (isKey_Enter_pressed && !isPlayerShooting && !isPowerUp) {
        isPlayerBig ? laserShootBig.play() : laserShoot.play();
        isPlayerShooting = true;
        isShotInstant = true;
    }

    if (isPowerUp) {
        if (isPlayerShooting) Entity::grow();
        else isPowerUp = false;
    }

    window.draw(player);
}

void Entity::resetGame () {
    backgroundSprite.setTexture(background);
    backgroundSprite.setPosition(0, 0);

    Entity::incrementLives(playerLives);
    Entity::setScale(playerInitialScale, playerInitialScale);
    Entity::setPosition(playerInitial_X, playerInitial_Y);
    isPlayerBig = false;

    for (Enemy& enemy : enemies) {
        enemy.setPosition(enemyInitialPosition);
    }

    livesText.setString(to_string(playerLives));
    playerScore = 0;
    scoreText.setString("SCORE " + to_string(playerScore));

    soundtrack.play();

    isGameOver = false;
}