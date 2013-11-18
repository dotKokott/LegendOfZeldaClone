#pragma once

#include "entity.h"

class Tektite : public Entity {
    public:
        Tektite(int posX, int posY);
        ~Tektite(void);

        Animation* Normal;
        Animation* JumpAnimation;

        vector3 Velocity;

        void Update(float deltaTime);

        void Jump();
    private:
        bool jumping;
        vector3 from;
        vector3 target;
};