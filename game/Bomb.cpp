#include "Helper.h"
#include "Assets.h"
#include "Scene.h"
#include "Player.h"

#include "Bomb.h"

Bomb::Bomb(int posX, int posY, bool exploding) {
    Graphic = Assets::Graphics["bomb"];
    
    Position.x = posX;
    Position.y = posY;

    Exploding = exploding;
	ExplodeAnimation = new Animation(*Assets::Animations["bomb_explode"]);

    if(Exploding) {
        SizeX = 64;
        SizeY = 64;

        Offset.x = -30;
        Offset.y = -25;

        bombTime = 2;
        bombTimer = 0;

        detonated = false;

        stayTime = 1.2f;
        stayTimer = 0;        
    } else {
        SizeX = 8;
        SizeY = 12;
        Type = "bomb";
    }
}

Bomb::~Bomb(void) {
}

void Bomb::Update(float deltaTime) {
    if(Exploding) {
        if(!detonated) {
			Hidden = Helper::GetRandomInt(0, 2);
            bombTimer += deltaTime;
            if(bombTimer >= bombTime) {
				Hidden = false;
                Mix_PlayChannel(-1, Assets::Sounds["bomb_explode"], 0);
                Type = "bomb_explosion";
                detonated = true;
				CurrentAnimation = ExplodeAnimation;
				ZOrder = 11;
				SDL_Rect box = GetHitbox();
				for(int i = 0; i < 10; i++) {
					int posX = box.x + Helper::GetRandomInt(0, box.w) - 10;
					int posY = box.y + Helper::GetRandomInt(0, box.h) - 10;

					vector3 pos;
					pos.x = posX;
					pos.y = posY;
					
					explosionPositions.push_back(pos);
				}
	
            }
        } else {
            stayTimer += deltaTime;
            if(stayTimer >= stayTime) {
                Scene->RemoveEntity(this);
            }
        }
    } else {
        Player* p = (Player*)CollidesWith("player");

        if(p) {
            Mix_PlayChannel(-1, Assets::Sounds["get_item"], 0);
            Scene->RemoveEntity(this);
            p->BombCount++;
        }
    }
}

void Bomb::Draw(Surface* screen, float deltaTime) {
	Entity::Draw(screen, deltaTime);

	if(CurrentAnimation != 0) {
		Surface* sur = CurrentAnimation->GetCurrentSurface();
		for(int i = 0; i < explosionPositions.size() -1; i++) {
			sur->AlphaCopyTo(screen, explosionPositions[i].x, explosionPositions[i].y);
		}
	}
}
