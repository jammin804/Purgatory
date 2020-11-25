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
        RockImage->LoadImage("Art/Enemy_D.png");//
        RockImage->SetScale((SplitsLeft + 1) * 0.33f);
    }
    if (Collision)
    {
        Collision->SetScale((SplitsLeft + 1) * 0.33f);
    }
	/*if (EnemyHealth)
	{
		EnemyHealth->LoadImage()
	}*/
}

void Rock::OnUpdate(float DeltaTime)
{
	bNeedsSwitch = true;
	MoveTimer += DeltaTime;
	if (MoveTimer > MaxMoveTime)
	{
		Switch();
	}

    //steal for power up movement
	//SetRotation(GetRotation() + RotationSpeed * DeltaTime); Removing rotation
    
    /*SetPosition(GetPositionX() + (MovementDirectionX * MovementSpeed * DeltaTime),
        GetPositionY() + (MovementDirectionY * MovementSpeed * DeltaTime));*/

	/*for (int i=0; i<2; i++) //tried to make a test to see if i can make a mini timer
	{
		if (i == 2) 
		{
			bNeedsSwitch = false;
			i = 0;
		}
	}*/

	if (bNeedsSwitch)
	{
		SetPosition(GetPositionX(), GetPositionY() + (MovementDirectionY * MovementSpeed * DeltaTime));
	}
	else 
	{
		SetPosition(650.0f, 100.0f);
	}

	/*if (MoveTimer > 30.0f)
	{
		bNeedsSwitch = false;
		MoveTimer = 0.0f;
	}*/

	// Setting timers to switch direction. A bool in order to switch directions
    LifeTimer += DeltaTime;
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
    }
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
    bNeedsSplit = true;
}
