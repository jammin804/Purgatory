#include "Wall.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "../GameObjectTypes.h"
#include "Player.h"
#include "Enemy.h"


void Wall::OnInit()
{
	SetType(GOT_Wall);
	WallImage = GameComponent::CreateInstance<ImageComponent>(this);
	Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);

}

void Wall::OnPostInit()
{
	float CollisionScaleX = 20.0f;
	float CollisionScaleY = 20.0f;

	if (WallImage)
	{
		WallImage->LoadImage("Art/Coins.png");

	}

	if (Collision)
	{
		Collision->SetCollisionSize(CollisionScaleX, CollisionScaleY);
	}
}

void Wall::OnCollision(GameObject* Other)
{
	if (Other->GetType() == GOT_Player)
	{
		Player* player = static_cast<Player*>(Other);
		player->RewindPosition();
	}
	else if (Other->GetType() == GOT_Enemy)
	{
		Enemy* enemy = static_cast<Enemy*>(Other);
		enemy->RewindPostion(); //Disappears?
	}
}
