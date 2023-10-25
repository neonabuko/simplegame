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
        Texture explosion25;
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
    }
    
    using namespace Textures;
    void loadTextures() {
        heart.loadFromFile("../src/assets/icon/heart.png");
        background.loadFromFile("../src/assets/icon/background.jpg");
        backgroundRed.loadFromFile("../src/assets/icon/backgroundRed.jpg");
        laserRed.loadFromFile("../src/assets/icon/laser.png");
        laserRed_reverse.loadFromFile("../src/assets/icon/laser_reverse.png");
        laserBlue.loadFromFile("../src/assets/icon/laserBlue.png");
        laserBlue_reverse.loadFromFile("../src/assets/icon/laserBlue_reverse.png");
        enemy.loadFromFile("../src/assets/icon/enemy.png");
        enemy_reverse.loadFromFile("../src/assets/icon/enemy_reverse.png");
        player.loadFromFile("../src/assets/icon/player.png");
        player_reverse.loadFromFile("../src/assets/icon/player_reverse.png");
        player_shooting.loadFromFile("../src/assets/icon/player_shooting.png");
        player_shooting_reverse.loadFromFile("../src/assets/icon/player_shooting_reverse.png");

        explosion1.loadFromFile("../src/assets/icon/explosion1.png");
        explosion2.loadFromFile("../src/assets/icon/explosion2.png");
        explosion3.loadFromFile("../src/assets/icon/explosion3.png");
        explosion4.loadFromFile("../src/assets/icon/explosion4.png");
        explosion5.loadFromFile("../src/assets/icon/explosion5.png");
        explosion6.loadFromFile("../src/assets/icon/explosion6.png");
        explosion7.loadFromFile("../src/assets/icon/explosion7.png");
        explosion8.loadFromFile("../src/assets/icon/explosion8.png");
        explosion9.loadFromFile("../src/assets/icon/explosion9.png");
        explosion10.loadFromFile("../src/assets/icon/explosion10.png");
        explosion11.loadFromFile("../src/assets/icon/explosion11.png");
        explosion12.loadFromFile("../src/assets/icon/explosion12.png");
        explosion13.loadFromFile("../src/assets/icon/explosion13.png");
        explosion14.loadFromFile("../src/assets/icon/explosion14.png");
        explosion15.loadFromFile("../src/assets/icon/explosion15.png");
        explosion16.loadFromFile("../src/assets/icon/explosion16.png");
        explosion17.loadFromFile("../src/assets/icon/explosion17.png");
        explosion18.loadFromFile("../src/assets/icon/explosion18.png");
        explosion19.loadFromFile("../src/assets/icon/explosion19.png");
        explosion20.loadFromFile("../src/assets/icon/explosion20.png");
        explosion21.loadFromFile("../src/assets/icon/explosion21.png");
        explosion22.loadFromFile("../src/assets/icon/explosion22.png");
        explosion23.loadFromFile("../src/assets/icon/explosion23.png");
        explosion24.loadFromFile("../src/assets/icon/explosion24.png");
        explosion25.loadFromFile("../src/assets/icon/explosion25.png");
    }

    using namespace Sounds;
    void loadSounds() {
        explosion.loadFromFile("../src/assets/sound/explosion.ogg");
        gameover.loadFromFile("../src/assets/sound/gameover.ogg");
        hurt.loadFromFile("../src/assets/sound/hurt.ogg");
        jump.loadFromFile("../src/assets/sound/jump.ogg");
        laserShoot.loadFromFile("../src/assets/sound/laserShoot.ogg");
        laserShootBig.loadFromFile("../src/assets/sound/laserShootBig.ogg");
        pop.loadFromFile("../src/assets/sound/pop.ogg");
        shrink_ray.loadFromFile("../src/assets/sound/shrink_ray.ogg");
        stomp.loadFromFile("../src/assets/sound/stomp.ogg");
    }
}
    