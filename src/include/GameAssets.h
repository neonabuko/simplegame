#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"
#include "Enemy.h"
#include "PlayerAssets.h"
#include "EnemyAssets.h"
#include "CollisionDetection.h"
#include "LaserAssets.h"
#include <random>

using namespace sf;
using namespace std;
using namespace PlayerAssets;
using namespace LaserAssets;
using namespace EnemyAssets;

namespace GameAssets {

    namespace GameVariables {
        inline float window_X;
        inline float window_Y;
        inline RenderWindow window;
        inline float playerScorePosition_X;
        inline float playerScorePosition_Y;
        inline float gameover_X;
        inline float gameover_Y;
        inline float deltaTime;
        inline float currentWindowRatio;
        inline float FPS_count;
        inline float livesText_X;
        inline float livesText_Y;
        inline int playerScore;
        inline int currentFrame;
        inline bool isGameOver;
        inline bool isExplosion;
        inline float playerEnemyDistance;
        inline float enemySoundsVolume;
        inline float stompLightVolume;
        inline Vector2u backgroundTextureSize;
    }

    namespace PlayerControls {
        inline bool isKey_A_pressed;
        inline bool isKey_D_pressed;
        inline bool isKey_Space_pressed;
        inline bool isKey_M_pressed;
        inline bool isKey_Enter_pressed;
        inline bool isKey_Escape_pressed;
        inline bool isKey_M_released;
    }

    namespace GameTime {
        inline Time explosionDuration = seconds(0.6);
        inline Time elapsedTimeSinceExplosion = Time::Zero;
        inline Time elapsedTimeSinceEnemyDied = Time::Zero;
        inline Time enemySpawnWait = seconds(1.2);
    }

    namespace GameTextures {
        inline Texture sound_on;
        inline Texture sound_off;
        inline Texture heart;
        inline Texture background;
        inline Texture backgroundRed;
        inline Texture enemy_normal;
        inline Texture enemy_reverse;

        inline vector<Texture> explosionTextures;
    }

    namespace GameSounds {
        inline SoundBuffer explosionBuffer;
        inline SoundBuffer gameoverBuffer;
        inline SoundBuffer jumpBuffer;
        inline SoundBuffer stompBuffer;
        inline SoundBuffer stompLightBuffer;
        inline Sound explosion;
        inline Sound gameover;
        inline Sound stomp;
        inline Sound jump;
        inline Sound stompLight;
        inline Music soundtrack;
        inline Music soundtrackBig;
    }

    namespace GameClocks {
        inline Clock deltaClock;
        inline Clock explosionClock;
        inline Clock enemySpawnClock;
    }

    namespace GameSprites {
        inline Sprite soundSprite;
        inline Sprite backgroundSprite;
        inline Sprite heartSprite;
        inline Sprite explosionSprite;
        inline RectangleShape windowBox;
    }

    namespace GameFonts {
        inline Font pixelFont;
    }

    namespace GameTexts {
        inline Text scoreText;
        inline Text livesText;
        inline Text gameoverText;
        inline Text debugText;
    }

    using namespace GameTextures;
    using namespace GameTexts;
    using namespace GameSprites;
    using namespace GameVariables;
    using namespace GameFonts;
    using namespace GameSounds;
    using namespace PlayerControls;
    
    inline void updateKeyboard() {
        isKey_A_pressed = Keyboard::isKeyPressed(Keyboard::A);
        isKey_D_pressed = Keyboard::isKeyPressed(Keyboard::D);
        isKey_Space_pressed = Keyboard::isKeyPressed(Keyboard::Space);
        isKey_M_pressed = Keyboard::isKeyPressed(Keyboard::M);
        isKey_Enter_pressed = Keyboard::isKeyPressed(Keyboard::Enter);
        isKey_Escape_pressed = Keyboard::isKeyPressed(Keyboard::Escape);
    }

    inline void updateGameCommands() {
        Event event{};
        while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

        if (isKey_Escape_pressed) window.close();

        if (isKey_M_pressed) {
            if (isKey_M_released) {
                soundtrack.getVolume() > 0 ? soundtrack.setVolume(0) : soundtrack.setVolume(100);
                soundtrack.getVolume() > 0 ? soundSprite.setTexture(sound_on) : soundSprite.setTexture(sound_off);
                isKey_M_released = false;
            }
        } else {
            isKey_M_released = true;
        }
    }

    inline void loadSprites() {
        window_X = 1600;
        window_Y = 900;
        window.create(VideoMode(window_X, window_Y), "Simple Game");
        window.setFramerateLimit(300);

        soundSprite.setTexture(sound_on);
        backgroundSprite.setTexture(background);
        heartSprite.setTexture(heart);
        backgroundTextureSize = background.getSize();
        windowBox.setScale(Vector2f(backgroundTextureSize.x, backgroundTextureSize.y));

        soundSprite.setScale(0.8, 0.8);
        backgroundSprite.setScale(1, (window_Y / backgroundSprite.getTexture()->getSize().y));
        heartSprite.setScale(0.35, 0.35);
        explosionSprite.setScale(1.5, 1.5);
    }

