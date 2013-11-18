#pragma once
#include "entity.h"
class Projectile : public Entity {
public:
    Projectile(int posX, int posY, vector3 velocity, bool collidesWithTiles);
    Projectile(int posX, int posY, Entity* target, bool collidesWithTiles);
    ~Projectile(void);

    bool CollidesTiles;

    vector3 Velocity;

    void Update(float deltaTime);
};

