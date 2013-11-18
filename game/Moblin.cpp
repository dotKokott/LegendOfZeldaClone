#include "Assets.h"
#include "Helper.h"
#include "Scene.h"
#include "PickupItem.h"

#include "Rupee.h"
#include "Moblin.h"

#define MOBLIN_SPEED 40

Moblin::Moblin(int posX, int posY) {
    Animations[ENTITY_DIRECTION_LEFT] = new Animation(*Assets::Animations["moblin_left"]);    
    Animations[ENTITY_DIRECTION_RIGHT] = new Animation(*Assets::Animations["moblin_right"]);
    Animations[ENTITY_DIRECTION_DOWN] = new Animation(*Assets::Animations["moblin_down"]);
    Animations[ENTITY_DIRECTION_UP] = new Animation(*Assets::Animations["moblin_up"]);    

    SizeX = SizeY = 32;

    Position.x = posX;
    Position.y = posY;

    Type = "enemy";

    Direction = ENTITY_DIRECTION_DOWN;

    ZOrder = 1;

    changeDirection();
}

Moblin::~Moblin(void) {
}

void Moblin::Update(float deltaTime) {
    CurrentAnimation = Animations[Direction];

    if(CollidesWith("bomb_explosion")) {
        Mix_PlayChannel(-1, Assets::Sounds["enemy_kill"], 0);
        Scene->RemoveEntity(this);

        int rnd = Helper::GetRandomInt(0, 5);
        if(rnd < 2) {
			Scene->AddEntity(new Rupee(Position.x, Position.y));
		} else if(rnd < 5) {
			Scene->AddEntity(new PickupItem(Position.x, Position.y, TypePickupBomb, false));
		}		
    }

    if(Helper::GetRandomInt(0, 500) == 0) changeDirection();    

    vector3 vel = Velocity * deltaTime;    
    vector3 pos = Position + vel;

    if(CollidesWithTiles(vel) || pos.x <= 0 || pos.x + SizeX >= SCRWIDTH || pos.y <= 96 || pos.y + SizeY >= SCRHEIGHT) {
        vector3 newPos;
		int tryCount = 15;
		do {
			changeDirection();
				
			newPos = pos + (Velocity * deltaTime);

			tryCount--;
			if(tryCount == 0) {
				break;
			}
		} while(CollidesWithTiles(Velocity * deltaTime) || newPos.x <= 0 || newPos.x + SizeX >= SCRWIDTH || newPos.y <= 96 || newPos.y + SizeY >= SCRHEIGHT);	
        vel.x = vel.y = 0;
    }

    Position = pos;
}

void Moblin::changeDirection() {
    int rnd = Helper::GetRandomInt(0, 4);

    ENTITY_DIRECTION dir = (ENTITY_DIRECTION)rnd;

    while(dir == Direction) {
        dir = (ENTITY_DIRECTION)Helper::GetRandomInt(0, 4);    
    }

    Direction = dir;

    Velocity.x = Velocity.y = 0;
    switch (Direction)
    {
        case ENTITY_DIRECTION_LEFT:
            Velocity.x = -MOBLIN_SPEED;

            break;
        case ENTITY_DIRECTION_RIGHT:
            Velocity.x = MOBLIN_SPEED;
            break;
        case ENTITY_DIRECTION_UP:
            Velocity.y = -MOBLIN_SPEED;
            break;
        case ENTITY_DIRECTION_DOWN:
            Velocity.y = MOBLIN_SPEED;
            break;
        default:
            break;
    }

    if(Helper::GetRandomInt(0, 3) == 0) {
        Velocity *= 2;
    }
}