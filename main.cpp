#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "entity/Entity.h"

int main() {
    float window_X = 1600;
    float window_Y = 900;
    float windowRatio = window_X / window_Y;
    sf::RenderWindow window(
            sf::VideoMode((int) window_X, (int) window_Y),
            "Simple Game"
            );

    // Textures
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../icon/background.jpg")) return 1;
    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("../icon/heart.png")) return 1;
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../icon/player.png")) return 1;
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../icon/enemy.png")) return 1;

    sf::Sprite background(backgroundTexture);

    sf::RectangleShape backgroundSolid(sf::Vector2f(window_X, window_Y));
    sf::Color backgroundSolidColor(40, 40, 40);
    backgroundSolid.setFillColor(backgroundSolidColor);

    sf::Sprite heartSprite(heartTexture);
    heartSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    heartSprite.setPosition((window_X / 2) - 50, 10);

    Entity player(playerTexture,(windowRatio / 4),0,5,(windowRatio / 9));
    float playerMax_X = window_X - player.getWidth();
    float playerMax_Y = window_Y - player.getHeight();

    Entity enemy(enemyTexture, (windowRatio / 4), window_Y, 0, 0);
    float enemyMax_X = window_X - enemy.getWidth();
    float enemyMax_Y = window_Y - enemy.getHeight();
    std::uniform_real_distribution<float> enemySpeedRange(-0.5f, 0.5f);

    sf::Font hackNerdFont;
    if (!hackNerdFont.loadFromFile("../font/HackNerdFont-Regular.ttf")) return 1;

    std::string livesToString = std::to_string(player.getLives());
    sf::Text livesText(livesToString, hackNerdFont, 30);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(heartSprite.getPosition().x + (float) livesText.getCharacterSize() * 2, heartSprite.getPosition().y);

    sf::Text gameover("GAME OVER", hackNerdFont, 55);
    gameover.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = gameover.getLocalBounds();
    float textX = (window_X - textBounds.width) / 2;
    float textY = (window_Y - textBounds.height) / 2;
    gameover.setPosition(textX, textY);

    // Random Number Generator
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    sf::Clock clock;
    std::uniform_real_distribution<float> timeIntervalRange(0.5f, 1.5f);
    float generationInterval = timeIntervalRange(gen);
    float elapsedTime = 0.0f;

    sf::SoundBuffer soundBufferPop;
    if (!soundBufferPop.loadFromFile("../sound/pop.ogg")) return 1;
    sf::SoundBuffer soundBufferShrink;
    if (!soundBufferShrink.loadFromFile("../sound/shrink_ray.ogg")) return 1;
    sf::Music soundtrack;
    if (!soundtrack.openFromFile("../sound/soundtrack.ogg")) return 1;

    sf::Sound popSound(soundBufferPop);
    sf::Sound shrinkRaySound(soundBufferShrink);

    soundtrack.setVolume(70);
    soundtrack.play();
    soundtrack.setLoop(true);

    bool isKey_M_released = true;

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
            random_X_speed = enemySpeedRange(gen);
            random_Y_speed = enemySpeedRange(gen);
            elapsedTime = 0.0f;
        }

        float playerBound_RIGHT = player.getPosition().x + player.getWidth();
        float playerBound_LEFT = player.getPosition().x - player.getWidth();
        float playerBound_DOWN = player.getPosition().y + player.getHeight();
        float playerBound_UP = player.getPosition().y - player.getHeight();

        float enemyBound_LEFT = enemy.getPosition().x;
        float enemyBound_RIGHT = enemy.getPosition().x;
        float enemyBound_UP = enemy.getPosition().y;
        float enemyBound_DOWN = enemy.getPosition().y;

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

            enemy.move(random_X_speed / 5, random_Y_speed / 5);
        }

        // Entity border limits
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

        // Collision player <-> enemy
        if (playerBound_RIGHT > enemyBound_LEFT && playerBound_LEFT < enemyBound_RIGHT &&
            playerBound_DOWN > enemyBound_UP && playerBound_UP < enemyBound_DOWN)
        {
            popSound.play();
            player.setPosition(player.getInitialPosition(), player.getInitialPosition());
            enemy.setPosition(enemy.getInitialPosition(), enemy.getInitialPosition());

            player.setLives(-1);
            livesText.setString(std::to_string(player.getLives()));
        }

        window.clear();
//        window.draw(background);
        window.draw(backgroundSolid);
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
