#include "Explosion.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"

void Explosion::OnInit()
{
    ExplosionImage = new ImageComponent(this);
    ExplosionSound = new SoundComponent(this);
    ExplosionSound->SetVolume(0.3f);
}

void Explosion::OnPostInit()
{
    ExplosionImage->LoadImage("Art/Explosion.png");
    ExplosionSound->LoadSample("Audio/Explosion.wav");
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
    delete ExplosionImage;
    ExplosionImage = nullptr;

    delete ExplosionSound;
    ExplosionSound = nullptr;
}
