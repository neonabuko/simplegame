#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "../src/include/Entity.h"
#include "../src/include/Assets.h"

using namespace std;
using namespace sf;
using namespace Assets;

float enemyRandomSpeed_X = -200;
float enemyRandomSpeed_Y;
float elapsedTimeSinceRandomSpeedGeneration;
uniform_real_distribution<float> speedGeneration_randomTimeInterval(1, 3);
uniform_real_distribution<float> enemyRandomSpeedRange(-200, -100);
random_device randomSpeedDevice;
mt19937 gen(randomSpeedDevice());
float randomSpeedGenerationInterval = speedGeneration_randomTimeInterval(gen);

Font hackNerdFont;

int FPS_count = 0;
string FPS_toString = to_string(FPS_count);
Text FPS_Text("FPS " + FPS_toString, hackNerdFont, 22);
Text someText("", hackNerdFont, 30);

void generateRandomSpeeds() {
    if (elapsedTimeSinceRandomSpeedGeneration >= randomSpeedGenerationInterval) {
        enemyRandomSpeed_X = enemyRandomSpeedRange(gen);
        enemyRandomSpeed_Y = enemyRandomSpeedRange(gen);
        elapsedTimeSinceRandomSpeedGeneration = 0;
    }
}

void displayFPS(float FPS) {
    string FPS_string = to_string(FPS);
    FPS_Text.setString(FPS_string);
    FPS_count = 0;    
}

