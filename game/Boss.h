#pragma once
#include "entity.h"
class Boss : public Entity {
	public:
		Boss(int posX, int posY);
		~Boss(void);

		int BombHealth;
		int ArrowHealth;
		int SwordHealth;

		void Update(float deltaTime);
	private:
		bool hurt;
		float blinkTime;
		float blinkTimer;

		float shootTime;
		float shootTimer;
};

