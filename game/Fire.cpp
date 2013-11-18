#include "Assets.h"
#include "Fire.h"


Fire::Fire(int posX, int posY) {
	Position.x = posX;
	Position.y = posY;

	CurrentAnimation = new Animation(*Assets::Animations["fire"]);
}

Fire::~Fire(void){
}
