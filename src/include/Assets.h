#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
namespace Assets {
    namespace Textures {
        Texture heart;

        Texture background;
        Texture backgroundRed;

        Texture laserRed;
        Texture laserRed_reverse;
        Texture laserBlue;
        Texture laserBlue_reverse;

        Texture enemy;
        Texture enemy_reverse;

        Texture player;
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
    }

    namespace Sounds {
        SoundBuffer explosion;
        SoundBuffer gameover;
        SoundBuffer hurt;
        SoundBuffer jump;
        SoundBuffer laserShoot;
        SoundBuffer laserShootBig;
        SoundBuffer pop;
        SoundBuffer shrink_ray;
        SoundBuffer stomp;
        SoundBuffer powerUp;
    }
    
    using namespace Textures;
    using namespace std;

    void loadTextures() {
        string iconPath = "../src/assets/icon/";

        heart.loadFromFile(iconPath + "heart.png");

        background.loadFromFile(iconPath + "background.jpg");
        backgroundRed.loadFromFile(iconPath + "backgroundRed.jpg");

        laserRed.loadFromFile(iconPath + "laser.png");
        laserRed_reverse.loadFromFile(iconPath + "laser_reverse.png");
        laserBlue.loadFromFile(iconPath + "laserBlue.png");
        laserBlue_reverse.loadFromFile(iconPath + "laserBlue_reverse.png");

        enemy.loadFromFile(iconPath + "enemy.png");
        enemy_reverse.loadFromFile(iconPath + "enemy_reverse.png");

        player.loadFromFile(iconPath + "player.png");
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
    }

    using namespace Sounds;
    void loadSounds() {
        string soundPath = "../src/assets/sound/";

        explosion.loadFromFile(soundPath + "explosion.ogg");
        gameover.loadFromFile(soundPath + "gameover.ogg");
        hurt.loadFromFile(soundPath + "hurt.ogg");
        jump.loadFromFile(soundPath + "jump.ogg");
        laserShoot.loadFromFile(soundPath + "laserShoot.ogg");
        laserShootBig.loadFromFile(soundPath + "laserShootBig.ogg");
        pop.loadFromFile(soundPath + "pop.ogg");
        shrink_ray.loadFromFile(soundPath + "shrink_ray.ogg");
        stomp.loadFromFile(soundPath + "stomp.ogg");
        powerUp.loadFromFile(soundPath + "powerUp.ogg");
    }
}