int main() {
    float window_X = 1600;
    float window_Y = 900;
    float windowRatio = window_X / window_Y;
    RenderWindow window(VideoMode((int) window_X, (int) window_Y), "Simple Game");

    loadTextures();
    loadSounds();
    hackNerdFont.loadFromFile("../src/assets/font/HackNerdFont-Regular.ttf");

    // Sounds
    Sound pop(Sounds::pop);
    Sound shrinkRay(Sounds::shrink_ray);
    Sound laserShoot(Sounds::laserShoot);
    Sound laserShootBig(Sounds::laserShootBig);
    Sound explosion(Sounds::explosion);
    Sound gameoverSound(Sounds::gameover);
    Sound jumpSound(Sounds::jump);
    Sound hurt(Sounds::hurt);
    Sound stomp(Sounds::stomp);
    Sound powerUp(Sounds::powerUp);

    Music soundtrack;
    soundtrack.openFromFile("../src/assets/sound/soundtrack.ogg");
    soundtrack.setVolume(100);
    // soundtrack.play();
    soundtrack.setLoop(true);

    Music soundtrackBig;
    soundtrackBig.openFromFile("../src/assets/sound/soundtrackBig.ogg");
    soundtrackBig.setVolume(100);
    soundtrackBig.setLoop(true);

    Sprite background(Textures::background);
    background.setScale(window_X / (1920), window_Y / 1080);

    RectangleShape windowBox(Vector2f(background.getLocalBounds().width, background.getLocalBounds().height));
    windowBox.setPosition(background.getPosition().x, background.getPosition().y);

    Sprite heart(Textures::heart);
    heart.setScale(windowRatio / 6, windowRatio / 6);
    heart.setPosition((window_X / 4), window_Y / 800);

    Sprite explosionSprite;
    explosionSprite.setScale(1.5, 1.5);

    vector<Texture> explosionTextures;

    for (int i = 1; i <= 24; ++i) {
        string texturePath = "../src/assets/icon/explosion" + to_string(i) + ".png";
        Texture texture;
        if (texture.loadFromFile(texturePath)) {
            explosionTextures.push_back(texture);
        } else {
            return 1;
        }
    }

    float playerSpeed_X = window_X / 3;
    float playerSpeed_Y = window_Y * 2;
    float playerAcceleration = 4000;
    int playerLives = 5;
    float playerScale = window_X / 5500;
    float playerScaleOriginal = window_X / 5500;
    Entity player(Textures::player, playerScale, 0, 0, playerLives, playerSpeed_X, playerSpeed_Y, playerAcceleration);
    player.setInitialPosition(0, window_Y - player.getHeight());
    player.setPosition(0, window_Y - player.getHeight());
    float playerMax_X;
    float playerMax_Y = window_Y - player.getHeight();

    RectangleShape playerBox;
    playerBox.setOutlineColor(sf::Color::Red);
    playerBox.setOutlineThickness(2.0f);
    playerBox.setFillColor(sf::Color::Transparent);    

    float enemyScale = (window_X / 2000);
    Entity enemy(Textures::enemy, enemyScale, 0, 0, 1, 1000, 1200, 4000);
    enemy.setInitialPosition(window_X - enemy.getWidth(), window_Y - enemy.getHeight());
    enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
    float enemyMax_X = window_X - enemy.getWidth();
    float enemyMax_Y = window_Y - enemy.getHeight() - 10;

    float laserScale = window_Y / 5500;
    float laserScaleOriginal = window_Y / 5500;
    Entity laser(Textures::laserBlue, laserScale, -window_X, 0, 0, 3000, 0, 0);

    int points = 0;
    string pointsToString = to_string(points);
    Text pointsText("SCORE " + pointsToString, hackNerdFont, 30);
    float points_X = window.getSize().x / 2.2;
    float points_Y = window.getSize().y / 800;
    pointsText.setFillColor(Color::White);
    pointsText.setPosition(points_X, points_Y);
    pointsText.setOutlineColor(Color::Black);
    pointsText.setOutlineThickness(2);    
    
    string livesToString = to_string(player.getLives());
    Text lives(livesToString, hackNerdFont, 30);
    lives.setFillColor(Color::White);
    lives.setOutlineColor(Color::Black);
    lives.setOutlineThickness(2);    
    float lives_X = heart.getPosition().x + heart.getGlobalBounds().width + 20;
    float lives_Y = heart.getPosition().y;
    lives.setPosition(lives_X, lives_Y);

    Text gameover("GAME OVER\nPress R to restart", hackNerdFont, 100 * (window_X / 1920));
    gameover.setFillColor(Color::White);
    gameover.setOutlineColor(Color::Black);
    gameover.setOutlineThickness(2);
    FloatRect gameoverBounds = gameover.getLocalBounds();
    float gameover_X = (window.getSize().x - gameoverBounds.width) / 2;
    float gameover_Y = (window.getSize().y - gameoverBounds.height) / 2;
    gameover.setPosition(gameover_X, gameover_Y);

    FPS_Text.setPosition(window_X / 1.1, pointsText.getPosition().y);

    Clock clock;
    Clock deltaClock;
    Clock laserClock;
    Clock explosionClock;
    Clock enemySpawnClock;

    float deltaTime = 0;
    Time laserCooldown = seconds(0.5);
    
    Time explosionDuration = seconds(0.4);
    Time elapsedTimeSinceExplosion = Time::Zero;
    Time elapsedTimeSinceEnemyDied = Time::Zero;
    Time elapsedTimeSinceShot = Time::Zero;

    Time enemySpawnWait = seconds(0.3);

    int currentFrame = 0;

    bool isKey_M_released = true;
    bool isShooting = false;
    bool isPlayerReverse = false;
    bool isPlayerJumping = false;
    bool isPlayerBig = false;
    bool isExplosion = false;
    bool isGameOver = false;
    bool isLaserReverse = false;
    bool isFullScreen = false;
    bool isF11Pressed = false;
    bool isPowerUp = false;

    float newWindowRatio;

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        newWindowRatio = window.getSize().x / window_X;

        player.setScale(playerScale * newWindowRatio, playerScale * newWindowRatio);
        laser.setScale(laserScale * newWindowRatio, laserScale * newWindowRatio);
        displayFPS(player.getSpeed_Y());

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::R)) {
            if (isGameOver) {
                isGameOver = false;
                player.setLives(playerLives);
                background.setTexture(Textures::background);
                playerScale = playerScaleOriginal;
                laserScale = laserScaleOriginal;
                isPlayerBig = false;
                soundtrack.play();
            }
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

        playerMax_X = window.getSize().x / 1.3;

        elapsedTimeSinceRandomSpeedGeneration += clock.restart().asSeconds();
        deltaTime = deltaClock.restart().asSeconds();
        FPS_count++;

        if (!isGameOver) {
            playerBox.setPosition(player.getPosition());
            playerBox.setSize(sf::Vector2f(player.getWidth(), player.getHeight()));

            if (isPowerUp) {
                laserScale += 0.03 * newWindowRatio * deltaTime;
                playerScale += 0.03 * newWindowRatio * deltaTime;
                playerMax_Y = window_Y - player.getHeight();
                if (!isPlayerJumping) {
                    player.setPosition(player.getPosition().x, playerMax_Y);
                }
            }

            // Set textures
            if (isPlayerReverse) {
                if (isShooting) {
                    if (isPowerUp) {
                        player.setTexture(Textures::player_shooting_reverse_powerup);
                    } else {
                        if (isPlayerBig) {
                            player.setTexture(Textures::player_golden_shooting_reverse);
                        } else {
                            player.setTexture(Textures::player_shooting_reverse);
                        }
                    }
                } else {
                    if (isPowerUp) {
                        player.setTexture(Textures::player_reverse_powerup);
                    } else {
                        if (isPlayerBig) {
                            player.setTexture(Textures::player_golden_reverse);
                        } else {
                            player.setTexture(Textures::player_reverse);
                        }
                    }
                }
            } else {
                if (isShooting && laser.getPosition().x < 1000) {
                    if (isPowerUp) {
                        player.setTexture(Textures::player_shooting_powerup);
                    } else {
                        if (isPlayerBig) {
                            player.setTexture(Textures::player_golden_shooting);
                        } else {
                            player.setTexture(Textures::player_shooting);
                        }
                    }
                } else {
                    if (isPowerUp) {
                        player.setTexture(Textures::player_powerup);    
                    } else {
                        if (isPlayerBig) {
                            player.setTexture(Textures::player_golden);
                        } else {
                            player.setTexture(Textures::player);
                        }
                    }
                }
            }
            if (player.getPosition().x < enemy.getPosition().x) {
                enemy.setTexture(Textures::enemy);
            } else {
                enemy.setTexture(Textures::enemy_reverse);
            }

            if (isPlayerBig) {
                if (isLaserReverse) {
                    laser.setTexture(Textures::laserRed_reverse);
                } else {
                    laser.setTexture(Textures::laserRed);
                }
                background.setTexture(Textures::backgroundRed);
            } else {
                if (isLaserReverse) {
                    laser.setTexture(Textures::laserBlue_reverse);
                } else {
                    laser.setTexture(Textures::laserBlue);
                }
                background.setTexture(Textures::background);
            }

            // Jumping
            if (isPlayerJumping) {
                player.accelerate(0, -1, -1, deltaTime);
                if (player.getPosition().y > playerMax_Y) {
                    player.setSpeed_Y(playerSpeed_Y);
                    isPlayerJumping = false;
                    if (isPlayerBig) {
                        stomp.play();  
                    }      
                }
            }

            // Gravity
            if (!isPlayerJumping && player.getPosition().y != playerMax_Y) {
                player.accelerate(0, 1, 1, deltaTime);
            }
                        
            // Player Controller
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                isPlayerReverse = true;
                player.move(-player.getSpeed_X() * deltaTime, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                isPlayerReverse = false;
                player.move(player.getSpeed_X() * deltaTime, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Space) && !isPlayerJumping) {
                if (player.getPosition().y == playerMax_Y) {
                    isPlayerJumping = true;
                }
                jumpSound.play();
            }

            // Shoot Laser
            if (Keyboard::isKeyPressed(Keyboard::Enter) && !isShooting) {
                elapsedTimeSinceShot = Time::Zero;
                float laserOrigin_X;
                float laserOrigin_Y;               
                if (isPlayerReverse) {
                    isLaserReverse = true;
                    laserOrigin_X = player.getPosition().x - player.getWidth() / 4; 
                    laserOrigin_Y = player.getPosition().y + player.getHeight() / 1.7;
                    laser.setPosition(Vector2f(laserOrigin_X, laserOrigin_Y));
                } else {
                    isLaserReverse = false;
                    laserOrigin_X = player.getPosition().x + player.getWidth() / 1.5; 
                    laserOrigin_Y = player.getPosition().y + player.getHeight() / 1.7;                    
                    laser.setPosition(Vector2f(laserOrigin_X, laserOrigin_Y));
                }
                if (isPlayerBig) {
                    laserShootBig.play();
                } else {
                    laserShoot.play();
                }
                isShooting = true;
                laserClock.restart();
            }

            if (isShooting) {
                elapsedTimeSinceShot = laserClock.getElapsedTime();
                if (elapsedTimeSinceShot > laserCooldown) {
                    isShooting = false;
                    elapsedTimeSinceShot = laserCooldown;
                }
            }

            if (isShooting) {
                if (isLaserReverse) {
                    if (laser.getPosition().x > -laser.getWidth()) {
                        laser.move(-(laser.getSpeed_X() * deltaTime), 0);
                    }
                } else {
                    if (laser.getPosition().x < window_X) {
                        laser.move(laser.getSpeed_X() * deltaTime, 0);
                    }
                }
            }
        }

        window.clear();
        window.draw(background);

        if (!isGameOver) {
            window.draw(player);
            if (enemy.isAlive()) {
                window.draw(enemy);
                if (player.getPosition().x < enemy.getPosition().x) {
                    // enemy.move(enemyRandomSpeed_X * deltaTime, 0);
                } else {
                    // enemy.move(-enemyRandomSpeed_X * deltaTime, 0);
                }                
            } else {
                enemy.setPosition(0, -enemy.getHeight());
                elapsedTimeSinceEnemyDied = enemySpawnClock.getElapsedTime();
                if (elapsedTimeSinceEnemyDied > enemySpawnWait) {
                    enemy.setLives(1);
                    elapsedTimeSinceEnemyDied = enemySpawnWait;
                    enemy.setPosition(window_X - enemy.getWidth(), window_Y - enemy.getHeight());
                }
            }
        } else {
            window.draw(gameover);
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

        // Laser border limits
        if (!laser.getGlobalBounds().intersects(windowBox.getGlobalBounds())) {
            laser.setPosition(window_X, -200);
        }

        FloatRect playerBounds = player.getGlobalBounds();
        FloatRect enemyBounds = enemy.getGlobalBounds();
        FloatRect laserBounds = laser.getGlobalBounds();
        
        // Player <-> Enemy collision
        if (playerBounds.intersects(enemyBounds)) {
            if (hurt.getStatus() != Sound::Playing) {
                hurt.play();
            }
            player.setPosition(player.getInitial_X(), player.getInitial_Y());
            player.setLives(-1);
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            lives.setString(to_string(player.getLives()));

            if (player.getLives() == 0) {
                soundtrack.stop();
                soundtrackBig.stop();
                gameoverSound.play();
                isGameOver = true;
            }
        }
        
        playerMax_X = window_X / 1.8;
        playerMax_Y = window_Y - player.getHeight();

        // Laser -> Enemy Collision 
        if (laserBounds.intersects(enemyBounds)) {
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

            if (player.getScale().x < 0.5 * newWindowRatio) {
                if (points % 2 == 0) {
                    isPowerUp = true;
                    powerUp.play();
                }
            } else {
                isPlayerBig = true;
                laserCooldown = seconds(0.38);

                soundtrack.stop();
                if (soundtrackBig.getStatus() != Sound::Playing) {
                    soundtrackBig.play();
                }
            }
            points++;
            pointsText.setString("SCORE " + to_string(points));
            isExplosion = true;
            explosionClock.restart();
            enemySpawnClock.restart();
        }

        // Background movement
        if (player.isAlive()) {
            if (player.getPosition().x > playerMax_X - 1 && Keyboard::isKeyPressed(Keyboard::D) && 
                background.getPosition().x + background.getGlobalBounds().width > window_X) {
                background.move(-200 * deltaTime, 0);
                enemy.move(-200 * deltaTime, 0);
            } else if (player.getPosition().x == 0 && Keyboard::isKeyPressed(Keyboard::A) && background.getPosition().x < 0) {
                background.move(200 * deltaTime, 0);
                enemy.move(200 * deltaTime, 0);
            }
        }

        generateRandomSpeeds();        
        window.draw(laser);

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

        window.draw(heart);
        window.draw(lives);
        window.draw(pointsText);
        window.draw(FPS_Text);
        window.draw(someText);
        window.draw(playerBox);

        window.display();
    }

    return 0;
}
