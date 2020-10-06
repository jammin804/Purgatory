#pragma once
#include "GameComponent.h"
#include <string>

using namespace std;

class ImageComponent : public GameComponent
{
public:
    ImageComponent(class GameObject* Owner);

    void LoadImage(string ImagePath);

    void SetVisible(bool bIsNowVisible);
protected:    
    virtual void OnShutdown() override;

    virtual void OnRender() override;

private:
    struct ALLEGRO_BITMAP* ImageBitmap;
    int ImageWidth = 0;
    int ImageHeight = 0;

    bool bIsVisible = true;
};

