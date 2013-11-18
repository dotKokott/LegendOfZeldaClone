#pragma once
#include "entity.h"
class LevelTrigger : public Entity {
	public:
		LevelTrigger(int posX, int posY);
		~LevelTrigger(void);

		void Init();
		void Update(float deltaTime);
};

