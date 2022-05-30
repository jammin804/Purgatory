#include "GameObject.h"
#include "GameFramework.h"
#include "GameComponent.h"

GameObject::GameObject()
{
    GameFramework::RegisterGameObject(this);
    GameComponents.reserve(8);
}

void GameObject::RegisterComponent(GameComponent* Component)
{
    GameComponents.push_back(Component);
}

void GameObject::DestroyComponent(GameComponent* Component)
{
    void* ComponentPointer = static_cast<void*>(Component);
    GameFramework::DestroyObject(ComponentPointer, sizeof(*Component));
}

void GameObject::Init()
{
    OnInit();
    for (GameComponent* Component : GameComponents)
    {
        Component->Init();
    }
	bInitialised = true;
}

void GameObject::PostInit()
{
	if (bInitialised) 
	{
		bFullyInitialised = true;
		OnPostInit();
	}

}

void GameObject::Update(float DeltaTime)
{
    OnUpdate(DeltaTime);
    for (GameComponent* Component : GameComponents)
    {
        Component->Update(DeltaTime);
    }
}

void GameObject::Render()
{
    for (GameComponent* Component : GameComponents)
    {
        Component->Render();
    }
}

void GameObject::Shutdown()
{
    for (GameComponent* Component : GameComponents)
    {
        Component->Shutdown();
        DestroyComponent(Component);
    }
    GameComponents.clear();
    OnShutdown();
}

GameComponent* GameObject::GetComponent(ComponentType Type)
{
	for (GameComponent* Component : GameComponents)
	{
		if (Component->GetType() == Type)
		{
			return Component;
		}
	}
    return nullptr;
}

void GameObject::SetWorldPositionX(float NewPosX)
{
    float ParentWorldPositionX = 0.0f;
    if (const GameObject* MyParent = GetParent())
    {
        ParentWorldPositionX = MyParent->GetWorldPositionX();
    }
    PositionX = NewPosX - ParentWorldPositionX;
}

void GameObject::SetWorldPositionY(float NewPosY)
{
    float ParentWorldPositionY = 0.0f;
    if (const GameObject* MyParent = GetParent())
    {
        ParentWorldPositionY = MyParent->GetWorldPositionY();
    }
    PositionY = NewPosY - ParentWorldPositionY;
}

float GameObject::GetWorldPositionX() const
{
    float FinalPositionX = GetPositionX();
    if (const GameObject* MyParent = GetParent())
    {
        FinalPositionX += MyParent->GetWorldPositionX();
    }
    return FinalPositionX;
}

float GameObject::GetWorldPositionY() const
{
    float FinalPositionY = GetPositionY();
    if (const GameObject* MyParent = GetParent())
    {
        FinalPositionY += MyParent->GetWorldPositionY();
    }
    return FinalPositionY;
}

float GameObject::GetWorldRotation() const
{
    float FinalRotation = GetRotation();
    if (const GameObject* MyParent = GetParent())
    {
        FinalRotation += MyParent->GetWorldRotation();
    }
    return FinalRotation;
}
