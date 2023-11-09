#include "../include/Enemy.h"
#include "../include/GameAssets.h"
#include "../include/PlayerAssets.h"

using namespace GameAssets;
using namespace GameTime;
using namespace GameClocks;
using namespace EnemyVariables;
using namespace PlayerAssets::PlayerVariables;

void Enemy::update() {
    enemyMax_Y = window_Y - Enemy::getHeight();
    enemySpeed_X = 200 * deltaTime;
    enemySpeed_Y = -1800 * deltaTime;
    enemyInitial_X = backgroundSprite.getGlobalBounds().width - backgroundSprite.getPosition().x - Enemy::getWidth();
    enemyInitial_Y = 0;
    enemyInitialPosition = Vector2f(enemyInitial_X, enemyInitial_Y);

    if (Enemy::getIsAlive()) {
        Enemy::setTexture(playerCurrent_X < Enemy::getPosition().x ? enemy_normal : enemy_reverse);

        playerCurrent_X < Enemy::getPosition().x ? Enemy::move(-enemySpeed_X, 0) : Enemy::move(enemySpeed_X, 0);

        if (Enemy::getPosition().y >= enemyMax_Y) {
            // if (stompLight.getStatus() != Sound::Playing) stompLight.play();
            Enemy::setSpeed_Y(enemySpeed_Y);
        } else Enemy::accelerate();
    } else {
        elapsedTimeSinceEnemyDied = enemySpawnClock.getElapsedTime();
        if (elapsedTimeSinceEnemyDied > enemySpawnWait) {
            elapsedTimeSinceEnemyDied = enemySpawnWait;
            Enemy::setLivesUp((int)(playerScore / 5) + 1);
        }
    }
}