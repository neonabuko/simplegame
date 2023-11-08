#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"
#include "Enemy.h"
#include "PlayerAssets.h"

#ifndef ASSETS_H
#define ASSETS_H

using namespace sf;
using namespace std;
namespace GameAssets {

    namespace GameVariables {
        inline float window_X = 1600;
        inline float window_Y = 900;
        inline RenderWindow window(VideoMode((int) window_X, (int) window_Y), "Simple Game");
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

    namespace EnemyVariables {
        inline vector<Enemy> enemies;
        inline Vector2f enemyInitialPosition;
        inline float enemyMax_X;
        inline float enemyMax_Y;
        inline float enemySpeed_X;
        inline float enemySpeed_Y;
        inline float enemyInitial_X;
        inline float enemyInitial_Y;
    }

    namespace GameTime {
        inline Time explosionDuration = seconds(0.6);
        inline Time elapsedTimeSinceExplosion = Time::Zero;
        inline Time elapsedTimeSinceEnemyDied = Time::Zero;
        inline Time enemySpawnWait = seconds(1.2);
    }

    namespace Textures {
        inline Texture heart;
        inline Texture background;
        inline Texture backgroundRed;
        inline Texture enemy_normal;
        inline Texture enemy_reverse;
        inline Texture explosion1;
        inline Texture explosion2;
        inline Texture explosion3;
        inline Texture explosion4;
        inline Texture explosion5;
        inline Texture explosion6;
        inline Texture explosion7;
        inline Texture explosion8;
        inline Texture explosion9;
        inline Texture explosion10;
        inline Texture explosion11;
        inline Texture explosion12;
        inline Texture explosion13;
        inline Texture explosion14;
        inline Texture explosion15;
        inline Texture explosion16;
        inline Texture explosion17;
        inline Texture explosion18;
        inline Texture explosion19;
        inline Texture explosion20;
        inline Texture explosion21;
        inline Texture explosion22;
        inline Texture explosion23;
        inline Texture explosion24;
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
        inline Sprite backgroundSprite;
        inline Vector2u backgroundTextureSize;
        inline RectangleShape windowBox;
        inline Sprite heartSprite;
        inline Sprite explosionSprite;
    }

    namespace Fonts {
        inline Font pixelFont;
    }

    namespace Texts {
        inline Text scoreText;
        inline Text livesText;
        inline Text gameoverText;
        inline Text debugText;
    }

    using namespace Textures;
    using namespace Texts;
    using namespace GameSprites;
    using namespace GameVariables;
    using namespace Fonts;
    using namespace GameSounds;
    using namespace PlayerControls;
    using namespace PlayerAssets::PlayerVariables;

    inline void updateKeyboard() {
        isKey_A_pressed = Keyboard::isKeyPressed(Keyboard::A);
        isKey_D_pressed = Keyboard::isKeyPressed(Keyboard::D);
        isKey_Space_pressed = Keyboard::isKeyPressed(Keyboard::Space);
        isKey_M_pressed = Keyboard::isKeyPressed(Keyboard::M);
        isKey_Enter_pressed = Keyboard::isKeyPressed(Keyboard::Enter);
        isKey_Escape_pressed = Keyboard::isKeyPressed(Keyboard::Escape);
    }

    inline void loadSprites() {
        backgroundSprite.setTexture(Textures::background);
        backgroundTextureSize = Textures::background.getSize();
        windowBox.setScale(Vector2f(backgroundTextureSize.x, backgroundTextureSize.y));
        heartSprite.setTexture(Textures::heart);
    }

    inline void loadTexts() {
        pixelFont.loadFromFile("../src/assets/font/SpaceMono-Regular.ttf");
        playerScore = 0;
        playerLives = 3;
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

        gameover_X = (window_X - gameoverText.getLocalBounds().width) / 2;
        gameover_Y = (window_Y - gameoverText.getLocalBounds().height) / 2;

        playerScorePosition_X = window_X / 2.2;
        playerScorePosition_Y = window_Y / 800;

        debugText.setFont(pixelFont);
        debugText.setOutlineThickness(2.5);
    }

    inline void loadTextures() {
        string iconPath = "../src/assets/icon/";

        heart.loadFromFile(iconPath + "heart.png");

        background.loadFromFile(iconPath + "background.jpg");
        backgroundRed.loadFromFile(iconPath + "backgroundRed.jpg");

        enemy_normal.loadFromFile(iconPath + "enemy.png");
        enemy_reverse.loadFromFile(iconPath + "enemy_reverse.png");

        explosion1.loadFromFile(iconPath + "explosion1.png");
        explosion2.loadFromFile(iconPath + "explosion2.png");
        explosion3.loadFromFile(iconPath + "explosion3.png");
        explosion4.loadFromFile(iconPath + "explosion4.png");
        explosion5.loadFromFile(iconPath + "explosion5.png");
        explosion6.loadFromFile(iconPath + "explosion6.png");
        explosion7.loadFromFile(iconPath + "explosion7.png");
        explosion8.loadFromFile(iconPath + "explosion8.png");
        explosion9.loadFromFile(iconPath + "explosion9.png");
        explosion10.loadFromFile(iconPath + "explosion10.png");
        explosion11.loadFromFile(iconPath + "explosion11.png");
        explosion12.loadFromFile(iconPath + "explosion12.png");
        explosion13.loadFromFile(iconPath + "explosion13.png");
        explosion14.loadFromFile(iconPath + "explosion14.png");
        explosion15.loadFromFile(iconPath + "explosion15.png");
        explosion16.loadFromFile(iconPath + "explosion16.png");
        explosion17.loadFromFile(iconPath + "explosion17.png");
        explosion18.loadFromFile(iconPath + "explosion18.png");
        explosion19.loadFromFile(iconPath + "explosion19.png");
        explosion20.loadFromFile(iconPath + "explosion20.png");
        explosion21.loadFromFile(iconPath + "explosion21.png");
        explosion22.loadFromFile(iconPath + "explosion22.png");
        explosion23.loadFromFile(iconPath + "explosion23.png");
        explosion24.loadFromFile(iconPath + "explosion24.png");

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

    inline void setSprites() {
        currentWindowRatio = window_X / 1600;

        livesText_X = heartSprite.getPosition().x + heartSprite.getGlobalBounds().width + 20;
        livesText_Y = heartSprite.getPosition().y + (heartSprite.getGlobalBounds().height / 6);

        heartSprite.setPosition((window_X / 4), window_Y / 800);
        livesText.setPosition(livesText_X, livesText_Y);
        scoreText.setPosition(playerScorePosition_X, playerScorePosition_Y);
        windowBox.setPosition(backgroundSprite.getPosition().x, backgroundSprite.getPosition().y);
        debugText.setPosition(window_X / 1.55, 10);

        livesText.setCharacterSize(window_X / 35.0);
        scoreText.setCharacterSize(window_X / 30.0);
        debugText.setCharacterSize(window_X / 37.0);

        backgroundSprite.setScale(1, (window_Y / backgroundSprite.getTexture()->getSize().y));
        heartSprite.setScale((window_X / 2800.0), (window_X / 2800.0));
        explosionSprite.setScale(1.5, 1.5);
    }
}

#endif