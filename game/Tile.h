#pragma once

#include "SDL.h"
#include "surface.h"

class Tile {
	public:
		Tile(int xIndex, int yIndex, int graphicIndex, Surface* graphic);
		~Tile(void);

        int GraphicIndex;
		int XIndex;
		int YIndex;

		Surface* Graphic;

		bool Blocks;

		SDL_Rect GetHitbox();
};