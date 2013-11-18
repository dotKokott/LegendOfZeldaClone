#pragma once
#include <map>

#include "entity.h"

class Oktorok : public Entity {
    public:
        Oktorok(int posX, int posY);
        ~Oktorok(void);

        std::map<ENTITY_DIRECTION, Animation*> Animations;

        vector3 Velocity;

        ENTITY_DIRECTION Direction;

        void Init();
        void Update(float deltaTime);

        void Shoot();
    private:
        void changeDirection();

};

