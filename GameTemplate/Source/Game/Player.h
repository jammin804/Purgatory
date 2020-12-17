#pragma once

#include "Framework/GameObject.h"

using namespace std;

class BoxCollisionComponent;
class ImageComponent;
class InputComponent;
class SoundComponent;
class Cross;

class Player : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnUpdate(float DeltaTime) override;
	virtual void OnRestart() override;

public:
    void SetAvatarImage(string ImagePath);
    void SetThrustersImage(string ImagePath);
    void SetThrustersSound(string SoundPath);
    bool HandleDeath();
    void CreateCross(float DirX, float DirY);
    vector<Cross*>& GetCross(){ return Crosses; }
    const BoxCollisionComponent* GetCollision() const { return Collision; }
    int GetLivesLeft() const { return HealthLeft; }
	int GetMaxLivesLeft() const { return MAX_LIFE; }
	int GetFearLeft() const { return FearLeft; }
	int GetMaxFearLeft() const { return MAX_FEAR; }
	bool IsInvulnerable() const;
private:
	void SetLivesLeft(int NewLivesLeft) { HealthLeft = NewLivesLeft; }

    ImageComponent* PlayerAvatarImageComponent = nullptr;
    ImageComponent* PlayerAvatarThrustersImageComponent = nullptr;
    InputComponent* InputComp = nullptr;
    SoundComponent* ThrusterSoundComponent = nullptr;
    BoxCollisionComponent* Collision = nullptr;

    float PlayerMovementSpeed = 200.0f;
    float RotationSpeed = 2.0f;
    bool bCanMakeLaser = true;
    vector<Cross*> Crosses;
	const int MAX_LIFE = 5;
    int HealthLeft = MAX_LIFE;
	const int MAX_FEAR = 120;
	int FearLeft = MAX_FEAR;
    bool bInvulnerable = false;
	bool bRespawning = false;
    float RespawnTimer = 0.0f;
    const float RespawningTime = 3.0f;

	int LookingDirectionX = 0;
	int LookingDirectionY = -1;

};

