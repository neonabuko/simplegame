#ifndef LASER_ASSETS_H
#define LASER_ASSETS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"

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
        inline Time laserCooldown;
        inline Clock laserClock;
        inline Time laserCooldownHalf;

        inline float laserOrigin_X;
        inline float laserOrigin_Y;
        inline float laserOriginalSpeed_X;
        inline float laserAcceleration;
        inline float laserScale;
        inline float laserScaleOriginal;
        inline float laserScaleIncreaseFactor;

        inline Laser laser(laserOriginalSpeed_X, laserAcceleration);
    }

    using namespace LaserTextures;
    using namespace LaserVariables;
    inline void loadLaserAssets() {
        std::string iconPath = "../src/assets/icon/";

        laserBlue.loadFromFile(iconPath + "laserBlue.png");
        laserBlue_reverse.loadFromFile(iconPath + "laserBlue_reverse.png");
        laserRed.loadFromFile(iconPath + "laser.png");
        laserRed_reverse.loadFromFile(iconPath + "laser_reverse.png");

        laserCooldown = seconds(0.5);
        laserOrigin_X = -1600;
        laserOrigin_Y = -900;
        laserOriginalSpeed_X = 3000;
        laserAcceleration = 20;
        laserScale = 0.2;
        laserScaleOriginal = 0.25;
        laserScaleIncreaseFactor = 0.03;

        laser.setPosition(laserOrigin_X, laserOrigin_Y);
    }
}

#endif