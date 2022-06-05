#pragma once
#include <vector>
#include "GameFramework.h"
#include "../ComponentTypes.h"

using namespace std;

class GameComponent;
struct EventMessage;

class GameObject
{
    friend class GameFramework;
    friend class GameComponent;

public:
    template<class T>
    static T* CreateInstance();

	GameComponent* GetComponent(ComponentType Type);

    int GetType() const { return Type; }
    void SetType(int NewType) { Type = NewType; }

    void SetWorldPositionX(float NewPosX);
    void SetWorldPositionY(float NewPosY);
    void SetWorldPosition(float NewPosX, float NewPosY) { SetWorldPositionX(NewPosX); SetWorldPositionY(NewPosY); }

    void SetPosX(float NewPosX) { PositionX = NewPosX; }
    void SetPosY(float NewPosY) { PositionY = NewPosY; }
    void SetPosition(float NewPosX, float NewPosY) { SetPosX(NewPosX); SetPosY(NewPosY); }
    void SetRotation(float NewRotation) { Rotation = NewRotation; }

    float GetWorldPositionX() const;
    float GetWorldPositionY() const;
    float GetWorldRotation() const;

    float GetPositionX() const { return PositionX; }
    float GetPositionY() const { return PositionY; }
    float GetRotation() const { return Rotation; }

    void RequestDestroy() { bShouldDestroy = true; }
    virtual void SetEnabled(bool bEnabled) { bIsEnabled = bEnabled; }
	virtual void Restart() {};
    bool IsEnabled() const { return bIsEnabled; }
    bool IsDestroyed() const { return bShouldDestroy; }

    void SetParent(const GameObject* ParentComponent){ Parent = ParentComponent; }
    const GameObject* GetParent() const { return Parent; }

    void SetRenderDepth(int NewRenderDepth) { RenderDepth = NewRenderDepth; }
    int GetRenderDepth() const { return RenderDepth; }

	virtual void OnRestart() {}

    virtual void OnCollision(GameObject* Other) {}
    virtual void OnEvent(const EventMessage& Msg) {}
    void BroadcastEvent(int);
    void AddEventListener(int);
    void RemoveEventListener(int);
protected:
    GameObject();
    virtual ~GameObject() {}

    virtual void OnInit(){}
    virtual void OnPostInit(){}
    virtual void OnUpdate(float DeltaTime){}
    virtual void OnShutdown() {}
	

private:

    void Init();
    void PostInit();
    void Update(float DeltaTime);
    void Render();
    void Shutdown();

    void RegisterComponent(GameComponent* Component);
    void DestroyComponent(GameComponent* Component);

    const GameObject* Parent = nullptr;

    vector<GameComponent*> GameComponents;

    float PositionX = 0.0f;
    float PositionY = 0.0f;
    float Rotation = 0.0f;
    bool bShouldDestroy = false;
    bool bIsEnabled = true;
    bool bIsDestroyed = false;
    bool bInitialised = false;
	bool bFullyInitialised = false;
    int RenderDepth = 0; // Higher values will be rendered(drawn) on top of GameObjects with smaller values
    size_t memsize;
    int Type = -1;
};

template<class T>
T* GameObject::CreateInstance()
{
    if (T* CreatedInstance = GameFramework::CreateObject<T>())
    {
        CreatedInstance->memsize = sizeof(T);
        return CreatedInstance;
    }
    return nullptr;
}

