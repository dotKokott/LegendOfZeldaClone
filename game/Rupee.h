#pragma once
#include "entity.h"
class Rupee : public Entity {
    public:
        Rupee(int posX, int posY);
        ~Rupee(void);

        void Update(float deltaTime);
};

