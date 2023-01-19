#pragma once

#include "Framework/GameFramework.h"

using namespace std;

class Player;
class Background;
class EnemyManager;
class GameFlow;
class UIHUD;
class CoinManager;
class ExplosionManager;
class LevelManager;

class PurgatoryGame : public GameFramework
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
    EnemyManager* EnemyMgr = nullptr;
    GameFlow* GFlow = nullptr;
	UIHUD* UI = nullptr;
    LevelManager* LevelMgr = nullptr;

};