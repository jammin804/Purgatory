#pragma once

#include "Framework/GameObject.h"

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

private:
	SBitmapCache* LevelData;
	vector<vector <bool>> SpawnPositions;
};