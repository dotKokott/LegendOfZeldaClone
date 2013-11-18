#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "template.h"
#include "surface.h"
#include "Animation.h"

class Scene;	

enum ENTITY_TYPE {
	None = 0,
	Collision = 1,
	TypePlayerStart = 2,
	TypeOctorokRed = 3,
	TypeTektite = 4,
    TypeMoblin = 5,
    TypeZola = 6,
	TypeTrigger = 7,
	TypePositionTrigger = 8,
	TypeRandomEnemies = 9,

	TypePickupSword = 10,	
	TypePickupBombs = 11,
	TypePickupBow = 12,
	
	TypePickupBomb = 13,
	TypePickupHeart = 14,
	TypePickupArrow = 15
};

enum ENTITY_DIRECTION {
	ENTITY_DIRECTION_LEFT = 0,
	ENTITY_DIRECTION_RIGHT = 1,
	ENTITY_DIRECTION_UP = 2,
	ENTITY_DIRECTION_DOWN = 3,
};

class Entity {
	public:
		Entity(void);
		~Entity(void);

		Surface* Graphic;
		Animation* CurrentAnimation;

		Scene* Scene;
		vector3 Position;

		int SizeX;
		int SizeY;
		
		vector3 Offset;
		vector3 DrawOffset;

		bool Hidden;
		int ZOrder;

		char* Type;			
		Entity* CollidesWith(char* type);
		bool CollidesWithTiles(vector3 velocity);
		bool DrawHitbox;


		//Init -> Entity gets added to the game
		bool Inited;
		virtual void Init() { Inited = true; };
		virtual void Update(float deltaTime) {};
		virtual void Draw(Surface* screen, float deltaTime);
		//Destroy -> Entity gets removed from the game
		virtual void Destroy() {};

		virtual SDL_Rect GetHitbox();

		static bool CompareByZOrder(const Entity* a, const Entity* b);
};