#include <random>
#include "../src/include/GameAssets.h"
#include "../src/include/PlayerAssets.h"
#include "../src/include/LaserAssets.h"
#include "../src/include/CollisionDetection.h"
#include "../src/include/EnemyAssets.h"

using namespace std;
using namespace sf;

using namespace GameAssets;
using namespace GameClocks;

using namespace EnemyAssets;

using namespace PlayerAssets;

using namespace LaserAssets;

int main() {
    loadGameAssets();

    loadPlayerAssets();
    loadLaserAssets();
    loadEnemyAssets();

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        updateSprites();
        updateKeyboard();
        updateGameCommands();

        deltaTime = deltaClock.restart().asSeconds();

        window.clear();
        window.draw(backgroundSprite);

        if (!isGameOver) {
            player.update();
            laser.update();

            if (isExplosion) onExplosion();

            for (Enemy& enemy : enemies) {
                enemy.update();

                if (getCollision(player, enemy)) onCollision_PlayerEnemy(player, enemy);

                if (getCollision(laser, enemy))  onCollision_LaserEnemy(laser, enemy);

                float playerEnemyDistance = abs(player.getPosition().x - enemy.getPosition().x);
                float jumpVolume = 108 * exp(-0.0004 * playerEnemyDistance);
                float stompLightVolume = jumpVolume;
                jump.setVolume(jumpVolume);

                window.draw(enemy);
            }

            window.draw(player);
            window.draw(laser);
            window.draw(soundSprite);
            window.draw(heartSprite);
            window.draw(livesText);
            window.draw(scoreText);
            window.draw(debugText);

            displayDebugText(enemies[0].getPosition().y);
        } else {
            window.draw(gameoverText);
            if (isKey_Enter_pressed) player.resetGame();
        }

        window.display();
    }

    return 0;
}
