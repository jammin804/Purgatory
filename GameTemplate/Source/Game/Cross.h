#pragma once

#include "Framework/GameObject.h"

class BoxCollisionComponent;

class Cross : public GameObject
{
    public:
        const BoxCollisionComponent* GetCollision() const { return Collision; }
		void SetInitialDirection(float x, float y);
		void SetOrbital(bool Orbital) { hasOrbital = true; }
    protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;
    virtual void OnCollision(GameObject* Other) override;

    private:
		float CrossRotationSpeed = 40.0f;
		float CrossSpeed = 500.0f;
		float CrossMovementDirectionX = 0.0f;
		float CrossMovementDirectionY = 0.0f;
        class ImageComponent* CrossImage = nullptr;
        BoxCollisionComponent* Collision = nullptr;
        class SoundComponent* LaserSound = nullptr;
        float LifeTimer = 0.0f;
        float MaxLifeTime = 5.0f;
		bool hasOrbital = false;
		float OrbitalAngle = 0.0f;
};