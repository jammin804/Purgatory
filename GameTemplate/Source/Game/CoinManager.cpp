#include "CoinManager.h"
#include "Coin.h"
#include "Framework/Globals.h"
#include "EventMessage.h"
#include "Framework/EventManager.h"

void CoinManager::OnInit()
{
	Coins.reserve(100);
	AddEventListener(GameEvent::EnemyDied);
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

void CoinManager::OnShutdown()
{
	RemoveEventListener(GameEvent::EnemyDied);
}

void CoinManager::OnEvent(const EventMessage& Msg)
{
	if (Msg.messageId == GameEvent::EnemyDied)
	{
 		int NumberOfCoinsToSpawn = (rand() % 4) + 1;
		for (int i = 0; i < NumberOfCoinsToSpawn; i++)
		{
			CreateCoin(Msg.PayloadFloats[0], Msg.PayloadFloats[1]);
		}
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
	NewCoin->SetParent(GetParent());
	Coins.push_back(NewCoin);
	NewCoin->SetWorldPosition(posX, posY);
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