#include "Rock.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Game/Player.h"

void Rock::OnInit()
{
    RockImage = GameComponent::CreateInstance<ImageComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	EnemyHealthLayer = GameComponent::CreateInstance<ImageComponent>(this);
	EnemyHealth = GameComponent::CreateInstance<ImageComponent>(this);
	//Player1 = GameObject::CreateInstance<Player>();
}

void Rock::OnPostInit()
{
	float HealthBarOffsetX = -50.0f;
	float HealthBarOffsetY = -60.0f;
	std::string EnemyImagePath = "";
	float EnemyScale = 1.0f;
	float CollisionScaleX = 150.0f;
	float CollisionScaleY = 150.0f;

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
		CollisionScaleX = 150.0f * 2;
		CollisionScaleY = 150.0f * 2;
		HealthBarOffsetX = -160.0f;
		HealthBarOffsetY = -70.0f;
		break;
	}
	}

    if (RockImage)
    {
		RockImage->LoadImage(EnemyImagePath);
		RockImage->SetScale(EnemyScale);
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

void Rock::OnUpdate(float DeltaTime)
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
		UpdateFleeState();
		break;

	}

	TimeInState += DeltaTime;
}

void Rock::OnRestart()
{
	//destroy Current Rocks
	SetEnabled(false);
	//RequestDestroy();
}

void Rock::SetEnemyLifePercentage(float EnemyPercentageLife)
{
	EnemyHealth->SetScaleX(EnemyLifeBarScale * EnemyPercentageLife);
}


void Rock::ChangeState(EState NewState)
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

void Rock::EnterIdleState()
{
	//Initializing information
	/*if (EEnemyType == Demon)
	{
		EnemyImagePath = "Art / Enemy_D.png";
	}
	else if (EEnemyType == Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat.png";
	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem.png";
	}*/
}

void Rock::UpdateIdleState(float Deltatime)
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

bool Rock::CheckForChase()
{
	float DirectionToPlayerX = Player1->GetWorldPositionX() - GetWorldPositionX();
	float DirectionToPlayerY = Player1->GetWorldPositionY() - GetWorldPositionY();
	float DirectionSize = sqrt(pow(DirectionToPlayerX, 2) + pow(DirectionToPlayerY, 2));

	if (DirectionSize < 200.0f)
	{
		ChangeState(EState::Chase);
		return true;
	}
	return false;
}

bool Rock::CheckForLostPlayer()
{
	float DirectionToPlayerX = Player1->GetWorldPositionX() - GetWorldPositionX();
	float DirectionToPlayerY = Player1->GetWorldPositionY() - GetWorldPositionY();
	float DirectionSize = sqrt(pow(DirectionToPlayerX, 2) + pow(DirectionToPlayerY, 2));

	if (DirectionSize > 300.0f)
	{
		ChangeState(EState::Idle);
		return true;
	}
	return false;
}

bool Rock::CheckForFear()
{
	//If enemy health is lower than 25% run away from players location
	if (ENEMY_MAX_LIFE < ENEMY_MAX_LIFE*0.25)
	{
		ChangeState(EState::Flee);
		return true;
	}
	return false;
}

void Rock::ExitIdleState()
{

}

void Rock::EnterPatrolState()
{
	/*if (EEnemyType == Demon)
	{
		EnemyImagePath = "Art / Enemy_D.png";
	}
	else if (EEnemyType == Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat.png";
	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem.png";
	}*/

}

void Rock::UpdatePatrolState(float Deltatime)
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
		SetPosition(GetPositionX() + (1.0f * MovementSpeed * Deltatime), GetPositionY());
		break;
	case Down:
		SetPosition(GetPositionX(), GetPositionY() + (1.0f * MovementSpeed * Deltatime));
		break;
	case Left:
		SetPosition(GetPositionX() - (1.0f * MovementSpeed * Deltatime), GetPositionY());
		break;
	case Up:
		SetPosition(GetPositionX(), GetPositionY() - (1.0f * MovementSpeed * Deltatime));
		break;

	}


	if (TimeInState > MaxMoveTime)
	{
		EnemyDirection = static_cast <EEnemyDir>((EnemyDirection + 1) % EEnemyDir::COUNT);
		ChangeState(EState::Idle);
	}
}

void Rock::ExitPatrolState()
{
	bNeedsSwitch = !bNeedsSwitch;
	MoveTimer = 0.0f;
}

void Rock::EnterChaseState()
{
	/*if (EEnemyType == Demon)
	{
		EnemyImagePath = "Art/Enemy_D.png";
	}
	else if (EEnemyType == Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat_Chase.png";
	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem_Chase.png";
	}*/

}

void Rock::UpdateChaseState(float Deltatime)
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

		SetPosition(GetPositionX() + (ChaseDirectionX *MovementSpeed*0.5f * Deltatime), GetPositionY() + (ChaseDirectionY * MovementSpeed*0.5f * Deltatime));
	}
	
}

void Rock::ExitChaseState()
{

}

void Rock::EnterFleeState()
{
	/*if (EEnemyType == Demon)
	{
		EnemyImagePath = "Art/Enemy_D.png";
	}
	else if (EEnemyType == Bat)
	{
		EnemyImagePath = "Art/Enemy_Bat_Flee.png";
	}
	else
	{
		EnemyImagePath = "Art/Enemy_Golem_Flee.png";
	}*/
	
}

void Rock::UpdateFleeState()
{

}

void Rock::ExitFleeState()
{

}

void Rock::Switch()
{
	bNeedsSwitch = true;
}

void Rock::SetEnemyDirection(EEnemyDir direction)
{
	EnemyDirection = direction;
}

void Rock::SetEnemyType(EEnemyType type)
{
	EnemyType = type;
}

void Rock::EnemyHit()
{
	EnemyHealthLeft -= 0.4f;
	if (EnemyHealthLeft < 0.0f)
	{
 		RequestDestroy();
		return;
	}
	SetEnemyLifePercentage(GetEnemyLivesLeft() / GetEnemyMaxLivesLeft());
}
