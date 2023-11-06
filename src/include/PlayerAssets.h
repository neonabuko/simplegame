#ifndef PLAYER_ASSETS_H
#define PLAYER_ASSETS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Laser.h"

using namespace sf;

namespace PlayerAssets {

    namespace PlayerTextures {
        Texture player_normal;
        Texture player_reverse;
        Texture player_shooting;
        Texture player_shooting_reverse;
        Texture player_powerup;
        Texture player_reverse_powerup;
        Texture player_shooting_powerup;
        Texture player_shooting_reverse_powerup;
        Texture player_golden;
        Texture player_golden_reverse;
        Texture player_golden_shooting;
        Texture player_golden_shooting_reverse;

        Texture laserBlue;
        Texture laserBlue_reverse;
        Texture laserRed;
        Texture laserRed_reverse;
    }

    namespace LaserDef {
        Laser laser(-1600, -900, 3000, 20);
    }

    namespace PlayerSounds {
        SoundBuffer hurtBuffer;
        SoundBuffer jumpPlayerBuffer;
        SoundBuffer stompLightPlayerBuffer;
        SoundBuffer powerUpBuffer;

        SoundBuffer laserShootBuffer;
        SoundBuffer laserShootBigBuffer;

        Sound hurt;
        Sound jumpPlayer;
        Sound stompLightPlayer;
        Sound powerUp;

        Sound laserShoot;
        Sound laserShootBig;
    }

    namespace Variables {
        Time laserCooldown = seconds(0.5);
        Time elapsedTimeSinceShot = Time::Zero;
        Clock laserClock;
        Time laserCooldownHalf;
        float playerScaleIncreaseFactor = 0.03;
        float playerInitialScale = 0.25;
        float laserOrigin_X;
        float laserOrigin_Y;
        float laserInitialSpeed_X = 3000;
        float laserScale;
        float laserScaleOriginal;
    }

    using namespace PlayerTextures;
    using namespace PlayerSounds;

    void loadPlayerTextures() {
        std::string iconPath = "../src/assets/icon/";

        player_normal.loadFromFile(iconPath + "player.png");
        player_reverse.loadFromFile(iconPath + "player_reverse.png");
        player_shooting.loadFromFile(iconPath + "player_shooting.png");
        player_shooting_reverse.loadFromFile(iconPath + "player_shooting_reverse.png");
        player_powerup.loadFromFile(iconPath + "player_powerup.png");
        player_reverse_powerup.loadFromFile(iconPath + "player_reverse_powerup.png");
        player_shooting_powerup.loadFromFile(iconPath + "player_shooting_powerup.png");
        player_shooting_reverse_powerup.loadFromFile(iconPath + "player_shooting_reverse_powerup.png");
        player_golden.loadFromFile(iconPath + "player_golden.png");
        player_golden_reverse.loadFromFile(iconPath + "player_golden_reverse.png");
        player_golden_shooting.loadFromFile(iconPath + "player_golden_shooting.png");
        player_golden_shooting_reverse.loadFromFile(iconPath + "player_golden_shooting_reverse.png");

        laserBlue.loadFromFile(iconPath + "laserBlue.png");
        laserBlue_reverse.loadFromFile(iconPath + "laserBlue_reverse.png");
        laserRed.loadFromFile(iconPath + "laser.png");
        laserRed_reverse.loadFromFile(iconPath + "laser_reverse.png");
    }

    void loadPlayerSounds() {
        std::string soundPath = "../src/assets/sound/";

        hurtBuffer.loadFromFile(soundPath + "hurt.ogg");
        jumpPlayerBuffer.loadFromFile(soundPath + "jumpPlayer.ogg");
        stompLightPlayerBuffer.loadFromFile(soundPath + "stompLightPlayer.ogg");
        powerUpBuffer.loadFromFile(soundPath + "powerUp.ogg");    

        laserShootBuffer.loadFromFile(soundPath + "laserShoot.ogg");
        laserShootBigBuffer.loadFromFile(soundPath + "laserShootBig.ogg");

        hurt = Sound(hurtBuffer);
        jumpPlayer = Sound(jumpPlayerBuffer);
        powerUp = Sound(powerUpBuffer);
        stompLightPlayer = Sound(stompLightPlayerBuffer);

        laserShoot = Sound(laserShootBuffer);
        laserShootBig = Sound(laserShootBigBuffer);
    }
}

#endif