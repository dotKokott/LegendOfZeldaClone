#include "lib\Dirent\include\dirent.h"
#include <stdio.h>
#include "Assets.h"
#include "Input.h"
#include "SceneManager.h"
#include "EditorScene.h"
#include "MenuScene.h"

#include "LevelSelectionScene.h"

LevelSelectionScene::LevelSelectionScene(void) {
	SelectedMenuItem = 0;
}

LevelSelectionScene::~LevelSelectionScene(void) {
}

void LevelSelectionScene::Init() {
	//code from: http://stackoverflow.com/questions/5043403/listing-only-folders-in-directory
	DIR *dir = opendir("assets/levels");

	struct dirent *entry = readdir(dir);
	int i = 0;

	while (entry != NULL) {
		if (entry->d_type == DT_DIR) {
			if(std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {
				std::string folder(entry->d_name);
				MenuItem* mi = new MenuItem(150, 50 + i * 20, folder);
				MenuItems.push_back(mi);
				AddEntity(mi);
			}            
		}            
		i++;
		entry = readdir(dir);
	}

	closedir(dir);    	
}

void LevelSelectionScene::Update(float deltaTime) {
	Scene::Update(deltaTime);	

	if(Input::IsKeyJustPressed(SDLK_UP) && SelectedMenuItem > 0) {
		SelectedMenuItem--;
	} else if(Input::IsKeyJustPressed(SDLK_DOWN) && SelectedMenuItem < MenuItems.size() -1) {
		SelectedMenuItem++;
	}

	for(int i = 0; i < MenuItems.size(); i++) {
		MenuItem* itm = MenuItems[i];		
		itm->Selected = (i == SelectedMenuItem);
		
		if(itm->Clicked) {
			Manager->SwitchScene(new EditorScene(Assets::Levels[itm->Text]));
		}
	}

	if(Input::IsKeyJustPressed(SDLK_ESCAPE)) {
		Manager->SwitchScene(new MenuScene());
	}
}

void LevelSelectionScene::Draw(Surface* screen, float deltaTime) {
	screen->Print("Please select a level to edit", (SCRWIDTH / 2) - 100, 25, 0xFFFFFF);

	Scene::Draw(screen, deltaTime);
}