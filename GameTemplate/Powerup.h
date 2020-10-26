#pragma once

#include "Framework/GameObject.h"

class BoxCollisionComponent;

class Powerup : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;
	virtual void OnUpdate(float DeltaTime) override;

public:
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
	float MovementSpeed = 100.0f;
	float MovementDirectionX = 0.0f;
	float MovementDirectionY = 0.0f;
};