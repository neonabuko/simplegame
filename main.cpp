#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>

int main() {
    float window_X = 1400;
    float window_Y = 900;

    // Window
    sf::RenderWindow window(sf::VideoMode(
            (int) window_X, (int) window_Y), "Simple Game"
            );

    // Player
    bool playerAlive = true;
    float playerRadius = 40;
    sf::CircleShape player(playerRadius);
    player.setFillColor(sf::Color::Yellow);
    float playerDiameter = player.getRadius() * 2;
    float playerMax_X = window_X - playerDiameter;
    float playerMax_Y = window_Y - playerDiameter;
    float playerSpeed_X = 0.1f;
    float playerSpeed_Y = 0.1f;
    int lives = 7;

    // Heart Texture
    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("../icon/heart.png")) {
        return 1;
    }


    // Heart Icon
    sf::Sprite heartSprite;
    heartSprite.setTexture(heartTexture);
    heartSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    heartSprite.setPosition((window_X / 2) - 50, 10);

    // Enemy Texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../icon/enemy.png")) {
        return 1;
    }
    // Enemy
    float enemyScale_X = 0.4f;
    float enemyScale_Y = 0.4f;
    float random_X_speed = 0.0f;
    float random_Y_speed = 0.0f;
    sf::Sprite enemy;
    enemy.setTexture(enemyTexture);
    enemy.setScale(sf::Vector2f(enemyScale_X, enemyScale_Y));
    enemy.setPosition(window_X - enemyScale_X, window_Y - enemyScale_Y);
    std::uniform_real_distribution<float> enemySpeedRange(-0.5f, 0.5f);
    float enemyWidth = enemy.getLocalBounds().width * 0.8f;
    float enemyHeight = enemy.getLocalBounds().height * 0.8f;

    // Font
    sf::Font hackNerdFont;
    if (!hackNerdFont.loadFromFile("../font/HackNerdFont-Regular.ttf")) {
        std::cout << "HackNerdFont-Regular.ttf not found " << std::endl;
        return 1;
    }


    // Lives Text
    std::string livesToString = std::to_string(lives);
    sf::Text livesText;
    livesText.setFont(hackNerdFont);
    livesText.setString(livesToString);
    livesText.setCharacterSize(30);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(heartSprite.getPosition().x + livesText.getCharacterSize() * 2, heartSprite.getPosition().y);

    // Game Over Text
    sf::Text gameover;
    gameover.setFont(hackNerdFont);
    gameover.setString("GAME OVER");
    gameover.setCharacterSize(50);
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
    if (!soundBufferPop.loadFromFile("../sounds/pop.ogg")) {
        return 1;
    }
    sf::Sound popSound;
    popSound.setBuffer(soundBufferPop);

    // shrink_ray sound
    sf::SoundBuffer soundBufferShrink;
    if (!soundBufferShrink.loadFromFile("../sounds/shrink_ray.ogg")) {
        return 1;
    }
    sf::Sound shrinkRaySound;
    shrinkRaySound.setBuffer(soundBufferShrink);

    shrinkRaySound.play();

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

        elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= generationInterval) {
            random_X_speed = enemySpeedRange(gen);
            random_Y_speed = enemySpeedRange(gen);
            elapsedTime = 0.0f;
        }

        float playerBound_RIGHT = player.getPosition().x + player.getRadius();
        float playerBound_LEFT = player.getPosition().x - player.getRadius();
        float playerBound_DOWN = player.getPosition().y + player.getRadius();
        float playerBound_UP = player.getPosition().y - player.getRadius();

        float enemyBound_LEFT = enemy.getPosition().x - enemyScale_X;
        float enemyBound_RIGHT = enemy.getPosition().x;
        float enemyBound_UP = enemy.getPosition().y - enemyScale_Y;
        float enemyBound_DOWN = enemy.getPosition().y;

        // Handle keyboard input
        if (playerAlive) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.move(-playerSpeed_X, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.move(playerSpeed_X, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.move(0.0f, -playerSpeed_Y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.move(0.0f, playerSpeed_Y);
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
        if (enemyBound_RIGHT > window_X - enemyWidth) {
            enemy.setPosition(window_X - enemyWidth, enemy.getPosition().y);
        }
        if (enemyBound_LEFT < 0) {
            enemy.setPosition(0, enemy.getPosition().y);
        }
        if (enemyBound_UP < 0) {
            enemy.setPosition(enemy.getPosition().x, 0);
        }
        if (enemyBound_DOWN > window_Y - enemyHeight) {
            enemy.setPosition(enemy.getPosition().x, window_Y - enemyHeight);
        }

        // Collision player -> enemy
        if (playerBound_RIGHT > enemyBound_LEFT && playerBound_LEFT < enemyBound_RIGHT &&
            playerBound_DOWN > enemyBound_UP && playerBound_UP < enemyBound_DOWN)
        {
            popSound.play();
            player.setPosition(0, 0);
            enemy.setPosition(window_X - enemyScale_X, window_Y - enemyScale_Y);
            lives -= 1;
            livesToString = std::to_string(lives);
            livesText.setString(livesToString);

            if (lives == 0) {
                playerAlive = false;
            }
        }

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.draw(livesText);
        window.draw(heartSprite);
        if (!playerAlive) {
            window.draw(gameover);
        }
        window.display();
    }

    return 0;
}
