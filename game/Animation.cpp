#include "Animation.h"


Animation::Animation(std::string animationName) {
    Name = animationName;
    FrameTime = 0.05f;
    frameTimeElapsed = 0;
    currentFrame = 0;
    Finished = false;
    LoopAnimation = true;
    FinishedCallback = 0;
}

Animation::~Animation(void) {
    for(unsigned int i = 0; i < Sprites.size(); i++) {
        delete Sprites[i];
    }

    Sprites.clear();
}

void Animation::Play(bool loop) {
    LoopAnimation = loop;
    currentFrame = 0;
    Finished = false;
}

void Animation::Update(float deltaTime) {    
    if(Finished) return;

    frameTimeElapsed += deltaTime;
    if (frameTimeElapsed >= FrameTime && !Finished) {
        if (currentFrame == FrameCount() - 1) {
            if (!LoopAnimation) {
                Finished = true;
                if(FinishedCallback != 0) {
                    FinishedCallback(this);
                }
                return;
            } else {
                currentFrame = 0;
            }
        } else {
            currentFrame++;
        }

        frameTimeElapsed = 0;
    }
}

void Animation::SetCurrentFrame(int frame) {
    currentFrame = frame > FrameCount() -1 ? FrameCount() -1 : frame;     
}
