#pragma once
#include "GameFramework.h"
#include "../ComponentTypes.h"

class GameObject;

class GameComponent
{
    friend class GameObject;
    friend class GameFramework;

public:
    void SetOffsetX(float NewOffsetX) { OffsetX = NewOffsetX; }
    void SetOffsetY(float NewOffsetY) { OffsetY = NewOffsetY; }
    void SetOffset(float NewOffsetX, float NewOffsetY) { SetOffsetX(NewOffsetX); SetOffsetY(NewOffsetY); }

    float GetOffsetX() const { return OffsetX; }
    float GetOffsetY() const { return OffsetY; }

    template<class T>
    static T* CreateInstance(GameObject* Owner);

protected: 
    GameComponent(GameObject* GOOwner, ComponentType CTType);
    virtual ~GameComponent() {}

    virtual void OnInit(){}

    virtual void OnUpdate(float DeltaTime){}

    virtual void OnRender() {}

    virtual void OnShutdown() {}

    const GameObject* GetOwner() const { return Owner; }

    const ComponentType GetType() const { return Type;  }

private:

    void Init();
    void Update(float DeltaTime);
    void Shutdown();
    void Render();
    GameObject* Owner = nullptr;
    ComponentType Type;
    float OffsetX = 0.0f;
    float OffsetY = 0.0f;

    size_t memsize = 0;
};

template<class T>
T* GameComponent::CreateInstance(GameObject* Owner)
{
    if (T* CreatedInstance = GameFramework::template CreateObjectOneArg<T, GameObject>(Owner))
    {
        CreatedInstance->memsize = sizeof(T);
        return CreatedInstance;
    }
    return nullptr;
}

