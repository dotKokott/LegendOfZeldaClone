#include "Assets.h"
#include "Helper.h"
#include "Scene.h"
#include "GameScene.h"

#include "Projectile.h"

#include "Zola.h"


Zola::Zola(int posX, int posY) {
    Position.x = OriginalPosition.x = posX;
    Position.y = OriginalPosition.y = posY;

    SizeX = SizeY = 32;
    CurrentAnimation = new Animation(*Assets::Animations["zola"]);    

    Shooted = false;

    setRandomPosition();

    waitForTime = waitForTimer = 0;

	Type = "enemy";
}

Zola::~Zola(void) {
}

void Zola::Update(float deltaTime) {  
    if(CurrentAnimation->GetCurrentFrame() >= 9 && !Shooted) {
        Scene->AddEntity(new Projectile(Position.x, Position.y, (Entity*)((GameScene*)Scene)->Player, false));
        Shooted = true;
    } else if(CurrentAnimation->Finished) {
        Hidden = true;

        waitForTimer += deltaTime;
        if(waitForTimer >= waitForTime) {
            waitForTimer = 0;
            CurrentAnimation->Play(false);
            Hidden = false;
            
            setRandomPosition();
        }        
    }
	
    if(CurrentAnimation->GetCurrentFrame() >= 8) {
		Entity* ar = CollidesWith("arrow");
		if(ar != 0) {
			Scene->RemoveEntity(ar);
			Scene->RemoveEntity(this);
		}

    }
}

void Zola::setRandomPosition() {
    Position.x = OriginalPosition.x + (Helper::GetRandomInt(0, 182));
    Position.y = OriginalPosition.y + (Helper::GetRandomInt(0, 60));

    waitForTime = (float)Helper::GetRandomInt(1, 5);
    waitForTimer = 0;

    Shooted = false;
        
}
