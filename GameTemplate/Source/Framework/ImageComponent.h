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
    bool IsVisible() const;
	
	void SetScaleFromLeft(bool NewScaleFromLeft) { ScaleFromLeft = NewScaleFromLeft; }
	void SetScale(float NewScale) { ScaleX = NewScale; ScaleY = NewScale; }
	void SetScaleX(float NewScaleX) { ScaleX = NewScaleX; }
	void SetScaleY(float NewScaleY) { ScaleY = NewScaleY; }
protected:
    virtual void OnShutdown() override;

    virtual void OnRender() override;

private:
    struct ALLEGRO_BITMAP* ImageBitmap;
    int ImageWidth = 0;
    int ImageHeight = 0;
	float ScaleX = 1.0f;
	float ScaleY = 1.0f;
	bool ScaleFromLeft = false;
    bool bIsVisible = true;
};

