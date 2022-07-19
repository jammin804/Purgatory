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
    CurrentBox[0] = CenterX - (HalfBoxWidth * Scale);
    CurrentBox[1] = CenterY - (HalfBoxHeight * Scale);
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

void BoxCollisionComponent::OnRender()
{
    if (bDrawDebug)
    {
        const GameObject* Owner = GetOwner();
        float CenterX = Owner->GetWorldPositionX() + GetOffsetX();
        float CenterY = Owner->GetWorldPositionY() + GetOffsetY();
        float HalfBoxWidth = BoxWidth * 0.5f;
        float HalfBoxHeight = BoxHeight * 0.5f;
        al_draw_filled_rectangle(
        CenterX - (HalfBoxWidth * Scale), 
        CenterY - (HalfBoxHeight * Scale),
        CenterX + (HalfBoxWidth * Scale),
        CenterY + (HalfBoxHeight * Scale),
        al_map_rgba_f(0.5f, 0, 0.0f, 0.8f));
    }
}
