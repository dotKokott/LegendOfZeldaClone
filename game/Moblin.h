#pragma once

#include <map>

#include "entity.h"

class Moblin : public Entity {
    public:
        Moblin(int posX, int posY);
        ~Moblin(void);

        std::map<ENTITY_DIRECTION, Animation*> Animations;

        vector3 Velocity;

        ENTITY_DIRECTION Direction;

        void Update(float deltaTime);
    private:
        void changeDirection();
};

