#pragma once

#include <vector>

#include "surface.h"

#include "Entity.h"

class SceneManager;

#define UI_OFFSET 96

class Scene {
	public:       
		Scene(void);
		~Scene(void);       

		std::vector<Entity*> Entities;
		std::vector<Entity*> ToDeleteEntities;

		SceneManager* Manager;

		void AddEntity(Entity* entity);
		virtual void RemoveEntity(Entity* entity);
        void RemoveEntityWithoutDestroy(Entity* entity);
		Entity* Colliding(Entity* entA, char* type);
		bool Colliding(Entity* entA, Entity* entB);

		virtual void Init() { };
		virtual void Update(float deltaTime);
		virtual void Draw(Surface* screen, float deltaTime);
        virtual void Destroy();
	private:
		void freeEntities();
};