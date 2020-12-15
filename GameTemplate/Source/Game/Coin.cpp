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
}

void Coin::OnUpdate(float DeltaTime)
{

}
