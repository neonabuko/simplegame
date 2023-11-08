#include "../include/CollisionDetection.h"
#include "../include/Entity.h"
#include "../include/PlayerAssets.h"
#include "../include/GameAssets.h"
#include "../include/Laser.h"

using namespace PlayerAssets;
using namespace GameAssets;
using namespace GameTime;
using namespace GameClocks;

bool getCollision(Entity& entity_A, Entity& entity_B) {
    return entity_A.getGlobalBounds().intersects(entity_B.getGlobalBounds());
}

void onPlayerEnemyCollision(Entity& player, Entity& enemy) {
    if (hurt.getStatus() != Sound::Playing) hurt.play();

    player.setPosition(player.getPosition().x - 300, player.getPosition().y);
    player.setLives(-1);

    livesText.setString(to_string(player.getLives()));

    if (player.getLives() == 0) {
        soundtrack.stop();
        soundtrackBig.stop();
        gameover.play();
        isGameOver = true;
    }
}

void onLaserEnemyCollision(Laser& laser, Entity& enemy) {
    elapsedTimeSinceExplosion = Time::Zero;
    elapsedTimeSinceEnemyDied = Time::Zero;
    if (explosion.getStatus() == Sound::Playing) explosion.stop();
    explosion.play();
    explosionSprite.setPosition(enemy.getPosition().x, enemy.getPosition().y - explosionSprite.getScale().y * 55);

    laser.setPosition(-laser.getWidth(), -laser.getHeight());

    enemy.setLives(-1);
    enemy.setInitialPosition(
        backgroundSprite.getLocalBounds().width + backgroundSprite.getPosition().x - enemy.getWidth(), window_Y - enemy.getHeight()
        );
    enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());

    playerScore++;
    scoreText.setString("SCORE " + to_string(playerScore));

    isExplosion = true;
    explosionClock.restart();
    enemySpawnClock.restart();
}