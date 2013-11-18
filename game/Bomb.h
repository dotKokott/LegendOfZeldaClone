#pragma once

#include <vector>

#include "entity.h"

class Bomb : public Entity {
    public:
        Bomb(int posX, int posY, bool exploding);
        ~Bomb(void);

        bool Exploding;

		Animation* ExplodeAnimation;

        void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);
    private:
        bool detonated;

        float bombTime;
        float bombTimer;

        float stayTime;
        float stayTimer;

		std::vector<vector3> explosionPositions;
};

