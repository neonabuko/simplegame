#ifndef LASER_ASSETS_H
#define LASER_ASSETS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

namespace LaserAssets {
    namespace LaserTextures {
        inline Texture laserBlue;
        inline Texture laserBlue_reverse;
        inline Texture laserRed;
        inline Texture laserRed_reverse;
    }

    namespace LaserSounds {
        inline SoundBuffer laserShootBuffer;
        inline SoundBuffer laserShootBigBuffer;
        inline Sound laserShoot;
        inline Sound laserShootBig;        
    }

    namespace LaserVariables {
        inline Time laserCooldown = seconds(0.5);
        inline Clock laserClock;
        inline Time laserCooldownHalf;

        inline float laserOrigin_X = -1600;
        inline float laserOrigin_Y = -900;
        inline float laserOriginalSpeed_X = 3000;
        inline float laserAcceleration = 20;
        inline float laserScale = 0.2;
        inline float laserScaleOriginal = 0.25;
        inline float laserScaleIncreaseFactor = 0.03;
    }

    using namespace LaserTextures;
    inline void loadLaserAssets() {
        std::string iconPath = "../src/assets/icon/";

        laserBlue.loadFromFile(iconPath + "laserBlue.png");
        laserBlue_reverse.loadFromFile(iconPath + "laserBlue_reverse.png");
        laserRed.loadFromFile(iconPath + "laser.png");
        laserRed_reverse.loadFromFile(iconPath + "laser_reverse.png");
    }
}

#endif