#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "../include/Entity.h"

int main() {
    float window_X = 1600;
    float window_Y = 900;
    float windowRatio = window_X / window_Y;
    sf::RenderWindow window(sf::VideoMode((int) window_X, (int) window_Y), "Simple Game");

    // Paths
    std::string iconPath = "../assets/icon/";
    std::string soundPath = "../assets/sound/";
    std::string fontPath = "../assets/font/";

    // Textures
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(iconPath + "background.jpg")) return 1;
    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile(iconPath + "heart.png")) return 1;
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile(iconPath + "player.png")) return 1;
    sf::Texture playerReverseTexture;
    if (!playerReverseTexture.loadFromFile(iconPath + "player_reverse.png")) return 1;
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile(iconPath + "enemy.png")) return 1;
    sf::Texture enemyShadowTexture;
    if (!enemyShadowTexture.loadFromFile(iconPath + "enemy_shadow.png")) return 1;
    sf::Texture enemyShadowReverseTexture;
    if (!enemyShadowReverseTexture.loadFromFile(iconPath + "enemy_shadow_reverse.png")) return 1;
    sf::Texture enemyReverseTexture;
    if (!enemyReverseTexture.loadFromFile(iconPath + "enemy_reverse.png")) return 1;
    sf::Texture laserTexture;
    if (!laserTexture.loadFromFile(iconPath + "laser.png")) return 1;
    sf::Texture laserReverseTexture;
    if (!laserReverseTexture.loadFromFile(iconPath + "laser_reverse.png")) return 1;

    // Sound Buffers
    sf::SoundBuffer pop_buffer;
    if (!pop_buffer.loadFromFile(soundPath + "hurt.ogg")) return 1;
    sf::SoundBuffer shrink_ray_buffer;
    if (!shrink_ray_buffer.loadFromFile(soundPath + "shrink_ray.ogg")) return 1;
    sf::SoundBuffer laser_shoot_buffer;
    if (!laser_shoot_buffer.loadFromFile(soundPath + "laserShoot.ogg")) return 1;
    sf::SoundBuffer explosion_buffer;
    if (!explosion_buffer.loadFromFile(soundPath + "explosion.ogg")) return 1;
    sf::SoundBuffer gameover_buffer;
    if (!gameover_buffer.loadFromFile(soundPath + "gameover.ogg")) return 1;
    sf::SoundBuffer jumpBuffer;
    if (!jumpBuffer.loadFromFile(soundPath + "jump.ogg")) return 1;

    // Sounds
    sf::Sound pop(pop_buffer);
    sf::Sound shrinkRay(shrink_ray_buffer);
    sf::Sound laserShoot(laser_shoot_buffer);
    sf::Sound explosion(explosion_buffer);
    sf::Sound gameoverSound(gameover_buffer);
    sf::Sound jumpSound(jumpBuffer);

    sf::Music soundtrack;
    if (!soundtrack.openFromFile(soundPath + "soundtrack.ogg")) return 1;

    soundtrack.setVolume(30);
    soundtrack.play();
    soundtrack.setLoop(true);

    sf::RectangleShape backgroundSolid(sf::Vector2f(window_X, window_Y));
    backgroundSolid.setFillColor(sf::Color(40, 40, 40));

    sf::Sprite background(backgroundTexture);

    sf::Sprite heart(heartTexture);
    heart.setScale(windowRatio / 6, windowRatio / 6);
    heart.setPosition((window_X / 3), windowRatio * 8);

    Entity player(playerTexture, (windowRatio / 5), 0, 0, 5, (windowRatio / 6), 0.0005);
    player.setInitialPosition(0, window_Y - player.getHeight());
    player.setPosition(0, window_Y - player.getHeight());

    Entity enemy(enemyTexture, (windowRatio / 5), 0, 0, 0, 0, 0.001);
    enemy.setInitialPosition(window_X - enemy.getWidth(), window_Y - enemy.getHeight());
    enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
    sf::Sprite enemyShadow(enemyShadowTexture);
    enemyShadow.setScale(enemy.getScale());

    Entity laser(laserTexture, (windowRatio / 20), -window_X, 0, 0, 1, 0);
    
    std::uniform_real_distribution<float> enemySpeedRange(-0.5, 0.5);

    sf::Font hackNerdFont;
    if (!hackNerdFont.loadFromFile(fontPath + "HackNerdFont-Regular.ttf")) return 1;

    sf::Text scoreText("SCORE", hackNerdFont, 30);
    scoreText.setFillColor(sf::Color::White);
    float score_X = window_X / 1.8;
    float score_Y = windowRatio * 8;
    scoreText.setPosition(score_X, score_Y);

    int points = 0;
    std::string pointsToString = std::to_string(points);
    sf::Text pointsText(pointsToString, hackNerdFont, 30);
    float points_X = scoreText.getPosition().x + scoreText.getLocalBounds().width + 40;
    float points_Y = scoreText.getPosition().y;
    pointsText.setPosition(points_X, points_Y);
    
    std::string livesToString = std::to_string(player.getLives());
    sf::Text lives(livesToString, hackNerdFont, 30);
    lives.setFillColor(sf::Color::White);
    float lives_X = heart.getPosition().x + heart.getGlobalBounds().width + 40;
    float lives_Y = heart.getPosition().y;
    lives.setPosition(lives_X, lives_Y);

    sf::Text gameover("GAME OVER", hackNerdFont, 55);
    gameover.setFillColor(sf::Color::White);
    sf::FloatRect gameoverBounds = gameover.getLocalBounds();
    float gameover_X = (window_X - gameoverBounds.width) / 2;
    float gameover_Y = (window_Y - gameoverBounds.height) / 2;
    gameover.setPosition(gameover_X, gameover_Y);

    // Random Number Generator
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    sf::Clock clock;
    std::uniform_real_distribution<float> timeIntervalRange(0.5, 1.5);
    float generationInterval = timeIntervalRange(gen);
    float elapsedTime;

    bool isKey_M_released = true;
    bool isKey_SPACE_released = true;
    bool isLaserShot = false;
    bool isPlayerReverse = false;
    bool isLaserReverse = false;
    bool isPlayerJumping = false;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            if (isKey_M_released) {
                if (soundtrack.getVolume() == 30) {
                    soundtrack.setVolume(0);
                } else {
                    soundtrack.setVolume(30);
                }
                isKey_M_released = false;
            }
        } else {
            isKey_M_released = true;
        }

        elapsedTime += clock.restart().asSeconds();
        float random_X_speed;
        float random_Y_speed;
        if (elapsedTime >= generationInterval) {
            random_X_speed = enemySpeedRange(gen);
            random_Y_speed = enemySpeedRange(gen);
            elapsedTime = 0;
        }

        // Handle keyboard input
        if (player.isAlive()) {
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.setTexture(playerReverseTexture);
                isPlayerReverse = true;
                player.move(-player.getSpeed(), 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.setTexture(playerTexture);
                isPlayerReverse = false;
                player.move(player.getSpeed(), 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (isKey_SPACE_released) {
                    isPlayerJumping = true;
                    if (jumpSound.getStatus() != sf::Sound::Playing) {
                        jumpSound.play();
                    }
                    isKey_SPACE_released = false;                    
                }
            } else {
                isKey_SPACE_released = true;
            }
            
            if (isPlayerJumping) {
                if (player.getSpeed() > 0) {
                    player.accelerate(0, -1, -1);
                } else {
                    isPlayerJumping = false;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.move(0, player.getSpeed());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isLaserShot) {
                if (isPlayerReverse) {
                    laser.setTexture(laserReverseTexture);
                    laser.setPosition(player.getPosition().x - player.getWidth() / 3, player.getPosition().y + player.getHeight() / 1.7);
                    isLaserReverse = true;
                } else {
                    laser.setTexture(laserTexture);
                    laser.setPosition(player.getPosition().x + player.getWidth() / 1.5, player.getPosition().y + player.getHeight() / 1.7);
                    isLaserReverse = false;
                }

                if (laserShoot.getStatus() != sf::Sound::Playing) {
                    laserShoot.play();
                }
                isLaserShot = true;
            }

            if (isLaserShot && laser.getGlobalBounds().intersects(backgroundSolid.getGlobalBounds()) && isLaserReverse) {
                if (laser.getPosition().x > -laser.getWidth()) {
                    laser.move(-windowRatio / 2, 0);
                }
            } else if (isLaserShot && laser.getGlobalBounds().intersects(backgroundSolid.getGlobalBounds()) && !isLaserReverse) {
                if (laser.getPosition().x > -laser.getWidth()) {
                    laser.move(windowRatio / 2, 0);
                }
            }

            if (random_X_speed < 0) {
                enemy.setTexture(enemyTexture);
                enemyShadow.setTexture(enemyShadowTexture);
            } else {
                enemy.setTexture(enemyReverseTexture);
                enemyShadow.setTexture(enemyShadowReverseTexture);
            }
            // enemy.move(random_X_speed, random_Y_speed);
        }

        // Player border limits
        float playerMax_X = window_X - player.getWidth();
        float playerMax_Y = window_Y - player.getHeight();

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

        // Enemy border limits
        float enemyMax_X = window_X - enemy.getWidth();
        float enemyMax_Y = window_Y - enemy.getHeight();

        if (enemy.getPosition().x > enemyMax_X) {
            enemy.setPosition(enemyMax_X, enemy.getPosition().y);
        }
        if (enemy.getPosition().x < 0) {
            enemy.setPosition(0, enemy.getPosition().y);
        }
        if (enemy.getPosition().y < 0) {
            enemy.setPosition(enemy.getPosition().x, 0);
        }
        if (enemy.getPosition().y > enemyMax_Y) {
            enemy.setPosition(enemy.getPosition().x, enemyMax_Y);
        }

        // Laser border limits
        if (!laser.getGlobalBounds().intersects(backgroundSolid.getGlobalBounds())) {
            laser.setPosition(window_X, laser.getPosition().y);
            isLaserShot = false;
        }

        // Entities Bounds
        sf::FloatRect playerGlobalBounds = player.getGlobalBounds();
        sf::FloatRect enemyGlobalBounds = enemy.getGlobalBounds();
        sf::FloatRect laserGlobalBounds = laser.getGlobalBounds();
        
        // Collision player <-> enemy
        if (playerGlobalBounds.intersects(enemyGlobalBounds)) {
            pop.play();
            player.setPosition(player.getInitial_X(), player.getInitial_Y());
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());

            player.setLives(-1);
            lives.setString(std::to_string(player.getLives()));

            if (player.getLives() == 0) {
                gameoverSound.play();
            }
        }

        // Collision laser -> enemy
        if (laserGlobalBounds.intersects(enemyGlobalBounds)) {
            if (explosion.getStatus() != sf::Sound::Playing) {
                explosion.play();
            }
            laser.setPosition(laser.getInitial_X(), laser.getInitial_Y());
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            points++;
            pointsText.setString(std::to_string(points));
        }

        enemyShadow.setPosition(enemy.getPosition().x + 5, enemy.getPosition().y + 5);

        if (!isPlayerJumping && player.getPosition().y != playerMax_Y) {
            player.accelerate(0, 1, 1);
        } else if (!isPlayerJumping && player.getPosition().y == playerMax_Y){
            player.setSpeed(0.4);
        }
        

        window.clear();
        // window.draw(background);
        window.draw(backgroundSolid);
        window.draw(player);        
        window.draw(laser);
        window.draw(enemyShadow);
        window.draw(enemy);
        window.draw(heart);
        window.draw(lives);
        window.draw(scoreText);
        window.draw(pointsText);

        if (!player.isAlive()) {
            window.draw(gameover);
        }

        window.display();
    }

    return 0;
}
