#include "Rock.h"
#include "Framework/ImageComponent.h"
#include "Framework/BoxCollisionComponent.h"

void Rock::OnInit()
{
    RockImage = GameComponent::CreateInstance<ImageComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
}

void Rock::OnPostInit()
{
    if (RockImage)
    {
        RockImage->LoadImage("Art/Rock.png");
        RockImage->SetScale((SplitsLeft + 1) * 0.33f);
    }
    if (Collision)
    {
        Collision->SetScale((SplitsLeft + 1) * 0.33f);
    }
}

void Rock::OnUpdate(float DeltaTime)
{
    SetRotation(GetRotation() + RotationSpeed * DeltaTime);
    
    SetPosition(GetPositionX() + (MovementDirectionX * MovementSpeed * DeltaTime),
        GetPositionY() + (MovementDirectionY * MovementSpeed * DeltaTime));

    LifeTimer += DeltaTime;
    if (LifeTimer > MaxLifeTime)
    {
        RequestDestroy();
    }
}

void Rock::Split()
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
    MovementDirectionX = CurrentMovementDirectionX;
}

void Rock::RequestSplit()
{
    bNeedsSplit = true;
}
