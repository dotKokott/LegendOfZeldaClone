#pragma once

#include <vector>
#include <map>

#include "Level.h"
#include "Entity.h"

#include "Tile.h"

class Room {
	public:
		Room(Level* parent, int xIndex, int yIndex);
		~Room(void);

		std::map<int, std::map<int, Tile*>> Map;
		std::map<int, std::map<int, ENTITY_TYPE>> DefinedEntities;

        std::vector<Entity*> Entities;

		static const int Width = 512;
		static const int Height = 448 - 96;

		Level* Parent;

		int XIndex;
		int YIndex;

		int TileCountX;
		int TileCountY;

        bool Inited;
		void Init();
		void Draw(Surface* screen, float deltaTime);
		void Destroy();

		void RemoveEntity(Entity* entity);

		bool IsFree(int posX, int posY);
		Tile* GetTile(int posX, int posY);

		vector3 GetEntityPosition(ENTITY_TYPE type);

		void SpawnRandomEnemies();
};