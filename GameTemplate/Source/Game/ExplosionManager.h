#pragma once
#include "Framework/GameObject.h"

class Explosion;

using namespace std;

class ExplosionManager : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnUpdate(float DeltaTime) override;
	virtual void OnShutdown() override;
	virtual void OnEvent(const EventMessage& Msg) override;
	virtual void OnRestart() override;
	virtual void SetEnabled(bool bEnabled) override;
public:
	Explosion* CreateExplosion(float posX, float posY);
private:
};