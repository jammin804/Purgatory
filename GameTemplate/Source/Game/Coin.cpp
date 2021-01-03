#include "Coin.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"


void Coin::OnInit()
{
	CoinImage = GameComponent::CreateInstance<ImageComponent>(this);
	Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	CoinSoundComponent = GameComponent::CreateInstance<SoundComponent>(this);
	CoinSoundComponent->SetVolume(0.3f);

}

void Coin::OnPostInit()
{
	if (CoinImage)
	{
		CoinImage->LoadImage("Art/Coins.png");
	}
	float StartDirX = rand() % Globals::WindowSizeX;
	float StartDirY = rand() % Globals::WindowSizeY;
}

void Coin::OnUpdate(float DeltaTime)
{

	CoinLifeTimer += DeltaTime;
	if (CoinLifeTimer > MAX_COIN_LIFE_TIMER)
	{
		RequestDestroy();
	}
}

void Coin::CoinCollision()
{
	RequestDestroy();
}

void Coin::SetCoinDropSound(string SoundPath)
{
	if (CoinSoundComponent)
	{
		CoinSoundComponent->LoadSample(SoundPath);
	}

}

void Coin::SetCoinPickUpSound(string SoundPath)
{
	if (CoinSoundComponent)
	{
		CoinSoundComponent->LoadSample(SoundPath);
	}

}

