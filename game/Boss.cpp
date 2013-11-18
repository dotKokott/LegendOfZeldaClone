#include "Helper.h"
#include "Assets.h"
#include "Scene.h"
#include "Boss.h"

#include "Rupee.h"

#include "Projectile.h"

Boss::Boss(int posX, int posY) {
	Position.x = posX;
	Position.y = posY;
		
	SwordHealth = 2;
	BombHealth = 2;
	ArrowHealth = 2;

	CurrentAnimation = new Animation(*Assets::Animations["boss"]);

	SizeX = 70;
	SizeY = 110;	

	Type = "enemy";

	blinkTime = 1.0f;
	blinkTimer = 0;
	hurt = false;

	shootTime = 3.0f;
	shootTimer = 0;
}

Boss::~Boss(void) {
}


void Boss::Update(float deltaTime) {	
	if(ArrowHealth > 0) {
		Entity* ar = CollidesWith("arrow");
		if(ar) {
			hurt = true;
			Scene->RemoveEntity(ar);
			ArrowHealth--;
		}
	} else if(BombHealth > 0) {
		Entity* b = CollidesWith("bomb_explosion");
		if(b) {
			hurt = true;
			BombHealth--;
			b->Type = "";
		}
	} else if(SwordHealth > 0) {
		Entity* s = CollidesWith("sword");
		if(s) {
			hurt = true;
			s->Type = "";
			SwordHealth--;
			if(SwordHealth == 0) {
				Scene->RemoveEntity(this);
				Mix_PlayChannel(-1, Assets::Sounds["item_fanfare"], 0);

				for(int i = 0; i < 100; i++) {
					Scene->AddEntity(new Rupee(Helper::GetRandomInt(32, SCRWIDTH - 32), Helper::GetRandomInt(96, SCRHEIGHT - 32)));
				}
			}
		}
	}

	if(hurt) {
		blinkTimer += deltaTime;
		Hidden = Helper::GetRandomInt(0, 2);
		if(blinkTimer >= blinkTime) {
			Hidden = false;
			hurt = false;
			blinkTimer = 0;
		}
	}

	shootTimer += deltaTime;
	if(shootTimer >= shootTime) {
		shootTimer = 0;
		SDL_Rect box = GetHitbox();
		for(int i = 0; i < 5; i++) {
			int posX = i * (SCRWIDTH / 4);
			vector3 pos;
			pos.x = posX;
			pos.y = SCRHEIGHT;
			
			vector3 origin;
			origin.x = box.x + (box.w / 2) - 16;
			origin.y = box.y + (box.h / 2) - 16;

			Projectile* p = new Projectile(origin.x, origin.y, pos - origin, true);
			Scene->AddEntity(p);
		}
	}
}