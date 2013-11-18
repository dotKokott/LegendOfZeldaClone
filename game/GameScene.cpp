#include "Assets.h"
#include "Input.h"
#include "SceneManager.h"
#include "MenuScene.h"

#include "Player.h"
#include "Room.h"

#include "GameScene.h"

GameScene::GameScene(void){
	CurrentLevel = 0;
	Player = 0;
}

GameScene::~GameScene(void){
}

void GameScene::Init() {
	CurrentLevel = Assets::Levels["overworld"];	
	CurrentLevel->CurrentRoomX = CurrentLevel->CurrentRoomY = 7;
    loadCurrentRoom();
}

void GameScene::SwitchLevel(std::string name) {
	LastLevel = CurrentLevel;
	CurrentLevel = Assets::Levels[name];

	LoadCurrentRoom();
}

void GameScene::Update(float deltaTime) {	
	Scene::Update(deltaTime);

    if(Input::IsKeyJustPressed(SDLK_ESCAPE) || (Player != 0 && Player->Health == 0)) {		
		Manager->SwitchScene(new MenuScene());		
		Assets::DestroyLevels();
    }
}

void GameScene::Draw(Surface* screen, float deltaTime) {
	CurrentLevel->Draw(screen, deltaTime);
	
	Scene::Draw(screen, deltaTime);	

    if(SwitchRoom) {
        loadCurrentRoom();
        SwitchRoom = false;
    }
}

void GameScene::LoadCurrentRoom() {    
	//Switching from dungeon to overworld again
	if(Player != 0) {
		Player->SizeX = Player->SizeY = 0;	
	}
	
	if(CurrentLevel->CurrentRoom() == 0) {
		CurrentLevel->CurrentRoomX = CurrentLevel->CurrentRoomY = 0;
		CurrentLevel = LastLevel;		
		Player->Position = CurrentLevel->CurrentRoom()->GetEntityPosition(TypeTrigger);
		Player->Position.y += 32;


	}
    SwitchRoom = true;
}

void GameScene::loadCurrentRoom() {
    Room* room = CurrentLevel->CurrentRoom();
    if(!room->Inited) {
        room->Init();
    }

    for(int i = (int)Entities.size() - 1; i >= 0; i--) {
        if(strcmp(Entities[i]->Type, "player") != 0) {
            RemoveEntityWithoutDestroy(Entities[i]);
        }
    }
    
    for(int i = 0; i < room->Entities.size(); i++) {
        AddEntity(room->Entities[i]);
    }

	if(Player != 0) {
		Player->SizeX = 22;
		Player->SizeY = 18;
	}
}

void GameScene::RemoveEntity(Entity* entity) {
	CurrentLevel->CurrentRoom()->RemoveEntity(entity);
	
	Scene::RemoveEntity(entity);
}