#include "Input.h"

InputState* Input::PreviousState = new InputState();
InputState* Input::State = new InputState();

void Input::NewState() {
    if(PreviousState != 0) {
        delete PreviousState;
    }

    PreviousState = new InputState(*State);
}
