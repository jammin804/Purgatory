#include "Wall.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "../GameObjectTypes.h"
#include "Player.h"
#include "Enemy.h"


void Wall::OnInit()
{
	SetType(GOT_Wall);
	ImageCpt = GameComponent::CreateInstance<ImageComponent>(this);
	CollisionCpt = GameComponent::CreateInstance<BoxCollisionComponent>(this);

}

void Wall::OnPostInit()
{
	float CollisionScaleX = 0.0f;
	float CollisionScaleY = 0.0f;

	if (ImageCpt)
	{
		ImageCpt->LoadImage("Art/Column.png");

		CollisionScaleX = ImageCpt->GetImageWidth();
		CollisionScaleY = ImageCpt->GetImageHeight();

		ImageCpt->SetTilingU(Width);
		ImageCpt->SetTilingV(Height);

		//TODO:Start Posx Start PosY and multiple by the width and height
		StartPosX = StartPosX * CollisionScaleX;
		StartPosY = StartPosY * CollisionScaleY;

		SetWorldPosition(StartPosX, StartPosY);


	}

	

	if (CollisionCpt)
	{
		CollisionCpt->SetBoxOffset(-(CollisionScaleX * 0.5f), -(CollisionScaleY * 0.5f));
		CollisionCpt->SetCollisionSize(CollisionScaleX * Width, CollisionScaleY * Height);
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
		enemy->RewindPostion();
	}
}

float Wall::GetImageWidth() const
{
	if (ImageCpt)
	{
		return ImageCpt->GetImageWidth();
	}

	return 0.0f;
}

float Wall::GetImageHeight() const
{
	if (ImageCpt)
	{
		return ImageCpt->GetImageHeight();
	}

	return 0.0f;
}
