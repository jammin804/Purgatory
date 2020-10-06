#pragma once

#include "Framework/GameObject.h"

class BoxCollisionComponent;

class Laser : public GameObject
{
    public:
        const BoxCollisionComponent* GetCollision() const { return Collision; }
    
    protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

    private:
        float LaserSpeed = 500.0f;
        class ImageComponent* LaserImage = nullptr;
        BoxCollisionComponent* Collision = nullptr;
        class SoundComponent* LaserSound = nullptr;
        float LifeTimer = 0.0f;
        float MaxLifeTime = 5.0f;
};