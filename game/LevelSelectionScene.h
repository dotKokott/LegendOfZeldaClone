#pragma once

#include <vector>
#include "MenuItem.h"

#include "scene.h"

class LevelSelectionScene : public Scene {
	public:
		LevelSelectionScene(void);
		~LevelSelectionScene(void);

		int SelectedMenuItem;
		std::vector<MenuItem*> MenuItems;

		void Init();
		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);
};