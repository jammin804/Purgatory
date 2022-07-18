#include "Enemy.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Game/Player.h"
#include "Background.h"
#include "../GameObjectTypes.h"
#include "GameEvent.h"
#include "Framework/EventManager.h"
#include "Framework/EventMessage.h"

void Enemy::OnInit()
{
	SetType(GOT_Enemy);
    EnemyImage = GameComponent::CreateInstance<ImageComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	EnemyHealthLayer = GameComponent::CreateInstance<ImageComponent>(this);
	EnemyHealth = GameComponent::CreateInstance<ImageComponent>(this);
	//Player1 = GameObject::CreateInstance<Player>();
}

void Enemy::OnPostInit()
{
	IsEnabled();

	float HealthBarOffsetX = -50.0f;
	float HealthBarOffsetY = -60.0f;
	std::string EnemyImagePath = "";
	float EnemyScale = 1.0f;


	switch (EnemyType)
	{
	case EEnemyType::Demon:
	default:
	{
		EnemyImagePath = "Art/Enemy_D.png";
		//EnemyScale = ENEMY_MAX_LIFE *0.5f;
		HealthBarOffsetX = -100.0f;
		HealthBarOffsetY = -60.0f;
		CollisionScaleX = 150.0f;
		CollisionScaleY = 150.0f;
		break;
	}

	case EEnemyType::Bat:
	{
		EnemyImagePath = "Art/Enemy_Bat.png";
		EnemyLifeBarScale = 0.5f;
		HealthBarOffsetX = -30.0f;
		HealthBarOffsetY = -15.0f;
		EnemyScale = 1.0f;
		CollisionScaleX = 40.0f;
		CollisionScaleY = 40.0f;
		break;
	}

	case EEnemyType::Golem:
	{
		EnemyImagePath = "Art/Enemy_Golem.png";
		CollisionScaleX = 200.0f;
		CollisionScaleY = 150.0f * 1.5;
		HealthBarOffsetX = -160.0f;
		HealthBarOffsetY = -70.0f;
		break;
	}
	}

    if (EnemyImage)
    {
		EnemyImage->LoadImage(EnemyImagePath);
		EnemyImage->SetScale(EnemyScale);
    }

	if (EnemyHealthLayer)
	{
		EnemyHealthLayer->SetScaleFromLeft(true);
		EnemyHealthLayer->LoadImage("Art/enemyhealthbar_layer.png");

		EnemyHealthLayer->SetOffsetY(HealthBarOffsetX);
		EnemyHealthLayer->SetOffsetX(HealthBarOffsetY);
		EnemyHealthLayer->SetScaleX(EnemyLifeBarScale);
	}

	if (EnemyHealth) 
	{

		EnemyHealth->SetScaleFromLeft(true);
		EnemyHealth->LoadImage("Art/enemyhealthbar.png");

		EnemyHealth->SetOffsetY(HealthBarOffsetX);
		EnemyHealth->SetOffsetX(HealthBarOffsetY);
		EnemyHealth->SetScaleX(EnemyLifeBarScale);
	}

	if (Collision)
	{
		
		Collision->SetCollisionSize(CollisionScaleX, CollisionScaleY);
	}

	EnterIdleState();
}

void Enemy::OnUpdate(float DeltaTime)
{

	switch (CurrentState)
	{
	case EState::Idle:
		UpdateIdleState(DeltaTime);
		break;
	case EState::Patrol:
		UpdatePatrolState(DeltaTime);
		break;
	case EState::Chase:
		UpdateChaseState(DeltaTime);
		break;
	case EState::Flee:
		UpdateFleeState(DeltaTime);
		break;

	}

	TimeInState += DeltaTime;
}

void Enemy::OnRestart()
{
	SetEnabled(false);
	//RequestDestroy();
}

void Enemy::OnCollision(GameObject* Other)
{
	if (Other->GetType() == static_cast<int>(GOT_Cross))
	{
		TakeDamage();
	}
}

void Enemy::SetEnemyLifePercentage(float EnemyPercentageLife)
{
	EnemyHealth->SetScaleX(EnemyLifeBarScale * EnemyPercentageLife);
}


void Enemy::ChangeState(EState NewState)
{
	switch(CurrentState)
	{
	case EState::Idle:
		ExitIdleState();
		break;
	case EState::Patrol:
		ExitPatrolState();
		break;
	case EState::Chase:
		ExitChaseState();
		break;
	case EState::Flee:
		ExitFleeState();
		break;

	}
	switch (NewState)
	{
	case EState::Idle:
		EnterIdleState();
		break;
	case EState::Patrol:
		EnterPatrolState();
		break;
	case EState::Chase:
		EnterChaseState();
		break;
	case EState::Flee:
		EnterFleeState();
		break;
	}

	CurrentState = NewState;
	TimeInState = 0.0f;
}

float RandomRange(float min, float max) 
{
	float Accuracy = 1000.0f;
	float Range = (max - min) * Accuracy;

	int RandomNum = rand() % static_cast <int> (Range);

	return (RandomNum / Accuracy) + min;
}

