#include "StaticGameObject.h"
#include "Framework/GameObject.h"


void StaticGameObject::OnInit()
{
	StaticObjectImage = GameComponent::CreateInstance<ImageComponent>(this);
	Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
}

void StaticGameObject::OnPostInit()
{
	std::string StaticObjectImagePath = "";
	float StaticImageScale = 1.0f;

	if (StaticObjectImage)
	{
		StaticObjectImage->LoadImage(StaticObjectImage);
		StaticObjectImage->SetScale(StaticImageScale);
	}
}

void StaticGameObject::OnUpdate(float DeltaTime)
{

}

void StaticGameObject::StaticObjectCollision()
{

}

