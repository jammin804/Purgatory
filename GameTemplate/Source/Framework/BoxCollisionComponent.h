#pragma once
#include "GameComponent.h"
#include <string>

using namespace std;

class BoxCollisionComponent : public GameComponent
{
public:
    BoxCollisionComponent(class GameObject* Owner);

    bool DoesCollide(const BoxCollisionComponent* OtherCollisionComponent) const;

protected:
    virtual void OnRender() override;

private:
    float BoxWidth = 50.0f;
    float BoxHeight = 50.0f;

    bool bDrawDebug = true;
};

