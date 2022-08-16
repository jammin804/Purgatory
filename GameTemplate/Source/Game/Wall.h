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
	void SetWidth(int NewWidth) { Width = NewWidth; }
	void SetHeight(int NewHeight) { Height = NewHeight; }

private:
	class ImageComponent* ImageCpt = nullptr;
	BoxCollisionComponent* CollisionCpt = nullptr;
	float StartDirX = 0.0f;
	float StartDirY = 0.0f;
	int Width = 1;
	int Height = 1;
};