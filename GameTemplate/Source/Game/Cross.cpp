#include "Cross.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Framework/SoundComponent.h"
#include "../GameObjectTypes.h"
#include "GameEventMessage.h"
#include "Framework/EventManager.h"
#include "Framework/EventMessage.h"



void Cross::OnInit()
{
	SetType(GOT_Cross);
    CrossImage = GameComponent::CreateInstance<ImageComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
    LaserSound = GameComponent::CreateInstance<SoundComponent>(this);
}

void Cross::OnPostInit()
{
    if (CrossImage)
    {
        CrossImage->LoadImage("Art/cross.png");
    }

    if (Collision)
    {
        Collision->SetCollisionSize(10.0f, 20.0f);
    }
    
    if (LaserSound)
    {
        LaserSound->LoadSample("Audio/Laser.wav");
        LaserSound->SetVolume(0.1f);
        LaserSound->Play();
    }
}

void Cross::OnUpdate(float DeltaTime)
{
	if (!hasOrbital)
	{
		float DirectionX = CrossMovementDirectionX * CrossSpeed * DeltaTime;
		float DirectionY = CrossMovementDirectionY * CrossSpeed * DeltaTime;
		SetPosition(GetPositionX() + DirectionX, GetPositionY() - DirectionY);
	}
	else
	{
		// Moving Bullet in a circle formation
		float PosX = 0.0f;
		float PosY = 0.0f;
		float OriginX = GetParent()->GetWorldPositionX();
		float OriginY = GetParent()->GetWorldPositionY();
		float Radius = 100.0f;
		float PI = 3.14;

		PosX = OriginX + cos(OrbitalAngle)*Radius;
		PosY = OriginY + sin(OrbitalAngle)*Radius;
		const float SpinSpeed = 10.0f;
		OrbitalAngle += SpinSpeed * DeltaTime;
		SetWorldPosition(PosX, PosY);
	}
	SetRotation(GetRotation() + CrossRotationSpeed * DeltaTime);


    LifeTimer += DeltaTime;
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
    }

}

void Cross::OnCollision(GameObject* Other)
{
	if (Other->GetType() == static_cast<int>(GOT_Enemy))
	{
		RequestDestroy();
		EventManager::BroadcastEvent(GameEventMessage::CrossDestroyed);	
	}
}

void Cross::SetInitialDirection(float x, float y)
{
	CrossMovementDirectionX = x;
	CrossMovementDirectionY = y;
}
