#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

namespace LaserAssets {
    namespace LaserTextures {
        Texture laserBlue;
        Texture laserBlue_reverse;
        Texture laserRed;
        Texture laserRed_reverse;
    }

    namespace LaserSounds {
        SoundBuffer laserShootBuffer;
        SoundBuffer laserShootBigBuffer;

        Sound laserShoot;
        Sound laserShootBig;        
    }

    namespace LaserVariables {
        Time laserCooldown = seconds(0.5);
        Time elapsedTimeSinceShot = Time::Zero;
        Clock laserClock;
        Time laserCooldownHalf;        
        float laserOrigin_X;
        float laserOrigin_Y;
        float laserInitialSpeed_X = 3000;
        float laserScale;
        float laserScaleOriginal;        
    }

    using namespace LaserTextures;
    void loadLaserAssets() {
        std::string iconPath = "../src/assets/icon/";

        laserBlue.loadFromFile(iconPath + "laserBlue.png");
        laserBlue_reverse.loadFromFile(iconPath + "laserBlue_reverse.png");
        laserRed.loadFromFile(iconPath + "laser.png");
        laserRed_reverse.loadFromFile(iconPath + "laser_reverse.png");

        // std::string soundPath = "../src/assets/sound/";        

        // laserShootBuffer.loadFromFile(soundPath + "laserShoot.ogg");
        // laserShootBigBuffer.loadFromFile(soundPath + "laserShootBig.ogg");        

        // laserShoot = Sound(laserShootBuffer);
        // laserShootBig = Sound(laserShootBigBuffer);
    }
}