    inline void loadTexts() {
        pixelFont.loadFromFile("../src/assets/font/SpaceMono-Regular.ttf");
        playerScore = 0;
        playerLives = 5;
        string pointsToString = to_string(playerScore);
        string livesToString = to_string(playerLives);

        scoreText.setString("SCORE " + pointsToString);
        scoreText.setFont(pixelFont);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(Color::White);
        scoreText.setOutlineColor(Color::Black);
        scoreText.setOutlineThickness(2.2);

        livesText.setString(livesToString);
        livesText.setFont(pixelFont);
        livesText.setCharacterSize(30);
        livesText.setFillColor(Color::White);
        livesText.setOutlineColor(Color::Black);
        livesText.setOutlineThickness(2);

        gameoverText.setString("\t  GAME OVER\nPress ENTER to restart");
        gameoverText.setFont(pixelFont);
        gameoverText.setCharacterSize(50);
        gameoverText.setFillColor(Color::White);
        gameoverText.setOutlineColor(Color::Black);
        gameoverText.setOutlineThickness(2);

        debugText.setFont(pixelFont);
        debugText.setOutlineThickness(2.5);

        gameover_X = (window_X - gameoverText.getLocalBounds().width) / 2;
        gameover_Y = (window_Y - gameoverText.getLocalBounds().height) / 2;

        playerScorePosition_X = window_X / 2.2;
        playerScorePosition_Y = window_Y / 800;
    }

    inline void loadTextures() {
        string iconPath = "../src/assets/icon/";

        sound_on.loadFromFile(iconPath + "sound_on.png");
        sound_off.loadFromFile(iconPath + "sound_off.png");
        heart.loadFromFile(iconPath + "heart.png");

        background.loadFromFile(iconPath + "background.jpg");
        backgroundRed.loadFromFile(iconPath + "backgroundRed.jpg");

        enemy_normal.loadFromFile(iconPath + "enemy.png");
        enemy_reverse.loadFromFile(iconPath + "enemy_reverse.png");

        for (int i = 1; i <= 24; ++i) {
            string texturePath = "../src/assets/icon/explosion" + to_string(i) + ".png";
            Texture texture;
            texture.loadFromFile(texturePath);
            explosionTextures.push_back(texture);
        }
    }

    inline void loadSounds() {
        string soundPath = "../src/assets/sound/";

        explosionBuffer.loadFromFile(soundPath + "explosion.ogg");
        gameoverBuffer.loadFromFile(soundPath + "gameover.ogg");

        jumpBuffer.loadFromFile(soundPath + "jump.ogg");
        stompBuffer.loadFromFile(soundPath + "stomp.ogg");
        stompLightBuffer.loadFromFile(soundPath + "stompLight.ogg");

        explosion = Sound(explosionBuffer);
        gameover  = Sound(gameoverBuffer);

        jump = Sound(jumpBuffer);
        stomp = Sound(stompBuffer);
        stompLight = Sound(stompLightBuffer);

        soundtrack.openFromFile("../src/assets/sound/soundtrack.ogg");
        soundtrackBig.openFromFile("../src/assets/sound/soundtrackBig.ogg");

        soundtrack.setVolume(100);
        soundtrack.play();
        soundtrack.setLoop(true);

        soundtrackBig.setVolume(100);
        soundtrackBig.setLoop(true);
    }

    using namespace GameClocks;
    inline void updateSprites() {
        currentWindowRatio = window_X / 1600;

        livesText_X = heartSprite.getPosition().x + heartSprite.getGlobalBounds().width + 20;

        soundSprite.setPosition(window_X / 1.6, 20);
        heartSprite.setPosition((window_X / 3), 20);
        livesText.setPosition(livesText_X, 20);
        scoreText.setPosition(playerScorePosition_X, 20);
        windowBox.setPosition(backgroundSprite.getPosition().x, backgroundSprite.getPosition().y);
        debugText.setPosition(window_X / 1.4, 20);

        livesText.setCharacterSize(35);
        scoreText.setCharacterSize(35);
        debugText.setCharacterSize(32);

        deltaTime = deltaClock.restart().asSeconds();

        window.clear();
        window.draw(backgroundSprite);
        window.draw(soundSprite);
        window.draw(heartSprite);
        window.draw(livesText);
        window.draw(scoreText);
        window.draw(debugText);
        window.draw(laser);

        for (Enemy& enemy : enemies) {
            if (getCollision(player, enemy)) onCollision_PlayerEnemy(player, enemy);
            if (getCollision(laser, enemy))  onCollision_LaserEnemy(laser, enemy);

            window.draw(enemy);
        }

        if (isExplosion) onExplosion();

        if (isGameOver) {
            gameoverText.setPosition(gameover_X, gameover_Y);
            window.draw(gameoverText);
            if (isKey_Enter_pressed) player.resetGame();
        }
    }

    inline void updateSounds() {
        for (Enemy& enemy : enemies) {
            playerEnemyDistance = abs(player.getPosition().x - enemy.getPosition().x);
            enemySoundsVolume = 114.0 * std::exp(-0.0008 * (playerEnemyDistance));
            if (enemySoundsVolume > 100) enemySoundsVolume = 100;
            stompLight.setVolume(enemySoundsVolume);

            if (enemy.getPosition().y > enemyMax_Y / 1.01 && enemy.getPosition().y < enemyMax_Y) {
                stompLight.play();
            }
        }

        if (isKey_Space_pressed) if (!player.getIsJumping()) jumpPlayer.play();

        if (isPowerUp) if (powerUp.getStatus() != 2) powerUp.play();

        if (isPlayerBig) {
            if (soundtrack.getStatus() == 2) soundtrack.stop();
            if (soundtrackBig.getStatus() != 2) soundtrackBig.play();
        }
    }

    inline void loadGameAssets() {
        loadTextures();
        loadSounds();
        loadSprites();
        loadTexts();
        loadPlayerAssets();
        loadLaserAssets();
        loadEnemyAssets();
    }

    inline void displayDebugText(float argument) {
        debugText.setString(to_string(argument));
    }
}

#endif