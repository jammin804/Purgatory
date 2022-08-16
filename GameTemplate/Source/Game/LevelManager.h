#pragma once

#include "Framework/GameObject.h"

class Wall;

using namespace std;

class LevelManager : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;
// 	virtual void OnUpdate(float DeltaTime) override;
// 	virtual void OnShutdown() override;
// 	virtual void OnEvent(const EventMessage& Msg) override;
// 	virtual void OnRestart() override;
// 	virtual void SetEnabled(bool bEnabled) override;

public:
	Wall* CreateWall(float posX, float posY, int Width, int Height); 

	vector<Wall*>& GetCoins() { return Walls; }
private:
	SBitmapCache* LevelData;
	vector<vector <bool>> SpawnPositions;
	vector<Wall*> Walls;
	int MaxWalls = 100;
};