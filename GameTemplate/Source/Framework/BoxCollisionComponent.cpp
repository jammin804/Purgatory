#include "BoxCollisionComponent.h"

#include "GameObject.h"
#include <allegro5/allegro_primitives.h>

BoxCollisionComponent::BoxCollisionComponent(GameObject* Owner)
    : GameComponent(Owner, ComponentType::BoxCollisionComponent)
{
    CollisionIndex = GameFramework::RegisterCollisionComponent(this);
}

void BoxCollisionComponent::OnShutdown()
{
    if (CollisionIndex != -1)
    {
        GameFramework::UnregisterCollisionComponent(CollisionIndex);
    }
}

void BoxCollisionComponent::OnUpdate(float deltaTime)
{
    float CenterX = GetOwner()->GetWorldPositionX() + GetOffsetX();
    float CenterY = GetOwner()->GetWorldPositionY() + GetOffsetY();
    float HalfBoxWidth = BoxWidth * 0.5f;
    float HalfBoxHeight = BoxHeight * 0.5f;
   if (isOverridingCenter)
   {
	   CurrentBox[0] = CenterX + (BoxOffsetX * Scale);
	   CurrentBox[1] = CenterY + (BoxOffsetY * Scale);
   }
   else
   {
	   CurrentBox[0] = CenterX - (HalfBoxWidth * Scale);
	   CurrentBox[1] = CenterY - (HalfBoxHeight * Scale);
   }

    CurrentBox[2] = BoxWidth * Scale;
    CurrentBox[3] = BoxHeight * Scale;
}

bool BoxCollisionComponent::DoesCollide(const BoxCollisionComponent* OtherCollisionComponent) const
{
    if (!OtherCollisionComponent)
    {
        return false;
    }

    enum Property
    {
        Left = 0,
        Top,
        Width,
        Height
    };

    const float* OtherBox = OtherCollisionComponent->CurrentBox;

    if ((CurrentBox[Left] < OtherBox[Left] + OtherBox[Width]) &&
        (CurrentBox[Left] + CurrentBox[Width] > OtherBox[Left]) &&
        (CurrentBox[Top] < OtherBox[Top] + OtherBox[Height]) &&
        (CurrentBox[Height] + CurrentBox[Top] > OtherBox[Top]))
    {
        return true;
    }

    return false;
}

void BoxCollisionComponent::SetDrawDebug()
{
    bDrawDebug = true;
}

void BoxCollisionComponent::SetBoxOffset(float OffsetX, float OffsetY)
{

    BoxOffsetX = OffsetX; 
    BoxOffsetY = OffsetY;

    isOverridingCenter = true;
}

void BoxCollisionComponent::OnRender()
{
    if (bDrawDebug)
    {

        al_draw_filled_rectangle(
        CurrentBox[0], CurrentBox[1],
        (CurrentBox[0]+ CurrentBox[2]),
        (CurrentBox[1] + CurrentBox[3]),
        al_map_rgba_f(0.5f, 0, 0.0f, 0.8f));
    }
}
