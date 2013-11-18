#pragma once

#include "Level.h"

#include "Scene.h"

class Player;

class GameScene : public Scene {
	public:
		GameScene(void);
		~GameScene(void);

		Level* LastLevel;

		Level* CurrentLevel;
        Player* Player;

        bool SwitchRoom;

		void Init();
		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);

		void RemoveEntity(Entity* entity);

        void LoadCurrentRoom();
		void LoadCurrentLevel();

		void SwitchLevel(std::string name);
    private:
        void loadCurrentRoom();		
};