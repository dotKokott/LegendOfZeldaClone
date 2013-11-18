#include "Assets.h"
#include "Scene.h"

#include "Player.h"

#include "Rupee.h"


Rupee::Rupee(int posX, int posY) {
    Position.x = posX;
    Position.y = posY;

    SizeX = 16;
    SizeY = 32;

    Type = "rupee";

    CurrentAnimation = new Animation(*Assets::Animations["rupee"]);
}

Rupee::~Rupee(void) {
}

void Rupee::Update(float deltaTime) {
    Player* p = (Player*)CollidesWith("player");
    if(p) {
        p->Rupees++;
        Scene->RemoveEntity(this);
        Mix_PlayChannel(-1, Assets::Sounds["get_rupee"], 0);
    }

}
