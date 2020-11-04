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
}

void GameObject::PostInit()
{
    bInitialised = true;
    OnPostInit();
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

float GameObject::GetPositionX() const
{
    float FinalPositionX = GetLocalPositionX();
    if (const GameObject* MyParent = GetParent())
    {
        FinalPositionX += MyParent->GetPositionX();
    }
    return FinalPositionX;
}

float GameObject::GetPositionY() const
{
    float FinalPositionY = GetLocalPositionY();
    if (const GameObject* MyParent = GetParent())
    {
        FinalPositionY += MyParent->GetPositionY();
    }
    return FinalPositionY;
}

float GameObject::GetRotation() const
{
    float FinalRotation = GetLocalRotation();
    if (const GameObject* MyParent = GetParent())
    {
        FinalRotation += MyParent->GetRotation();
    }
    return FinalRotation;
}
