#ifndef PLAYER_ASSETS_H
#define PLAYER_ASSETS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

namespace PlayerAssets {

    namespace Textures {
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
    }

    namespace Sounds {
        SoundBuffer hurtBuffer;
        SoundBuffer jumpPlayerBuffer;
        SoundBuffer stompLightPlayerBuffer;
        SoundBuffer powerUpBuffer;

        Sound explosion;
        Sound gameover;
        Sound hurt;
        Sound jumpPlayer;
        Sound stompLightPlayer;
        Sound powerUp;
    }

    namespace Variables {
        Time laserCooldown = seconds(0.3);
        Time elapsedTimeSinceShot = Time::Zero;
    }

    using namespace Textures;
    using namespace Sounds;

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
    }

    void loadPlayerSounds() {
        std::string soundPath = "../src/assets/sound/";

        hurtBuffer.loadFromFile(soundPath + "hurt.ogg");
        jumpPlayerBuffer.loadFromFile(soundPath + "jumpPlayer.ogg");
        stompLightPlayerBuffer.loadFromFile(soundPath + "stompLightPlayer.ogg");
        powerUpBuffer.loadFromFile(soundPath + "powerUp.ogg");    

        hurt = Sound(hurtBuffer);
        jumpPlayer = Sound(jumpPlayerBuffer);
        powerUp = Sound(powerUpBuffer);
        stompLightPlayer = Sound(stompLightPlayerBuffer);    
    }
}

#endif