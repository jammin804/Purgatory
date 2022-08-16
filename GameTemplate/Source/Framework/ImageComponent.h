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

	int GetImageHeight() const;
	int GetImageWidth() const;

	void SetTilingU(int NewTilingU) { TilingU = NewTilingU; }
	void SetTilingV(int NewTilingV) { TilingV = NewTilingV; }
protected:
    virtual void OnShutdown() override;

    virtual void OnRender() override;

private:
	const SBitmapCache* ImageBitmap = nullptr;
	float ScaleX = 1.0f;
	float ScaleY = 1.0f;
	bool ScaleFromLeft = false;
    bool bIsVisible = true;
	int TilingU = 1;
	int TilingV = 1;
};

