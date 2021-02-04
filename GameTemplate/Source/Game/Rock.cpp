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
		HealthBarOffsetY = ENEMY_MAX_LIFE * -30.0f;
		CollisionScaleX = 150.0f;
		CollisionScaleY = 150.0f;
		break;
	}

	case EEnemyType::Bat:
	{
		EnemyImagePath = "Art/Enemy_Bat.png";
		EnemyLifeBarScale = 0.5f;
		HealthBarOffsetX = -10.0f;
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
		EnemyHealthLayer->LoadImage("Art/healthbar_layer.png");

		EnemyHealthLayer->SetOffsetY(HealthBarOffsetX);
		EnemyHealthLayer->SetOffsetX(HealthBarOffsetY);
		EnemyHealthLayer->SetScaleX(EnemyLifeBarScale);
	}

	if (EnemyHealth) 
	{

		EnemyHealth->SetScaleFromLeft(true);
		EnemyHealth->LoadImage("Art/fear.png");

		EnemyHealth->SetOffsetY(HealthBarOffsetX);
		EnemyHealth->SetOffsetX(HealthBarOffsetY);
		EnemyHealth->SetScaleX(EnemyLifeBarScale);
	}

	if (Collision)
	{
		
		Collision->SetCollisionSize(CollisionScaleX, CollisionScaleY);
	}
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
		UpdateChaseState();
		break;
	case EState::Flee:
		UpdateFleeState();
		break;

	}

	
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
}

void Rock::EnterIdleState()
{
	//Initializing information
	MovementSpeed = 0.0f;
	IdleTimer = MaxIdleTime;
}

void Rock::UpdateIdleState(float Deltatime)
{
	//If enemy health is lower than 25% run away from players location
	if (ENEMY_MAX_LIFE < ENEMY_MAX_LIFE*0.25)
	{
		ChangeState(EState::Flee);
	}
	// Is player close?
	/*if (Player1->GetWorldPositionX() > GetWorldPositionX() + 100.0f)
	{
		ChangeState(EState::Chase);
	}*/
	else
	{
		
		IdleTimer -= Deltatime;
		if (IdleTimer <= 0)
		{
			ChangeState(EState::Patrol);
		}

	}



}

void Rock::ExitIdleState()
{
	//Cleaning up
	IdleTimer = 0.0f;
}

void Rock::EnterPatrolState()
{
	MoveTimer = 0.0f;
	MovementSpeed = 100.0f;

}

void Rock::UpdatePatrolState(float Deltatime)
{
	//MoveTimer += Deltatime;
	if (ENEMY_MAX_LIFE < ENEMY_MAX_LIFE*0.25)
	{
		ChangeState(EState::Flee);
	}

	switch (EnemyDirection)
	{
	default:
		break;
	}

	if (bNeedsSwitch) //Switching directions
	{
		SetPosition(GetPositionX(), GetPositionY() + (MovementDirectionY * MovementSpeed * Deltatime));
	}
	else
	{
		SetPosition(GetPositionX() + (MovementDirectionX * MovementSpeed * Deltatime), GetPositionY());
	}

	MoveTimer += Deltatime;
	if (MoveTimer > MaxMoveTime)
	{
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

}

void Rock::UpdateChaseState()
{
	if (ENEMY_MAX_LIFE < ENEMY_MAX_LIFE*0.25)
	{
		ChangeState(EState::Flee);
	}
}

void Rock::ExitChaseState()
{

}

void Rock::EnterFleeState()
{
	
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
