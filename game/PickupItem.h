#pragma once
#include "entity.h"

class PickupItem : public Entity {
	public:
		PickupItem(int posX, int posY, ENTITY_TYPE type, bool costsOnPickup);
		~PickupItem(void);

		bool CostsOnPickup;
		ENTITY_TYPE EntityType;

		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);
};

