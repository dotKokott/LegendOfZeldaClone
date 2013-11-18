#include "Input.h"
#include "MenuItem.h"

MenuItem::MenuItem(int posX, int posY, std::string text) {
	Position.x = posX;
	Position.y = posY;

	Text = text;

	Selected = false;
	Clicked = false;
}

MenuItem::~MenuItem(void) {
}

void MenuItem::Update(float deltaTime) {
	Clicked = Selected && Input::IsKeyJustPressed(SDLK_RETURN);	
}

void MenuItem::Draw(Surface* screen, float deltaTime) {
	if(Selected) {
		screen->Print("---o", Position.x - 30, Position.y, 0xFFFFFF);
	}
	screen->Print(&Text[0], Position.x, Position.y, 0xFFFFFF);
}