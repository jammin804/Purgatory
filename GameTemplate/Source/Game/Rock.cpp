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
		EnemyHealth->SetScaleY(ENEMY_MAX_LIFE);

        RockImage->LoadImage("Art/Enemy_D.png");//
        RockImage->SetScale((SplitsLeft + 1) * 0.33f);
    }
    if (Collision)
    {
        Collision->SetScale((SplitsLeft + 1) * 0.33f);
    }

}

void Rock::OnUpdate(float DeltaTime)
{
	if (NewRock) 
	{
		SetEnemyLifePercentage(NewRock->GetEnemyLivesLeft()/ static_cast <float>(NewRock->GetEnemyMaxLivesLeft()));
	}


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

	// Setting timers to switch direction. A bool in order to switch directions
    LifeTimer += DeltaTime;
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
    }
}

void Rock::SetEnemyLifePercentage(float EnemyPercentageLife)
{
	EnemyHealth->SetScaleX(ENEMY_MAX_LIFE * EnemyPercentageLife);
}


void Rock::Split() //Prevents split
{
    bNeedsSplit = false;

    if (SplitsLeft-- == 0)
    {
        RequestDestroy();
        return;
    }

    MovementSpeed *= 1.2;
    if (RockImage)
    {
        RockImage->SetScale((SplitsLeft + 1) * 0.33f);
    }
    if (Collision)
    {
        Collision->SetScale((SplitsLeft + 1) * 0.33f);
    }
    float CurrentMovementDirectionX = MovementDirectionX;
    MovementDirectionX = MovementDirectionY;
    MovementDirectionY = CurrentMovementDirectionX;
}

void Rock::Switch()
{
	bNeedsSwitch = true;
}

void Rock::RequestSplit()
{
    bNeedsSplit = false;
}
