#include "Player.h"

#include "PlayerStartTrigger.h"

PlayerStartTrigger::PlayerStartTrigger(int posX, int posY) {
    Position.x = posX;
    Position.y = posY;
}

PlayerStartTrigger::~PlayerStartTrigger(void) {
}

void PlayerStartTrigger::Init() {
    Entity::Init();

    Player* p = new Player();
    p->Position = Position;
    
    Scene->AddEntity(p);    

    ((GameScene*)Scene)->Player = p;
}
