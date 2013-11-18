#include <algorithm>
#include "Helper.h"

#include "PlayerStartTrigger.h"
#include "Oktorok.h"
#include "Tektite.h"
#include "Moblin.h"
#include "Zola.h"
#include "LevelTrigger.h"
#include "PositionTrigger.h"
#include "PickupItem.h"
#include "Boss.h"
#include "Fire.h"

#include "Room.h"

Room::Room(Level* parent, int xIndex, int yIndex) {
	Parent = parent;

	XIndex = xIndex;
	YIndex = yIndex;

	TileCountX = ceil(Room::Width / TILE_SIZE);
	TileCountY = ceil(Room::Height / TILE_SIZE);

    Inited = false;
}

Room::~Room(void) {
}

void Room::Init() {
    Inited = true;

	for(int x = 0; x < TileCountX; x++) {
		for(int y = 0; y < TileCountY; y++) {
            ENTITY_TYPE type = DefinedEntities[x][y];
	        if(type != None && type != Collision) {
                int posX = x * TILE_SIZE;
                int posY = (y * TILE_SIZE) + 96;

                switch (type) {
                    case TypePlayerStart:
                        Entities.push_back(new PlayerStartTrigger(posX, posY));

                        break;
                    case TypeOctorokRed:
                        Entities.push_back(new Oktorok(posX, posY));
                        break;
                    case TypeTektite:
                        Entities.push_back(new Tektite(posX, posY));
                        break;
                    case TypeMoblin:
                        Entities.push_back(new Moblin(posX, posY));
                        break;
                    case TypeZola:
                        Entities.push_back(new Zola(posX, posY));
                        break;
					case TypeTrigger:
						Entities.push_back(new LevelTrigger(posX, posY));
						break;
					case TypePositionTrigger:
						Entities.push_back(new PositionTrigger(posX, posY));
						break;
					case TypeRandomEnemies:
						SpawnRandomEnemies();
						break;
                }
            }
        }
    }

	if(strcmp(&Parent->Name[0], "room 1") == 0) {
		Entities.push_back(new PickupItem(215, 265, TypePickupBombs, false));
		Entities.push_back(new PickupItem(235, 265, TypePickupSword, false));
		Entities.push_back(new PickupItem(265, 265, TypePickupBow, false));

		Entities.push_back(new Fire(150, 226));
		Entities.push_back(new Fire(340, 226));
	}
	
	if(strcmp(&Parent->Name[0], "boss") == 0) {
		Entities.push_back(new Boss(215, 35 + 96));
	}	

	if(strcmp(&Parent->Name[0], "shopkeeper") == 0) {
		Entities.push_back(new PickupItem(215, 300, TypePickupBomb, true));
		Entities.push_back(new PickupItem(280, 285, TypePickupArrow, true));		

		Entities.push_back(new Fire(150, 226));
		Entities.push_back(new Fire(340, 226));
	}


}

void Room::Draw(Surface* screen, float deltaTime) {
	for(int x = 0; x < TileCountX; x++) {
		for(int y = 0; y < TileCountY; y++) {			
			Map[x][y]->Graphic->AlphaCopyTo(screen, x * TILE_SIZE, 96 + y * TILE_SIZE);            
		}
	} 
}

bool Room::IsFree(int posX, int posY) {
	return !Map[posX / TILE_SIZE][posY / TILE_SIZE]->Blocks;
}

Tile* Room::GetTile(int posX, int posY) {
	return Map[posX / TILE_SIZE][posY / TILE_SIZE];
}

vector3 Room::GetEntityPosition(ENTITY_TYPE type) {
	vector3 pos;

	for(int x = 0; x < TileCountX; x++) {
		for(int y = 0; y < TileCountY; y++) {
			if(DefinedEntities[x][y] == type) {
				pos.x = x * TILE_SIZE;
				pos.y = (y * TILE_SIZE) + 96;

				return pos;
			}
		}
	}

	return pos;
}

void Room::RemoveEntity(Entity* entity) {
	Entities.erase(std::remove(Entities.begin(), Entities.end(), entity), Entities.end());
}

void Room::SpawnRandomEnemies() {
	int count = Helper::GetRandomInt(3, 7);
	for(int i = 0; i < count; i++) {
		int tileX = Helper::GetRandomInt(1, TileCountX);
		int tileY = Helper::GetRandomInt(1, TileCountY);

		while(Map[tileX][tileY]->Blocks) {
			tileX = Helper::GetRandomInt(1, TileCountX);
			tileY = Helper::GetRandomInt(1, TileCountY);
		}

		int rnd = Helper::GetRandomInt(0, 3);
		int posX = tileX * TILE_SIZE;
		int posY = (tileY * TILE_SIZE) + 96;

		if(rnd == 0) {
			Entities.push_back(new Oktorok(posX, posY));
		}

		if(rnd == 1) {
			Entities.push_back(new Tektite(posX, posY));
		}		

		if(rnd == 2) {
			Entities.push_back(new Moblin(posX, posY));		
		}
	}
}

void Room::Destroy() {
	for(int i = 0; i < Entities.size(); i++) {
		delete Entities[i];
	}

	Entities.clear();

	Inited = false;
}