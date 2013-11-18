#pragma once

#include "Level.h"
#include "EntityItem.h"

#include "Scene.h"

class EditorScene :	public Scene {
	public:
		EditorScene(Level* level);
		~EditorScene(void);

		Level* CurrentLevel;
		
		EntityItem* CurrentItem;

		void Init();
		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);

		void SetBlockValueFor(int tileIndex, bool value);
};

