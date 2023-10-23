#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "../src/include/Entity.h"
#include "../src/include/Assets.h"

float enemyRandomSpeed_X;
float enemyRandomSpeed_Y;
float elapsedTime;
std::uniform_real_distribution<float> timeIntervalRange(1, 1);
std::uniform_real_distribution<float> enemySpeedRange(-0.5, 0.5);
std::random_device randomDevice;
std::mt19937 gen(randomDevice());
float generationInterval = timeIntervalRange(gen);

sf::Font hackNerdFont;


int FPS_count = 0;
std::string FPS_toString = std::to_string(FPS_count);
sf::Text FPS_Text("FPS " + FPS_toString, hackNerdFont, 22);

void generateRandomSpeeds() {
    if (elapsedTime >= generationInterval) {
        enemyRandomSpeed_X = enemySpeedRange(gen);
        enemyRandomSpeed_Y = enemySpeedRange(gen);
        elapsedTime = 0;
        FPS_Text.setString("FPS " + std::to_string(FPS_count));
        FPS_count = 0;
    }
}

int main() {
    float window_X = 1600;
    float window_Y = 900;
    float windowRatio = window_X / window_Y;
    sf::RenderWindow window(sf::VideoMode((int) window_X, (int) window_Y), "Simple Game");

    Assets::loadTextures();
    Assets::loadSounds();
    hackNerdFont.loadFromFile("../src/assets/font/HackNerdFont-Regular.ttf");

    // Sounds
    sf::Sound pop(Assets::Sounds::pop);
    sf::Sound shrinkRay(Assets::Sounds::shrink_ray);
    sf::Sound laserShoot(Assets::Sounds::laserShoot);
    sf::Sound explosion(Assets::Sounds::explosion);
    sf::Sound gameoverSound(Assets::Sounds::gameover);
    sf::Sound jumpSound(Assets::Sounds::jump);

    sf::Music soundtrack;
    soundtrack.openFromFile("../src/assets/sound/soundtrack.ogg");

    soundtrack.setVolume(30);
    soundtrack.play();
    soundtrack.setLoop(true);

    sf::RectangleShape windowBox(sf::Vector2f(window_X, window_Y));

    sf::Sprite background(Assets::Textures::background);
    background.setScale(window_X / (1920 / 4), window_Y / 1080);

    sf::Sprite heart(Assets::Textures::heart);
    heart.setScale(windowRatio / 6, windowRatio / 6);
    heart.setPosition((window_X / 4), window_Y / 800);

    float playerSpeed_X = (1000);
    float playerSpeed_Y = (1200);
    float playerAcceleration = (4000);
    Entity player(Assets::Textures::player, (window_X / 5500), 0, 0, 5, playerSpeed_X, playerSpeed_Y, playerAcceleration);
    player.setInitialPosition(0, window_Y - player.getHeight());
    player.setPosition(0, window_Y - player.getHeight());
    float playerMax_X = window_X - player.getWidth() - 200;
    float playerMax_Y = window_Y - player.getHeight();

    Entity enemy(Assets::Textures::enemy, (window_X / 5500), 0, 0, 0, 0, (windowRatio / 6), 0.001);
    enemy.setInitialPosition(window_X - enemy.getWidth(), window_Y - enemy.getHeight());
    enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
    float enemyMax_X = window_X - enemy.getWidth();
    float enemyMax_Y = window_Y - enemy.getHeight();

    Entity laser(Assets::Textures::laser, (windowRatio / 20), -window_X, 0, 0, 3000, 0, 0);

    int points = 0;
    std::string pointsToString = std::to_string(points);
    sf::Text pointsText("SCORE " + pointsToString, hackNerdFont, 30);
    float points_X = window.getSize().x / 2.2;
    float points_Y = window.getSize().y / 800;
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(points_X, points_Y);
    
    std::string livesToString = std::to_string(player.getLives());
    sf::Text lives(livesToString, hackNerdFont, 30);
    lives.setFillColor(sf::Color::White);
    float lives_X = heart.getPosition().x + heart.getGlobalBounds().width + 20;
    float lives_Y = heart.getPosition().y;
    lives.setPosition(lives_X, lives_Y);

    sf::Text gameover("GAME OVER", hackNerdFont, 55);
    gameover.setFillColor(sf::Color::White);
    sf::FloatRect gameoverBounds = gameover.getLocalBounds();
    float gameover_X = (window.getSize().x - gameoverBounds.width) / 2;
    float gameover_Y = (window.getSize().y - gameoverBounds.height) / 2;
    gameover.setPosition(gameover_X, gameover_Y);

    FPS_Text.setPosition(window_X / 1.1, pointsText.getPosition().y);

    sf::Clock clock;
    sf::Clock deltaClock;
    float deltaTime = 0.0f;

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
        deltaTime = deltaClock.restart().asSeconds();
        FPS_count++;
        generateRandomSpeeds();

        // Handle keyboard input
        if (player.isAlive()) {   
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player.setTexture(Assets::Textures::player_reverse);
                isPlayerReverse = true;
                player.move(-player.getSpeed_X() * deltaTime, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player.setTexture(Assets::Textures::player);
                isPlayerReverse = false;
                player.move(player.getSpeed_X() * deltaTime, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (isKey_SPACE_released) {
                    if (player.getPosition().y == playerMax_Y) {
                        isPlayerJumping = true;
                        if (jumpSound.getStatus() != sf::Sound::Playing) {
                            jumpSound.play();
                        }
                    }            
                    isKey_SPACE_released = false;                    
                }
            } else {
                isKey_SPACE_released = true;
            }

            // Jumping        
            if (isPlayerJumping) {
                player.accelerate(0, -1, -1, deltaTime);
                if (player.getPosition().y > playerMax_Y) {
                    isPlayerJumping = false;
                    player.setSpeed_Y(playerSpeed_Y);
                }
            }

            // Gravity
            if (!isPlayerJumping && player.getPosition().y != playerMax_Y) {
                player.accelerate(0, 1, 1, deltaTime);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isLaserShot) {
                if (isPlayerReverse) {
                    laser.setTexture(Assets::Textures::laser_reverse);
                    laser.setPosition(player.getPosition().x - player.getWidth() / 3, player.getPosition().y + player.getHeight() / 1.7);
                    isLaserReverse = true;
                } else {
                    laser.setTexture(Assets::Textures::laser);
                    laser.setPosition(player.getPosition().x + player.getWidth() / 1.5, player.getPosition().y + player.getHeight() / 1.7);
                    isLaserReverse = false;
                }

                if (laserShoot.getStatus() != sf::Sound::Playing) {
                    laserShoot.play();
                }
                isLaserShot = true;
            }

            if (isLaserShot && isLaserReverse) {
                if (laser.getPosition().x > -laser.getWidth()) {
                    laser.move(-(laser.getSpeed_X() * deltaTime), 0);
                }
            } else if (isLaserShot && !isLaserReverse) {
                if (laser.getPosition().x > -laser.getWidth()) {
                    laser.move(laser.getSpeed_X() * deltaTime, 0);
                }
            }


            if (enemyRandomSpeed_X < 0) {
                enemy.setTexture(Assets::Textures::enemy);
            } else {
                enemy.setTexture(Assets::Textures::enemy_reverse);
            }
            enemy.move(enemyRandomSpeed_X, enemyRandomSpeed_Y);
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

        // Laser border limits
        if (!laser.getGlobalBounds().intersects(windowBox.getGlobalBounds())) {
            laser.setPosition(window_X, laser.getPosition().y);
            isLaserShot = false;
        }

        // Entities Bounds
        sf::FloatRect playerGlobalBounds = player.getGlobalBounds();
        sf::FloatRect enemyGlobalBounds = enemy.getGlobalBounds();
        sf::FloatRect laserGlobalBounds = laser.getGlobalBounds();
        
        // Collision player <-> enemy
        // if (playerGlobalBounds.intersects(enemyGlobalBounds)) {
        //     pop.play();
        //     player.setPosition(player.getInitial_X(), player.getInitial_Y());
        //     enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());

        //     player.setLives(-1);
        //     lives.setString(std::to_string(player.getLives()));

        //     if (player.getLives() == 0) {
        //         gameoverSound.play();
        //     }
        // }

        // Collision laser -> enemy
        if (laserGlobalBounds.intersects(enemyGlobalBounds)) {
            if (explosion.getStatus() != sf::Sound::Playing) {
                explosion.play();
            }
            laser.setPosition(laser.getInitial_X(), laser.getInitial_Y());
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            points++;
            pointsText.setString("SCORE " + std::to_string(points));
        }

        // Background movement
        if (player.getPosition().x > playerMax_X - 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && 
            background.getPosition().x + background.getGlobalBounds().width > window_X) {
            background.move(-0.1, 0);
        } else if (player.getPosition().x == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
            background.getPosition().x < 0) {
            background.move(0.1, 0);
        }

        window.clear();

        window.draw(background);
        window.draw(player);        
        window.draw(laser);
        window.draw(enemy);
        window.draw(heart);
        window.draw(lives);
        window.draw(pointsText);
        window.draw(FPS_Text);

        if (!player.isAlive()) {
            window.draw(gameover);
        }

        window.display();
    }

    return 0;
}
