#pragma once
/* Goals: 
Bring in health bar images into game.
Layer Images so the border is above the life rectangle
Have player's health associate with the health bar
If the player gets hit, scale the life rectangle with by 1/player health
*/

#include "Framework/GameObject.h"
#include "Player.h"


using namespace std;

class ImageComponent;
class Player; 
class GameFlow;
class UIText;

class GUI : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;
	virtual void OnUpdate(float DeltaTime) override;

public:
	void SetBorderImage(string ImagePath);
	void SetLifeImage(string ImagePath);
	void SetFearImage(string ImagePath);
	void SetFearBorderImage(string ImagePath);
	void SetPlayer(const Player* NewPlayer) { player = NewPlayer; }
	void SetCoinImage(string ImagePath);
	void SetFearPercentage(float FearPercentageLife);
	//void UpdateFearRemaining(int NewTimeMins, int NewTimeSeconds);
	
private:
	void SetLifePercentage(float PercentageLife);
private:
	ImageComponent* BorderGUIImageComponent = nullptr;
	ImageComponent* LifeGUIImageComponent = nullptr;
	ImageComponent* FearGUIImageComponent = nullptr;
	ImageComponent* FearBorderGUIImageComponent = nullptr;
	ImageComponent* CoinGUIImageComponent = nullptr;
	const Player* player = nullptr;
	const UIText* uitext = nullptr;
	const float MAX_LIFESCALE = 2.0f;
};