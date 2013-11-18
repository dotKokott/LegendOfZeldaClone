#include "Assets.h"
#include "Input.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "LevelSelectionScene.h"

#include "MenuScene.h"


MenuScene::MenuScene(void) {
	Items[0] = new MenuItem((SCRWIDTH / 2) - 20, (SCRHEIGHT / 2) + 80, "Start");
	Items[1] = new MenuItem((SCRWIDTH / 2) - 20, (SCRHEIGHT / 2) + 95, "Map Editor");

	Items[0]->Selected = true;

	IntroAnimation = new Animation(*Assets::Animations["logo"]);
	IntroAnimation->Play(true);

	AddEntity(Items[0]);
	AddEntity(Items[1]);
}

MenuScene::~MenuScene(void) {
	RemoveEntity(Items[0]);
	RemoveEntity(Items[1]);
}

void MenuScene::Init() {

}

void MenuScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if(Input::IsKeyJustPressed(SDLK_UP)) {
		Items[0]->Selected = true;
		Items[1]->Selected = false;            
	}

	if(Input::IsKeyJustPressed(SDLK_DOWN)) {
		Items[0]->Selected = false;
		Items[1]->Selected = true; 
	}

	if(Items[0]->Clicked) Manager->SwitchScene(new GameScene());
	if(Items[1]->Clicked) Manager->SwitchScene(new LevelSelectionScene());

	if(Input::IsKeyJustPressed(SDLK_ESCAPE)) {
		Manager->ExitGame = true;
	}
}

void MenuScene::Draw(Surface* screen, float deltaTime) {
	IntroAnimation->Update(deltaTime);
	IntroAnimation->GetCurrentSurface()->CopyTo(screen, 0, 0);

	Scene::Draw(screen, deltaTime);
}
