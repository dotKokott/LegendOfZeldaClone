#pragma once
#include "entity.h"
class Sword : public Entity {
    public:
        Sword(int posX, int posY);
        ~Sword(void);

        void Update(float deltaTime);
    private:
        int frameCount;

};

