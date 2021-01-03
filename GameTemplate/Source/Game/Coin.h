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

	
public:
    const BoxCollisionComponent* GetCollision() const { return Collision; }
	void CoinCollision();
	void SetCoinDropSound(string SoundPath);
	void SetCoinPickUpSound(string SoundPaht);
private:
    class ImageComponent* CoinImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
	SoundComponent* CoinSoundComponent = nullptr;
	float CoinLifeTimer = 0.0f;
	float const MAX_COIN_LIFE_TIMER = 300.0f;
	//Add Coin StartDirX and StartDirY here for Coin movement
};