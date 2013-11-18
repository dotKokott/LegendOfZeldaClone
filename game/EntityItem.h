#pragma once

#include "entity.h"

class EntityItem : public Entity {
	public:
		EntityItem(ENTITY_TYPE type, int posX, int posY);
		~EntityItem(void);	

		ENTITY_TYPE EntityType;

		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);
	private:
		bool mouseOver;

};

