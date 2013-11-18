
#include "Tile.h"


Tile::Tile(int xIndex, int yIndex, int graphicIndex, Surface* graphic) {    
	XIndex = xIndex;
	YIndex = yIndex;

    GraphicIndex = graphicIndex;
	Graphic = graphic;

	Blocks = false;
}


Tile::~Tile(void) {
}

SDL_Rect Tile::GetHitbox() { 
	SDL_Rect rect;
	rect.x = XIndex * 32;
    rect.y = YIndex * 32;
    rect.w = rect.h = 32;

	return rect;
}
