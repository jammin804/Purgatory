#pragma once

#include "Framework/GameObject.h"

using namespace std;

class ImageComponent;
class InputComponent;
class SoundComponent;

class Sfx : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;
    virtual void OnShutdown() override;

public:
   
private:
    SoundComponent* SfxSound = nullptr;
	float SfxLifetime = 0.2f;
	float SfxTimer = 0.0f;
};

