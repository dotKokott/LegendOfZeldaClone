#pragma once
#include "template.h"

#include "SDL.h"

class Helper {
	public:
		static int GetRandomInt(int min, int max);
		static bool SDL_IntersectRect(const SDL_Rect *A, const SDL_Rect *B, SDL_Rect *intersection);

		static float DegreesToRadians(float degrees) { return degrees * (PI / 180); }

		static int Sign(float value) { return (value > 0) ? 1 : ((value < 0) ? -1 : 0) ; }
};