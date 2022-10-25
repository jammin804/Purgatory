#include "ImageComponent.h"

#include "GameObject.h"
#include <allegro5/bitmap_draw.h>
#include <mutex>

ImageComponent::ImageComponent(GameObject* Owner)
    : GameComponent(Owner, ComponentType::ImageComponent)
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
        
        float Rotation = Owner->GetWorldRotation();
        ALLEGRO_BITMAP* ImageBMP = ImageBitmap->ImageBitmap;

        for (int i = 0; i < TilingU; i++)
        {

            for (int j = 0; j < TilingV; j++)
            {
                float CenterX = ImageBitmap->ImageWidth * (ScaleFromLeft ? 0.0f : 0.5f);
                float CenterY = ImageBitmap->ImageHeight * 0.5f;
                float DestinationX = Owner->GetWorldPositionX() + GetOffsetX() + i * ImageBitmap->ImageWidth;
                float DestinationY = Owner->GetWorldPositionY() + GetOffsetY() + j * ImageBitmap->ImageHeight;

				al_draw_scaled_rotated_bitmap(ImageBMP, CenterX, CenterY, DestinationX, DestinationY, ScaleX, ScaleY, Rotation, 0);
				
            }
        }
    }
}

void ImageComponent::LoadImage(string ImagePath)
{
    ImageBitmap = GameFramework::Get().GetBitmapManager().FindOrAddBitmap(ImagePath);
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


int ImageComponent::GetImageHeight() const
{
    if (ImageBitmap)
    {
        return ImageBitmap->ImageHeight;
    }

    return 0;
}

int ImageComponent::GetImageWidth() const
{
	if (ImageBitmap)
	{
		return ImageBitmap->ImageWidth;
	}

    return 0;
}

