#pragma once

#include "Framework/GameFramework.h"

using namespace std;

class GameObject;

class AsteroidsGame : public GameFramework
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

private:
    void CreateExplosion(float PositionX, float PositionY, float ExplosionScale = 1.0f);

    class Player* Player1 = nullptr;
    class Background* BG = nullptr;
    class RockManager* RockMgr = nullptr;
    class GameFlow* GFlow = nullptr;
    int CurrentScore = 0;
};