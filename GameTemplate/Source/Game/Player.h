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

public:
    void SetAvatarImage(string ImagePath);
    void SetThrustersImage(string ImagePath);
    void SetThrustersSound(string SoundPath);
    bool HandleDeath();
    void CreateCross();
    vector<Cross*>& GetCross(){ return Crosses; }
    const BoxCollisionComponent* GetCollision() const { return Collision; }
    int GetLivesLeft() const { return HealthLeft; }
private:
    ImageComponent* PlayerAvatarImageComponent = nullptr;
    ImageComponent* PlayerAvatarThrustersImageComponent = nullptr;
    InputComponent* InputComp = nullptr;
    SoundComponent* ThrusterSoundComponent = nullptr;
    BoxCollisionComponent* Collision = nullptr;

    float PlayerMovementSpeed = 200.0f;
    float RotationSpeed = 2.0f;
    bool bCanMakeLaser = true;
    vector<Cross*> Crosses;
    int HealthLeft = 5;
    bool bInvulnerable = false;
    bool bRespawning = false;
    bool bExploding = false;
    float ExplodeTimer = 0.0f;
    float RespawnTimer = 0.0f;
    const float ExplodingTime = 3.0f;
    const float RespawningTime = 3.0f;
public:
    bool IsInvulnerable() const; //why is this in another public statement?
};

