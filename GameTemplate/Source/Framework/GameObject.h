#pragma once
#include <vector>

using namespace std;

class GameComponent;

class GameObject
{
    friend class GameFramework;
    friend class GameComponent;

public:
    GameObject();
    virtual ~GameObject() {}

    void SetPosX(float NewPosX) { PositionX = NewPosX; }
    void SetPosY(float NewPosY) { PositionY = NewPosY; }
    void SetPosition(float NewPosX, float NewPosY) { SetPosX(NewPosX); SetPosY(NewPosY); }
    void SetRotation(float NewRotation) { Rotation = NewRotation; }

    float GetPositionX() const { return PositionX; }
    float GetPositionY() const { return PositionY; }
    float GetRotation() const { return Rotation; }

    void RequestDestroy() { bShouldDestroy = true; }
protected:   
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

    vector<GameComponent*> GameComponents;

    float PositionX = 0.0f;
    float PositionY = 0.0f;
    float Rotation = 0.0f;
    bool bShouldDestroy = false;
};

