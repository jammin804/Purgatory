#include "Explosion.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"
#include "../GameObjectTypes.h"

void Explosion::OnInit()
{
    SetType(GOT_Explosion);
    ExplosionImage = GameComponent::CreateInstance<ImageComponent>(this);
    ExplosionSound = GameComponent::CreateInstance<SoundComponent>(this);
    ExplosionSound->SetVolume(0.3f);
}

void Explosion::OnPostInit()
{
    ExplosionImage->LoadImage("Art/Bloodsplats.png");
    ExplosionImage->SetScale(ExplosionScale);
	SetRenderDepth(5.0f);
    ExplosionSound->LoadSample("Audio/Hit.wav");
    ExplosionSound->Play();
	SetRotation(rand() % 360);
	int RandomOffSetX = 50 - rand() % 100;
	int RandomOffSetY = 50 - rand() % 100;
	SetPosition(GetPositionX() + RandomOffSetX, GetPositionY() + RandomOffSetY);
}

void Explosion::OnUpdate(float DeltaTime)
{
    ExplosionTimer += DeltaTime;

    if (ExplosionTimer > ExplosionLifetime)
    {
        RequestDestroy();
    }
}

void Explosion::OnShutdown()
{
}
