#include "Assets.h"
#include "Player.h"

#include "PickupItem.h"


PickupItem::PickupItem(int posX, int posY, ENTITY_TYPE type, bool costsOnPickup) {
	Position.x = posX;
	Position.y = posY;

	EntityType = type;
	CostsOnPickup = costsOnPickup;

	switch (EntityType)
	{
		case TypePickupSword:
			Graphic = Assets::Graphics["pickup_sword"];
			break;
		case TypePickupBombs:
			Graphic = Assets::Graphics["bomb"];
			break;
		case TypePickupBow:
			Graphic = Assets::Graphics["pickup_bow"];
			break;
		case TypePickupBomb:
			Graphic = Assets::Graphics["bomb"];
			break;
		case TypePickupHeart:
			Graphic = Assets::Graphics["heart"];
			break;
		case TypePickupArrow:
			Graphic = Assets::Graphics["arrow_up"];

			break;
		default:
			break;
	}

	Type = "pickup";

	SizeX = Graphic->GetWidth();
	SizeY = Graphic->GetHeight();
}


PickupItem::~PickupItem(void)
{
}

void PickupItem::Update(float deltaTime) {
	Player* p = (Player*)CollidesWith("player");
	if(p) {
		Mix_PlayChannel(-1, Assets::Sounds["get_item"], 0);

		switch (EntityType)
		{
			case TypePickupSword:
				p->HasSword = true;
				break;
			case TypePickupBombs:
				p->HasBombs = true;
				break;
			case TypePickupBow:
				p->HasBow = true;
				break;
			case TypePickupBomb:
				if(CostsOnPickup && p->Rupees >= 20) {
					p->BombCount += 10;
					p->Rupees -= 20;
				} else {
					p->BombCount++;
				}

				break;
			case TypePickupHeart:
				p->Health += 2;
				break;
			case TypePickupArrow:
				if(CostsOnPickup && p->Rupees >= 10) {
					p->ArrowCount += 10;
					p->Rupees -= 10;
				} else {
					p->ArrowCount++;
				}

				break;
			default:
				break;
		}

		Scene->RemoveEntity(this);
	}
}

void PickupItem::Draw(Surface* screen, float deltaTime) {
	Entity::Draw(screen, deltaTime);
	
	if(CostsOnPickup) {
		if(EntityType == TypePickupBomb) {
			screen->Print("20", Position.x, Position.y + SizeY + 5, 0xFFFFFF);
		}

		if(EntityType == TypePickupArrow) {
			screen->Print("10", Position.x, Position.y + SizeY + 5, 0xFFFFFF);
		}
	}
}