void Enemy::EnterIdleState()
{
	//Initializing information - change to switch
	std::string EnemyImagePath = "";
	if (EnemyType == EEnemyType::Demon)
	{
		EnemyImagePath = "Art/Enemy_D.png";
		MaxIdleTime = RandomRange(3.0f, 5.0f);
		MaxDetectionRadius = 300.0f;

	}
	else if (EnemyType == EEnemyType::Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat.png";
		MaxIdleTime = RandomRange(1.0f, 3.0f);
		MaxDetectionRadius = 300.0f;

	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem.png";
		MaxIdleTime = RandomRange(5.0f, 7.0f);
		MaxDetectionRadius = 300.0f;

	}

	EnemyImage->LoadImage(EnemyImagePath);

}

void Enemy::UpdateIdleState(float Deltatime)
{
	if (CheckForFear())
	{
		return;
	}

	if (CheckForChase())
	{
		return;
	}

	if(TimeInState >= MaxIdleTime)
	{
		ChangeState(EState::Patrol);
	}

}

bool Enemy::CheckForChase()
{
	float DirectionToPlayerX = Player1->GetWorldPositionX() - GetWorldPositionX();
	float DirectionToPlayerY = Player1->GetWorldPositionY() - GetWorldPositionY();
	float DirectionSize = sqrt(pow(DirectionToPlayerX, 2) + pow(DirectionToPlayerY, 2));

	if (DirectionSize <= MaxDetectionRadius) // Added new rand range to detection but its just blinks at a
	{
		ChangeState(EState::Chase);
		return true;
	}
	return false;
}

bool Enemy::CheckForLostPlayer()
{
	float DirectionToPlayerX = Player1->GetWorldPositionX() - GetWorldPositionX();
	float DirectionToPlayerY = Player1->GetWorldPositionY() - GetWorldPositionY();
	float DirectionSize = sqrt(pow(DirectionToPlayerX, 2) + pow(DirectionToPlayerY, 2));

	if (DirectionSize > 500.0f)
	{
		ChangeState(EState::Idle);
		return true;
	}
	return false;
}

bool Enemy::CheckForFear()
{
	float DirectionToPlayerX = Player1->GetWorldPositionX() - GetWorldPositionX();
	float DirectionToPlayerY = Player1->GetWorldPositionY() - GetWorldPositionY();
	float DirectionSize = sqrt(pow(DirectionToPlayerX, 2) + pow(DirectionToPlayerY, 2));

	//If enemy health is lower than 25% run away from players location
	if ((EnemyHealthLeft < ENEMY_MAX_LIFE*0.25) && (DirectionSize < 300.0f))
	{
		ChangeState(EState::Flee);
		return true;
	}
	return false;
}

void Enemy::ExitIdleState()
{

}

void Enemy::EnterPatrolState()
{
	std::string EnemyImagePath = "";
	if (EnemyType == EEnemyType::Demon)
	{
		EnemyImagePath = "Art/Enemy_D.png";
		MaxMoveTime = RandomRange(3.0f, 5.0f);
	}
	else if (EnemyType == EEnemyType::Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat.png";
		MaxMoveTime = RandomRange(5.0f, 7.0f);
	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem.png";
		MaxMoveTime = RandomRange(1.0f, 3.0f);
	}
	if (EnemyImage)
	{
		EnemyImage->LoadImage(EnemyImagePath);
	}


}

void Enemy::UpdatePatrolState(float Deltatime)
{

	if (CheckForFear())
	{
		return;
	}

	if (CheckForChase())
	{
		return;
	}


	switch (EnemyDirection)
	{
	case Right:
	default:
		UpdateMovement(GetPositionX() + (1.0f * MovementSpeed * Deltatime), GetPositionY());
		break;
	case Down:
		UpdateMovement(GetPositionX(), GetPositionY() + (1.0f * MovementSpeed * Deltatime));
		break;
	case Left:
		UpdateMovement(GetPositionX() - (1.0f * MovementSpeed * Deltatime), GetPositionY());
		break;
	case Up:
		UpdateMovement(GetPositionX(), GetPositionY() - (1.0f * MovementSpeed * Deltatime));
		break;

	}

	float TotalTimeToMove = MaxMoveTime;
	
	if ((EnemyDirection == Left && SpawnStart == ESpawnStart::RightCenter) ||
		(EnemyDirection == Right && SpawnStart == ESpawnStart::LeftCenter) ||
		(EnemyDirection == Up && SpawnStart == ESpawnStart::BottomCenter) ||
		(EnemyDirection == Down && SpawnStart == ESpawnStart::TopCenter))
	{
		TotalTimeToMove *= 3.0f;
	}

	if (TimeInState > TotalTimeToMove)
	{
		ChangeDirection();

		ChangeState(EState::Idle);
	}
}

void Enemy::ChangeDirection()
{
	EnemyDirection = static_cast <EEnemyDir>((EnemyDirection + 1) % EEnemyDir::COUNT);
}

EState Enemy::GetState() const
{
	return CurrentState;
}

