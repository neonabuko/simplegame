#include "../include/CollisionDetection.h"
#include "../include/Entity.h"
#include "../include/PlayerAssets.h"
#include "../include/GameAssets.h"
#include "../include/Laser.h"
#include "../include/EnemyAssets.h"

using namespace PlayerAssets;
using namespace PlayerVariables;
using namespace GameAssets;
using namespace EnemyAssets::EnemyVariables;
using namespace GameTime;
using namespace GameClocks;

bool getCollision(Entity& entity_A, Entity& entity_B) {
    return entity_A.getGlobalBounds().intersects(entity_B.getGlobalBounds());
}

void onCollision_PlayerEnemy(Entity& player, Entity& enemy) {
    if (hurt.getStatus() != Sound::Playing) hurt.play();

    player.setPosition(player.getPosition().x - 400, player.getPosition().y);
    player.incrementLives(-1);

    livesText.setString(to_string(player.getLives()));

    if (player.getLives() == 0) {
        soundtrack.stop();
        soundtrackBig.stop();
        gameover.play();
        isGameOver = true;
    }
}

void onCollision_LaserEnemy(Laser& laser, Entity& enemy) {
    playerScore++;

    if (playerScore > 0 && playerScore % 5 == 0) isPowerUp = true;
    scoreText.setString("SCORE " + to_string(playerScore));

    elapsedTimeSinceExplosion = Time::Zero;
    elapsedTimeSinceEnemyDied = Time::Zero;

    if (explosion.getStatus() != Sound::Playing) explosion.play();
    explosionSprite.setPosition(enemy.getPosition().x, enemy.getPosition().y - explosionSprite.getScale().y * 55);

    laser.setPosition(-laser.getWidth(), -laser.getHeight());

    enemy.incrementLives(-1);

    if (!enemy.getIsAlive()) {
        float enemyRestart_X = (backgroundSprite.getLocalBounds().width + backgroundSprite.getPosition().x);
        enemy.setScale(enemy.getScale().x * 1.03, enemy.getScale().y * 1.03);
        enemyInitialPosition = Vector2f(enemyRestart_X, 0);
        enemy.setPosition(enemyInitialPosition);
    }

    isExplosion = true;
    explosionClock.restart();
    enemySpawnClock.restart();
}

void onExplosion() {
    elapsedTimeSinceExplosion = explosionClock.getElapsedTime();
    if (elapsedTimeSinceExplosion < explosionDuration) {
        currentFrame = static_cast<int>(elapsedTimeSinceExplosion.asSeconds() * explosionTextures.size() / explosionDuration.asSeconds());
        currentFrame = min(currentFrame, static_cast<int>(explosionTextures.size() - 1));
        explosionSprite.setTexture(explosionTextures[currentFrame]);
        window.draw(explosionSprite);
    } else {
        isExplosion = false;
        elapsedTimeSinceExplosion = explosionDuration;
    }
}