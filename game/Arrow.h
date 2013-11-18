#pragma once

#include <map>

#include "entity.h"

class Arrow : public Entity {
	public:
		Arrow(int posX, int posY, ENTITY_DIRECTION direction);
		~Arrow(void);

		std::map<ENTITY_DIRECTION, Surface*> Graphics;

		ENTITY_DIRECTION Direction;

		vector3 Velocity;

		void Update(float deltaTime);
};

