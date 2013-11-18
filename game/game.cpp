// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009

#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "stdlib.h"
#include "SDL.h"
#include "Assets.h"
#include "game.h"
#include "Input.h"

#include "SceneManager.h"
#include "MenuScene.h"

using namespace std;

void Game::Init() {  
	srand( time( NULL ) ); 

	ExitGame = false;

	Input::NewState();

	Assets::Load();

	Manager = new SceneManager();
	Manager->AddScene(new MenuScene());
}

void Game::Tick( float deltaTime ) { 
	float secondsDeltaTime = deltaTime / 1000;
	
	Screen->Clear(0);    

	Manager->Update(secondsDeltaTime);
	Manager->Draw(Screen, secondsDeltaTime);    

	Input::NewState();

	ExitGame = Manager->ExitGame;
}

void Game::KeyDown( unsigned int code ) {
	Input::State->KeyDown[code] = true;
}

void Game::KeyUp( unsigned int code ) {
	Input::State->KeyDown[code] = false;
}

void Game::MouseMove( unsigned int x, unsigned int y ) {
	Input::State->MouseX = x;
	Input::State->MouseY = y;
}

void Game::MouseDown( unsigned int button ) {
	Input::State->MouseDown[button] = true;
}

void Game::MouseUp( unsigned int button ) {
	Input::State->MouseDown[button] = false;
}