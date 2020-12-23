#include "CoinManager.h"
#include "Coin.h"
#include "Framework/Globals.h"

void CoinManager::OnInit()
{
	Coins.reserve(100);
}

void CoinManager::OnUpdate(float DeltaTime)
{
	for (auto CoinIter = Coins.begin(); CoinIter != Coins.end();)
	{
		Coin& CoinToUpdate = *(*CoinIter);


		if (CoinToUpdate.IsDestroyed())
		{
			CoinIter = Coins.erase(CoinIter);
			continue;
		}
		++CoinIter;
	}
}

void CoinManager::OnRestart()
{
	//Reset the CoinManager Coin vector
	for (Coin* CurrentCoin : Coins)
	{
		CurrentCoin->RequestDestroy();
	}
	Coins.clear();
}

Coin* CoinManager::CreateCoin(float posX, float posY)
{
	Coin* NewCoin = GameObject::CreateInstance<Coin>();
	Coins.push_back(NewCoin);
	NewCoin->SetPosition(posX, posY);
	return NewCoin;
}

void CoinManager::SetEnabled(bool bEnabled)
{
	__super::SetEnabled(bEnabled);
	for (auto CoinIter = Coins.begin(); CoinIter != Coins.end(); ++CoinIter)
	{
		Coin& CoinToUpdate = *(*CoinIter);
		CoinToUpdate.SetEnabled(bEnabled);
	}
}