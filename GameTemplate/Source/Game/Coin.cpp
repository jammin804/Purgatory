#include "Coin.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Framework/SoundComponent.h"
#include "../GameObjectTypes.h"


void Coin::OnInit()
{
	SetType(GOT_Coin);
	CoinImage = GameComponent::CreateInstance<ImageComponent>(this);
	Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	CoinSoundComponentDrop = GameComponent::CreateInstance<SoundComponent>(this);
	
}

void Coin::OnPostInit()
{
	float CollisionScaleX = 20.0f;
	float CollisionScaleY = 20.0f;

	if (CoinImage)
	{
		CoinImage->LoadImage("Art/Coins.png");
	}
	StartDirX = (rand() % 10)/10.0f;
	StartDirX -= 0.5f;
	StartDirY = -1.0f;
	if (CoinSoundComponentDrop)
	{
		CoinSoundComponentDrop->SetVolume(1.0f);
		CoinSoundComponentDrop->LoadSample("Audio/Coin_Drop.wav");
		CoinSoundComponentDrop->Play();
	}
	StartPosY = GetPositionY();
	UpdateMovement(0.2f);

	if (Collision)
	{

		Collision->SetCollisionSize(CollisionScaleX, CollisionScaleY);
	}
}

void Coin::OnUpdate(float DeltaTime)
{
	if (GetPositionY() <= StartPosY) 
	{
		UpdateMovement(DeltaTime);

	}


	CoinLifeTimer += DeltaTime;
	if (CoinLifeTimer > MAX_COIN_LIFE_TIMER)
	{
		RequestDestroy();
	}
}

void Coin::OnCollision(GameObject* Other)
{
	if (Other->GetType() == static_cast<int>(GOT_Player))
	{
		RequestDestroy();
	}
}

void Coin::UpdateMovement(float DeltaTime)
{
	SetPosition(GetPositionX() + (StartDirX * DeltaTime * HorizontalMovementSpeed), GetPositionY() + (StartDirY * DeltaTime * VerticalMovementSpeed));
	HorizontalMovementSpeed *= 0.8f - DeltaTime;
	VerticalMovementSpeed -= 2000.0f*DeltaTime;
}

