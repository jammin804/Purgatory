#include "BoxCollisionComponent.h"

#include "GameObject.h"
#include <allegro5/allegro_primitives.h>

BoxCollisionComponent::BoxCollisionComponent(GameObject* Owner)
    : GameComponent(Owner)
{

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

    float Box1[4];
    {
        float CenterX = GetOwner()->GetWorldPositionX() + GetOffsetX();
        float CenterY = GetOwner()->GetWorldPositionY() + GetOffsetY();
        float HalfBoxWidth = BoxWidth * 0.5f;
        float HalfBoxHeight = BoxHeight * 0.5f;
        float BoxLocal[] = { CenterX - (HalfBoxWidth * Scale),
        CenterY - (HalfBoxHeight * Scale),
        BoxWidth * Scale,
        BoxHeight * Scale};
        for (int i = 0; i < 4; ++i)
        {
            Box1[i] = BoxLocal[i];
        }
    }
    float Box2[4];
    {
        float CenterX = OtherCollisionComponent->GetOwner()->GetWorldPositionX() + GetOffsetX();
        float CenterY = OtherCollisionComponent->GetOwner()->GetWorldPositionY() + GetOffsetY();
        float HalfBoxWidth = BoxWidth * 0.5f;
        float HalfBoxHeight = BoxHeight * 0.5f;
        float BoxLocal[] = { CenterX - (HalfBoxWidth * Scale),
        CenterY - (HalfBoxHeight * Scale),
        BoxWidth * Scale,
        BoxHeight * Scale };
        for (int i = 0; i < 4; ++i)
        {
            Box2[i] = BoxLocal[i];
        }
    }

    /*
    if (1.position.left < 2.position.left + 2.position.width &&
      1.position.left + 1.position.width > 2.position.left &&
      1.position.top < 2.position.top + 2.position.height &&
      1.position.height + 1.position.top > 2.position.top)
    */

    if ((Box1[Left] < Box2[Left] + Box2[Width]) &&
        (Box1[Left] + Box1[Width] > Box2[Left]) &&
        (Box1[Top] < Box2[Top] + Box2[Height]) &&
        (Box1[Height] + Box1[Top] > Box2[Top])) 
    {
        return true;
    }

    return false;
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
