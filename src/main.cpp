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
using namespace Sounds;
using namespace Booleans;
using namespace Clocks;

Font pixelFont;
Text FPS_Text;

void FPS_to_text(float argument) {
    string argumentToString = to_string(argument);
    FPS_Text.setString(argumentToString);
}

int main() {
    float windowInitial_X = 1600;
    float windowInitial_Y = 900;
    RenderWindow window(VideoMode((int) windowInitial_X, (int) windowInitial_Y), "Simple Game");
    window.setFramerateLimit(300);

    loadTextures();
    loadSounds();

    soundtrack.setVolume(100);
    soundtrack.play();
    soundtrack.setLoop(true);

    soundtrackBig.setVolume(100);
    soundtrackBig.setLoop(true);
    
    Sprite background(Textures::background);
    Vector2u backgroundTextureSize = background.getTexture()->getSize();
    RectangleShape windowBox(Vector2f(backgroundTextureSize.x, backgroundTextureSize.y));
    Sprite heart(Textures::heart);
    Sprite explosionSprite;

    float playerScale = 0.25;
    float playerInitialScale = 0.25;
    float playerInitial_X, playerInitial_Y = 0;
    int playerLives = 1;
    float playerSpeed_X = windowInitial_X / 2.1;
    float playerInitialSpeed_Y = windowInitial_Y * 2.2;
    float playerAcceleration = 5000;
    Entity player(Textures::player, playerInitialScale, playerInitial_X, playerInitial_Y, playerLives, playerSpeed_X, playerInitialSpeed_Y, playerAcceleration);
    player.setPosition(0, windowInitial_Y - player.getHeight());
    float playerMax_X;
    float playerMax_Y;

    RectangleShape playerBox;
    playerBox.setOutlineColor(sf::Color::Red);
    playerBox.setOutlineThickness(2.0f);
    playerBox.setFillColor(sf::Color::Transparent);    

    float enemyScale = (windowInitial_X / 3000);
    Entity enemy(Textures::enemy, enemyScale, 0, 0, 1, 1000, playerInitialSpeed_Y, 4000);
    enemy.setInitialPosition(windowInitial_X - enemy.getWidth(), windowInitial_Y - enemy.getHeight());
    enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
    float enemyMax_X = windowInitial_X - enemy.getWidth();
    float enemyMax_Y;

    vector<Entity> enemies;
    enemies.push_back(enemy);
    enemies.push_back(enemy);
    enemies.push_back(enemy);

    float enemiesMax_Y;

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].setPosition(300 * (i + 1), windowInitial_Y - enemies[i].getHeight());
    }

    float laserScale = windowInitial_Y / 6500;
    float laserScaleOriginal = windowInitial_Y / 6500;
    float laserInitialSpeed_X = 3000;
    Entity laser(Textures::laserBlue, laserScale, -windowInitial_X, -windowInitial_Y, 0, laserInitialSpeed_X, 0, 0);

    pixelFont.loadFromFile("../src/assets/font/SpaceMono-Regular.ttf");

    int playerScore = 0;
    string pointsToString = to_string(playerScore);
    Text scoreText("SCORE " + pointsToString, pixelFont, 30);
    float playerScorePosition_X = window.getSize().x / 2.2;
    float playerScorePosition_Y = window.getSize().y / 800;
    scoreText.setFillColor(Color::White);
    scoreText.setOutlineColor(Color::Black);
    scoreText.setOutlineThickness(2.2);
    
    string livesToString = to_string(player.getLives());
    Text livesText(livesToString, pixelFont, (windowInitial_X / 40));
    livesText.setFillColor(Color::White);
    livesText.setOutlineColor(Color::Black);
    livesText.setOutlineThickness(2);

    Sprite gameoverFrame(Textures::frame);
    gameoverFrame.setPosition((windowInitial_X - gameoverFrame.getGlobalBounds().width) / 2, -gameoverFrame.getGlobalBounds().height);

    Text gameoverText("\tGAME OVER\nPress R to restart", pixelFont, 50 * (windowInitial_X / 1920));
    gameoverText.setFillColor(Color::White);
    gameoverText.setOutlineColor(Color::Black);
    gameoverText.setOutlineThickness(2);
    FloatRect gameoverBounds = gameoverText.getLocalBounds();
    float gameover_X = (windowInitial_X - gameoverBounds.width) / 2;
    float gameover_Y = (windowInitial_Y - gameoverBounds.height) / 2;

    FPS_Text.setPosition(windowInitial_X / 1.13, scoreText.getPosition().y);
    FPS_Text.setCharacterSize(25);
    FPS_Text.setFont(pixelFont);
    FPS_Text.setOutlineThickness(2.5);

    Time FPSStart = Time::Zero;
    Time FPSTimeConstraint = seconds(1);
    Time laserCooldown = seconds(0.5);
    Time explosionDuration = seconds(0.6);
    Time elapsedTimeSinceExplosion = Time::Zero;
    Time elapsedTimeSinceEnemyDied = Time::Zero;
    Time elapsedTimeSinceShot = Time::Zero;
    Time enemySpawnWait = seconds(0.3);

    float deltaTime;
    float playerScaleIncreaseFactor = 0.03;
    float enemySpeed_X = -400;
    float currentWindowRatio;
    float FPS_count;
    float laserOrigin_X;
    float laserOrigin_Y;

    int currentFrame;
    
    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        currentWindowRatio = window.getSize().x / windowInitial_X;

        player.setScale(playerScale * currentWindowRatio, playerScale * currentWindowRatio);
        laser.setScale(laserScale * currentWindowRatio, laserScale * currentWindowRatio);
        
        background.setScale(1, (windowInitial_Y / background.getTexture()->getSize().y));
        heart.setScale((window.getSize().x / 2500.0), (window.getSize().x / 2500.0));
        explosionSprite.setScale(1.5, 1.5);
        float livesText_X = heart.getPosition().x + heart.getGlobalBounds().width + 20;
        float livesText_Y = heart.getPosition().y + (heart.getGlobalBounds().height / 6);
        heart.setPosition((windowInitial_X / 4), windowInitial_Y / 800);
        livesText.setPosition(livesText_X, livesText_Y);
        scoreText.setPosition(playerScorePosition_X, playerScorePosition_Y);
        windowBox.setPosition(background.getPosition().x, background.getPosition().y);
        livesText.setCharacterSize(window.getSize().x / 35.0);
        scoreText.setCharacterSize(window.getSize().x / 35.0);
        gameoverFrame.setScale(window.getSize().x / 1500, window.getSize().x / 1500);

        FPSStart = FPSClock.getElapsedTime();
        if (FPSStart < FPSTimeConstraint) {
            FPS_count++;
        } else {
            FPS_count = 0;
            FPSStart = FPSClock.restart();
        }

        if (Keyboard::isKeyPressed(Keyboard::R) && isGameOver) {
            player.setLives(playerLives);
            livesText.setString(to_string(playerLives));
            background.setTexture(Textures::background);
            playerScale = playerInitialScale;
            laserScale = laserScaleOriginal;
            laser.setSpeed_X(laserInitialSpeed_X);
            laserCooldown = seconds(0.5);
            isPlayerBig = false;
            isGameOver = false;
            gameoverFrame.setPosition(gameoverFrame.getPosition().x, -gameoverFrame.getLocalBounds().height);
            soundtrack.play();
        }

        if (Keyboard::isKeyPressed(Keyboard::M)) {
            if (isKey_M_released) {
                if (soundtrack.getVolume() > 0) {
                    soundtrack.setVolume(0);
                } else {
                    soundtrack.setVolume(100);
                }
                isKey_M_released = false;
            }
        } else {
            isKey_M_released = true;
        }

        playerMax_X = windowInitial_X - player.getWidth();
        playerMax_Y = windowInitial_Y - player.getHeight();
        enemyMax_Y = windowInitial_Y - enemy.getHeight();

        if (player.getPosition().y == playerMax_Y) {
            player.setSpeed_Y(playerInitialSpeed_Y);
        }
        
        float playerEnemyDistance = abs(player.getPosition().x - enemy.getPosition().x);
        float jumpVolume = 100 * exp(-0.0002 * playerEnemyDistance);
        jump.setVolume(jumpVolume);
        
        if (enemy.getPosition().y > enemyMax_Y) {
            enemy.setSpeed_Y(playerInitialSpeed_Y);
            jump.play();
        }

        playerBox.setPosition(player.getPosition());
        playerBox.setSize(sf::Vector2f(player.getWidth(), player.getHeight()));

        deltaTime = deltaClock.restart().asSeconds();

        if (!isGameOver) {
            if (isPowerUp) {
                laserScale += (playerScaleIncreaseFactor * currentWindowRatio * deltaTime) * 1.6;
                playerScale += playerScaleIncreaseFactor * currentWindowRatio * deltaTime;
            }

            // Player textures
            elapsedTimeSinceShot = laserClock.getElapsedTime();
            Time laserCooldownHalf = seconds(laserCooldown.asSeconds() / 2);
            if (isPlayerReverse) {
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


            // Enemy textures
            isEnemyReverse = player.getPosition().x < enemy.getPosition().x;
            enemy.setTexture(isEnemyReverse ? Textures::enemy : Textures::enemy_reverse);

            // Laser textures
            if (isPlayerBig) {
                laser.setTexture(isLaserReverse ? Textures::laserRed_reverse : Textures::laserRed);
            } else {
                laser.setTexture(isLaserReverse ? Textures::laserBlue_reverse : Textures::laserBlue);
            }

            // Gravity Player
            if (!isPlayerJumping && player.getPosition().y < playerMax_Y) {
                player.accelerate(0, 1, 1, deltaTime);
            }

            // Gravity Enemy
            if (!isEnemyJumping && enemy.getPosition().y < enemyMax_Y) {
                enemy.accelerate(0, 1, 1, deltaTime);
            } else {
                isEnemyJumping = enemy.jump(deltaTime);
            }

            // Gravity Enemies
            for (int i = 0; i < enemies.size(); i++) {
                if (!areJumping && enemies[i].getPosition().y < enemyMax_Y) {
                    enemies[i].accelerate(0, 1, 1, deltaTime);
                } else {
                    areJumping = enemies[i].jump(deltaTime);
                    if (enemies[i].getPosition().y > enemyMax_Y) {
                        enemies[i].setSpeed_Y(playerInitialSpeed_Y);
                    }
                }
            }
     
            // Move Left
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                isPlayerReverse = true;
                player.move(-player.getSpeed_X() * deltaTime, 0);
            }
            // Move Right
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                isPlayerReverse = false;
                player.move(player.getSpeed_X() * deltaTime, 0);
            }
            // Jump
            if (Keyboard::isKeyPressed(Keyboard::Space) && player.getPosition().y == playerMax_Y) {
                jump.play();
                isPlayerJumping = true;
            }
            // Jumping
            if (isPlayerJumping) {
                isPlayerJumping = player.jump(deltaTime);
            }

            // Shoot Laser
            if (Keyboard::isKeyPressed(Keyboard::Enter) && !isShooting && !isPowerUp) {
                elapsedTimeSinceShot = Time::Zero;
                laserOrigin_X = isPlayerReverse ? player.getPosition().x - player.getWidth() / 4 : player.getPosition().x + player.getWidth() / 1.5;
                laserOrigin_Y = player.getPosition().y + player.getHeight() / 1.65;
                isLaserReverse = isPlayerReverse;
                laser.setPosition(Vector2f(laserOrigin_X, laserOrigin_Y));
                isPlayerBig ? laserShootBig.play() : laserShoot.play();
                isShooting = true;
                laserClock.restart();
            }

            if (isShooting) {
                elapsedTimeSinceShot = laserClock.getElapsedTime();
                isLaserReverse ? laser.move(-(laser.getSpeed_X() * deltaTime), 0) : laser.move(laser.getSpeed_X() * deltaTime, 0);
                if (elapsedTimeSinceShot > laserCooldown) {
                    isShooting = false;
                    elapsedTimeSinceShot = laserCooldown;
                    laser.setPosition(-windowInitial_X, laser.getInitial_Y());
                }
            }
        }

        window.clear();
        window.draw(background);

        if (!isGameOver) {
            window.draw(player);
            if (enemy.isAlive()) {
                window.draw(enemy);
                for (Entity en : enemies) {
                    window.draw(en);
                }
                if (player.getPosition().x < enemy.getPosition().x) {
                    enemy.move(enemySpeed_X * deltaTime, 0);
                } else {
                    enemy.move(-enemySpeed_X * deltaTime, 0);
                }   
            } else {
                enemy.setPosition(0, -enemy.getHeight());
                elapsedTimeSinceEnemyDied = enemySpawnClock.getElapsedTime();
                if (elapsedTimeSinceEnemyDied > enemySpawnWait) {
                    enemy.setLives(1);
                    elapsedTimeSinceEnemyDied = enemySpawnWait;
                    enemy.setPosition(windowInitial_X - enemy.getWidth(), windowInitial_Y - enemy.getHeight());
                }
            }
            window.draw(heart);
            window.draw(livesText);
            window.draw(scoreText);
            window.draw(FPS_Text);
            window.draw(laser);
            // window.draw(playerBox);          
        } else {
            if (gameoverFrame.getPosition().y < (window.getSize().y - gameoverFrame.getGlobalBounds().height) / 3) {
                gameoverFrame.move(0, 3);
                FloatRect frameRect = gameoverFrame.getGlobalBounds();
                gameoverText.setPosition(gameoverFrame.getPosition().x + 200 * currentWindowRatio, gameoverFrame.getPosition().y + 270 * currentWindowRatio);
            }
            window.draw(gameoverFrame);
            window.draw(gameoverText);
        }

        // Player border limits
        if (player.getPosition().x > playerMax_X) {
            player.setPosition(playerMax_X, player.getPosition().y);
        }
        if (player.getPosition().x < 0) {
            player.setPosition(0, player.getPosition().y);
        }
        if (player.getPosition().y > playerMax_Y) {
            player.setPosition(player.getPosition().x, playerMax_Y);
        }
        if (player.getPosition().y < 0) {
            player.setPosition(player.getPosition().x, 0);
        }
        
        // Player <-> Enemy collision
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            if (hurt.getStatus() != Sound::Playing) {
                hurt.play();
            }
            player.setPosition(player.getInitial_X(), player.getInitial_Y());
            player.setLives(-1);
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            livesText.setString(to_string(player.getLives()));
            background.setPosition(0, 0);

            if (player.getLives() == 0) {
                soundtrack.stop();
                soundtrackBig.stop();
                gameover.play();
                isGameOver = true;
            }
        }

        // Laser -> Enemy Collision 
        if (laser.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            elapsedTimeSinceExplosion = Time::Zero;
            if (explosion.getStatus() == Sound::Playing) {
                explosion.stop();
            }
            explosion.play();
            explosionSprite.setPosition(enemy.getPosition().x, enemy.getPosition().y - explosionSprite.getScale().y * 55);

            laser.setPosition(laser.getInitial_X(), laser.getInitial_Y());
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            enemy.setLives(-1);
            elapsedTimeSinceEnemyDied = Time::Zero;

            playerScore++;
            enemySpeed_X -= 100;

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
                if (soundtrack.getStatus() == Sound::Playing) {
                    soundtrack.stop();
                }
                if (soundtrackBig.getStatus() != Sound::Playing) {
                    soundtrackBig.play();
                }
            }
            scoreText.setString("SCORE " + to_string(playerScore));
            isExplosion = true;
            explosionClock.restart();
            enemySpawnClock.restart();
        }

        // Background movement
        if (player.isAlive()) {
            if (player.getPosition().x > playerMax_X - 1 && Keyboard::isKeyPressed(Keyboard::D) && 
                background.getPosition().x + background.getGlobalBounds().width > windowInitial_X) {
                background.move(-200 * deltaTime, 0);
                player.move(-(player.getSpeed_X() * 0.8) * deltaTime, 0);
                enemy.move(-200 * deltaTime, 0);
            } else if (player.getPosition().x == 0 && Keyboard::isKeyPressed(Keyboard::A) && background.getPosition().x < 0) {
                background.move(200 * deltaTime, 0);
                enemy.move(200 * deltaTime, 0);
            }
        }

        if (isExplosion) {
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
            elapsedTimeSinceExplosion = explosionClock.getElapsedTime();
        }
        window.display();
    }

    return 0;
}
