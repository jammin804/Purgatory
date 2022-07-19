#pragma once

#include "Framework/GameObject.h"
#include <vector>

class Enemy;
class Player;
class GameFlow;

using namespace std;

class EnemyManager : public GameObject
{
    protected:
        virtual void OnInit() override;
		virtual void OnPostInit() override;
        virtual void OnUpdate(float DeltaTime) override;
		virtual void OnRestart() override;

    public:      
		const vector<Enemy*>& GetEnemies() const { return Enemies; }
        virtual void SetEnabled(bool bEnabled) override;
		void SetPlayer(const Player* NewPlayer) { Player1 = NewPlayer; }
    private:
        void SetRandomPosition(Enemy& EnemyToPosition);
        Enemy* CreateEnemy(const int MAX_ENEMY_HEALTH = 2); //Changed Splits Left to Max Enemy Health
private:
        vector<Enemy*> Enemies;
        int NumberOfEnemiesToSpawn = 20;
		//int NumberOfEnemiesToSpawn = 300;
		int NumberOfEnemiesInASpace = 1;
		const Player* Player1 = nullptr;
};