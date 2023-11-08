#ifndef PLAYER_ASSETS_H
#define PLAYER_ASSETS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

namespace PlayerAssets {
    
    namespace PlayerTextures {
        inline Texture player_normal;
        inline Texture player_reverse;
        inline Texture player_shooting;
        inline Texture player_shooting_reverse;
        inline Texture player_powerup;
        inline Texture player_reverse_powerup;
        inline Texture player_shooting_powerup;
        inline Texture player_shooting_reverse_powerup;
        inline Texture player_golden;
        inline Texture player_golden_reverse;
        inline Texture player_golden_shooting;
        inline Texture player_golden_shooting_reverse;
    }

    namespace PlayerSounds {
        inline SoundBuffer hurtBuffer;
        inline SoundBuffer jumpPlayerBuffer;
        inline SoundBuffer stompLightPlayerBuffer;
        inline SoundBuffer powerUpBuffer;
        inline SoundBuffer laserShootBuffer;
        inline SoundBuffer laserShootBigBuffer;
        inline Sound hurt;
        inline Sound jumpPlayer;
        inline Sound stompLightPlayer;
        inline Sound powerUp;
        inline Sound laserShoot;
        inline Sound laserShootBig;
    }

    namespace PlayerVariables {
        inline Time shootWait = seconds(0.25);
        inline Time elapsedTimeSinceShot = Time::Zero;

        inline float playerScaleIncreaseFactor = 0.03;
        inline float playerInitial_X = 10;
        inline float playerInitial_Y;
        inline float playerInitialScale = 0.25;
        inline float playerInitialSpeed_X = 600;
        inline float playerInitialSpeed_Y = -7;
        inline float playerAcceleration = 20;
        inline float playerMax_X;
        inline float playerMax_Y;

        inline bool isPlayerBig;
        inline bool isPlayerReverse;
        inline bool isPowerUp;
        inline bool isShotInstant;
        inline bool isPlayerShooting;

        inline float laserPlaceholder_X;
        inline float laserPlaceholderReverse_X;
        inline float laserPlaceholder_Y;
    }

    using namespace PlayerTextures;
    using namespace PlayerSounds;

    inline void loadPlayerTextures() {
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
    }

    inline void loadPlayerSounds() {
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
