#include "Helper.h"
#include "Assets.h"
#include "Input.h"
#include "Room.h"

#include "Sword.h"
#include "Bomb.h"
#include "Arrow.h"

#include "Player.h"

#define PLAYER_SPEED 200.0

Player::Player(void) {
	WalkAnimations[ENTITY_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_normal_left"]);
	WalkAnimations[ENTITY_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_normal_right"]);
	WalkAnimations[ENTITY_DIRECTION_DOWN] = new Animation(*Assets::Animations["player_normal_down"]);
	WalkAnimations[ENTITY_DIRECTION_UP] = new Animation(*Assets::Animations["player_normal_up"]);    

	SwordAnimations[ENTITY_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_sword_left"]);
	SwordAnimations[ENTITY_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_sword_right"]);
	SwordAnimations[ENTITY_DIRECTION_DOWN] = new Animation(*Assets::Animations["player_sword_down"]);
	SwordAnimations[ENTITY_DIRECTION_UP] = new Animation(*Assets::Animations["player_sword_up"]);    

	SizeX = 22;
	SizeY = 18;

	Offset.x = 6;
	Offset.y = 10;

	Type = "player";

	CurrentAnimation = WalkAnimations[ENTITY_DIRECTION_LEFT];
	Direction = ENTITY_DIRECTION_LEFT;

	HasSword = false;
	HasBombs = false;
	HasBow = false;
	Attacking = false;
	BombCount = 10;
	ArrowCount = 50;
    Rupees = 50;

	DrawHitbox = false;
	ZOrder = 10;

	Health = 6;
	Hurtable = true;

	notHurtableTime = 2.0f;
	notHurtableTimer = 0;
}

Player::~Player(void) {
}

void Player::Init() {
	Entity::Init();

	gameScene = (GameScene*)Scene;
}


void Player::Update(float deltaTime) {
	if(Health == 0) return; 

	setDirectionAndVelocity();

	if(Attacking) {
		if(Direction == ENTITY_DIRECTION_LEFT) {
			DrawOffset.x = -22;
		} else if(Direction == ENTITY_DIRECTION_UP) {
			DrawOffset.y = -22;
		}		

		if(CurrentAnimation->Finished) {
			Attacking = false;
			Graphic = WalkAnimations[Direction]->GetCurrentSurface();
			DrawOffset.x = DrawOffset.y = 0;
		}
	}

	if(!Attacking) {
		CurrentAnimation = WalkAnimations[Direction];
	}

	vector3 vel = Velocity * deltaTime;

	if(vel.x == 0 && vel.y == 0) {  
		if(!Attacking) {
			CurrentAnimation = 0;
		}        
	} else {
		if(checkTileCollision(vel)) {
			vel.x = vel.y = 0;
		}
	}    

	Position += vel;

	if(!Attacking && HasSword && Input::IsKeyJustPressed(SDLK_SPACE)) {
		Attack();
	}

	if(HasBombs && BombCount > 0 && Input::IsKeyJustPressed(SDLK_LSHIFT)) {
		 DropBomb();
	}

	if(HasBow && ArrowCount > 0 && Input::IsKeyJustPressed(SDLK_LCTRL)) {
		 Shoot();
	}

	if(Hurtable) {
		if(CollidesWith("projectile") || CollidesWith("enemy")) {
			Mix_PlayChannel(-1, Assets::Sounds["hurt"], 0);
			Health--;
			Hurtable = false;
		}
	}

	if(!Hurtable) {
		Hidden = Helper::GetRandomInt(0, 2);
		notHurtableTimer += deltaTime;
		if(notHurtableTimer >= notHurtableTime) {
			notHurtableTimer = 0;
			Hurtable = true;
			Hidden = false;
		}
	}
}

void Player::Attack() {
	int swordX = 0;
	int swordY = 0;

	SDL_Rect box = GetHitbox();

	switch (Direction)
	{
		case ENTITY_DIRECTION_LEFT:
			swordX = box.x - 25;
			swordY = box.y;

			break;
		case ENTITY_DIRECTION_RIGHT:
			swordX = box.x + box.w;
			swordY = box.y;

			break;
		case ENTITY_DIRECTION_UP:
			swordX = box.x;
			swordY = box.y - 25;

			break;
		case ENTITY_DIRECTION_DOWN:
			swordX = box.x;
			swordY = box.y + box.h;

			break;
		default:
			break;
	}

	Sword* s = new Sword(swordX, swordY);
	Scene->AddEntity(s);

	Mix_PlayChannel(-1, Assets::Sounds["sword_slash"], 0);
	Attacking = true;
	SwordAnimations[Direction]->Play(false);
	CurrentAnimation = SwordAnimations[Direction];
}

void Player::DropBomb() {
	Mix_PlayChannel(-1, Assets::Sounds["bomb_drop"], 0);
	BombCount--;
	Scene->AddEntity(new Bomb(Position.x, Position.y, true));  
}

void Player::Shoot() {
	Mix_PlayChannel(-1, Assets::Sounds["arrow_shoot"], 0);
	ArrowCount--;
	Scene->AddEntity(new Arrow(Position.x + (SizeX / 2), Position.y + (SizeY / 2), Direction));
}

bool Player::checkTileCollision(vector3 velocity) {
	SDL_Rect box = GetHitbox();

	if(box.x < 0 || box.x + box.w >= SCRWIDTH || box.y < 96 || box.y + box.h >= SCRHEIGHT) {
		if(Velocity.x < 0) {
			gameScene->CurrentLevel->CurrentRoomX--;
			Position.x = SCRWIDTH - 32;
		} else if(Velocity.x > 0) {
			gameScene->CurrentLevel->CurrentRoomX++;   
			Position.x = 0;
		} else if(Velocity.y < 0) {
			gameScene->CurrentLevel->CurrentRoomY--;
			Position.y = SCRHEIGHT - 32;
		} else if(Velocity.y > 0) {
			gameScene->CurrentLevel->CurrentRoomY++; 
			Position.y = 96;
		}

		printf("Changing room\n");

		gameScene->LoadCurrentRoom();

		return false;
	}

	return CollidesWithTiles(velocity);
}

void Player::setDirectionAndVelocity() {
	if(Attacking) return;

	Velocity.x = Velocity.y = 0;    

	bool walking = false;
	if(Input::IsKeyDown(SDLK_UP)) {
		Direction = ENTITY_DIRECTION_UP;  
		walking = true;
	} else if(Input::IsKeyDown(SDLK_DOWN)) {
		Direction = ENTITY_DIRECTION_DOWN;
		walking = true;
	} else if(Input::IsKeyDown(SDLK_LEFT)) {
		Direction = ENTITY_DIRECTION_LEFT;
		walking = true;
	} else if(Input::IsKeyDown(SDLK_RIGHT)) {
		Direction = ENTITY_DIRECTION_RIGHT;
		walking = true;
	}

	if(!walking) return;

	switch (Direction)
	{
		case ENTITY_DIRECTION_LEFT:
			Velocity.x = -PLAYER_SPEED;

			break;
		case ENTITY_DIRECTION_RIGHT:
			Velocity.x = PLAYER_SPEED;

			break;
		case ENTITY_DIRECTION_UP:
			Velocity.y = -PLAYER_SPEED;

			break;
		case ENTITY_DIRECTION_DOWN:
			Velocity.y = PLAYER_SPEED;

			break;
		default:
			break;
	}
}

void Player::Draw(Surface* screen, float deltaTime) {
	Entity::Draw(screen, deltaTime);

	screen->Bar(0, 0, SCRWIDTH, 96, 0);

	Assets::Graphics["rupees"]->AlphaCopyTo(screen, 135, 20);
	std::string rupees = "x" + std::to_string(Rupees);
	screen->Print(&rupees[0], 135 + 18, 20 + 8, 0xFFFFFF);

	if(HasBombs) {
		Assets::Graphics["bomb"]->AlphaCopyTo(screen, 135, 40);
		std::string bombs = "x" + std::to_string(BombCount);
		screen->Print(&bombs[0], 135 + 18, 40 + 8, 0xFFFFFF);
	}

	if(HasBow) {
		Assets::Graphics["ui_arrow"]->AlphaCopyTo(screen, 135, 60);
		std::string arrows = "x" + std::to_string(ArrowCount);
		screen->Print(&arrows[0], 135 + 18, 60 + 8, 0xFFFFFF);
	}

	Assets::Graphics["life_label"]->CopyTo(screen, 385, 15);

	screen->Bar(5, 22, 123, 80, 0x808080);
	Level* l = gameScene->CurrentLevel;	

	int rectW = 118 / l->RoomCountX;
	int rectH = 58 / l->RoomCountY;
	int rectX = (l->CurrentRoomX * rectW) + 5;
	int rectY = (l->CurrentRoomY * rectH) + 22;

	screen->Bar(rectX, rectY, rectX + rectW, rectY + rectH, 0x7EEE49);

	Assets::Graphics["bomb_slot"]->AlphaCopyTo(screen, 180, 20);
	Assets::Graphics["arrow_slot"]->AlphaCopyTo(screen, 245, 20);
	Assets::Graphics["sword_slot"]->AlphaCopyTo(screen, 310, 20);

	if(HasSword) {
		Assets::Graphics["inslot_sword"]->AlphaCopyTo(screen, 310 + 22, 20 + 20);
	}

	if(HasBombs) {
		Assets::Graphics["bomb"]->AlphaCopyTo(screen, 180 + 25, 20 + 30);
	}

	if(HasBow) {
		Assets::Graphics["inslot_bow"]->AlphaCopyTo(screen, 245 + 22, 20 + 20);
	}

	for(int i = 0; i < ceil(Health / 2.0f); i++) {
		if(i == ceil(Health / 2.0f) - 1 && Health % 2 != 0) {
			Assets::Graphics["heart_half"]->AlphaCopyTo(screen, 385 + (i * 18), 60);
		} else {
			Assets::Graphics["heart"]->AlphaCopyTo(screen, 385 + (i * 18), 60);
		}
	}
}