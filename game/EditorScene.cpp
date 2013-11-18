#include "Assets.h"
#include "Input.h"
#include "Room.h"

#include "SceneManager.h"
#include "LevelSelectionScene.h"

#include "EntityItem.h"

#include "EditorScene.h"

EditorScene::EditorScene(Level* level) {
	CurrentLevel = level;
	CurrentItem = 0;
}

EditorScene::~EditorScene(void) {
}

void EditorScene::Init() {
	AddEntity(new EntityItem(TypePlayerStart, 10, 10));
	AddEntity(new EntityItem(TypeOctorokRed, 50, 10));
    AddEntity(new EntityItem(TypeTektite, 90, 10));
    AddEntity(new EntityItem(TypeMoblin, 130, 10));
    AddEntity(new EntityItem(TypeZola, 170, 10));
	AddEntity(new EntityItem(TypeTrigger, 210, 10));
	AddEntity(new EntityItem(TypePositionTrigger, 250, 10));
	
	AddEntity(new EntityItem(TypeRandomEnemies, 290, 10));
	/*
	AddEntity(new EntityItem(TypePickupSword, 290, 10));
	AddEntity(new EntityItem(TypePickupBomb, 330, 10));
	AddEntity(new EntityItem(TypePickupBow, 370, 10));

	AddEntity(new EntityItem(TypePickupBomb, 410, 10));
	AddEntity(new EntityItem(TypePickupArrow, 450, 10));
	*/
}

void EditorScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if(Input::IsKeyJustPressed(SDLK_LEFT)) {
		if(CurrentLevel->CurrentRoomX > 0) CurrentLevel->CurrentRoomX--;
	}

	if(Input::IsKeyJustPressed(SDLK_RIGHT)) {
		if(CurrentLevel->CurrentRoomX < CurrentLevel->RoomCountX -1) CurrentLevel->CurrentRoomX++;
	}

	if(Input::IsKeyJustPressed(SDLK_UP)) {
		if(CurrentLevel->CurrentRoomY > 0) CurrentLevel->CurrentRoomY--;
	}

	if(Input::IsKeyJustPressed(SDLK_DOWN)) {
		if(CurrentLevel->CurrentRoomY < CurrentLevel->RoomCountY -1) CurrentLevel->CurrentRoomY++;
	}

	if(Input::IsKeyJustPressed(SDLK_c)) {
		CurrentItem = 0;
	}

	int tileX = (Input::State->MouseX / TILE_SIZE);
	int tileY = ((Input::State->MouseY - 96) / TILE_SIZE);

	Tile* selected = CurrentLevel->CurrentRoom()->Map[tileX][tileY];
	if(selected == 0) return;

	//Only do collision stuff if now entityItem is selected
	if(CurrentItem == 0) {
		if(Input::IsMouseJustDown(MOUSE_LEFT)) {
			SetBlockValueFor(selected->GraphicIndex, true);   
		}
		if(Input::IsMouseJustDown(MOUSE_RIGHT)) {
			SetBlockValueFor(selected->GraphicIndex, false);
		}
	} else {
		if(Input::IsMouseJustDown(MOUSE_LEFT)) {
			CurrentLevel->CurrentRoom()->DefinedEntities[tileX][tileY] = CurrentItem->EntityType;
			CurrentLevel->SaveCollisionMap();
        } else if(Input::IsMouseJustDown(MOUSE_RIGHT)) {
            CurrentLevel->CurrentRoom()->DefinedEntities[tileX][tileY] = None;
        }
	}

	if(Input::IsKeyJustPressed(SDLK_ESCAPE)) {
		Manager->SwitchScene(new LevelSelectionScene());
	}
}

void EditorScene::Draw(Surface* screen, float deltaTime) {	
	CurrentLevel->Draw(screen, deltaTime);

	Room* currentRoom = CurrentLevel->CurrentRoom();

	for(int x = 0; x < currentRoom->TileCountX; x++) {
		for(int y = 0; y < currentRoom->TileCountY; y++) {
			int posX = x * TILE_SIZE;
			int posY = (y * TILE_SIZE) + 96;

			int color = currentRoom->Map[x][y]->Blocks ? 0xFF0000 : 0x00FF00;            
			screen->Box(posX, posY, posX + TILE_SIZE, posY + TILE_SIZE, color);

			if(currentRoom->DefinedEntities[x][y] != 0) {
				Assets::Graphics["editor_" + std::to_string(currentRoom->DefinedEntities[x][y])]->CopyTo(screen, posX, posY);
			}
		}
	}

	int tileX = (Input::State->MouseX / TILE_SIZE);
	int tileY = ((Input::State->MouseY - 96) / TILE_SIZE);

	Tile* selected = CurrentLevel->CurrentRoom()->Map[tileX][tileY];

	if(selected != 0 && CurrentItem != 0) {
		CurrentItem->Graphic->CopyTo(screen, tileX * TILE_SIZE, (tileY * TILE_SIZE) + 96);
	}

	Scene::Draw(screen, deltaTime);
}

void EditorScene::SetBlockValueFor(int tileIndex, bool value) {
	for(int rX = 0; rX < CurrentLevel->RoomCountX; rX++) {
		for(int rY = 0; rY < CurrentLevel->RoomCountY; rY++) {
			Room* room = CurrentLevel->Rooms[rX][rY];
			
			for(int x = 0; x < room->TileCountX; x++) {
				for(int y = 0; y < room->TileCountY; y++) {
					if(room->Map[x][y]->GraphicIndex == tileIndex) {
						room->Map[x][y]->Blocks = value;
					}                    
				}
			}
		}
	}

	CurrentLevel->SaveCollisionMap();
}