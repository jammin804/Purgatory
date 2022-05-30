#include "GameComponent.h"
#include "GameObject.h"

GameComponent::GameComponent(GameObject* GOOwner, ComponentType CTType)
{
    Type = CTType;
    Owner = GOOwner;
    if (Owner)
    {
        Owner->RegisterComponent(this);
    }
}

void GameComponent::Init()
{
    OnInit();
}

void GameComponent::Update(float DeltaTime)
{
    OnUpdate(DeltaTime);
}

void GameComponent::Shutdown()
{
    OnShutdown();
}

void GameComponent::Render()
{
    OnRender();
}

