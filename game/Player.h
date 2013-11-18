#pragma once
#include <map>

#include "GameScene.h"

#include "Entity.h"

class Player : public Entity {
	public:
		Player(void);
		~Player(void);

        Animation* NormalUp;
        Animation* NormalDown;
        Animation* NormalLeft;
        Animation* NormalRight;

        std::map<ENTITY_DIRECTION, Animation*> WalkAnimations;
        std::map<ENTITY_DIRECTION, Animation*> SwordAnimations;

        ENTITY_DIRECTION Direction;

		vector3 Velocity;

        bool Attacking;
        bool HasSword;
		bool HasBombs;
		bool HasBow;
        int BombCount;
		int ArrowCount;

		int Health;

        int Rupees;

		bool Hurtable;

		void Init();
		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);

        void Attack();
        void DropBomb();
		void Shoot();
    private:
        GameScene* gameScene;
        bool checkTileCollision(vector3 velocity);
        void setDirectionAndVelocity();

		float notHurtableTime;
		float notHurtableTimer;
};