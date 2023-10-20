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

    // Player Texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../icon/player.png")) {
        return 1;
    }

    // Player
    bool playerAlive = true;
    float playerInitial_X = 0;
    float playerInitial_Y = 0;
    float playerScale_X = 0.3f;
    float playerScale_Y = 0.3f;
    sf::Sprite player;
    player.setTexture(playerTexture);
    player.setScale(playerScale_X, playerScale_Y);
    player.setPosition(playerInitial_X, playerInitial_Y);
    float playerWidth = player.getLocalBounds().width * playerScale_X;
    float playerMax_X = window_X - playerWidth;
    float playerMax_Y = window_Y - playerWidth;
    float playerSpeed_X = 0.1f;
    float playerSpeed_Y = 0.1f;
    int lives = 7;

    // Enemy Texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../icon/enemy.png")) {
        return 1;
    }
    // Enemy
    float enemyScale_X = 0.3f;
    float enemyScale_Y = 0.3f;
    float random_X_speed = 0.0f;
    float random_Y_speed = 0.0f;
    sf::Sprite enemy;
    enemy.setTexture(enemyTexture);
    enemy.setScale(sf::Vector2f(enemyScale_X, enemyScale_Y));
    float enemyWidth = enemy.getLocalBounds().width * enemyScale_X;
    float enemyHeight = enemy.getLocalBounds().height * enemyScale_Y;
    float enemyInitial_X = window_X - enemyWidth * 1.5f;
    float enemyInitial_Y = window_Y - enemyHeight * 1.5f;
    enemy.setPosition(enemyInitial_X, enemyInitial_Y);
    std::uniform_real_distribution<float> enemySpeedRange(-0.5f, 0.5f);

    // Font
    sf::Font hackNerdFont;
    if (!hackNerdFont.loadFromFile("../font/HackNerdFont-Regular.ttf")) {
        std::cout << "HackNerdFont-Regular.ttf not found " << std::endl;
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

    // Soundtrack
    sf::Music soundtrack;

    if (!soundtrack.openFromFile("../sounds/soundtrack.ogg")) {
        return 1;
    }

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
                if (soundtrack.getVolume() == 100) {
                    soundtrack.setVolume(0);
                } else {
                    soundtrack.setVolume(100);
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

        float playerBound_RIGHT = player.getPosition().x;
        float playerBound_LEFT = player.getPosition().x;
        float playerBound_DOWN = player.getPosition().y;
        float playerBound_UP = player.getPosition().y;

        float enemyBound_LEFT = enemy.getPosition().x;
        float enemyBound_RIGHT = enemy.getPosition().x;
        float enemyBound_UP = enemy.getPosition().y;
        float enemyBound_DOWN = enemy.getPosition().y;

        // Handle keyboard input
        if (playerAlive) {
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
        if (playerBound_RIGHT > enemyBound_LEFT && playerBound_LEFT < enemyBound_RIGHT + enemyWidth / 2 &&
            playerBound_DOWN > enemyBound_UP && playerBound_UP < enemyBound_DOWN + enemyHeight / 2)
        {
            popSound.play();
            player.setPosition(playerInitial_X, playerInitial_Y);
            enemy.setPosition(enemyInitial_X, enemyInitial_Y);
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
