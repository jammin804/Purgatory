#include "Cross.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Framework/SoundComponent.h"

void Cross::OnInit()
{
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
    float DirectionX = sin(GetRotation()) * CrossSpeed * DeltaTime;
    float DirectionY = cos(GetRotation()) * CrossSpeed * DeltaTime;
    SetPosition(GetPositionX() + DirectionX, GetPositionY() - DirectionY);

	/*SetRotation(GetRotation() + CrossRotationSpeed * DeltaTime); // Issues trying to get the cross to both rotate and move across the screen.

	SetPosition(GetPositionX() + (CrossMovementDirectionX * CrossSpeed * DeltaTime),
		GetPositionY() + (CrossMovementDirectionY * CrossSpeed * DeltaTime));
    LifeTimer += DeltaTime;*/
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
    }
}
