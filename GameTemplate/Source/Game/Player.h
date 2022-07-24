#pragma once

#include "Framework/GameObject.h"



using namespace std;

class BoxCollisionComponent;
class ImageComponent;
class InputComponent;
class SoundComponent;
class Cross;
class Background;
class Wall;

class Player : public GameObject
{
protected:
    virtual void OnInit() override;
	virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;
	virtual void OnShutdown() override;
	virtual void OnCollision(GameObject* Other) override;
	virtual void OnEvent(const EventMessage& Msg) override;
	virtual void OnRestart() override;

public:
    void SetAvatarImage(string ImagePath);
    bool HandleDeath();
    void CreateCross(float DirX, float DirY);
    const vector<Cross*>& GetCross() const { return Crosses; }
    const BoxCollisionComponent* GetCollision() const { return Collision; }
    int GetLivesLeft() const { return HealthLeft; }
	int GetMaxLivesLeft() const { return MaxLife; }
	int GetFearLeft() const { return FearLeft; }
	int GetMaxFearLeft() const { return MAX_FEAR; }
	bool IsInvulnerable() const;
	void CollectCoin();
	int GetNumberOfCoins() const { return NumberOfCoins; }
	void SetBackground(Background* NewBG) { BG = NewBG; }
	void UpgradeWeaponLevel() { WeaponLevel = WeaponLevel < 2 ? WeaponLevel+1 : WeaponLevel; }
	void UpgradeSpeedLevel() { SpeedLevel = SpeedLevel < 2 ? SpeedLevel + 1 : SpeedLevel; }
	void UpdgradeHealthLevel() { HealthLevel = HealthLevel < 2 ? HealthLevel + 1 : HealthLevel; }
	void SpendCoins(int NumberOfCoinsToSpend) { NumberOfCoins -= NumberOfCoinsToSpend; }
	void RewindPosition();
	int WeaponLevel = 0;
	int SpeedLevel = 0;
	int HealthLevel = 0;

private:
	void SetLivesLeft(int NewLivesLeft) { HealthLeft = NewLivesLeft; }
	void SetFearLeft(int NewFearLeft) { FearLeft = NewFearLeft;  }
	void ShootSpread();
	void ShootOrbital();
	void ShootBase();
	void UpdateWeapon();
	void UpdateSprite();
	void UpdateMovement(float DeltaTime);
	void UpdateRespawn(float DeltaTime);
	ImageComponent* PlayerAvatarImageComponent = nullptr;
    ImageComponent* PlayerAvatarThrustersImageComponent = nullptr;
    InputComponent* InputComp = nullptr;
	SoundComponent* CoinSoundComponentPickup = nullptr;
    BoxCollisionComponent* Collision = nullptr;
	Background* BG = nullptr;
	Wall* WallImg = nullptr;

	static const float BASE_MOVEMENT_SPEED;
    float PlayerVerticalMovementSpeed = BASE_MOVEMENT_SPEED;
	float PlayerHorizontalMovementSpeed = BASE_MOVEMENT_SPEED;
    float RotationSpeed = 2.0f;
    bool bCanMakeLaser = true;
    vector<Cross*> Crosses;
	static const int BASE_LIFE = 5;
	int MaxLife = BASE_LIFE;
    int HealthLeft = MaxLife;
	const int MAX_FEAR = 120;
	int FearLeft = MAX_FEAR;
    bool bInvulnerable = false;
	bool bRespawning = false;
    float RespawnTimer = 0.0f;
    const float RespawningTime = 3.0f;
	float SpreadAmount = 30.0f;
	int LookingDirectionX = 0;
	int LookingDirectionY = -1;

	int NumberOfCoins = 0;

	float PreviousPosX = 0.0f;
	float PreviousPosY = 0.0f;

};

