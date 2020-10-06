#pragma once
#include "GameComponent.h"
#include <string>

using namespace std;

class BoxCollisionComponent : public GameComponent
{
public:
    BoxCollisionComponent(class GameObject* Owner);

    bool DoesCollide(BoxCollisionComponent* OtherCollisionComponent);

protected:
    virtual void OnRender() override;

private:
    float BoxWidth = 0.0f;
    float BoxHeight = 0.0f;

    bool bDrawDebug = true;
};

