#pragma once

#include "Framework/GameObject.h"

using namespace std;

class BoxCollisionComponent;
class ImageComponent;
class InputComponent;
class SoundComponent;
class Laser;

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
    void CreateLaser();
    vector<Laser*>& GetLasers(){ return Lasers; }
    const BoxCollisionComponent* GetCollision() const { return Collision; }
    int GetLivesLeft() const { return LivesLeft; }
private:
    ImageComponent* PlayerAvatarImageComponent = nullptr;
    ImageComponent* PlayerAvatarThrustersImageComponent = nullptr;
    InputComponent* InputComp = nullptr;
    SoundComponent* ThrusterSoundComponent = nullptr;
    BoxCollisionComponent* Collision = nullptr;

    float PlayerMovementSpeed = 200.0f;
    float RotationSpeed = 2.0f;
    bool bCanMakeLaser = true;
    vector<Laser*> Lasers;
    int LivesLeft = 2;
    bool bInvulnerable = false;
    bool bRespawning = false;
    bool bExploding = false;
    float ExplodeTimer = 0.0f;
    float RespawnTimer = 0.0f;
    const float ExplodingTime = 3.0f;
    const float RespawningTime = 3.0f;
public:
    bool IsInvulnerable() const;
};

