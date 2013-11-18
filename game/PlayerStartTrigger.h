#pragma once
#include "entity.h"
class PlayerStartTrigger : public Entity {
    public:
        PlayerStartTrigger(int posX, int posY);
        ~PlayerStartTrigger(void);

        void Init();
};

