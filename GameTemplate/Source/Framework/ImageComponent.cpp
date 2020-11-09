#include "ImageComponent.h"

#include "GameObject.h"
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

ImageComponent::ImageComponent(GameObject* Owner)
    : GameComponent(Owner)
{

}

void ImageComponent::OnShutdown()
{
    if (ImageBitmap)
    {
        al_destroy_bitmap(ImageBitmap);
        ImageBitmap = nullptr;
    }
}

void ImageComponent::OnRender()
{
    if (ImageBitmap && bIsVisible)
    {
        const GameObject* Owner = GetOwner();
		if (ScaleFromLeft) 
		{
			al_draw_scaled_rotated_bitmap(ImageBitmap, ImageWidth * 0.0f, ImageHeight * 0.5f, Owner->GetPositionX() + GetOffsetX(), Owner->GetPositionY() + GetOffsetY(), ScaleX, ScaleY, Owner->GetRotation(), 0);
		}
		else 
		{
			al_draw_scaled_rotated_bitmap(ImageBitmap, ImageWidth * 0.5f, ImageHeight * 0.5f, Owner->GetPositionX() + GetOffsetX(), Owner->GetPositionY() + GetOffsetY(), ScaleX, ScaleY, Owner->GetRotation(), 0);
		}
       
    }
}

void ImageComponent::LoadImage(string ImagePath)
{
    ImageBitmap = al_load_bitmap(ImagePath.c_str());
    if (!ImageBitmap)
    {
        printf("Couldn't load Image\n");
    }
    else
    {
        ImageWidth = al_get_bitmap_width(ImageBitmap);
        ImageHeight = al_get_bitmap_height(ImageBitmap);
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

