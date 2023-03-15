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
        virtual void OnEvent(const EventMessage& Msg) override;
        virtual void OnShutdown() override;

    public:      
		const vector<Enemy*>& GetEnemies() const { return Enemies; }
        virtual void SetEnabled(bool bEnabled) override;
		void SetPlayer(const Player* NewPlayer) { Player1 = NewPlayer; }
    private:
        void SetRandomPosition(Enemy& EnemyToPosition);
        Enemy* CreateEnemy();
        void ClearEnemy();
private:
        vector<Enemy*> Enemies;
        int NumberOfEnemiesToSpawn = 20; //TODO: Is this needed?
		//int NumberOfEnemiesToSpawn = 300;
		int NumberOfEnemiesInASpace = 1;
		const Player* Player1 = nullptr;
};