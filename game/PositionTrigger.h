#pragma once

#include "entity.h"

class PositionTrigger : public Entity {
	public:
		PositionTrigger(int posX, int posY);
		~PositionTrigger(void);

		void Init();
};