#include "Sfx.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"

void Sfx::OnInit()
{
    SfxSound = GameComponent::CreateInstance<SoundComponent>(this);
    SfxSound->SetVolume(0.3f);
}

void Sfx::OnPostInit()
{
    SfxSound->LoadSample("Audio/Pickup");
    SfxSound->Play();
}

void Sfx::OnUpdate(float DeltaTime)
{
    SfxTimer += DeltaTime;

    if (SfxTimer > SfxLifetime)
    {
        RequestDestroy();
    }
}

void Sfx::OnShutdown()
{
}
