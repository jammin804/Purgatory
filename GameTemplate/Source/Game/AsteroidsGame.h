#pragma once

#include "Framework/GameFramework.h"

using namespace std;

class Player;
class Background;
class RockManager;
class GameFlow;
class GUI;
class CoinManger;
class Coin;

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
	Coin* TempCoin = nullptr;
    Background* BG = nullptr;
    RockManager* RockMgr = nullptr;
    GameFlow* GFlow = nullptr;
	GUI* UI = nullptr;
    int CurrentScore = 0;
};