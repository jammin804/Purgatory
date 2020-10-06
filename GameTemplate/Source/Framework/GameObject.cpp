#include "GameObject.h"
#include "GameFramework.h"
#include "GameComponent.h"

GameObject::GameObject()
{
    GameFramework::RegisterGameObject(this);
}

void GameObject::RegisterComponent(GameComponent* Component)
{
    GameComponents.push_back(Component);
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
    }
    OnShutdown();
}
