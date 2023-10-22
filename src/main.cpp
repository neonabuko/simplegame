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
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile(iconPath + "enemy.png")) return 1;
    sf::Texture laserTexture;
    if (!laserTexture.loadFromFile(iconPath + "laser.png")) return 1;

    sf::Sprite background(backgroundTexture);

    sf::RectangleShape backgroundSolid(sf::Vector2f(window_X, window_Y));
    backgroundSolid.setFillColor(sf::Color(40, 40, 40));

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

    Entity player(playerTexture,(windowRatio / 4),0, 0,5,(windowRatio / 6));

    Entity enemy(enemyTexture, (windowRatio / 4), window_X, window_Y, 0, 0);

    Entity laser(laserTexture, (windowRatio / 15), -window_X, 0, 0, 1);
    
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

    sf::SoundBuffer pop_buffer;
    if (!pop_buffer.loadFromFile(soundPath + "pop.ogg")) return 1;
    sf::SoundBuffer shrink_ray_buffer;
    if (!shrink_ray_buffer.loadFromFile(soundPath + "shrink_ray.ogg")) return 1;
    sf::SoundBuffer laser_shoot_buffer;
    if (!laser_shoot_buffer.loadFromFile(soundPath + "laserShoot.ogg")) return 1;

    sf::Music soundtrack;
    if (!soundtrack.openFromFile(soundPath + "soundtrack.ogg")) return 1;

    sf::Sound popSound(pop_buffer);
    sf::Sound shrinkRaySound(shrink_ray_buffer);
    sf::Sound laserShootSound(laser_shoot_buffer);

    // soundtrack.setVolume(70);
    // soundtrack.play();
    // soundtrack.setLoop(true);

    bool isKey_M_released = true;
    bool isLaserShot = false;

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
                if (soundtrack.getVolume() == 70) {
                    soundtrack.setVolume(0);
                } else {
                    soundtrack.setVolume(70);
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
                player.move(-player.getSpeed(), 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.move(player.getSpeed(), 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.move(0, -player.getSpeed());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.move(0, player.getSpeed());
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                laser.setPosition(player.getPosition().x + 200, player.getPosition().y + 150);
                if (laserShootSound.getStatus() != sf::Sound::Playing) {
                    laserShootSound.play();
                }
                isLaserShot = true;
            }
            
            if (isLaserShot && laser.getPosition().x != laser.getInitial_X()) {
                laser.move(1, 0);
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
        if (laser.getPosition().x > window_X) {
            laser.setPosition(window_X, laser.getPosition().y);
        }
        if (laser.getPosition().y > window_Y) {
            laser.setPosition(laser.getPosition().x, window_Y);
        }

        // Entities Bounds
        sf::FloatRect playerGlobalBounds = player.getGlobalBounds();
        sf::FloatRect enemyGlobalBounds = enemy.getGlobalBounds();
        sf::FloatRect laserGlobalBounds = laser.getGlobalBounds();
        
        // Collision player <-> enemy
        if (playerGlobalBounds.intersects(enemyGlobalBounds)) {
            popSound.play();
            player.setPosition(player.getInitial_X(), player.getInitial_Y());
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());

            player.setLives(-1);
            livesText.setString(std::to_string(player.getLives()));
        }

        // Collision laser -> enemy
        if (laserGlobalBounds.intersects(enemyGlobalBounds)) {
            if (popSound.getStatus() != sf::Sound::Playing) {
                popSound.play();
            }
            laser.setPosition(laser.getInitial_X(), laser.getInitial_Y());
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
        }

        window.clear();
        // window.draw(background);
        window.draw(backgroundSolid);
        window.draw(laser);
        window.draw(player);
        window.draw(enemy);
        window.draw(livesText);
        window.draw(heartSprite);
        window.draw(player);

        if (!player.isAlive()) {
            window.draw(gameover);
        }

        window.display();
    }

    return 0;
}
