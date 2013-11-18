#pragma once
#include "entity.h"
class Zola : public Entity {
    public:
        Zola(int posX, int posY);
        ~Zola(void);

        bool Shooted;

        vector3 OriginalPosition;

        void Update(float deltaTime);
    private:
        void setRandomPosition();

        float waitForTime;
        float waitForTimer;
};

