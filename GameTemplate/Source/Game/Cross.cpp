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
    float DirectionX = CrossMovementDirectionX * CrossSpeed * DeltaTime;
    float DirectionY = CrossMovementDirectionY * CrossSpeed * DeltaTime;
    SetPosition(GetPositionX() + DirectionX, GetPositionY() - DirectionY);
	SetRotation(GetRotation() + CrossRotationSpeed * DeltaTime);

	// Moving Bullet in a circle formation
	/*float PosX = 0.0f;
	float PosY = 0.0f;
	float OriginX = GetPositionX();
	float OriginY = GetPositionY();
	float Radius = 10.0f;
	int Angle = 0;
	float PI = 3.14;

	PosX = OriginX + cos(Angle)*Radius;
	PosY = OriginY + sin(Angle)*Radius;

	Angle += 2 * PI / 180;*/

    LifeTimer += DeltaTime;
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
    }

}

void Cross::SetInitialDirection(float x, float y)
{
	CrossMovementDirectionX = x;
	CrossMovementDirectionY = y;
}
