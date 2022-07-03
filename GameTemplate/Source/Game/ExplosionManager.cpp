#include "ExplosionManager.h"
#include "GameEvent.h"
#include "Framework/EventManager.h"
#include "Explosion.h"
#include "Framework/EventMessage.h"

void ExplosionManager::OnInit()
{
	Explosions.reserve(25); //May optimize to a pool via resize
	AddEventListener(GameEvent::EnemyHurt);
}

void ExplosionManager::OnUpdate(float DeltaTime)
{
	for (auto iter = Explosions.begin(); iter != Explosions.end();)
	{
		Explosion& ExplosionToUpdate = *(*iter);

		if (ExplosionToUpdate.IsDestroyed())
		{
			iter = Explosions.erase(iter);
			continue;
		}
		++iter;
	}
}

void ExplosionManager::OnShutdown()
{
	RemoveEventListener(GameEvent::EnemyHurt);
}

void ExplosionManager::OnEvent(const EventMessage& Msg)
{
	if(Msg.messageId == GameEvent::EnemyHurt)
	{
		if (Msg.payload.size() < 3)
		{
			return;
		}

		CreateExplosion(Msg.payload[0].GetAsFloat(), Msg.payload[1].GetAsFloat(), Msg.payload[2].GetAsFloat());
	}
}

void ExplosionManager::OnRestart()
{
	for (Explosion* CurrentExplosion : Explosions)
	{
		CurrentExplosion->RequestDestroy();
	}
	Explosions.clear();
}

void ExplosionManager::SetEnabled(bool bEnabled)
{
	__super::SetEnabled(bEnabled);
	for (auto iter = Explosions.begin(); iter != Explosions.end(); ++iter)
	{
		Explosion& ExplosionToUpdate = *(*iter);
		ExplosionToUpdate.SetEnabled(bEnabled);
	}
}

void ExplosionManager::CreateExplosion(float posX, float posY, float ExplosionScale)
{
	Explosion* NewExplosion = GameObject::CreateInstance<Explosion>();
	NewExplosion->SetParent(GetParent());
	NewExplosion->SetWorldPosition(posX, posY);
	NewExplosion->SetExplosionScale(ExplosionScale);
	Explosions.push_back(NewExplosion);
}

