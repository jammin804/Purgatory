#pragma once

#include "Framework/GameObject.h"

using namespace std;

class ImageComponent;
class SoundComponent;

class Background : public GameObject
{
protected:
    virtual void OnInit() override;
	virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

public:
    void SetImage(string ImagePath);
    void SetMusic(string MusicPath);
	int GetBackgroundHeight() const { return BackgroundHeight; }
	int GetBackgroundWidth() const { return BackgroundWidth; }
private:
	ImageComponent* BackgroundImage;
	SoundComponent* BackgroundMusic = nullptr;
	ImageComponent* WallVImage = nullptr;
	static int const BackgroundHeight = 4320;
	static int const BackgroundWidth = 7680;
};

