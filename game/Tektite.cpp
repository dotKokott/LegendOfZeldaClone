#include "Assets.h"
#include "Helper.h"
#include "Scene.h"
#include "Rupee.h"
#include "PickupItem.h"

#include "Tektite.h"

#define TAKTITE_SPEED 150

Tektite::Tektite(int posX, int posY) {
    Position.x = posX;
    Position.y = posY;

    Normal = new Animation(*Assets::Animations["tektite"]);    
    JumpAnimation = new Animation(*Assets::Animations["tektite_jump"]);

    CurrentAnimation = Normal;

    SizeX = SizeY = 28;
    Offset.x = Offset.y = 4;

    Type = "enemy";

    Jump();
}


Tektite::~Tektite(void) {
}

void Tektite::Update(float deltaTime) {
	Entity* ar = CollidesWith("arrow");
    if(ar || CollidesWith("bomb_explosion") || CollidesWith("sword")) {
        Mix_PlayChannel(-1, Assets::Sounds["enemy_kill"], 0);
		Scene->RemoveEntity(ar);
        Scene->RemoveEntity(this);

        int rnd = Helper::GetRandomInt(0, 5);
        if(rnd < 3) {
			Scene->AddEntity(new Rupee(Position.x, Position.y));
		} else if(rnd < 4) {
			Scene->AddEntity(new PickupItem(Position.x, Position.y, TypePickupArrow, false));
		} else if(rnd < 6) {
			Scene->AddEntity(new PickupItem(Position.x, Position.y, TypePickupHeart, false));
		}
    }

    if(Velocity.x == 0 && Velocity.y == 0 && Helper::GetRandomInt(0, 600) == 0) {
        Jump();
    }

    if(Velocity.x == 0 && Velocity.y == 0) {
        CurrentAnimation = Normal;
    } else {
        CurrentAnimation = JumpAnimation;
    }    

    if(target.x != 0 || target.y != 0) {
        Velocity.x = Position.x > target.x ? -TAKTITE_SPEED : TAKTITE_SPEED;

        if(abs(target.x - Position.x) < abs((target.x - from.x) / 2)) {
            Velocity.y = TAKTITE_SPEED;           
        } else {
            Velocity.y = -TAKTITE_SPEED;
        }        

        Position += Velocity * deltaTime;

        if(floor(target.x - Position.x) == 0 && floor(target.y - Position.y)) {
            Velocity.x = Velocity.y = 0;
            target.x = target.y = 0;
        }
    }
}

void Tektite::Jump() {
    from = Position;
    target.x = Helper::GetRandomInt(10, SCRWIDTH - 30);
    target.y = Helper::GetRandomInt(116, SCRHEIGHT - 30);    
}
