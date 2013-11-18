#include <iostream>
#include <fstream>
#include <sstream>

#include "Assets.h"
#include "Input.h"
#include "Room.h"

#include "Level.h"

Level::Level(std::string name) {    
	Name = name;
	
	CurrentRoomX = CurrentRoomY = 0;
	RoomCountX = RoomCountY = 0;

	Inited = false;
}

Level::~Level(void) {
}

void Level::Init() {
	Inited = true;

	std::string fileName = "assets/levels/" + Name + "/background.png";

	//HACK HACK HACK but well
	if(strcmp(&Name[0], "overworld") == 0) {
		CurrentRoomX = 7;
		CurrentRoomY = 7;
	}

	Surface* background = new Surface(&fileName[0]);
	
	RoomCountX = ceil(background->GetWidth() / Room::Width);
	RoomCountY = ceil(background->GetHeight() / Room::Height);

	int roomTileCountX = ceil(Room::Width / TILE_SIZE);
	int roomTileCountY = ceil(Room::Height / TILE_SIZE);

	for(int rX = 0; rX < RoomCountX; rX++) {
		for(int rY = 0; rY < RoomCountY; rY++) {
			Room* room = new Room(this, rX, rY);
			Rooms[rX][rY] = room;

			for(int x = 0; x < roomTileCountX; x++) {
				for(int y = 0; y < roomTileCountY; y++) {
					Surface* pixels = new Surface(TILE_SIZE, TILE_SIZE);
					
					int posX = (rX * Room::Width) + (x * TILE_SIZE);
					int posY = (rY * Room::Height) + (y * TILE_SIZE);

					background->CopyTo(pixels, -posX, -posY);

					int index = getNewTileIndex(pixels);
			
					room->Map[x][y] = new Tile(x, y, index, Tiles[index]);
				}
			}
			
		}
	}

    delete background;

	LoadCollisionMap();
}

void Level::Draw(Surface* screen, float deltaTime) {
	Rooms[CurrentRoomX][CurrentRoomY]->Draw(screen, deltaTime);   
}

int Level::getNewTileIndex(Surface* tile) {    
	for(int i = 0; i < Tiles.size(); i++) {

		bool sameTile = true;    
		for(int j = 0; j < (TILE_SIZE * TILE_SIZE); j++) {

			Pixel _old = Tiles[i]->GetBuffer()[j];
			Pixel _new = tile->GetBuffer()[j];

			if(_old != _new) {
				sameTile = false;            
				break;
			}           
		}

		if(sameTile) return i;
	}

	Tiles.push_back(tile);

	 return Tiles.size() -1;
}

void Level::SaveCollisionMap() {
	std::ofstream file;
	
	file.open("assets/levels/" + Name + "/data.txt", std::ios::out | std::ios::trunc);

	if (file.is_open()) {
		for(int rX = 0; rX < RoomCountX; rX++) {
			for(int rY = 0; rY < RoomCountY; rY++) {
				Room* room = Rooms[rX][rY];
			
				for(int x = 0; x < room->TileCountX; x++) {
					for(int y = 0; y < room->TileCountY; y++) {
						if(room->DefinedEntities[x][y] == None) {
							file << room->Map[x][y]->Blocks;
						} else {
							file << room->DefinedEntities[x][y];
						}
					}
				}
			}
		}
	} else {
		printf("Error saving collision map\n");
	}

	file.flush();
	file.close();

	printf("Done saving collision map\n");
}

void Level::LoadCollisionMap() {
	printf("Loading collision map\n");

	std::ifstream file("assets/levels/" + Name + "/data.txt");

	while(file.good()) {
		for(int rX = 0; rX < RoomCountX; rX++) {
			for(int rY = 0; rY < RoomCountY; rY++) {
				Room* room = Rooms[rX][rY];
			
				for(int x = 0; x < room->TileCountX; x++) {
					for(int y = 0; y < room->TileCountY; y++) {                        
						char value = file.get();

						room->Map[x][y]->Blocks = (value == '1');

						if(value != '1') {							
							room->DefinedEntities[x][y] = (ENTITY_TYPE)(value - '0');
						}
					}
				}
			}
		}

		break;
	}

	file.close();

	printf("Done loading collision map\n");
}

void Level::Destroy() {
	if(strcmp(&Name[0], "overworld") == 0) {
		CurrentRoomX = 7;
		CurrentRoomY = 7;
	}

	for(int rX = 0; rX < RoomCountX; rX++) {
		for(int rY = 0; rY < RoomCountY; rY++) {
			Rooms[rX][rY]->Destroy();			
		}
	}
}