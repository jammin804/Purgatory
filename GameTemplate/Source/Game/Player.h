#pragma once

#include "Framework/GameObject.h"

using namespace std;

class ImageComponent;
class InputComponent;
class SoundComponent;

class Player : public GameObject
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
    ImageComponent* PlayerAvatar = nullptr;
    ImageComponent* PlayerAvatarThrusters = nullptr;
    InputComponent* InputComp = nullptr;
    SoundComponent* ThrusterSound = nullptr;

    float PlayerMovementSpeed = 10.0f;
    float RotationSpeed = 0.2f;
};

