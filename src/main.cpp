#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "../src/include/Entity.h"
#include "../src/include/GameAssets.h"
#include "../src/include/PlayerAssets.h"
#include "../src/include/LaserAssets.h"
#include "../src/include/CollisionDetection.h"
#include "../src/include/Enemy.h"

using namespace std;
using namespace sf;
using namespace GameAssets;
using namespace Textures;
using namespace GameSounds;
using namespace GameClocks;
using namespace GameVariables;
using namespace EnemyVariables;
using namespace GameTime;
using namespace GameSprites;
using namespace PlayerAssets::PlayerVariables;
using namespace PlayerAssets::PlayerSounds;
using namespace LaserAssets::LaserVariables;

void displayDebugText(float argument) {
    string argumentToString = to_string(argument);
    debugText.setString(argumentToString);
}

int main() {
    loadTextures();
    loadSounds();
    loadTexts();
    loadSprites();

    window.setFramerateLimit(300);

    Entity player(playerLives, playerInitialSpeed_X, playerInitialSpeed_Y, playerAcceleration);
    player.loadPlayerAssets();

    Enemy enemy;
    enemy.setLives(1);
    enemy.setAcceleration(20);

    Laser laser(laserOriginalSpeed_X, laserAcceleration);
    laser.load();
    laser.setPosition(laserOrigin_X, laserOrigin_Y);

    vector<Enemy> enemies;
    enemies.push_back(enemy);
    enemies.push_back(enemy);

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].setPosition(1600 + (i * 100), 0);
        enemies[i].setScale(window_X / 3300, window_X / 3300);
    }    

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

            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].update();

                if (getCollision(player, enemies[i])) {
                    onCollision_PlayerEnemy(player, enemies[i]);
                }

                if (getCollision(laser, enemies[i])) {
                    onCollision_LaserEnemy(laser, enemies[i]);
                }

                // Background Movement
                if (player.getPosition().x > playerMax_X / 1.8 && isKey_D_pressed && 
                    backgroundSprite.getPosition().x + backgroundSprite.getGlobalBounds().width > currentWindow_X) {

                    backgroundSprite.move(-200 * deltaTime, 0);
                    player.setSpeed_X(0);
                    enemies[i].move(-200 * deltaTime, 0);
                } else if (player.getPosition().x <= 0 && isKey_A_pressed && backgroundSprite.getPosition().x < 0) {
                    backgroundSprite.move(200 * deltaTime, 0);
                    enemies[i].move(200 * deltaTime, 0);
                } else {
                    player.setSpeed_X(playerInitialSpeed_X);
                }

                float playerEnemyDistance = abs(player.getPosition().x - enemies[i].getPosition().x);
                float jumpVolume = 108 * exp(-0.0004 * playerEnemyDistance);
                float stompLightVolume = jumpVolume;
                jump.setVolume(jumpVolume);
                stompLight.setVolume(stompLightVolume);

                window.draw(enemies[i]);
            }

            window.draw(player);
            window.draw(laser);
            window.draw(heartSprite);
            window.draw(livesText);
            window.draw(scoreText);
            window.draw(debugText);

            // displayDebugText(enemySpeed_X);
        } else {
            gameoverText.setPosition(gameover_X, gameover_Y);
            window.draw(gameoverText);

            if (isKey_Enter_pressed) {
                backgroundSprite.setTexture(background);
                backgroundSprite.setPosition(0, 0);

                player.setLives(playerLives);
                player.setScale(playerInitialScale, playerInitialScale);
                player.setPosition(playerInitial_X, playerInitial_Y);
                isPlayerBig = false;

                for (int i = 0; i < enemies.size(); i++) {
                    enemies[i].setPosition(enemyInitialPosition);
                }

                livesText.setString(to_string(playerLives));

                soundtrack.play();

                isGameOver = false;
            }
        }

        window.display();
    }

    return 0;
}
