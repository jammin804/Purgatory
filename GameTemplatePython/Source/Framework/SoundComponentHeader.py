#pragma once

#include "GameComponent.h"
#include <string>
#include <allegro5/allegro_audio.h>

using namespace std;

class SoundComponent : public GameComponent
{
public:
    SoundComponent(class GameObject* Owner);

    void LoadSample(string SamplePath);
    void Play();
    void Stop();
    void SetLooped(bool bIsNowLooped);
    void SetVolume(float NewVolume);
    bool IsPlaying() const { return bIsPlaying; }

protected:
    virtual void OnInit() override;

    virtual void OnUpdate() override;
    
    virtual void OnShutdown() override;

private:
    ALLEGRO_SAMPLE* AudioSample = nullptr;
    ALLEGRO_SAMPLE_ID AudioSampleId;
    bool bIsLooped = false;
    bool bIsPlaying = false;
    float Volume = 1.0f;
};
