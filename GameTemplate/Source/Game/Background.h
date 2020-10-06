#pragma once

#include "Framework/GameObject.h"

using namespace std;

class ImageComponent;
class SoundComponent;

class Background : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnUpdate(float DeltaTime) override;
    virtual void OnShutdown() override;

public:
    void SetImage(string ImagePath);
    void SetMusic(string MusicPath);
private:
    ImageComponent* BackgroundImage = nullptr;
    SoundComponent* BackgroundMusic = nullptr;
};

