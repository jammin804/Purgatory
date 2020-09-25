#pragma once

#include "Framework/GameFramework.h"

using namespace std;

class GameObject;

class AsteroidsGame : public GameFramework
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate() override;

private:
    class UIText* PlayerScore;
    class Player* Player1;
    class Background* BG;
    int CurrentScore = 0;
};