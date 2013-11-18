#include "Assets.h"
#include "Helper.h"
#include "Scene.h"

#include "Projectile.h"
#include "Rupee.h"
#include "PickupItem.h"

#include "Oktorok.h"

#define OKTOROK_SPEED 50

Oktorok::Oktorok(int posX, int posY) {
    Animations[ENTITY_DIRECTION_LEFT] = new Animation(*Assets::Animations["oktorok_left"]);    
    Animations[ENTITY_DIRECTION_RIGHT] = new Animation(*Assets::Animations["oktorok_right"]);
    Animations[ENTITY_DIRECTION_DOWN] = new Animation(*Assets::Animations["oktorok_down"]);
    Animations[ENTITY_DIRECTION_UP] = new Animation(*Assets::Animations["oktorok_up"]);    

    SizeX = SizeY = 32;

    Position.x = posX;
    Position.y = posY;

    Type = "enemy";

    Direction = ENTITY_DIRECTION_DOWN;

    ZOrder = 1;
}

Oktorok::~Oktorok(void) {
}

void Oktorok::Init() {
    Entity::Init();

    changeDirection();
}

void Oktorok::Update(float deltaTime) {
    CurrentAnimation = Animations[Direction];

	Entity* ar = CollidesWith("arrow");
    if(ar || CollidesWith("bomb_explosion") || CollidesWith("sword")) {
        Mix_PlayChannel(-1, Assets::Sounds["enemy_kill"], 0);
		Scene->RemoveEntity(ar);
        Scene->RemoveEntity(this);

        int rnd = Helper::GetRandomInt(0, 6);
        if(rnd < 3) {
			Scene->AddEntity(new Rupee(Position.x, Position.y));
		} else if(rnd < 4) {
			Scene->AddEntity(new PickupItem(Position.x, Position.y, TypePickupArrow, false));
		} else if(rnd < 6) {
			Scene->AddEntity(new PickupItem(Position.x, Position.y, TypePickupHeart, false));
		}
    }

    if(Helper::GetRandomInt(0, 500) == 0) changeDirection();
    if(Helper::GetRandomInt(0, 400) == 0) Shoot();

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

void Oktorok::Shoot() {
    Projectile* p = new Projectile(Position.x, Position.y, Velocity * 2, true);
    Scene->AddEntity(p);
}

void Oktorok::changeDirection() {
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
            Velocity.x = -OKTOROK_SPEED;

            break;
        case ENTITY_DIRECTION_RIGHT:
            Velocity.x = OKTOROK_SPEED;
            break;
        case ENTITY_DIRECTION_UP:
            Velocity.y = -OKTOROK_SPEED;
            break;
        case ENTITY_DIRECTION_DOWN:
            Velocity.y = OKTOROK_SPEED;
            break;
        default:
            break;
    }
}