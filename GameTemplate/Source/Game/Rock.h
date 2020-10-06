#pragma once

#include "Framework/GameObject.h"

class BoxCollisionComponent;

class Rock : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

public:
    void SetSplitsLeft(int NewSplitsLeft) { SplitsLeft = NewSplitsLeft; }
    int GetSplitsLeft() const { return SplitsLeft; }

    void Split();
    bool NeedsSplit() const { return bNeedsSplit; }

    void SetMovementSpeed(float NewMovementSpeed) { MovementSpeed = NewMovementSpeed; }
    float GetMovementSpeed() const { return MovementSpeed; }
    void SetMovementDirection(float DirX, float DirY) { MovementDirectionX = DirX; MovementDirectionY = DirY; }
    float GetMovementDirectionX() const { return MovementDirectionX; }
    float GetMovementDirectionY() const { return MovementDirectionY; }
    const BoxCollisionComponent* GetCollision() const { return Collision; }
private:
    float RotationSpeed = 1.0f;
    class ImageComponent* RockImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
    float LifeTimer = 0.0f;
    float MaxLifeTime = 30.0f;
    bool bNeedsSplit = false;
    int SplitsLeft = 2;
    float MovementSpeed = 100.0f;
    float MovementDirectionX = 0.0f;
    float MovementDirectionY = 0.0f;
public:
    void RequestSplit();
};