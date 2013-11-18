#include "Assets.h"
#include "Scene.h"

#include "Arrow.h"

#define ARROW_SPEED 400

Arrow::Arrow(int posX, int posY, ENTITY_DIRECTION direction) {
	Position.x = posX;
	Position.y = posY;

	Graphics[ENTITY_DIRECTION_LEFT] = Assets::Graphics["arrow_left"];
	Graphics[ENTITY_DIRECTION_RIGHT] = Assets::Graphics["arrow_right"];
	Graphics[ENTITY_DIRECTION_UP] = Assets::Graphics["arrow_up"];
	Graphics[ENTITY_DIRECTION_DOWN] = Assets::Graphics["arrow_down"];

	Direction = direction;

	SizeX = 10;
	SizeY = 32;

	switch (Direction)
	{
		case ENTITY_DIRECTION_LEFT:
			Velocity.x = -ARROW_SPEED;
			SizeX = 32;
			SizeY = 10;

			break;
		case ENTITY_DIRECTION_RIGHT:
			Velocity.x = ARROW_SPEED;
			SizeX = 32;
			SizeY = 10;

			break;
		case ENTITY_DIRECTION_UP:
			Velocity.y = -ARROW_SPEED;
			break;
		case ENTITY_DIRECTION_DOWN:
			Velocity.y = ARROW_SPEED;
			break;
		default:
			break;
	}

	Graphic = Graphics[Direction];

	DrawHitbox = true;

	Type = "arrow";
}

Arrow::~Arrow(void) {
}

void Arrow::Update(float deltaTime) {
	vector3 vel = Velocity * deltaTime;
	vector3 pos = Position + vel;	

	if(pos.x <= 0 || pos.x + SizeX >= SCRWIDTH || pos.y <= 96 || pos.y + SizeY >= SCRHEIGHT) {
		Scene->RemoveEntity(this);
	}

	Position = pos;
}