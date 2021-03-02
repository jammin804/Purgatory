#pragma once

#include "Framework/GameObject.h"
#include "Player.h"

class BoxCollisionComponent;
class Player;
enum class EEnemyType : int
{
	Demon = 0,
	Bat,
	Golem,
	COUNT
};
enum EEnemyDir : int
{
	Right = 0,
	Down,
	Left,
	Up,
	COUNT
};
enum class EState : int
{
	Idle = 0,
	Patrol,
	Chase,
	Flee,
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
	void SetEnemyDirection(EEnemyDir direction);
    const BoxCollisionComponent* GetCollision() const { return Collision; }
	void SetEnemyType(EEnemyType type);
	EEnemyType GetEnemyType() const; // Trying to access to the enemy types in AsteroidsGame.cpp to change explosion scale
	void SetPlayer(const Player* NewPlayer) { Player1 = NewPlayer; }
	void ChangeDirection();
	EState GetState();

private:
	
    float RotationSpeed = 1.0f;
    class ImageComponent* EnemyImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
	class ImageComponent* EnemyHealthLayer = nullptr;
	class ImageComponent* EnemyHealth = nullptr;
    float LifeTimer = 0.0f;
    float MaxLifeTime = 30.0f;
	float MoveTimer = 0.0f; // when timer runs out switch
	float MaxMoveTime = 3.0f;
	float ENEMY_MAX_LIFE = (float) ((rand() % 4) + 2);
	float EnemyLifeBarScale = 2.0f;
	float EnemyHealthLeft = ENEMY_MAX_LIFE;
    float MovementSpeed = 100.0f;
    float MovementDirectionX = 0.0f;
    float MovementDirectionY = 0.0f;
	bool bNeedsSwitch = false; // bool for switching
	EEnemyType EnemyType = EEnemyType::Demon;
	EEnemyDir EnemyDirection = EEnemyDir::Right;
	EState CurrentState = EState::Idle;
	float MaxIdleTime = 5.0f;
	float TimeInState = MaxIdleTime;
	float MaxDetectionRadius = 0.0f;
	const Player* Player1 = nullptr;
	float CollisionScaleX = 150.0f;
	float CollisionScaleY = 150.0f;
private:
	void SetEnemyLifePercentage(float EnemyPercentageLife);
	void ChangeState(EState NewState);
	void EnterIdleState();
	void UpdateIdleState(float Deltatime);

	bool CheckForChase();

	bool CheckForLostPlayer();
	bool CheckForFear();

	void ExitIdleState();
	void EnterPatrolState();
	void UpdatePatrolState(float Deltatime);
	void ExitPatrolState();
	void EnterChaseState();
	void UpdateChaseState(float Deltatime);
	void ExitChaseState();
	void EnterFleeState();
	void UpdateFleeState(float DeltaTime);
	void ExitFleeState();

	void UpdateMovement(float DesiredX, float DesiredY);
};