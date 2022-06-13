#include "ExplosionManager.h"
#include "EventMessage.h"
#include "Framework/EventManager.h"

void ExplosionManager::OnInit()
{
	AddEventListener(GameEvent::EnemyDied);
}

void ExplosionManager::OnUpdate(float DeltaTime)
{

}

void ExplosionManager::OnShutdown()
{
	RemoveEventListener(GameEvent::EnemyDied);
}

void ExplosionManager::OnEvent(const EventMessage& Msg)
{
	if(Msg.messageId == GameEvent::EnemyDied)
	{
		int NumberOfCoinsToSpawn = (rand() % 4) + 1;
		for (int i = 0; i < NumberOfCoinsToSpawn; i++)
		{
			CreateCoin(Msg.PayloadFloats[0], Msg.PayloadFloats[1]);
		}
	}
}

