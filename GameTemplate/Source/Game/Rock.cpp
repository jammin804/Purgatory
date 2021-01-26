#include "Rock.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"

void Rock::OnInit()
{
    RockImage = GameComponent::CreateInstance<ImageComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	EnemyHealthLayer = GameComponent::CreateInstance<ImageComponent>(this);
	EnemyHealth = GameComponent::CreateInstance<ImageComponent>(this);
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

	if (bNeedsSwitch) //Switching directions
	{
		SetPosition(GetPositionX(), GetPositionY() + (MovementDirectionY * MovementSpeed * DeltaTime));
	}
	else 
	{
		SetPosition(GetPositionX() + (MovementDirectionX * MovementSpeed * DeltaTime), GetPositionY());
	}

	MoveTimer += DeltaTime;
	if (MoveTimer > MaxMoveTime)
	{
		bNeedsSwitch = !bNeedsSwitch;
		MoveTimer = 0.0f;
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


void Rock::Switch()
{
	bNeedsSwitch = true;
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
