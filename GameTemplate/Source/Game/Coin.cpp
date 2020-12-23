#include "Coin.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"


void Coin::OnInit()
{
	CoinImage = GameComponent::CreateInstance<ImageComponent>(this);
	Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);

}

void Coin::OnPostInit()
{
	if (CoinImage)
	{
		CoinImage->LoadImage("Art/Coins.png");
	}
	float StartPosX = rand() % Globals::WindowSizeX;
	float StartPosY = rand() % Globals::WindowSizeY;
	SetPosition(StartPosX, StartPosY);
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

