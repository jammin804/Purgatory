#include "BoxCollisionComponent.h"

#include "GameObject.h"
#include <allegro5/allegro_primitives.h>

BoxCollisionComponent::BoxCollisionComponent(GameObject* Owner)
    : GameComponent(Owner)
{

}

bool BoxCollisionComponent::DoesCollide(BoxCollisionComponent* OtherCollisionComponent)
{
    if (!OtherCollisionComponent)
    {
        return false;
    }

    float Box1[4];
    {
        float CenterX = GetOwner()->GetPositionX() + GetOffsetX();
        float CenterY = GetOwner()->GetPositionY() + GetOffsetY();
        float HalfBoxWidth = BoxWidth * 0.5f;
        float HalfBoxHeight = BoxHeight * 0.5f;
        float BoxLocal[] = { CenterX - HalfBoxWidth,
        CenterY - HalfBoxHeight,
        CenterX + HalfBoxWidth,
        CenterY + HalfBoxHeight };
        for (int i = 0; i < 4; ++i)
        {
            Box1[i] = BoxLocal[i];
        }
    }
    float Box2[4];
    {
        float CenterX = OtherCollisionComponent->GetOwner()->GetPositionX() + GetOffsetX();
        float CenterY = OtherCollisionComponent->GetOwner()->GetPositionY() + GetOffsetY();
        float HalfBoxWidth = BoxWidth * 0.5f;
        float HalfBoxHeight = BoxHeight * 0.5f;
        float BoxLocal[] = { CenterX - HalfBoxWidth,
        CenterY - HalfBoxHeight,
        CenterX + HalfBoxWidth,
        CenterY + HalfBoxHeight };
        for (int i = 0; i < 4; ++i)
        {
            Box2[i] = BoxLocal[i];
        }
    }

    if (Box1[0] < Box2[0] + Box2[2] &&
        Box1[0] + Box1[2] > Box2[0] &&
        Box1[1] < Box2[1] + Box2[3] &&
        Box1[1] + Box1[3] > Box2[1]) 
    {
        return true;
    }

    return true;
}

void BoxCollisionComponent::OnRender()
{
    if (bDrawDebug)
    {
        const GameObject* Owner = GetOwner();
        float CenterX = Owner->GetPositionX() + GetOffsetX();
        float CenterY = Owner->GetPositionY() + GetOffsetY();
        float HalfBoxWidth = BoxWidth * 0.5f;
        float HalfBoxHeight = BoxHeight * 0.5f;
        al_draw_filled_rectangle(
        CenterX - HalfBoxWidth, 
        CenterY - HalfBoxHeight, 
        CenterX + HalfBoxWidth, 
        CenterY + HalfBoxHeight, 
        al_map_rgba_f(0.5f, 0, 0.0f, 0.8f));
    }
}
