#pragma once

#include "Framework/GameObject.h"

using namespace std;

class ImageComponent;
class InputComponent;
class SoundComponent;

class Explosion : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnUpdate(float DeltaTime) override;
    virtual void OnShutdown() override;

public:
    void SetExplosionImage(string ImagePath);
    void SetExplosionSound(string SoundPath);
    void SetExplosionScale(float Scale) { ExplosionScale = Scale; }
private:
    ImageComponent* ExplosionImage = nullptr;
    SoundComponent* ExplosionSound = nullptr;

    float ExplosionScale = 1.0f;
    float ExplosionLifetime = 2.0f;
    float ExplosionTimer = 0.0f;
};

