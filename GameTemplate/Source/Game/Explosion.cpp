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

void Explosion::SetExplosionImage(string ImagePath)
{
    if (ExplosionImage)
    {
        ExplosionImage->LoadImage(ImagePath);
    }
}

void Explosion::SetExplosionSound(string SoundPath)
{
    if (ExplosionSound)
    {
        ExplosionSound->LoadSample(SoundPath);
    }
}
