#include "surface.h"
#include "template.h"
#include "Helper.h"
#include "game.h"
#include "Scene.h"

#include "GameScene.h"
#include "Level.h"
#include "Room.h"

#include "Entity.h"

Entity::Entity(void) {
	Inited = false;

	Graphic = 0;
	CurrentAnimation = 0;
	
	SizeX = 26;
	SizeY = 26;

	Hidden = false;
	ZOrder = 0;

	Type = "";
	DrawHitbox = false;
}

Entity::~Entity(void) {	
}

void Entity::Draw(Surface* surface, float deltaTime) {
	if(CurrentAnimation != 0) {
		CurrentAnimation->Update(deltaTime);
		Graphic = CurrentAnimation->GetCurrentSurface();
	}

	if(!Hidden && Graphic != 0) {
		Graphic->AlphaCopyTo(surface, Position.x + DrawOffset.x, Position.y + DrawOffset.y);
	}

	if(DrawHitbox && strcmp(Type, "") != 0) {
		SDL_Rect box = GetHitbox();
		surface->Box(box.x, box.y, box.x + box.w, box.y + box.h, 0xFF0000);
	}
}

Entity* Entity::CollidesWith(char* type) {
	return Scene->Colliding(this, type);	
}

SDL_Rect Entity::GetHitbox() {
	SDL_Rect hitbox;

	hitbox.x = Position.x + Offset.x;
	hitbox.y = Position.y + Offset.y;
	hitbox.w = SizeX;
	hitbox.h = SizeY;

	return hitbox;
}

bool Entity::CompareByZOrder(const Entity* a, const Entity* b) {
	return a->ZOrder < b->ZOrder;
}

bool Entity::CollidesWithTiles(vector3 velocity) {
	SDL_Rect box = GetHitbox();
	
	int nextX, nextY = 0;    
	if(velocity.x < 0) {
		nextX = floor(box.x + velocity.x);
	} else {
		nextX = ceil(box.x + velocity.x);
	}

	if(velocity.y < 0) {
		nextY = floor(box.y + velocity.y - 96);
	} else {
		nextY = ceil(box.y + velocity.y - 96);
	}

	box.x = nextX;
	box.y = nextY;

	Room* room = ((GameScene*)Scene)->CurrentLevel->CurrentRoom();
	for(int x = 0; x < room->TileCountX; x++) {
		for(int y = 0; y < room->TileCountY; y++) {
			if(room->Map[x][y]->Blocks) {
				SDL_Rect inter;
				if(Helper::SDL_IntersectRect(&box, &room->Map[x][y]->GetHitbox(), &inter)) {
					return true;
				}
			}
		}
	}

	return false;    
}