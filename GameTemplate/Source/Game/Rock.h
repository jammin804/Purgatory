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

	//handling Enemy Health
	int GetEnemyLivesLeft() const { return EnemyHealthLeft; }
	int GetEnemyMaxLivesLeft() const { return ENEMY_MAX_LIFE; }
	void EnemyHit();
    void SetMovementSpeed(float NewMovementSpeed) { MovementSpeed = NewMovementSpeed; }
    float GetMovementSpeed() const { return MovementSpeed; }
    void SetMovementDirection(float DirX, float DirY) { MovementDirectionX = DirX; MovementDirectionY = DirY; }
    float GetMovementDirectionX() const { return MovementDirectionX; }
    float GetMovementDirectionY() const { return MovementDirectionY; }
	void Switch(); // Function to switch when function is called
	bool SwitchDirection() const { return bNeedsSwitch; } // 
    const BoxCollisionComponent* GetCollision() const { return Collision; }
private:
    float RotationSpeed = 1.0f;
    class ImageComponent* RockImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
	class ImageComponent* EnemyHealth = nullptr;
    float LifeTimer = 0.0f;
    float MaxLifeTime = 30.0f;
	float MoveTimer = 0.0f; // when timer runs out switch
	float MaxMoveTime = 2.0f;
	float ENEMY_MAX_LIFE = 2.0f;
	float EnemyHealthLeft = ENEMY_MAX_LIFE;
    float MovementSpeed = 100.0f;
    float MovementDirectionX = 0.0f;
    float MovementDirectionY = 0.0f;
	bool bNeedsSwitch = false; // bool for switching
private:
	void SetEnemyLifePercentage(float EnemyPercentageLife);
};