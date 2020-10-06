#include "Laser.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Framework/SoundComponent.h"

void Laser::OnInit()
{
    LaserImage = new ImageComponent(this);
    Collision = new BoxCollisionComponent(this);
    LaserSound = new SoundComponent(this);
}

void Laser::OnPostInit()
{
    if (LaserImage)
    {
        LaserImage->LoadImage("Art/Laser.png");
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
