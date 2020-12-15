#pragma once

#include "Framework/GameObject.h"

class BoxCollisionComponent;

class Coin : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

public:
    const BoxCollisionComponent* GetCollision() const { return Collision; }
private:
    float RotationSpeed = 1.0f;
    class ImageComponent* CoinImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
};