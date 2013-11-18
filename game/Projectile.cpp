#include "Assets.h"

#include "Scene.h"

#include "Projectile.h"

Projectile::Projectile(int posX, int posY, vector3 velocity, bool collidesTiles) {
    Position.x = posX;
    Position.y = posY;

    Velocity = velocity;

    CurrentAnimation = new Animation(*Assets::Animations["rock_projectile"]);
    Graphic = CurrentAnimation->Sprites[0];
    SizeX = Graphic->GetWidth();
    SizeY = Graphic->GetHeight();

    CollidesTiles = collidesTiles;

    Type = "projectile";    
}

Projectile::Projectile(int posX, int posY, Entity* target, bool collidesTiles) {
    Position.x = posX;
    Position.y = posY;

    CollidesTiles = collidesTiles;

    Velocity = target->Position - Position;
    CurrentAnimation = new Animation(*Assets::Animations["rock_projectile"]);
    Graphic = CurrentAnimation->Sprites[0];
    SizeX = Graphic->GetWidth();
    SizeY = Graphic->GetHeight();

    Type = "projectile";    
}

Projectile::~Projectile(void) {
}

void Projectile::Update(float deltaTime) {
    vector3 vel = Velocity * deltaTime;

    vector3 pos = Position + vel;

    if((CollidesTiles && CollidesWithTiles(vel)) || CollidesWith("player") || pos.x <= 0 || pos.x + SizeX >= SCRWIDTH || pos.y <= 96 || pos.y + SizeY >= SCRHEIGHT) {
        Scene->RemoveEntity(this);
        return;
    }

	//Deflect
	if((vel.x == 0 || vel.y == 0) && Type == "projectile" && CollidesWith("sword")) {
		Velocity *= -1;
		Type = "arrow";
	}

    Position = pos;
}