#pragma once

#include <vector>

#include "Scene.h"

class SceneManager {
	public:
		SceneManager(void);
		~SceneManager(void);

		std::vector<Scene*> Scenes;

		Scene* GetTopScene() { return Scenes[Scenes.size() -1]; }

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);

		void SwitchScene(Scene* scene);

		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);    
		
		std::vector<Scene*> ToDeleteScenes;

		bool ExitGame;
	private:
		void freeScenes();
};