#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "../src/include/Entity.h"
#include "../src/include/GameAssets.h"
#include "../src/include/PlayerAssets.h"
#include "../src/include/LaserAssets.h"
#include "../src/include/CollisionDetection.h"

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

void debugDisplay(float argument) {
    string argumentToString = to_string(argument);
    FPS_Text.setString(argumentToString);
}

int main() {
    loadTextures();
    loadSounds();
    loadTexts();
    loadSprites();

    RenderWindow window(VideoMode((int) window_X, (int) window_Y), "Simple Game");
    window.setFramerateLimit(300);

    Entity player(playerInitial_X, playerInitial_Y, playerLives, playerInitialSpeed_X, playerInitialSpeed_Y, playerAcceleration);
    player.loadPlayerAssets();

    Entity enemy(backgroundSprite.getGlobalBounds().width, 0, 1, 1000, playerInitialSpeed_Y, 20);

    Laser laser(laserOriginalSpeed_X, laserAcceleration);
    laser.load();
    laser.setPosition(laserOrigin_X, laserOrigin_Y);

    vector<Entity> enemies;
    enemies.push_back(enemy);
    enemies.push_back(enemy);

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].setInitialPosition(backgroundSprite.getGlobalBounds().width - backgroundSprite.getPosition().x - enemies[i].getWidth(), 
                                      window_Y - enemies[i].getHeight());
        enemies[i].setPosition(enemy.getInitial_X() - (i * enemies[i].getWidth() / 2), window_Y - enemies[i].getHeight());
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

        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        if (Keyboard::isKeyPressed(Keyboard::R) && isGameOver) {
            isGameOver = false;

            backgroundSprite.setTexture(background);
            backgroundSprite.setPosition(0, 0);            

            player.setLives(playerLives);
            player.setScale(playerInitialScale, playerInitialScale);
            player.setPosition(playerInitial_X, playerInitial_Y);
            isPlayerBig = false;

            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            }

            livesText.setString(to_string(playerLives));

            gameoverFrame.setPosition(gameoverFrame.getPosition().x, -gameoverFrame.getLocalBounds().height);

            soundtrack.play();
        }

        if (Keyboard::isKeyPressed(Keyboard::M) && isKey_M_released) {
            soundtrack.getVolume() > 0 ? soundtrack.setVolume(0) : soundtrack.setVolume(100);
            isKey_M_released = false;
        } else {
            isKey_M_released = true;
        }

        playerMax_X = currentWindow_X - player.getWidth();
        playerMax_Y = currentWindow_Y - player.getHeight();

        deltaTime = deltaClock.restart().asSeconds();

        window.clear();
        window.draw(backgroundSprite);

        if (!isGameOver) {
            player.update(deltaTime, currentWindow_X, currentWindow_Y);
            laser.update(deltaTime);

            for (int i = 0; i < enemies.size(); i++) {

                // Player -> Enemy Collision
                if (getCollision(player, enemies[i])) {
                    onPlayerEnemyCollision(player, enemies[i]);
                }

                // Laser -> Enemy Collision 
                if (getCollision(laser, enemies[i])) {
                    onLaserEnemyCollision(laser, enemies[i]);
                    player.grow();
                }

                // Background Movement
                if (player.getPosition().x > playerMax_X / 2 && Keyboard::isKeyPressed(Keyboard::D) && 
                    backgroundSprite.getPosition().x + backgroundSprite.getGlobalBounds().width > currentWindow_X) {

                    backgroundSprite.move(-200 * deltaTime, 0);
                    player.move(-(player.getSpeed_X() * 0.8) * deltaTime, 0);
                    enemies[i].move(-400 * deltaTime, 0);

                } else if (player.getPosition().x <= 0 && Keyboard::isKeyPressed(Keyboard::A) && backgroundSprite.getPosition().x < 0) {
                    backgroundSprite.move(200 * deltaTime, 0);
                    enemies[i].move(400 * deltaTime, 0);
                }

                // Enemy Rendering
                if (enemies[i].getIsAlive()) {
                    enemyMax_Y = currentWindow_Y - enemies[i].getHeight();
                    float playerEnemyDistance = abs(player.getPosition().x - enemies[i].getPosition().x);
                    float jumpVolume = 108 * exp(-0.0004 * playerEnemyDistance);
                    float stompLightVolume = jumpVolume;
                    jump.setVolume(jumpVolume);
                    stompLight.setVolume(stompLightVolume);

                    enemies[i].setTexture(player.getPosition().x < enemies[i].getPosition().x ? enemy_normal : enemy_reverse);
                    enemies[i].accelerate(deltaTime);

                    enemySpeed_X = 200 * deltaTime;
                    enemySpeed_Y = -1800 * deltaTime;
                    player.getPosition().x < enemies[i].getPosition().x ? enemies[i].move(-enemySpeed_X, 0) : enemies[i].move(enemySpeed_X, 0);

                    if (enemies[i].getPosition().y >= enemyMax_Y) {
                        if (jump.getStatus() != Sound::Playing) jump.play();
                        if (stompLight.getStatus() != Sound::Playing) stompLight.play();
                        enemies[i].setSpeed_Y(enemySpeed_Y);
                    }

                    window.draw(enemies[i]);
                } else {
                    elapsedTimeSinceEnemyDied = enemySpawnClock.getElapsedTime();
                    if (elapsedTimeSinceEnemyDied > enemySpawnWait) {
                        elapsedTimeSinceEnemyDied = enemySpawnWait;
                        enemies[i].setLives(1);
                    }
                }
            }
            
            window.draw(player);
            window.draw(laser);
            window.draw(heartSprite);
            window.draw(livesText);
            window.draw(scoreText);
            window.draw(FPS_Text);
        } else {
            if (gameoverFrame.getPosition().y < (currentWindow_Y - gameoverFrame.getGlobalBounds().height) / 3) {
                gameoverFrame.move(0, 3);
                FloatRect frameRect = gameoverFrame.getGlobalBounds();
                gameoverText.setPosition(gameoverFrame.getPosition().x + 200 * currentWindowRatio, gameoverFrame.getPosition().y + 270 * currentWindowRatio);
            }
            window.draw(gameoverFrame);
            window.draw(gameoverText);
        }

        // Player border limits
        if (player.getPosition().x > playerMax_X) player.setPosition(playerMax_X, player.getPosition().y);
        if (player.getPosition().x < 0)           player.setPosition(0, player.getPosition().y);
        if (player.getPosition().y > playerMax_Y) player.setPosition(player.getPosition().x, playerMax_Y);
        if (player.getPosition().y < 0)           player.setPosition(player.getPosition().x, 0);
        
        debugDisplay(player.getLives());

        if (isExplosion) {
            elapsedTimeSinceExplosion = explosionClock.getElapsedTime();
            if (elapsedTimeSinceExplosion < explosionDuration) {
                currentFrame = static_cast<int>(elapsedTimeSinceExplosion.asSeconds() * explosionTextures.size() / explosionDuration.asSeconds());
                currentFrame = min(currentFrame, static_cast<int>(explosionTextures.size() - 1));
                explosionSprite.setTexture(explosionTextures[currentFrame]);
                window.draw(explosionSprite);
            } else {
                isExplosion = false;
                player.setIsPowerup(false);
                elapsedTimeSinceExplosion = explosionDuration;
            }
        }
        window.display();
    }

    return 0;
}
