#pragma once

#include "Framework/GameObject.h"
#include "Framework/SoundComponent.h"

class BoxCollisionComponent;

class StaticGameObject : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate(float DeltaTime) override;

	
public:
    const BoxCollisionComponent* GetCollision() const { return Collision; }
	void StaticObjectCollision();
private:
    class ImageComponent* StaticObjectImage = nullptr;
    BoxCollisionComponent* Collision = nullptr;
};