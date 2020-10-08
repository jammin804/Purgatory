#pragma once

#include "Framework/GameObject.h"

using namespace std;

class TextComponent;

class UIText : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnShutdown() override;

public:
    void SetWelcomeToTheGame();
    void SetInGame();
    void SetGameOver(int FinalScore);
    void SetYouSurvived(int FinalScore);
    void UpdateScore(int NewScore);
    void UpdateLivesLeft(int NewLivesLeft);
    void UpdateTimeRemaining(int NewTimeMins, int NewTimeSeconds);
private:
    TextComponent* TopLeftText = nullptr;
    TextComponent* TopCenterText = nullptr;
    TextComponent* TopRightText = nullptr;
    TextComponent* MiddleTextLine1 = nullptr;
    TextComponent* MiddleTextLine2 = nullptr;
    TextComponent* MiddleTextLine3 = nullptr;
};

