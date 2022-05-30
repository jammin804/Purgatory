#pragma once

#include "Framework/GameObject.h"
#include <vector>

class Rock;
class Player;
class GameFlow;

using namespace std;

class RockManager : public GameObject
{
    protected:
        virtual void OnInit() override;
		virtual void OnPostInit() override;
        virtual void OnUpdate(float DeltaTime) override;
		virtual void OnRestart() override;

    public:      
		const vector<Rock*>& GetRocks() const { return Rocks; }
        virtual void SetEnabled(bool bEnabled) override;
		void SetPlayer(const Player* NewPlayer) { Player1 = NewPlayer; }
    private:
        void SetRandomPosition(Rock& RockToPosition);
        Rock* CreateRock(const int MAX_ENEMY_HEALTH = 2); //Changed Splits Left to Max Enemy Health
private:
        vector<Rock*> Rocks;
		int NumberOfEnemiesToSpawn = 20;
		int NumberOfEnemiesInASpace = 1;
		int OffscreenStart = 0;
		const Player* Player1 = nullptr;
};