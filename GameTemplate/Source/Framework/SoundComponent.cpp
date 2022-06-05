#include "SoundComponent.h"


SoundComponent::SoundComponent(class GameObject* Owner)
    : GameComponent(Owner, ComponentType::SoundComponent){}

void SoundComponent::OnShutdown()
{
    if (AudioSample)
    {
        al_destroy_sample(AudioSample);
        AudioSample = nullptr;
    }
}

void SoundComponent::SetLooped(bool bIsNowLooped)
{
    bIsLooped = bIsNowLooped;
}

void SoundComponent::SetVolume(float NewVolume)
{
    Volume = NewVolume;
}

void SoundComponent::LoadSample(string SamplePath)
{
    if (!AudioSample)
    {
        AudioSample = al_load_sample(SamplePath.c_str());
        if (!AudioSample)
        {
            printf("Couldn't load Audio sample\n");
        }
    }
}

void SoundComponent::Play()
{
    if (AudioSample)
    {
        al_play_sample(AudioSample, Volume, 0.0, 1.0, bIsLooped ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE, &AudioSampleId);
        bIsPlaying = true;
    }
}

void SoundComponent::Stop()
{
    al_stop_sample(&AudioSampleId);
    bIsPlaying = false;
}
