#pragma once

#include "Framework/GameObject.h"
#include "Framework/SoundComponent.h"

class BoxCollisionComponent;

class Coin : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

	void UpdateMovement(float DeltaTime);

	
public:
    const BoxCollisionComponent* GetCollision() const { return Collision; }
	void CoinCollision();
private:
    class ImageComponent* CoinImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
	SoundComponent* CoinSoundComponentDrop = nullptr;
	float CoinLifeTimer = 0.0f;
	float const MAX_COIN_LIFE_TIMER = 300.0f;
	float StartDirX = 0.0f;
	float StartDirY = 0.0f;
	float HorizontalMovementSpeed = 1000.0f;
	float VerticalMovementSpeed = 1000.0f;
	float StartPosY = 0.0f;
};