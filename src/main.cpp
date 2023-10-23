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
    sf::Texture enemyReverseTexture;
    if (!enemyReverseTexture.loadFromFile(iconPath + "enemy_reverse.png")) return 1;
    sf::Texture laserTexture;
    if (!laserTexture.loadFromFile(iconPath + "laser.png")) return 1;
    sf::Texture laserReverseTexture;
    if (!laserReverseTexture.loadFromFile(iconPath + "laser_reverse.png")) return 1;

    // Sound Buffers
    sf::SoundBuffer pop_buffer;
    if (!pop_buffer.loadFromFile(soundPath + "pop.ogg")) return 1;
    sf::SoundBuffer shrink_ray_buffer;
    if (!shrink_ray_buffer.loadFromFile(soundPath + "shrink_ray.ogg")) return 1;
    sf::SoundBuffer laser_shoot_buffer;
    if (!laser_shoot_buffer.loadFromFile(soundPath + "laserShoot.ogg")) return 1;
    sf::SoundBuffer explosion_buffer;
    if (!explosion_buffer.loadFromFile(soundPath + "explosion.ogg")) return 1;

    // Sounds
    sf::Sound pop(pop_buffer);
    sf::Sound shrinkRay(shrink_ray_buffer);
    sf::Sound laserShoot(laser_shoot_buffer);
    sf::Sound explosion(explosion_buffer);

    sf::Music soundtrack;
    if (!soundtrack.openFromFile(soundPath + "soundtrack.ogg")) return 1;

    soundtrack.setVolume(30);
    soundtrack.play();
    soundtrack.setLoop(true);

    sf::RectangleShape backgroundSolid(sf::Vector2f(window_X, window_Y));
    backgroundSolid.setFillColor(sf::Color(40, 40, 40));

    sf::Sprite background(backgroundTexture);

    sf::Sprite heartSprite(heartTexture);
    heartSprite.setScale(sf::Vector2f(0.3, 0.3));
    heartSprite.setPosition((window_X / 2) - 50, 10);

    sf::Font hackNerdFont;
    if (!hackNerdFont.loadFromFile(fontPath + "HackNerdFont-Regular.ttf")) return 1;

    sf::Text gameover("GAME OVER", hackNerdFont, 55);
    gameover.setFillColor(sf::Color::White);
    sf::FloatRect gameoverBounds = gameover.getLocalBounds();
    float gameover_X = (window_X - gameoverBounds.width) / 2;
    float gameover_Y = (window_Y - gameoverBounds.height) / 2;
    gameover.setPosition(gameover_X, gameover_Y);

    Entity player(playerTexture, (windowRatio / 5), 0, window_Y, 5, (windowRatio / 6));

    Entity enemy(enemyTexture, (windowRatio / 5), window_X, window_Y, 0, 0);

    Entity laser(laserTexture, (windowRatio / 20), -window_X, 0, 0, 1);
    
    std::uniform_real_distribution<float> enemySpeedRange(-1, 1);
    
    std::string livesToString = std::to_string(player.getLives());
    sf::Text livesText(livesToString, hackNerdFont, 30);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(heartSprite.getPosition().x + (float) livesText.getCharacterSize() * 2, heartSprite.getPosition().y);

    // Random Number Generator
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    sf::Clock clock;
    std::uniform_real_distribution<float> timeIntervalRange(0.5, 1.5);
    float generationInterval = timeIntervalRange(gen);
    float elapsedTime;

    bool isKey_M_released = true;
    bool isLaserShot = false;
    bool isPlayerReverse = false;
    bool isLaserReverse = false;

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
            random_X_speed = enemySpeedRange(gen) / 3;
            random_Y_speed = enemySpeedRange(gen) / 3;
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.move(0, -player.getSpeed());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.move(0, player.getSpeed());
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isLaserShot) {
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
            } else {
                enemy.setTexture(enemyReverseTexture);
            }
            enemy.move(random_X_speed, random_Y_speed);
        }

        // Entity border limits
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
            livesText.setString(std::to_string(player.getLives()));
        }

        // Collision laser -> enemy
        if (laserGlobalBounds.intersects(enemyGlobalBounds)) {
            if (explosion.getStatus() != sf::Sound::Playing) {
                explosion.play();
            }
            laser.setPosition(laser.getInitial_X(), laser.getInitial_Y());
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
        }

        window.clear();
        // window.draw(background);
        window.draw(backgroundSolid);
        window.draw(player);
        window.draw(laser);
        window.draw(enemy);
        window.draw(livesText);
        window.draw(heartSprite);

        if (!player.isAlive()) {
            window.draw(gameover);
        }

        window.display();
    }

    return 0;
}
