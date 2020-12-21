#pragma once

#include "Framework/GameObject.h"

class BoxCollisionComponent;

class Coin : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

	void CoinCollision();
public:
    const BoxCollisionComponent* GetCollision() const { return Collision; }
private:
    class ImageComponent* CoinImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
	float CoinLifeTimer = 0.0f;
	float const MAX_COIN_LIFE_TIMER = 2.0f;
	float Co
};