void Enemy::ExitPatrolState()
{
	bNeedsSwitch = !bNeedsSwitch;
	MoveTimer = 0.0f;
}

void Enemy::EnterChaseState()
{
	std::string EnemyImagePath = "";
	if (EnemyType == EEnemyType::Demon)
	{
		EnemyImagePath = "Art/Enemy_D_Chase.png";
	}
	else if (EnemyType == EEnemyType::Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat_Chase.png";
	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem_Chase.png";
	}

	EnemyImage->LoadImage(EnemyImagePath);

}

void Enemy::UpdateChaseState(float Deltatime)
{
	if (CheckForFear())
	{
		return;
	}

	if (CheckForLostPlayer())
	{
		return;
	}

	float ChaseDirectionX = Player1->GetWorldPositionX() - GetWorldPositionX();
	float ChaseDirectionY = Player1->GetWorldPositionY() - GetWorldPositionY();
	float ChaseDirectionSize = sqrt(pow(ChaseDirectionX, 2) + pow(ChaseDirectionY, 2));
	
	if (ChaseDirectionSize != 0.0f)
	{
		ChaseDirectionX /= ChaseDirectionSize;
		ChaseDirectionY /= ChaseDirectionSize;

		UpdateMovement(GetPositionX() + (ChaseDirectionX *MovementSpeed * Deltatime), GetPositionY() + (ChaseDirectionY * MovementSpeed * Deltatime));
	}
	
}

void Enemy::ExitChaseState()
{

}

void Enemy::EnterFleeState()
{
	std::string EnemyImagePath = "";
	if (EnemyType == EEnemyType::Demon)
	{
		EnemyImagePath = "Art/Enemy_D_Flee.png";

	}
	else if (EnemyType == EEnemyType::Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat_Flee.png";

	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem_Flee.png";

	}

	EnemyImage->LoadImage(EnemyImagePath);

	//Collision->DoesCollide(false); // Not working yet
	
}

void Enemy::UpdateFleeState(float DeltaTime)
{
	

	if (CheckForLostPlayer())
	{
		return;
	}

	float FleeDirectionX = Player1->GetWorldPositionX() + GetWorldPositionX();
	float FleeDirectionY = Player1->GetWorldPositionY() + GetWorldPositionY();
	float FleeDirectionSize = sqrt(pow(FleeDirectionX, 2) - pow(FleeDirectionY, 2));

	if (FleeDirectionSize != 0.0f)
	{
		FleeDirectionX /=FleeDirectionSize;
		FleeDirectionY /= FleeDirectionSize;

		UpdateMovement(GetPositionX() - (FleeDirectionX *MovementSpeed*0.5f * DeltaTime), GetPositionY() - (FleeDirectionY * MovementSpeed*0.5f * DeltaTime));
	}
}

void Enemy::ExitFleeState()
{

}

void Enemy::UpdateMovement(float DesiredX, float DesiredY)
{
	if (const Background* BG = static_cast<const Background*>(GetParent()))
	{
		if (DesiredX > -BG->GetBackgroundWidth() * 0.5f && DesiredX < BG->GetBackgroundWidth()*0.5f &&
			DesiredY > -BG->GetBackgroundHeight() * 0.5f && DesiredY < BG->GetBackgroundHeight()*0.5f)
		{
			SetPosition(DesiredX, DesiredY);
		}

	}

}

void Enemy::Switch()
{
	bNeedsSwitch = true;
}

void Enemy::SetEnemyDirection(EEnemyDir direction)
{
	EnemyDirection = direction;
}

void Enemy::SetEnemyType(EEnemyType type)
{
	EnemyType = type;
}

EEnemyType Enemy::GetEnemyType() const
{
	return EnemyType;
}

void Enemy::TakeDamage()
{
	EnemyHealthLeft -= 0.4f;
	float ExplosionScale = 1.0f;
	if (GetEnemyType() == EEnemyType::Demon)
	{
		ExplosionScale = 1.8f;
	}
	else if (GetEnemyType() == EEnemyType::Bat)
	{
		ExplosionScale = 0.5f;
	}
	else
	{
		ExplosionScale = 2.2f;
	}

	EventMessage Evt(GameEvent::EnemyHurt);
	EventPayload WorldPosX, WorldPosY, Scale;

	WorldPosX.SetAsFloat(GetWorldPositionX());
	WorldPosY.SetAsFloat(GetWorldPositionY());
	Scale.SetAsFloat(ExplosionScale);

	Evt.payload.push_back(WorldPosX);
	Evt.payload.push_back(WorldPosY);
	Evt.payload.push_back(Scale);
	EventManager::BroadcastEvent(Evt);

	if (EnemyHealthLeft < 0.0f)
	{
		EventMessage Evt(GameEvent::EnemyDied);
		Evt.payload.push_back(WorldPosX);
		Evt.payload.push_back(WorldPosY);
		EventManager::BroadcastEvent(Evt);
 		RequestDestroy();
		return;
	}
	SetEnemyLifePercentage(GetEnemyLivesLeft() / GetEnemyMaxLivesLeft());
}
