#include "Coin.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Framework/SoundComponent.h"


void Coin::OnInit()
{
	CoinImage = GameComponent::CreateInstance<ImageComponent>(this);
	Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	CoinSoundComponentDrop = GameComponent::CreateInstance<SoundComponent>(this);
	
}

void Coin::OnPostInit()
{
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

void Coin::UpdateMovement(float DeltaTime)
{
	SetPosition(GetPositionX() + (StartDirX * DeltaTime * HorizontalMovementSpeed), GetPositionY() + (StartDirY * DeltaTime * VerticalMovementSpeed));
	HorizontalMovementSpeed *= 1.0f - DeltaTime;
	VerticalMovementSpeed -= 1000.0f*DeltaTime;
}

void Coin::CoinCollision()
{

	RequestDestroy();
}

