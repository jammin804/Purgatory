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
    void SetPos(float NewPosX, float NewPosY) { SetPosX(NewPosX); SetPosY(NewPosY); }
    void SetRotation(float NewRotation) { Rotation = NewRotation; }

    float GetPosX() const { return PositionX; }
    float GetPosY() const { return PositionY; }
    float GetRotation() const { return Rotation; }

protected:   
    virtual void OnInit() = 0;
    virtual void OnPostInit(){}
    virtual void OnUpdate() = 0;

    virtual void OnShutdown() {}

private:
    void Init();
    void PostInit();
    void Update();
    void Render();
    void Shutdown();

    void RegisterComponent(GameComponent* Component);

    vector<GameComponent*> GameComponents;

    float PositionX = 0.0f;
    float PositionY = 0.0f;
    float Rotation = 0.0f;
};

