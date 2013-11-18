#pragma once

#include <string>
#include <vector>
#include "surface.h"

class Animation {
    public:
        Animation(std::string animationName);
        ~Animation(void);

        std::vector<Surface*> Sprites;

        float FrameTime;        
        std::string Name;
        bool LoopAnimation;
        bool Finished;

        void (*FinishedCallback)(Animation* anim);

        void AddSprite(Surface* sprite) { Sprites.push_back(sprite); }
        void Play(bool loop);
        void Update(float deltaTime);

        int FrameCount() { return Sprites.size(); }

        int GetCurrentFrame() { return currentFrame; }
        void SetCurrentFrame(int frame);

        Surface* GetCurrentSurface() { return Sprites[GetCurrentFrame()]; }
    private:
        int currentFrame;
        float frameTimeElapsed;        
};