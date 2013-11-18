#pragma once

#include <map>

class InputState {
    public:
        InputState();
        ~InputState();

        std::map<unsigned int, bool> KeyDown;

        int MouseX;
        int MouseY;

        std::map<unsigned int, bool> MouseDown;
};