#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "Entity.h"
#include "Laser.h"

bool getCollision(Entity& entity_A, Entity& entity_B);

void onCollision_PlayerEnemy(Entity& entity_A, Entity& entity_B);

void onCollision_LaserEnemy(Laser& laser, Entity& enemy);

void onExplosion();

#endif