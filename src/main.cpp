#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include "../src/include/Entity.h"
#include "../src/include/Assets.h"

using namespace std;
using namespace sf;
using namespace Assets;

Font pixelFont;
Text FPS_Text;

void FPS_to_text(float argument) {
    string argumentToString = to_string(argument);
    FPS_Text.setString(argumentToString);
}

int main() {
    float window_X = 1600;
    float window_Y = 900;
    RenderWindow window(VideoMode((int) window_X, (int) window_Y), "Simple Game");
    window.setFramerateLimit(300);

    loadTextures();
    loadSounds();
    pixelFont.loadFromFile("../src/assets/font/SpaceMono-Regular.ttf");

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
    soundtrack.play();
    soundtrack.setLoop(true);

    Music soundtrackBig;
    soundtrackBig.openFromFile("../src/assets/sound/soundtrackBig.ogg");
    soundtrackBig.setVolume(100);
    soundtrackBig.setLoop(true);
    

    Sprite background(Textures::background);
    background.setScale(1, (window_Y / background.getTexture()->getSize().y));

    Vector2u backgroundTextureSize = background.getTexture()->getSize();

    RectangleShape windowBox(Vector2f(backgroundTextureSize.x, backgroundTextureSize.y));
    windowBox.setPosition(background.getPosition().x, background.getPosition().y);

    Sprite heart(Textures::heart);
    heart.setScale((window_X / 2) / 1920, (window_Y / 2) / 1080);
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

    float playerScale = window_X / 5500;
    float playerInitial_X = 0;
    float playerInitial_Y = window_Y;
    int playerLives = 1;
    float playerSpeed_X = window_X / 2.5;
    float playerInitialSpeed_Y = window_Y * 2;
    float playerAcceleration = 5000;

    Entity player(Textures::player, playerScale, playerInitial_X, playerInitial_Y, playerLives, playerSpeed_X, playerInitialSpeed_Y, playerAcceleration);
    player.setPosition(0, window_Y - player.getHeight());
    float playerMax_X;
    float playerMax_Y;
    float playerInitialScale = player.getInitialScale_X();

    RectangleShape playerBox;
    playerBox.setOutlineColor(sf::Color::Red);
    playerBox.setOutlineThickness(2.0f);
    playerBox.setFillColor(sf::Color::Transparent);    

    float enemyScale = (window_X / 3000);
    Entity enemy(Textures::enemy, enemyScale, 0, 0, 1, 1000, playerInitialSpeed_Y, 4000);
    enemy.setInitialPosition(window_X - enemy.getWidth(), window_Y - enemy.getHeight());
    enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
    float enemyMax_X = window_X - enemy.getWidth();
    float enemyMax_Y;

    float laserScale = window_Y / 6500;
    float laserScaleOriginal = window_Y / 6500;
    float laserInitialSpeed_X = 3000;
    Entity laser(Textures::laserBlue, laserScale, -window_X, -window_Y, 0, laserInitialSpeed_X, 0, 0);

    int playerScore = 0;
    string pointsToString = to_string(playerScore);
    Text playerScoreText("SCORE " + pointsToString, pixelFont, 30);
    float playerScorePosition_X = window.getSize().x / 2.2;
    float playerScorePosition_Y = window.getSize().y / 800;
    playerScoreText.setFillColor(Color::White);
    playerScoreText.setPosition(playerScorePosition_X, playerScorePosition_Y);
    playerScoreText.setOutlineColor(Color::Black);
    playerScoreText.setOutlineThickness(2.2);
    
    string livesToString = to_string(player.getLives());
    Text lives(livesToString, pixelFont, (window_X / 40));
    lives.setFillColor(Color::White);
    lives.setOutlineColor(Color::Black);
    lives.setOutlineThickness(2);

    Sprite gameoverFrame(Textures::frame);
    gameoverFrame.setPosition((window_X - gameoverFrame.getGlobalBounds().width) / 2, -gameoverFrame.getGlobalBounds().height);

    Text gameover("\tGAME OVER\nPress R to restart", pixelFont, 50 * (window_X / 1920));
    gameover.setFillColor(Color::White);
    gameover.setOutlineColor(Color::Black);
    gameover.setOutlineThickness(2);
    FloatRect gameoverBounds = gameover.getLocalBounds();
    float gameover_X = (window_X - gameoverBounds.width) / 2;
    float gameover_Y = (window_Y - gameoverBounds.height) / 2;
    gameover.setPosition((gameoverFrame.getPosition().x + gameover.getGlobalBounds().width) / 2, 0);

    FPS_Text.setPosition(window_X / 1.13, playerScoreText.getPosition().y);
    FPS_Text.setCharacterSize(25);
    FPS_Text.setFont(pixelFont);
    FPS_Text.setOutlineThickness(2.5);

    Clock randomSpeedClock;
    Clock deltaClock;
    Clock laserClock;
    Clock explosionClock;
    Clock enemySpawnClock;
    Clock FPSClock;

    Time FPSStart = Time::Zero;
    Time FPSTimeConstraint = seconds(1);
    Time laserCooldown = seconds(0.5);
    Time explosionDuration = seconds(0.6);
    Time elapsedTimeSinceExplosion = Time::Zero;
    Time elapsedTimeSinceEnemyDied = Time::Zero;
    Time elapsedTimeSinceShot = Time::Zero;

    float deltaTime = 0;
    float playerScaleIncreaseFactor = 0.08;

    Time enemySpawnWait = seconds(0.3);

    int currentFrame = 0;

    bool isKey_M_released = true;
    bool isKey_Space_released = true;
    bool isShooting = false;
    bool isPlayerReverse = false;
    bool isPlayerJumping = false;
    bool isEnemyJumping = false;
    bool isPlayerBig = false;
    bool isExplosion = false;
    bool isGameOver = false;
    bool isLaserReverse = false;
    bool isFullScreen = false;
    bool isF11Pressed = false;
    bool isPowerUp = false;

    float enemySpeed_X = -200;
    float currentWindowRatio;
    float FPS_count = 0;
    
    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        float currentWindow_X = window.getSize().x;

        currentWindowRatio = window.getSize().x / window_X;

        player.setScale(playerScale * currentWindowRatio, playerScale * currentWindowRatio);
        laser.setScale(laserScale * currentWindowRatio, laserScale * currentWindowRatio);
        
        heart.setScale((window.getSize().x / 2500.0), (window.getSize().x / 2500.0));
        float lives_X = heart.getPosition().x + heart.getGlobalBounds().width + 20;
        float lives_Y = heart.getPosition().y + (heart.getGlobalBounds().height / 6);
        lives.setPosition(lives_X, lives_Y);
        lives.setCharacterSize(window.getSize().x / 35.0);
        playerScoreText.setCharacterSize(window.getSize().x / 35.0);
        gameoverFrame.setScale(currentWindow_X / 1500, currentWindow_X / 1500);

        FPSStart = FPSClock.getElapsedTime();
        if (FPSStart < FPSTimeConstraint) {
            FPS_count++;
        } else {
            FPS_count = 0;
            FPSStart = FPSClock.restart();
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::R)) {
            if (isGameOver) {
                player.setLives(playerLives);
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

        playerMax_X = window_X - player.getWidth();
        playerMax_Y = window_Y - player.getHeight();
        enemyMax_Y = window_Y - enemy.getHeight();

        if (player.getPosition().y == playerMax_Y) {
            player.setSpeed_Y(playerInitialSpeed_Y);
        }

        float playerEnemyDistance = abs(player.getPosition().x - enemy.getPosition().x);
        float jumpVolume = 100 - (playerEnemyDistance / 32);
        
        if (enemy.getPosition().y > enemyMax_Y) {
            enemy.setSpeed_Y(playerInitialSpeed_Y);
            jumpSound.setVolume(jumpVolume);
            jumpSound.play();
        }

        playerBox.setPosition(player.getPosition());
        playerBox.setSize(sf::Vector2f(player.getWidth(), player.getHeight()));

        deltaTime = deltaClock.restart().asSeconds();

        FPS_to_text(jumpSound.getVolume());

        if (!isGameOver) {
            if (isPowerUp) {
                laserScale += (playerScaleIncreaseFactor * currentWindowRatio * deltaTime) * 1.6;
                playerScale += playerScaleIncreaseFactor * currentWindowRatio * deltaTime;
            }

            // Player textures
            if (isPlayerReverse) {
                elapsedTimeSinceShot = laserClock.getElapsedTime();
                Time laserCooldownHalf = seconds(laserCooldown.asSeconds() / 2);
                if (isShooting && elapsedTimeSinceShot < laserCooldownHalf) {
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
                elapsedTimeSinceShot = laserClock.getElapsedTime();
                Time laserCooldownHalf = seconds(laserCooldown.asSeconds() / 2);                
                if (isShooting && elapsedTimeSinceShot < laserCooldownHalf) {
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

            // Enemy textures
            if (player.getPosition().x < enemy.getPosition().x) {
                enemy.setTexture(Textures::enemy);
            } else {
                enemy.setTexture(Textures::enemy_reverse);
            }

            // Laser textures
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

            // Gravity Player
            if (!isPlayerJumping && player.getPosition().y < playerMax_Y) {
                player.accelerate(0, 1, 1, deltaTime);
            }

            // Gravity Enemy
            if (!isEnemyJumping && enemy.getPosition().y < enemyMax_Y) {
                enemy.accelerate(0, 1, 1, deltaTime);
            } else {
                isEnemyJumping = enemy.jump(deltaTime, 4000);
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
                jumpSound.play();
                isPlayerJumping = true;
            }
            // Jumping
            if (isPlayerJumping) {
                isPlayerJumping = player.jump(deltaTime, playerInitialSpeed_Y);
            }

            // Shoot Laser
            if (Keyboard::isKeyPressed(Keyboard::Enter) && !isShooting && !isPowerUp) {
                elapsedTimeSinceShot = Time::Zero;
                float laserOrigin_X;
                float laserOrigin_Y;               
                if (isPlayerReverse) {
                    isLaserReverse = true;
                    laserOrigin_X = player.getPosition().x - player.getWidth() / 4; 
                    laserOrigin_Y = player.getPosition().y + player.getHeight() / 1.65;
                    laser.setPosition(Vector2f(laserOrigin_X, laserOrigin_Y));
                } else {
                    isLaserReverse = false;
                    laserOrigin_X = player.getPosition().x + player.getWidth() / 1.5; 
                    laserOrigin_Y = player.getPosition().y + player.getHeight() / 1.65;                    
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
                    laser.setPosition(-window_X, laser.getInitial_Y());
                }
                if (isLaserReverse) {
                    laser.move(-(laser.getSpeed_X() * deltaTime), 0);
                } else {
                    laser.move(laser.getSpeed_X() * deltaTime, 0);
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
                    enemy.setPosition(window_X - enemy.getWidth(), window_Y - enemy.getHeight());
                }
            }
        } else {
            if (gameoverFrame.getPosition().y < (window.getSize().y - gameoverFrame.getGlobalBounds().height) / 3) {
                gameoverFrame.move(0, 3);
                FloatRect frameRect = gameoverFrame.getGlobalBounds();
                gameover.setPosition(gameoverFrame.getPosition().x + 200, gameoverFrame.getPosition().y + 270);
            }
            window.draw(gameoverFrame);
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
        
        // Player <-> Enemy collision
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            if (hurt.getStatus() != Sound::Playing) {
                hurt.play();
            }
            player.setPosition(player.getInitial_X(), player.getInitial_Y());
            player.setLives(-1);
            enemy.setPosition(enemy.getInitial_X(), enemy.getInitial_Y());
            lives.setString(to_string(player.getLives()));
            background.setPosition(0, 0);

            if (player.getLives() == 0) {
                soundtrack.stop();
                soundtrackBig.stop();
                gameoverSound.play();
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

            if (player.getScale().x < 0.5 * currentWindowRatio) {
                if (playerScore % 3 == 0) {
                    isPowerUp = true;
                    powerUp.play();
                } else {
                    isPowerUp = false;
                }
            } else {
                laser.setSpeed_X(laserInitialSpeed_X * 2);
                isPlayerBig = true;
                laserCooldown = seconds(0.38);
                soundtrack.stop();
                if (soundtrackBig.getStatus() != Sound::Playing) {
                    soundtrackBig.play();
                }
            }
            playerScore++;
            playerScoreText.setString("SCORE " + to_string(playerScore));
            isExplosion = true;
            explosionClock.restart();
            enemySpawnClock.restart();
        }

        // Background movement
        if (player.isAlive()) {
            if (player.getPosition().x > playerMax_X - 1 && Keyboard::isKeyPressed(Keyboard::D) && 
                background.getPosition().x + background.getGlobalBounds().width > window_X) {
                background.move(-200 * deltaTime, 0);
                player.move(-(player.getSpeed_X() * 0.8) * deltaTime, 0);
                enemy.move(-200 * deltaTime, 0);
            } else if (player.getPosition().x == 0 && Keyboard::isKeyPressed(Keyboard::A) && background.getPosition().x < 0) {
                background.move(200 * deltaTime, 0);
                enemy.move(200 * deltaTime, 0);
            }
        }

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
        window.draw(playerScoreText);
        window.draw(FPS_Text);
        // window.draw(playerBox);

        window.display();
    }

    return 0;
}
