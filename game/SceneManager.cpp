#include <algorithm>

#include "SceneManager.h"


SceneManager::SceneManager(void) {
	ExitGame = false;
}


SceneManager::~SceneManager(void) {
}

void SceneManager::AddScene(Scene* scene) {
	Scenes.push_back(scene);

	scene->Manager = this;

	scene->Init();
}

void SceneManager::RemoveScene(Scene* scene) {
	Scenes.erase(std::remove(Scenes.begin(), Scenes.end(), scene), Scenes.end());
	scene->Destroy();
	ToDeleteScenes.push_back(scene);
}

void SceneManager::SwitchScene(Scene* scene) {
	int size = Scenes.size();
	if(size > 0) {
		for(int i = size -1; i >= 0; i--) {
			Scene* _scene = Scenes[i];
					
			_scene->Destroy();
			Scenes.erase(Scenes.begin() + i);            

			ToDeleteScenes.push_back(_scene);		
		}        
	}

	Scenes.push_back(scene);

	scene->Manager = this;
	scene->Init();
}

void SceneManager::Update(float deltaTime) {
	GetTopScene()->Update(deltaTime);
	
	freeScenes();
}

void SceneManager::Draw(Surface* screen, float deltaTime) {
	for(unsigned int i = 0; i < Scenes.size(); i++) {
		Scenes[i]->Draw(screen, deltaTime);
	}
}

void SceneManager::freeScenes() {
	int size = ToDeleteScenes.size();
	if(size > 0) {
		for(int i = size -1; i >= 0; i--) {
			Scene* scene = ToDeleteScenes[i];
												   
			ToDeleteScenes.erase(ToDeleteScenes.begin() + i);            

			delete scene;            
		}        
	}
}