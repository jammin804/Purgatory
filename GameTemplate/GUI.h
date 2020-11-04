#pragma once
/* Goals: 
Bring in health bar images into game.
Layer Images so the border is above the life rectangle
Have player's health associate with the health bar
If the player gets hit, scale the life rectangle with by 1/player health
*/

#include "Framework/GameObject.h"


using namespace std;

class ImageComponent;

class GUI : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;
	virtual void OnUpdate(float DeltaTime) override;

public:
	void SetBorderImage(string ImagePath);
	void SetLifeImage(string ImagePath);

private:
	ImageComponent* BorderGUIImageComponent = nullptr;
	ImageComponent* LifeGUIImageComponent = nullptr;
};