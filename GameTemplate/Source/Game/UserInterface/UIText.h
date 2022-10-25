#pragma once

#include "Framework/GameObject.h"
#include "UIEndGameMessage.h"

using namespace std;

class TextComponent;

class UIText : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;

public:
    void SetInGame();

	void SetGamePaused();
    void SetYouSurvived(int FinalScore);
    void UpdateScore(int NewScore);
    void UpdateLivesLeft(int NewLivesLeft);
    void UpdateTimeRemaining(int NewTimeMins, int NewTimeSeconds);

private:
    TextComponent* MiddleTextLine1 = nullptr;
    TextComponent* MiddleTextLine2 = nullptr;
    TextComponent* MiddleTextLine3 = nullptr;
	TextComponent* MiddleTextLine4 = nullptr;
	TextComponent* MiddleTextLine5 = nullptr;
	TextComponent* MiddleTextLine6 = nullptr;
	TextComponent* MiddleTextLine7 = nullptr;
	TextComponent* BottomCenterText = nullptr;
	int FontSize = 18;
};

