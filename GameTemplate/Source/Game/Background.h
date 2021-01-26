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
	void SetWallVImage(string ImagePath);
    void SetMusic(string MusicPath);
	int GetBackgroundHeight() const { return BackgroundHeight; }
	int GetBackgroundWidth() const { return BackgroundWidth; }
private:
    ImageComponent* BackgroundImage = nullptr;
	SoundComponent* BackgroundMusic = nullptr;
	ImageComponent* WallVImage = nullptr;
	int BackgroundHeight = 1440;
	int BackgroundWidth = 2560;
};

