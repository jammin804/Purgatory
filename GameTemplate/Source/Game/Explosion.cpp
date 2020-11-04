#include "Explosion.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"

void Explosion::OnInit()
{
    ExplosionImage = GameComponent::CreateInstance<ImageComponent>(this);
    ExplosionSound = GameComponent::CreateInstance<SoundComponent>(this);
    ExplosionSound->SetVolume(0.3f);
}

void Explosion::OnPostInit()
{
    ExplosionImage->LoadImage("Art/Bloodsplats.png");
    ExplosionImage->SetScale(ExplosionScale);
    ExplosionSound->LoadSample("Audio/Hit.wav");
    ExplosionSound->Play();
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
