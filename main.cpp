#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "entity/Player.h"

int main() {
    float window_X = 1600;
    float window_Y = 900;

    // Window
    sf::RenderWindow window(sf::VideoMode(
            (int) window_X, (int) window_Y), "Simple Game"
            );

    // Background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../icon/background.jpg")) {
        return 1;
    }
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    // Solid Background
    sf::RectangleShape backgroundSolid;
    sf::Color backgroundSolidColor;
    backgroundSolidColor.r = 40;
    backgroundSolidColor.g = 40;
    backgroundSolidColor.b = 40;
    backgroundSolid.setFillColor(backgroundSolidColor);
    backgroundSolid.setSize(sf::Vector2f(window_X, window_Y));

    // Heart
    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("../icon/heart.png")) {
        return 1;
    }
    sf::Sprite heartSprite;
    heartSprite.setTexture(heartTexture);
    heartSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    heartSprite.setPosition((window_X / 2) - 50, 10);

    // Player
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../icon/player.png")) {
        return 1;
    }
    Player player (playerTexture,
                   (window_X / window_Y) / 4,
                   0,
                   5);
    player.setSpeed(window_X / window_Y / 9);
    float playerSpeed_X = player.getSpeed();
    float playerSpeed_Y = player.getSpeed();
    float playerWidth = player.getLocalBounds().width * player.getScale().x;
    float playerHeight = player.getLocalBounds().height * player.getScale().y;
    float playerMax_X = window_X - playerWidth;
    float playerMax_Y = window_Y - playerHeight;
    int lives = player.getLives();

    // Enemy
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../icon/enemy.png")) {
        return 1;
    }
    float enemyScale_X = (window_X / window_Y) / 4;
    float enemyScale_Y = (window_X / window_Y) / 4;
    float random_X_speed = 0.0f;
    float random_Y_speed = 0.0f;
    sf::Sprite enemy;
    enemy.setTexture(enemyTexture);
    enemy.setScale(sf::Vector2f(enemyScale_X, enemyScale_Y));
    float enemyWidth = enemy.getLocalBounds().width * enemyScale_X;
    float enemyHeight = enemy.getLocalBounds().height * enemyScale_Y;
    float enemyMax_X = window_X - enemyWidth;
    float enemyMax_Y = window_Y - enemyHeight;
    float enemyInitial_X = window_X - enemyWidth * 1.5f;
    float enemyInitial_Y = window_Y - enemyHeight * 1.5f;
    enemy.setPosition(enemyInitial_X, enemyInitial_Y);
    std::uniform_real_distribution<float> enemySpeedRange(-0.5f, 0.5f);

    // Font
    sf::Font hackNerdFont;
    if (!hackNerdFont.loadFromFile("../font/HackNerdFont-Regular.ttf")) {
        return 1;
    }

    // Lives Text
    std::string livesToString = std::to_string(lives);
    sf::Text livesText;
    float fontSize = 30;
    livesText.setFont(hackNerdFont);
    livesText.setString(livesToString);
    livesText.setCharacterSize((int) fontSize);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(heartSprite.getPosition().x + fontSize * 2, heartSprite.getPosition().y);

    // Game Over Text
    sf::Text gameover;
    gameover.setFont(hackNerdFont);
    gameover.setString("GAME OVER");
    gameover.setCharacterSize(55);
    gameover.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = gameover.getLocalBounds();
    float textX = (window_X - textBounds.width) / 2;
    float textY = (window_Y - textBounds.height) / 2;
    gameover.setPosition(textX, textY);

    // Random Number Generator
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    // Time
    sf::Clock clock;
    std::uniform_real_distribution<float> timeIntervalRange(0.5f, 1.5f);
    float generationInterval = timeIntervalRange(gen);
    float elapsedTime = 0.0f;

    // pop sound
    sf::SoundBuffer soundBufferPop;
    if (!soundBufferPop.loadFromFile("../sound/pop.ogg")) {
        return 1;
    }
    sf::Sound popSound;
    popSound.setBuffer(soundBufferPop);

    // shrink_ray sound
    sf::SoundBuffer soundBufferShrink;
    if (!soundBufferShrink.loadFromFile("../sound/shrink_ray.ogg")) {
        return 1;
    }
    sf::Sound shrinkRaySound;
    shrinkRaySound.setBuffer(soundBufferShrink);

    // Soundtrack
    sf::Music soundtrack;

    if (!soundtrack.openFromFile("../sound/soundtrack.ogg")) {
        return 1;
    }

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
        if (elapsedTime >= generationInterval) {
            random_X_speed = enemySpeedRange(gen);
            random_Y_speed = enemySpeedRange(gen);
            elapsedTime = 0.0f;
        }

        player.setSpeed((float) window.getSize().x / window_Y / 9);
        float playerBound_RIGHT = player.getPosition().x + playerWidth;
        float playerBound_LEFT = player.getPosition().x - playerWidth;
        float playerBound_DOWN = player.getPosition().y + playerHeight;
        float playerBound_UP = player.getPosition().y - playerHeight;

        float enemyBound_LEFT = enemy.getPosition().x;
        float enemyBound_RIGHT = enemy.getPosition().x;
        float enemyBound_UP = enemy.getPosition().y;
        float enemyBound_DOWN = enemy.getPosition().y;

        // Handle keyboard input
        if (player.isAlive()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.move(-playerSpeed_X, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.move(playerSpeed_X, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.move(0, -playerSpeed_Y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.move(0, playerSpeed_Y);
            }

            enemy.move(random_X_speed / 5, random_Y_speed / 5);
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

        // Collision player -> enemy
        if (playerBound_RIGHT > enemyBound_LEFT && playerBound_LEFT < enemyBound_RIGHT &&
            playerBound_DOWN > enemyBound_UP && playerBound_UP < enemyBound_DOWN)
        {
            popSound.play();
            player.setPosition(player.getInitialPosition(), player.getInitialPosition());
            enemy.setPosition(enemyInitial_X, enemyInitial_Y);
            player.setLives(-1);
            lives = player.getLives();
            livesToString = std::to_string(lives);
            livesText.setString(livesToString);
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
