#pragma once

#include "Framework/GameFramework.h"

using namespace std;

class Player;
class Background;
class Wall;
class EnemyManager;
class GameFlow;
class GUI;
class CoinManager;
class ExplosionManager;
class LevelManager;

class AsteroidsGame : public GameFramework
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;

private:
    Player* Player1 = nullptr;
	Player* Player2 = nullptr;
	CoinManager* CoinMgr = nullptr;
    ExplosionManager* ExplodeMgr = nullptr;
    Background* BG = nullptr;
    Wall* WallImg = nullptr;
    EnemyManager* EnemyMgr = nullptr;
    GameFlow* GFlow = nullptr;
	GUI* UI = nullptr;
    LevelManager* LevelMgr = nullptr;

};