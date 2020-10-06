#pragma once

#include "Framework/GameObject.h"
#include <vector>

class Rock;

using namespace std;

class RockManager : public GameObject
{
    protected:
        virtual void OnInit() override;
        virtual void OnUpdate(float DeltaTime) override;

    public:
        Rock* CreateRock(int SplitsLeft = 2);
        vector<Rock*>& GetRocks() { return Rocks; }
    private:
        void SetRandomPosition(Rock& RockToPosition);
private:
        vector<Rock*> Rocks;
        float TimeSinceSpawn = 0.0f;
        float SpawnTimer = 3.0f;
};