#pragma once

#include "Entity.h"

class MenuItem : public Entity {
	public:
		MenuItem(int posX, int posY, std::string text);
		~MenuItem(void);

		bool Selected;
		bool Clicked;
		std::string Text;

		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);
};

