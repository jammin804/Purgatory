#include "ExplosionManager.h"
#include "EventMessage.h"
#include "Framework/EventManager.h"
#include "Explosion.h"

void ExplosionManager::OnInit()
{
	Explosions.reserve(100);
	AddEventListener(GameEvent::EnemyHurt);
}

void ExplosionManager::OnUpdate(float DeltaTime)
{

}

void ExplosionManager::OnShutdown()
{
	RemoveEventListener(GameEvent::EnemyHurt);
}

void ExplosionManager::OnEvent(const EventMessage& Msg)
{
	if(Msg.messageId == GameEvent::EnemyHurt)
	{

		CreateExplosion(Msg.PayloadFloats[0], Msg.PayloadFloats[1], Msg.PayloadFloats[2]);
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

}

Explosion* ExplosionManager::CreateExplosion(float posX, float posY, float ExplosionScale)
{
	Explosion* NewExplosion = GameObject::CreateInstance<Explosion>();
	NewExplosion->SetParent(GetParent());
	NewExplosion->SetWorldPosition(posX, posY);
	NewExplosion->SetExplosionScale(ExplosionScale);
}

