#pragma once

#include "Framework/GameObject.h"
#include "Framework/SoundComponent.h"

class BoxCollisionComponent;
class Player;
class Enemy;

class Wall : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;
	virtual void OnCollision(GameObject* Other) override;

public:


private:
	class ImageComponent* WallImage = nullptr;
	BoxCollisionComponent* Collision = nullptr;
	float StartDirX = 0.0f;
	float StartDirY = 0.0f;
};