#pragma once

#include <vector>
#include <map>

#include "surface.h"
#include "Tile.h"

#define TILE_SIZE 32

class Room;

class Level {
	public:
		Level(std::string name);
		~Level(void);

		std::string Name;

		std::map<int, std::map<int, Room*>> Rooms;
		std::vector<Surface*> Tiles;

		int RoomCountX;
		int RoomCountY;

		int CurrentRoomX;
		int CurrentRoomY;       
		
		bool Inited;
		void Init();
		void Draw(Surface* screen, float deltaTime);

		Room* CurrentRoom() { return Rooms[CurrentRoomX][CurrentRoomY]; }

		void SaveCollisionMap();
		void LoadCollisionMap();

		void Destroy();
	private:
		int getNewTileIndex(Surface* tile);
};