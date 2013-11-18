#include "GameScene.h"

#include "LevelTrigger.h"


LevelTrigger::LevelTrigger(int posX, int posY) {
	Position.x = posX;
	Position.y = posY;

	SizeX = SizeY = 32;

	Type = "trigger";
}


LevelTrigger::~LevelTrigger(void) {
}

void LevelTrigger::Init() {

}

void LevelTrigger::Update(float deltaTime) {
	if(CollidesWith("player")) {
		GameScene* scene = (GameScene*)Scene;

		int roomX = scene->CurrentLevel->CurrentRoomX;
		int roomY = scene->CurrentLevel->CurrentRoomY;

		if(roomX == 7 && roomY == 7) {
			scene->SwitchLevel("room 1");
			return;
		}

		if(roomX == 4 && roomY == 6) {
			scene->SwitchLevel("boss");
			return;
		}

		if(roomX == 6 && roomY == 6) {
			scene->SwitchLevel("shopkeeper");
			return;
		}


		scene->SwitchLevel("random");
	}
}
