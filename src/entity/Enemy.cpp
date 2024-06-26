#include "../include/Enemy.h"
#include "../include/GameAssets.h"
#include "../include/PlayerAssets.h"
#include "../include/EnemyAssets.h"

using namespace GameAssets;
using namespace GameTime;
using namespace GameClocks;
using namespace EnemyAssets::EnemyVariables;
using namespace PlayerAssets::PlayerVariables;

void Enemy::update() {
    enemyMax_Y = window_Y - Enemy::getHeight();
    enemySpeed_X = 200 * deltaTime;
    enemySpeed_Y = -1800 * deltaTime;
    enemyInitial_X = backgroundSprite.getGlobalBounds().width - backgroundSprite.getPosition().x - Enemy::getWidth();
    enemyInitialPosition = Vector2f(enemyInitial_X, enemyInitial_Y);

    if (Enemy::getIsAlive()) {
        Enemy::setTexture(playerCurrent_X < Enemy::getPosition().x ? enemy_normal : enemy_reverse);

        playerCurrent_X < Enemy::getPosition().x ? Enemy::move(-enemySpeed_X, 0) : Enemy::move(enemySpeed_X, 0);

        if (Enemy::getPosition().y < enemyMax_Y) {
            Enemy::accelerate();
        } else {
            Enemy::setSpeed_Y(enemySpeed_Y);
            Enemy::setPosition(Enemy::getPosition().x, enemyMax_Y);
        }
    } else {
        elapsedTimeSinceEnemyDied = enemySpawnClock.getElapsedTime();
        if (elapsedTimeSinceEnemyDied > enemySpawnWait) {
            elapsedTimeSinceEnemyDied = enemySpawnWait;
            Enemy::incrementLives(1);
        }
    }
}