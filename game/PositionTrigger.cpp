#include "GameScene.h"
#include "Player.h"

#include "PositionTrigger.h"


PositionTrigger::PositionTrigger(int posX, int posY) {
	Position.x = posX;
	Position.y = posY;
}

PositionTrigger::~PositionTrigger(void) {
}

void PositionTrigger::Init() {
	((GameScene*)Scene)->Player->Position = Position;
}