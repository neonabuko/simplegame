#include <random>
#include "../src/include/GameAssets.h"
#include "../src/include/PlayerAssets.h"
#include "../src/include/LaserAssets.h"
#include "../src/include/CollisionDetection.h"
#include "../src/include/EnemyAssets.h"

using namespace std;
using namespace sf;

using namespace GameAssets;
using namespace GameTextures;
using namespace GameSounds;
using namespace GameClocks;
using namespace GameVariables;
using namespace GameTime;
using namespace GameSprites;

using namespace EnemyAssets;
using namespace EnemyVariables;

using namespace PlayerAssets;
using namespace PlayerVariables;
using namespace PlayerSounds;

using namespace LaserAssets;
using namespace LaserVariables;

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

        float currentWindow_X = (float) window.getSize().x;
        float currentWindow_Y = (float) window.getSize().y;

        currentWindowRatio = currentWindow_X / window_X;

        setSprites();

        updateKeyboard();

        if (isKey_Escape_pressed) window.close();

        if (isKey_M_pressed) {
            if (isKey_M_released) {
                soundtrack.getVolume() > 0 ? soundtrack.setVolume(0) : soundtrack.setVolume(100);
                soundtrack.getVolume() > 0 ? soundSprite.setTexture(sound_on) : soundSprite.setTexture(sound_off);
                isKey_M_released = false;
            }
        } else {
            isKey_M_released = true;
        }

        playerMax_X = currentWindow_X - player.getWidth();
        playerMax_Y = currentWindow_Y - player.getHeight();

        deltaTime = deltaClock.restart().asSeconds();

        window.clear();
        window.draw(backgroundSprite);

        if (!isGameOver) {
            player.update();
            laser.update();

            if (isExplosion) onExplosion();

            for (Enemy& enemy : enemies) {
                enemy.update();

                if (getCollision(player, enemy)) {
                    onCollision_PlayerEnemy(player, enemy);
                }

                if (getCollision(laser, enemy)) {
                    onCollision_LaserEnemy(laser, enemy);
                }

                float playerEnemyDistance = abs(player.getPosition().x - enemy.getPosition().x);
                float jumpVolume = 108 * exp(-0.0004 * playerEnemyDistance);
                float stompLightVolume = jumpVolume;
                jump.setVolume(jumpVolume);
                stompLight.setVolume(stompLightVolume);

                window.draw(enemy);
            }

            window.draw(player);
            window.draw(laser);
            window.draw(soundSprite);
            window.draw(heartSprite);
            window.draw(livesText);
            window.draw(scoreText);
            window.draw(debugText);

            displayDebugText(player.getSpeed_Y());
        } else {
            window.draw(gameoverText);
            if (isKey_Enter_pressed) player.resetGame();
        }

        window.display();
    }

    return 0;
}
