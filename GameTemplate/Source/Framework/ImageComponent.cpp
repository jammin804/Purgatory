#include "ImageComponent.h"

#include "GameObject.h"
#include <allegro5/bitmap_draw.h>

ImageComponent::ImageComponent(GameObject* Owner)
    : GameComponent(Owner)
{

}

void ImageComponent::OnShutdown()
{
    if (ImageBitmap)
    {
        ImageBitmap = nullptr;
    }
}

void ImageComponent::OnRender()
{
    if (ImageBitmap && bIsVisible)
    {
        const GameObject* Owner = GetOwner();
        al_draw_scaled_rotated_bitmap(ImageBitmap->ImageBitmap, ImageBitmap->ImageWidth * 0.5f, ImageBitmap->ImageHeight * 0.5f, Owner->GetWorldPositionX() + GetOffsetX(), Owner->GetWorldPositionY() + GetOffsetY(), Scale, Scale, Owner->GetWorldRotation(), 0);
    }
}

void ImageComponent::LoadImage(string ImagePath)
{
    ImageBitmap = GameFramework::Get().GetBitmapManager().FindOrAddBitmap(ImagePath);;
    if (!ImageBitmap)
    {
        printf("Couldn't load Image\n");
    }
}

void ImageComponent::SetVisible(bool bIsNowVisible)
{
    bIsVisible = bIsNowVisible;
}

bool ImageComponent::IsVisible() const
{
    return bIsVisible;
}

