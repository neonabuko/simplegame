#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "../src/include/Entity.h"
#include "../src/include/Assets.h"
#include "../src/include/Booleans.h"

using namespace std;
using namespace sf;
using namespace Assets;
using namespace Textures;
using namespace Sounds;
using namespace Booleans;
using namespace Clocks;
using namespace Player;
using namespace Enemy;
using namespace TimeDef;
using namespace GameSprites;

void FPS_to_text(float argument) {
    string argumentToString = to_string(argument);
    FPS_Text.setString(argumentToString);
}

int main() {
    RenderWindow window(VideoMode((int) window_X, (int) window_Y), "Simple Game");
    window.setFramerateLimit(300);

    loadTextures();
    loadSounds();
    loadTexts(window_X, window_Y);
    loadSprites();

    float playerInitial_Y = (float)window.getSize().y;
    Entity player(Textures::player, playerInitial_X, playerInitial_Y, playerLives, playerInitialSpeed_X, playerInitialSpeed_Y, playerAcceleration);
    player.setPosition(0, (float)window.getSize().y - player.getHeight());

    Entity enemy(Textures::enemy, backgroundSprite.getGlobalBounds().width, 0, 1, 1000, playerInitialSpeed_Y, 20);

    vector<Entity> enemies;
    enemies.push_back(enemy);
    enemies.push_back(enemy);

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].setInitialPosition(backgroundSprite.getGlobalBounds().width - backgroundSprite.getPosition().x - enemies[i].getWidth(), (float)window.getSize().y - enemies[i].getHeight());
        enemies[i].setPosition(enemy.getInitial_X() - (i * enemies[i].getWidth() / 2), (float)window.getSize().y - enemies[i].getHeight());
        enemies[i].setScale((float)window.getSize().x / 3300, (float)window.getSize().x / 3300);
    }

    float laserScale = (float)window.getSize().y / 6500;
    float laserScaleOriginal = (float)window.getSize().y / 6500;
    Entity laser(Textures::laserBlue, -(float)window.getSize().x, -(float)window.getSize().y, 0, laserInitialSpeed_X, 0, 0);
    
    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        currentWindowRatio = (float)window.getSize().x / (float)window.getSize().x;

        enemyMax_X = (float)window.getSize().x - enemy.getWidth();
        
        float livesText_X = heartSprite.getPosition().x + heartSprite.getGlobalBounds().width + 20;
        float livesText_Y = heartSprite.getPosition().y + (heartSprite.getGlobalBounds().height / 6);

        heartSprite.setPosition(((float)window.getSize().x / 4), (float)window.getSize().y / 800);
        livesText.setPosition(livesText_X, livesText_Y);
        scoreText.setPosition(playerScorePosition_X, playerScorePosition_Y);
        windowBox.setPosition(backgroundSprite.getPosition().x, backgroundSprite.getPosition().y);
        FPS_Text.setPosition((float)window.getSize().x / 1.55, 10);

        livesText.setCharacterSize((float)window.getSize().x / 35.0);
        scoreText.setCharacterSize((float)window.getSize().x / 30.0);
        FPS_Text.setCharacterSize((float)window.getSize().x / 37.0);

        gameoverFrame.setScale(window.getSize().x / 1500, (float)window.getSize().x / 1500);
        backgroundSprite.setScale(1, (window_Y / backgroundSprite.getTexture()->getSize().y));
        heartSprite.setScale(((float)window.getSize().x / 2800.0), ((float)window.getSize().x / 2800.0));
        explosionSprite.setScale(1.5, 1.5);
        player.setScale(playerInitialScale * currentWindowRatio, playerInitialScale * currentWindowRatio);
        laser.setScale(laserScale * currentWindowRatio, laserScale * currentWindowRatio);

        FPSStart = FPSClock.getElapsedTime();
        if (FPSStart < FPSTimeConstraint) {
            FPS_count++;
        } else {
            FPS_count = 0;
            FPSStart = FPSClock.restart();
        }

        if (Keyboard::isKeyPressed(Keyboard::R) && isGameOver) {
            isGameOver = false;

            backgroundSprite.setTexture(Textures::background);
            backgroundSprite.setPosition(0, 0);            

            player.setLives(playerLives);
            player.setScale(playerInitialScale, playerInitialScale);
            player.setPosition(playerInitial_X, playerInitial_Y);
            isPlayerBig = false;

            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            }

            livesText.setString(to_string(playerLives));

            laserScale = laserScaleOriginal;
            laser.setSpeed_X(laserInitialSpeed_X);
            laserCooldown = seconds(0.5);

            gameoverFrame.setPosition(gameoverFrame.getPosition().x, -gameoverFrame.getLocalBounds().height);

            soundtrack.play();
        }

        if (Keyboard::isKeyPressed(Keyboard::M) && isKey_M_released) {
            soundtrack.getVolume() > 0 ? soundtrack.setVolume(0) : soundtrack.setVolume(100);
            isKey_M_released = false;
        } else {
            isKey_M_released = true;
        }

        playerMax_X = (float)window.getSize().x - player.getWidth();
        playerMax_Y = (float)window.getSize().y - player.getHeight();

        deltaTime = deltaClock.restart().asSeconds();

        window.clear();
        window.draw(backgroundSprite);

        if (!isGameOver) {
            if (isPowerUp) {
                laserScale += (playerScaleIncreaseFactor * currentWindowRatio * deltaTime) * 1.6;
                playerInitialScale += playerScaleIncreaseFactor * currentWindowRatio * deltaTime;
            }

            // Player textures
            elapsedTimeSinceShot = laserClock.getElapsedTime();
            Time laserCooldownHalf = seconds(laserCooldown.asSeconds() / 2);
            if (player.getIsReverse()) {
                if (isShooting && elapsedTimeSinceShot < laserCooldownHalf) {
                    player.setTexture(isPowerUp ? Textures::player_shooting_reverse_powerup : 
                    (isPlayerBig ? Textures::player_golden_shooting_reverse : Textures::player_shooting_reverse));
                } else {
                    player.setTexture(isPowerUp ? Textures::player_reverse_powerup : 
                    (isPlayerBig ? Textures::player_golden_reverse : Textures::player_reverse));
                }
            } else {
                if (isShooting && elapsedTimeSinceShot < laserCooldownHalf) {
                    player.setTexture(isPowerUp ? Textures::player_shooting_powerup : 
                    (isPlayerBig ? Textures::player_golden_shooting : Textures::player_shooting));
                } else {
                    player.setTexture(isPowerUp ? Textures::player_powerup : 
                    (isPlayerBig ? Textures::player_golden : Textures::player));
                }
            }

            // Laser textures
            isPlayerBig ? laser.setTexture(isLaserReverse ? Textures::laserRed_reverse : Textures::laserRed) : 
                          laser.setTexture(isLaserReverse ? Textures::laserBlue_reverse : Textures::laserBlue);
     
            player.update(deltaTime, (float)window.getSize().x, (float)window.getSize().y);

            // Shoot Laser
            if (Keyboard::isKeyPressed(Keyboard::Enter) && !isShooting && !isPowerUp) {
                laserOrigin_X = player.getIsReverse() ? (player.getPosition().x - player.getWidth() / 4) : 
                                                        (player.getPosition().x + player.getWidth() / 1.5);
                laserOrigin_Y = player.getPosition().y + player.getHeight() / 1.65;
                isLaserReverse = player.getIsReverse();
                laser.setPosition(Vector2f(laserOrigin_X, laserOrigin_Y));
                isPlayerBig ? laserShootBig.play() : laserShoot.play();
                isShooting = true;
                laserClock.restart();
            }

            if (isShooting) {
                elapsedTimeSinceShot = Time::Zero;
                elapsedTimeSinceShot = laserClock.getElapsedTime();
                isLaserReverse ? laser.move(-(laser.getSpeed_X() * deltaTime), 0) : laser.move(laser.getSpeed_X() * deltaTime, 0);
                if (elapsedTimeSinceShot > laserCooldown) {
                    isShooting = false;
                    elapsedTimeSinceShot = laserCooldown;
                    laser.setPosition(-(float)window.getSize().x, laser.getInitial_Y());
                }
            }

            for (int i = 0; i < enemies.size(); i++) {
                // Player -> Enemy Collision
                if (player.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
                    if (hurt.getStatus() != Sound::Playing) hurt.play();

                    player.setPosition(player.getPosition().x - 200, player.getPosition().y);
                    player.setLives(-1);

                    enemies[i].setPosition(enemies[i].getPosition().x + 200, enemies[i].getPosition().y);

                    livesText.setString(to_string(player.getLives()));

                    if (player.getLives() == 0) {
                        soundtrack.stop();
                        soundtrackBig.stop();
                        gameover.play();
                        isGameOver = true;
                    }          
                }

                // Laser -> Enemy Collision 
                if (laser.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
                    elapsedTimeSinceExplosion = Time::Zero;
                    elapsedTimeSinceEnemyDied = Time::Zero;
                    if (explosion.getStatus() == Sound::Playing) explosion.stop();
                    explosion.play();
                    explosionSprite.setPosition(enemies[i].getPosition().x, enemies[i].getPosition().y - explosionSprite.getScale().y * 55);

                    laser.setPosition(laser.getInitial_X(), laser.getInitial_Y());

                    enemies[i].setLives(-1);
                    enemies[i].setInitialPosition(backgroundSprite.getLocalBounds().width + backgroundSprite.getPosition().x - enemy.getWidth(), 
                                            (float)window.getSize().y - enemy.getHeight());
                    enemies[i].setPosition(enemies[i].getInitial_X(), enemies[i].getInitial_Y());

                    playerScore++;
                    scoreText.setString("SCORE " + to_string(playerScore));

                    if (player.getScale().x <= (playerInitialScale * 2) * currentWindowRatio) {
                        if (playerScore % 5 == 0) {
                            isPowerUp = true;
                            powerUp.play();
                        } else {
                            isPowerUp = false;
                        }
                    } else if ((int) player.getScale().x * 10 == (int) playerInitialScale * 20) {
                        laser.setSpeed_X(laserInitialSpeed_X * 2);
                        isPlayerBig = true;
                        laserCooldown = seconds(0.38);
                        if (soundtrack.getStatus() == Sound::Playing) soundtrack.stop();
                        if (soundtrackBig.getStatus() != Sound::Playing) soundtrackBig.play();
                    }                

                    isExplosion = true;
                    explosionClock.restart();
                    enemySpawnClock.restart();
                }                

                // Background Movement
                if (player.getPosition().x > playerMax_X / 2 && Keyboard::isKeyPressed(Keyboard::D) && 
                    backgroundSprite.getPosition().x + backgroundSprite.getGlobalBounds().width > (float)window.getSize().x) {

                    backgroundSprite.move(-200 * deltaTime, 0);
                    player.move(-(player.getSpeed_X() * 0.8) * deltaTime, 0);
                    enemies[i].move(-400 * deltaTime, 0);

                } else if (player.getPosition().x <= 0 && Keyboard::isKeyPressed(Keyboard::A) && backgroundSprite.getPosition().x < 0) {
                    backgroundSprite.move(200 * deltaTime, 0);
                    enemies[i].move(400 * deltaTime, 0);
                }

                // Enemy Rendering
                if (enemies[i].isAlive()) {
                    enemyMax_Y = (float)window.getSize().y - enemies[i].getHeight();
                    float playerEnemyDistance = abs(player.getPosition().x - enemies[i].getPosition().x);
                    float jumpVolume = 108 * exp(-0.0004 * playerEnemyDistance);
                    float stompLightVolume = jumpVolume;
                    jump.setVolume(jumpVolume);
                    stompLight.setVolume(stompLightVolume);

                    enemies[i].setTexture(player.getPosition().x < enemies[i].getPosition().x ? Textures::enemy : Textures::enemy_reverse);
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
            window.draw(heartSprite);
            window.draw(livesText);
            window.draw(scoreText);
            window.draw(FPS_Text);
            window.draw(laser);
            // window.draw(playerBox);
        } else {
            if (gameoverFrame.getPosition().y < ((float)window.getSize().y - gameoverFrame.getGlobalBounds().height) / 3) {
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

        FPS_to_text(playerMax_Y);

        if (isExplosion) {
            elapsedTimeSinceExplosion = explosionClock.getElapsedTime();
            if (elapsedTimeSinceExplosion < explosionDuration) {
                currentFrame = static_cast<int>(elapsedTimeSinceExplosion.asSeconds() * explosionTextures.size() / explosionDuration.asSeconds());
                currentFrame = min(currentFrame, static_cast<int>(explosionTextures.size() - 1));
                explosionSprite.setTexture(explosionTextures[currentFrame]);
                window.draw(explosionSprite);
            } else {
                isExplosion = false;
                isPowerUp = false;
                elapsedTimeSinceExplosion = explosionDuration;
            }
        }
        window.display();
    }

    return 0;
}
