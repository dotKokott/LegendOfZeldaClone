#pragma once

#include <vector>
#include "surface.h"

class Entity;
class SceneManager;

class Game { 
	public:
		void SetTarget( Surface* a_Surface ) { Screen = a_Surface; }
		void Init();
		void Tick( float deltaTime );
		void KeyDown( unsigned int code );
		void KeyUp( unsigned int code );
		void MouseMove( unsigned int x, unsigned int y );
		void MouseUp( unsigned int button );
		void MouseDown( unsigned int button );

		Surface* Screen;

		SceneManager* Manager;

		bool ExitGame;
	private:
		void freeEntities();
};