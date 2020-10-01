#pragma once

#include "Framework/GameObject.h"

using namespace std;

class ImageComponent;
class InputComponent;
class SoundComponent;

class Enemy : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnUpdate() override;
    virtual void OnShutdown() override;

public:
    void SetAvatarImage(string ImagePath);
    void SetThrustersImage(string ImagePath);
    void SetThrustersSound(string SoundPath);
private:
    ImageComponent* EnemyAvatarImageComponent = nullptr;
    ImageComponent* EnemyAvatarThrustersImageComponent = nullptr;
    SoundComponent* ThrusterSoundComponent = nullptr;

    float EnemyMovementSpeed = 10.0f;
    float RotationSpeed = 0.2f;
};

