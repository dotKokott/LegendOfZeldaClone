#pragma once

#include "template.h"
#include "InputState.h"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 3

class Input {
	public:
		static InputState* PreviousState;
		static InputState* State;

		static void NewState();

		static bool IsKeyDown(unsigned int code) { return isKeyDown(State, code); }
		static bool IsKeyUp(unsigned int code) { return IsKeyDownPrevious(code) && !isKeyDown(State, code); }

        static bool IsKeyJustPressed(unsigned int code) { return !IsKeyDownPrevious(code) && IsKeyDown(code); }
        
        static bool IsKeyDownPrevious(unsigned int code) { return isKeyDown(PreviousState, code); }                       

        static bool IsMouseJustDown(unsigned int code) { return !IsMouseDownPrevious(code) && IsMouseDown(code); }

		static bool IsMouseDown(unsigned int code) { return isMouseDown(State, code); }
		static bool IsMouseUp(unsigned int code) { return IsMouseDownPrevious(code) && !isMouseDown(State, code); }

		static bool IsMouseDownPrevious(unsigned int code) { return isMouseDown(PreviousState, code); }
	private:
		static bool isKeyDown(InputState* state, unsigned int code) { return state->KeyDown[code]; }
        static bool isMouseDown(InputState* state, unsigned int code) { return state->MouseDown[code]; }
};

