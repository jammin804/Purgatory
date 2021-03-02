#pragma once
#include "GameComponent.h"
#include <string>

using namespace std;

class BoxCollisionComponent : public GameComponent
{
public:
    BoxCollisionComponent(class GameObject* Owner);

    bool DoesCollide(const BoxCollisionComponent* OtherCollisionComponent) const;
    void SetScale(float NewScale) { Scale = NewScale; }
    void SetCollisionSize(float Width, float Height){ BoxWidth = Width; BoxHeight = Height; }
protected:
    virtual void OnRender() override;

private:
    float BoxWidth = 50.0f;
    float BoxHeight = 50.0f;
    float Scale = 1.0f;

    bool bDrawDebug = true;
};

