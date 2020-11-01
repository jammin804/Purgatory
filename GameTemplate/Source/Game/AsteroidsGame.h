#pragma once

#include "Framework/GameFramework.h"

using namespace std;

class Player;
class Background;
class RockManager;
class GameFlow;

class AsteroidsGame : public GameFramework
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

private:
    void CreateExplosion(float PositionX, float PositionY, float ExplosionScale = 1.0f);

    Player* Player1 = nullptr;
	Player* Player2 = nullptr;
    Background* BG = nullptr;
    RockManager* RockMgr = nullptr;
    GameFlow* GFlow = nullptr;
    int CurrentScore = 0;
};