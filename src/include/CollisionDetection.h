#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "Entity.h"
#include "Laser.h"

bool getCollision(Entity& entity_A, Entity& entity_B);

void onPlayerEnemyCollision(Entity& entity_A, Entity& entity_B);

void onLaserEnemyCollision(Laser& laser, Entity& enemy);

#endif