#include "Input.h"
#include "Helper.h"
#include "Assets.h"

#include "EditorScene.h"

#include "EntityItem.h"

EntityItem::EntityItem(ENTITY_TYPE type, int posX, int posY) {
	std::string name = "editor_" + std::to_string(type);

	Graphic = Assets::Graphics[name];
	EntityType = type;
	Position.x = posX;
	Position.y = posY;
	SizeX = Graphic->GetWidth();
	SizeY = Graphic->GetHeight();

	mouseOver = false;
}

EntityItem::~EntityItem(void) {
}

void EntityItem::Update(float deltaTime) {
	SDL_Rect mouseRect;
	mouseRect.x = Input::State->MouseX;
	mouseRect.y = Input::State->MouseY;
	mouseRect.w = mouseRect.h = 3;

	SDL_Rect inter;
	if(Helper::SDL_IntersectRect(&GetHitbox(), &mouseRect, &inter)) {		
		mouseOver = true;

		if(Input::IsMouseJustDown(MOUSE_LEFT)) {
			((EditorScene*)Scene)->CurrentItem = this;
		}
	} else {
		mouseOver = false;
	}
}

void EntityItem::Draw(Surface* screen, float deltaTime) {	
	Entity::Draw(screen, deltaTime);

	int color = mouseOver || ((EditorScene*)Scene)->CurrentItem == this ? 0x00FF00 : 0xFF0000;
	screen->Box(Position.x, Position.y, Position.x + Graphic->GetWidth(), Position.y + Graphic->GetHeight(), color);
}
