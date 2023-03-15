#pragma once

#include "Framework/GameObject.h"

class Wall;
class Enemy;

using namespace std;

enum class SpawnType
{
	Empty,
	Wall,
	Enemy
};

class LevelManager : public GameObject
{
protected:
	virtual void OnInit() override;



	virtual void OnPostInit() override;

	virtual void SetEnabled(bool bEnabled) override;
	virtual void OnEvent(const EventMessage& Msg) override;
	virtual void OnShutdown() override;

private:
	Wall* CreateWall(float posX, float posY, int Width, int Height); 
	void ReadLevelImage(string LevelImagePath);
	void PopulateWorld();
	void UnloadWorld();

private:
	SBitmapCache* LevelData;
	string LevelImage = "Art/Level.png";
	vector<vector <SpawnType>> SpawnPositions;
	vector<Wall*> Walls;
	int MaxWalls = 100;
};