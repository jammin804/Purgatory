#pragma once

#include "Framework/GameObject.h"

class BoxCollisionComponent;
enum class EEnemyType : int
{
	Demon = 0,
	Bat,
	Golem,
	COUNT
};
class Rock : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;
	virtual void OnRestart() override;

public:


	float GetEnemyLivesLeft() const { return EnemyHealthLeft; }
	float GetEnemyMaxLivesLeft() const { return ENEMY_MAX_LIFE; }
	void EnemyHit();
    void SetMovementSpeed(float NewMovementSpeed) { MovementSpeed = NewMovementSpeed; }
    float GetMovementSpeed() const { return MovementSpeed; }
    void SetMovementDirection(float DirX, float DirY) { MovementDirectionX = DirX; MovementDirectionY = DirY; }
    float GetMovementDirectionX() const { return MovementDirectionX; }
    float GetMovementDirectionY() const { return MovementDirectionY; }
	void Switch(); // Function to switch when function is called
	bool SwitchDirection() const { return bNeedsSwitch; } // 
    const BoxCollisionComponent* GetCollision() const { return Collision; }
	void SetEnemyType(EEnemyType type);
private:
    float RotationSpeed = 1.0f;
    class ImageComponent* RockImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
	class ImageComponent* EnemyHealthLayer = nullptr;
	class ImageComponent* EnemyHealth = nullptr;
    float LifeTimer = 0.0f;
    float MaxLifeTime = 30.0f;
	float MoveTimer = 0.0f; // when timer runs out switch
	float MaxMoveTime = 2.0f;
	float ENEMY_MAX_LIFE = (float) ((rand() % 4) + 2);
	float EnemyLifeBarScale = 2.0f;
	float EnemyHealthLeft = ENEMY_MAX_LIFE;
    float MovementSpeed = 100.0f;
    float MovementDirectionX = 0.0f;
    float MovementDirectionY = 0.0f;
	bool bNeedsSwitch = false; // bool for switching
	EEnemyType EnemyType = EEnemyType::Demon;
private:
	void SetEnemyLifePercentage(float EnemyPercentageLife);
};