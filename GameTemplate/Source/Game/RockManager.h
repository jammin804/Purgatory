#pragma once

#include "Framework/GameObject.h"
#include <vector>

class Rock;

using namespace std;

class RockManager : public GameObject
{
    protected:
        virtual void OnInit() override;
		virtual void OnPostInit() override;
        virtual void OnUpdate(float DeltaTime) override;
		virtual void OnRestart() override;

    public:
        Rock* CreateRock(const int MAX_ENEMY_HEALTH = 2); //Changed Splits Left to Max Enemy Health
        vector<Rock*>& GetRocks() { return Rocks; }
        virtual void SetEnabled(bool bEnabled) override;
    private:
        void SetRandomPosition(Rock& RockToPosition);
private:
        vector<Rock*> Rocks;
		int NumberOfEnemiesToSpawn = 20;
};