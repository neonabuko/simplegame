#ifndef ENEMY_ASSETS_H
#define ENEMY_ASSETS_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"

using namespace std;
using namespace sf;
namespace EnemyAssets {

    namespace EnemyVariables {
        inline Enemy enemy;
        inline vector<Enemy> enemies;
        inline Vector2f enemyInitialPosition;
        inline int enemyLives;
        inline float enemyAcceleration;
        inline float enemyMax_X;
        inline float enemyMax_Y;
        inline float enemySpeed_X;
        inline float enemySpeed_Y;
        inline float enemyInitial_X;
        inline float enemyInitial_Y;
    }

    using namespace EnemyVariables;
    inline void loadEnemyAssets() {
        enemyLives = 1;
        enemyAcceleration = 20;
        enemy.load();

        for (int i = 0; i < 1; i++) {
            enemies.push_back(enemy);
        }

        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].setPosition(1600 + (i * 100), 0);
            enemies[i].setScale(0.5, 0.5);
        }        
    }
}

#endif