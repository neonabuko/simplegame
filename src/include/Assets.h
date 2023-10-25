#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Assets {
    namespace Textures {
        sf::Texture background;
        sf::Texture backgroundRed;
        sf::Texture enemy;
        sf::Texture enemy_reverse;
        sf::Texture heart;
        sf::Texture laserRed;
        sf::Texture laserRed_reverse;
        sf::Texture laserBlue;
        sf::Texture laserBlue_reverse;
        sf::Texture player;
        sf::Texture player_reverse;
        sf::Texture explosion1;
        sf::Texture explosion2;
        sf::Texture explosion3;
        sf::Texture explosion4;
        sf::Texture explosion5;
        sf::Texture explosion6;
        sf::Texture explosion7;
        sf::Texture explosion8;
        sf::Texture explosion9;
        sf::Texture explosion10;
        sf::Texture explosion11;
        sf::Texture explosion12;
        sf::Texture explosion13;
        sf::Texture explosion14;
        sf::Texture explosion15;
        sf::Texture explosion16;
        sf::Texture explosion17;
        sf::Texture explosion18;
        sf::Texture explosion19;
        sf::Texture explosion20;
        sf::Texture explosion21;
        sf::Texture explosion22;
        sf::Texture explosion23;
        sf::Texture explosion24;
        sf::Texture explosion25;
    }

    namespace Sounds {
        sf::SoundBuffer explosion;
        sf::SoundBuffer gameover;
        sf::SoundBuffer hurt;
        sf::SoundBuffer jump;
        sf::SoundBuffer laserShoot;
        sf::SoundBuffer laserShootBig;
        sf::SoundBuffer pop;
        sf::SoundBuffer shrink_ray;
        sf::SoundBuffer stomp;
    }
    
    void loadTextures() {
        Textures::background.loadFromFile("../src/assets/icon/background.jpg");
        Textures::backgroundRed.loadFromFile("../src/assets/icon/backgroundRed.jpg");
        Textures::heart.loadFromFile("../src/assets/icon/heart.png");
        Textures::laserRed.loadFromFile("../src/assets/icon/laser.png");
        Textures::laserRed_reverse.loadFromFile("../src/assets/icon/laser_reverse.png");
        Textures::laserBlue.loadFromFile("../src/assets/icon/laserBlue.png");
        Textures::laserBlue_reverse.loadFromFile("../src/assets/icon/laserBlue_reverse.png");
        Textures::enemy.loadFromFile("../src/assets/icon/enemy.png");
        Textures::enemy_reverse.loadFromFile("../src/assets/icon/enemy_reverse.png");
        Textures::player.loadFromFile("../src/assets/icon/player.png");
        Textures::player_reverse.loadFromFile("../src/assets/icon/player_reverse.png");

        Textures::explosion1.loadFromFile("../src/assets/icon/explosion1.png");
        Textures::explosion2.loadFromFile("../src/assets/icon/explosion2.png");
        Textures::explosion3.loadFromFile("../src/assets/icon/explosion3.png");
        Textures::explosion4.loadFromFile("../src/assets/icon/explosion4.png");
        Textures::explosion5.loadFromFile("../src/assets/icon/explosion5.png");
        Textures::explosion6.loadFromFile("../src/assets/icon/explosion6.png");
        Textures::explosion7.loadFromFile("../src/assets/icon/explosion7.png");
        Textures::explosion8.loadFromFile("../src/assets/icon/explosion8.png");
        Textures::explosion9.loadFromFile("../src/assets/icon/explosion9.png");
        Textures::explosion10.loadFromFile("../src/assets/icon/explosion10.png");
        Textures::explosion11.loadFromFile("../src/assets/icon/explosion11.png");
        Textures::explosion12.loadFromFile("../src/assets/icon/explosion12.png");
        Textures::explosion13.loadFromFile("../src/assets/icon/explosion13.png");
        Textures::explosion14.loadFromFile("../src/assets/icon/explosion14.png");
        Textures::explosion15.loadFromFile("../src/assets/icon/explosion15.png");
        Textures::explosion16.loadFromFile("../src/assets/icon/explosion16.png");
        Textures::explosion17.loadFromFile("../src/assets/icon/explosion17.png");
        Textures::explosion18.loadFromFile("../src/assets/icon/explosion18.png");
        Textures::explosion19.loadFromFile("../src/assets/icon/explosion19.png");
        Textures::explosion20.loadFromFile("../src/assets/icon/explosion20.png");
        Textures::explosion21.loadFromFile("../src/assets/icon/explosion21.png");
        Textures::explosion22.loadFromFile("../src/assets/icon/explosion22.png");
        Textures::explosion23.loadFromFile("../src/assets/icon/explosion23.png");
        Textures::explosion24.loadFromFile("../src/assets/icon/explosion24.png");
        Textures::explosion25.loadFromFile("../src/assets/icon/explosion25.png");
    }

    void loadSounds() {
        Sounds::explosion.loadFromFile("../src/assets/sound/explosion.ogg");
        Sounds::gameover.loadFromFile("../src/assets/sound/gameover.ogg");
        Sounds::hurt.loadFromFile("../src/assets/sound/hurt.ogg");
        Sounds::jump.loadFromFile("../src/assets/sound/jump.ogg");
        Sounds::laserShoot.loadFromFile("../src/assets/sound/laserShoot.ogg");
        Sounds::laserShootBig.loadFromFile("../src/assets/sound/laserShootBig.ogg");
        Sounds::pop.loadFromFile("../src/assets/sound/pop.ogg");
        Sounds::shrink_ray.loadFromFile("../src/assets/sound/shrink_ray.ogg");
        Sounds::stomp.loadFromFile("../src/assets/sound/stomp.ogg");
    }
}
    