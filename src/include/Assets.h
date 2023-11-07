#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Laser.h"

#ifndef ASSETS_H
#define ASSETS_H

using namespace sf;
using namespace std;
namespace Assets {

    namespace Player {

        float window_X = 1600;
        float window_Y = 900;

        int playerScore = 0;
        float playerInitial_Y;
        float playerInitialScale = 0.25;
        float playerInitial_X = 10;
        int playerLives = 3;
        float playerInitialSpeed_X = 600;
        float playerInitialSpeed_Y = -7;
        float playerAcceleration = 20;
        float playerMax_X;
        float playerMax_Y;

        float deltaTime;
        float playerScaleIncreaseFactor = 0.03;
        float currentWindowRatio;
        float FPS_count;

        int currentFrame;
    }

    namespace Enemy {
        float enemyMax_X;
        float enemyMax_Y;
        double enemySpeed_X;
        double enemySpeed_Y;                
    }

    namespace TimeDef {
        Time FPSStart = Time::Zero;
        Time FPSTimeConstraint = seconds(1);
        Time explosionDuration = seconds(0.6);
        Time elapsedTimeSinceExplosion = Time::Zero;
        Time elapsedTimeSinceEnemyDied = Time::Zero;
        Time enemySpawnWait = seconds(1.2);        
    }

    namespace Textures {
        Texture heart;
        Texture frame;

        Texture background;
        Texture backgroundRed;

        Texture enemy_normal;
        Texture enemy_reverse;

        Texture explosion1;
        Texture explosion2;
        Texture explosion3;
        Texture explosion4;
        Texture explosion5;
        Texture explosion6;
        Texture explosion7;
        Texture explosion8;
        Texture explosion9;
        Texture explosion10;
        Texture explosion11;
        Texture explosion12;
        Texture explosion13;
        Texture explosion14;
        Texture explosion15;
        Texture explosion16;
        Texture explosion17;
        Texture explosion18;
        Texture explosion19;
        Texture explosion20;
        Texture explosion21;
        Texture explosion22;
        Texture explosion23;
        Texture explosion24;

        vector<Texture> explosionTextures;
    }

    namespace Sounds {
        SoundBuffer explosionBuffer;
        SoundBuffer gameoverBuffer;

        SoundBuffer jumpBuffer;
        SoundBuffer laserShootBuffer;
        SoundBuffer laserShootBigBuffer;
        SoundBuffer popBuffer;
        SoundBuffer shrink_rayBuffer;
        SoundBuffer stompBuffer;
        SoundBuffer stompLightBuffer;

        Sound explosion;
        Sound gameover;

        Sound stomp;
        Sound jump;
        Sound laserShoot;
        Sound laserShootBig;
        Sound pop;
        Sound shrink_ray;
        Sound stompLight;

        Music soundtrack;
        Music soundtrackBig;        
    }

    namespace Clocks {
        Clock randomSpeedClock;
        Clock deltaClock;
        Clock laserClock;
        Clock explosionClock;
        Clock enemySpawnClock;
        Clock FPSClock;        
    }
    
    namespace GameSprites {
        Sprite backgroundSprite;
        Vector2u backgroundTextureSize;
        RectangleShape windowBox;
        Sprite heartSprite;
        Sprite explosionSprite;
    }

    namespace Texts {
        Font pixelFont;
        Text scoreText;
        Text livesText;
        Sprite gameoverFrame(Textures::frame);
        Text gameoverText;
        Text FPS_Text;

        float playerScorePosition_X;
        float playerScorePosition_Y;
        float gameover_X;
        float gameover_Y;
        float livesText_X = GameSprites::heartSprite.getPosition().x + GameSprites::heartSprite.getGlobalBounds().width + 20;
        float livesText_Y = GameSprites::heartSprite.getPosition().y + (GameSprites::heartSprite.getGlobalBounds().height / 6);        
    }    

    using namespace Textures;
    using namespace std;
    using namespace Texts;
    using namespace GameSprites;

