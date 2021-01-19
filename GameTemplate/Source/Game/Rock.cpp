#include "Rock.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"

void Rock::OnInit()
{
    RockImage = GameComponent::CreateInstance<ImageComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	EnemyHealth = GameComponent::CreateInstance<ImageComponent>(this);
}

void Rock::OnPostInit()
{
    if (RockImage)
    {
		//load power up image
		EnemyHealth->SetScaleFromLeft(true);
		EnemyHealth->LoadImage("Art/fear.png");
		EnemyHealth->SetOffsetY(-50.0f);
		EnemyHealth->SetOffsetX(-60.0f);
		EnemyHealth->SetScaleX(ENEMY_MAX_LIFE);
		if (ENEMY_MAX_LIFE > 2.0f)
		{
			RockImage->LoadImage("Art/Enemy_D.png");
			if (ENEMY_MAX_LIFE > 3.0f);
			{
				RockImage->SetScale(2);
			}
		}
		else
		{
			RockImage->LoadImage("Art/Enemy_Bat.png");
		}
        
    }

	if (Collision)
	{
		Collision->SetCollisionSize(150.0f, 150.0f);
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

    LifeTimer += DeltaTime;
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
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
	EnemyHealth->SetScaleX(ENEMY_MAX_LIFE * EnemyPercentageLife);
}


void Rock::Switch()
{
	bNeedsSwitch = true;
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
