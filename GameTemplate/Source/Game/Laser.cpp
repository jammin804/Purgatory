#include "Laser.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Framework/SoundComponent.h"

void Laser::OnInit()
{
    LaserImage = GameComponent::CreateInstance<ImageComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
    LaserSound = GameComponent::CreateInstance<SoundComponent>(this);
}

void Laser::OnPostInit()
{
    if (LaserImage)
    {
        LaserImage->LoadImage("Art/Laser.png");
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

void Laser::OnUpdate(float DeltaTime)
{
    float DirectionX = sin(GetRotation()) * LaserSpeed * DeltaTime;
    float DirectionY = cos(GetRotation()) * LaserSpeed * DeltaTime;
    SetPosition(GetPositionX() + DirectionX, GetPositionY() - DirectionY);
    LifeTimer += DeltaTime;
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
    }
}
