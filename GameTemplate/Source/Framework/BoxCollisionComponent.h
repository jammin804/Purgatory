#pragma once
#include "GameComponent.h"
#include <string>

using namespace std;

class BoxCollisionComponent : public GameComponent
{
    friend class GameFramework;
public:
    BoxCollisionComponent(class GameObject* Owner);

    bool DoesCollide(const BoxCollisionComponent* OtherCollisionComponent) const;
    void SetScale(float NewScale) { Scale = NewScale; }
    void SetCollisionSize(float Width, float Height){ BoxWidth = Width; BoxHeight = Height; }
    void SetDrawDebug();
    void SetBoxOffset(float OffsetX, float OffsetY);
protected:
    virtual void OnRender() override;
    virtual void OnShutdown() override;
    virtual void OnUpdate(float deltaTime) override;
private:
    float BoxWidth = 50.0f;
    float BoxHeight = 50.0f;
    float Scale = 1.0f;
    bool bDrawDebug = true;
    int CollisionIndex = -1;
    float CurrentBox[4];
    float BoxOffsetX;
    float BoxOffsetY;
    bool isOverridingCenter = false;
};

