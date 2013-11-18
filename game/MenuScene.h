#pragma once

#include "Scene.h"
#include "MenuItem.h"


class MenuScene : public Scene {
    public:
        MenuScene(void);
        ~MenuScene(void);

        Animation* IntroAnimation;

        MenuItem* Items[2];

        void Init();
        void Update(float deltaTime);
        void Draw(Surface* screen, float deltaTime);        
};