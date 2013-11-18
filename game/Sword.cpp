#include "Scene.h"

#include "Sword.h"


Sword::Sword(int posX, int posY) {
    Position.x = posX;
    Position.y = posY;

    SizeX = SizeY = 25;

    Type = "sword";

    frameCount = 0;

	DrawHitbox = false;
}


Sword::~Sword(void) {
}

void Sword::Update(float deltaTime) {
    frameCount++;
    if(frameCount > 10) {
        Scene->RemoveEntity(this);
    }
}
