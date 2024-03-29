#include "CoinManager.h"
#include "Coin.h"
#include "Framework/Globals.h"
#include "Framework/EventMessage.h"
#include "Framework/EventManager.h"
#include "GameEventMessage.h"

void CoinManager::OnInit()
{
	Coins.reserve(MaxCoins);
	AddEventListener(GameEventMessage::EnemyDied);
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
	RemoveEventListener(GameEventMessage::EnemyDied);
}

void CoinManager::OnEvent(const EventMessage& Msg)
{
	if (Msg.messageId == GameEventMessage::EnemyDied)
	{
		if (Msg.payload.size() < 2)
		{
			return;
		}
		
		float WorldPosX = Msg.payload[0].GetAsFloat();
		float WorldPosY = Msg.payload[1].GetAsFloat();

 		int NumberOfCoinsToSpawn = (rand() % 4) + 1;
		for (int i = 0; i < NumberOfCoinsToSpawn; i++)
		{
			CreateCoin(WorldPosX, WorldPosY);
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
	if (Coins.size() < MaxCoins)
	{
		Coin* NewCoin = GameObject::CreateInstance<Coin>();
		NewCoin->SetParent(GetParent());
		Coins.push_back(NewCoin);
		NewCoin->SetWorldPosition(posX, posY);
		return NewCoin;
	}
	
	return nullptr;

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