    void loadSprites() {
        backgroundSprite.setTexture(Textures::background);
        backgroundTextureSize = Textures::background.getSize();
        windowBox.setScale(Vector2f(backgroundTextureSize.x, backgroundTextureSize.y));
        heartSprite.setTexture(Textures::heart);
    }

    void loadTexts(float window_X, float window_Y) {
        pixelFont.loadFromFile("../src/assets/font/SpaceMono-Regular.ttf");

        string pointsToString = "0";
        string livesToString = "0";
        gameover_X = (window_X - gameoverText.getLocalBounds().width) / 2;
        gameover_Y = (window_Y - gameoverText.getLocalBounds().height) / 2;
        playerScorePosition_X = window_X / 2.2;
        playerScorePosition_Y = window_Y / 800;

        scoreText.setString("SCORE " + pointsToString);
        scoreText.setFont(pixelFont);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(Color::White);
        scoreText.setOutlineColor(Color::Black);
        scoreText.setOutlineThickness(2.2);

        livesText.setString(livesToString);
        livesText.setFont(pixelFont);
        livesText.setCharacterSize(window_X / 40);
        livesText.setFillColor(Color::White);
        livesText.setOutlineColor(Color::Black);
        livesText.setOutlineThickness(2);

        gameoverText.setString("\tGAME OVER\nPress R to restart");
        gameoverText.setFont(pixelFont);
        gameoverText.setCharacterSize(50 * (window_X / 40));
        gameoverText.setFillColor(Color::White);
        gameoverText.setOutlineColor(Color::Black);
        gameoverText.setOutlineThickness(2);

        FPS_Text.setFont(pixelFont);
        FPS_Text.setOutlineThickness(2.5);          
    }

    void loadTextures() {
        string iconPath = "../src/assets/icon/";

        heart.loadFromFile(iconPath + "heart.png");
        frame.loadFromFile(iconPath + "frame.png");

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

    using namespace Sounds;
    void loadSounds() {
        string soundPath = "../src/assets/sound/";

        explosionBuffer.loadFromFile(soundPath + "explosion.ogg");
        gameoverBuffer.loadFromFile(soundPath + "gameover.ogg");

        jumpBuffer.loadFromFile(soundPath + "jump.ogg");
        laserShootBuffer.loadFromFile(soundPath + "laserShoot.ogg");
        laserShootBigBuffer.loadFromFile(soundPath + "laserShootBig.ogg");
        popBuffer.loadFromFile(soundPath + "pop.ogg");
        shrink_rayBuffer.loadFromFile(soundPath + "shrink_ray.ogg");
        stompBuffer.loadFromFile(soundPath + "stomp.ogg");
        stompLightBuffer.loadFromFile(soundPath + "stompLight.ogg");

        explosion = Sound(explosionBuffer);
        gameover  = Sound(gameoverBuffer);

        jump = Sound(jumpBuffer);
        laserShoot = Sound(laserShootBuffer);
        laserShootBig = Sound(laserShootBigBuffer);
        pop = Sound(popBuffer);
        shrink_ray = Sound(shrink_rayBuffer);
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

    using namespace Player;
    void setSprites(float window_X, float window_Y) {
        playerInitial_Y = window_Y;
        livesText_X = heartSprite.getPosition().x + heartSprite.getGlobalBounds().width * 1.3;

        heartSprite.setPosition((window_X / 4), window_Y / 800);
        livesText.setPosition(livesText_X, livesText_Y);
        scoreText.setPosition(playerScorePosition_X, playerScorePosition_Y);
        windowBox.setPosition(backgroundSprite.getPosition().x, backgroundSprite.getPosition().y);
        FPS_Text.setPosition(window_X / 1.55, 10);

        livesText.setCharacterSize(window_X / 35.0);
        scoreText.setCharacterSize(window_X / 30.0);
        FPS_Text.setCharacterSize(window_X / 37.0);

        gameoverFrame.setScale(window_X / 1500, window_X / 1500);
        backgroundSprite.setScale(1, (window_Y / backgroundSprite.getTexture()->getSize().y));
        heartSprite.setScale((window_X / 2800.0), (window_X / 2800.0));
        explosionSprite.setScale(1.5, 1.5);
    }
}

#endif