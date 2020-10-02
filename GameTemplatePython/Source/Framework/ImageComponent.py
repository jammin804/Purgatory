#include "ImageComponent.h"

#include "GameObject.h"
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

import pygame
import Framework.GameComponent

class ImageComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)

    def LoadImage(self, ImagePath):
        self.Image = pygame.image.load(ImagePath)
        self.OriginalImage = self.Image
        self.ImageRect = self.Image.get_rect()
        
    def SetVisible(self, bIsNowVisible):
        self.bIsVisible = bIsNowVisible
            
    def OnRender(self, Screen):
        for axis in range(0, 2):
            self.ImageRect[axis] = int(self.Owner.Position[axis])
        rotated_image = pygame.transform.rotate(self.OriginalImage, -self.Owner.Rotation)
        new_rect = rotated_image.get_rect(center = self.OriginalImage.get_rect(topleft = self.ImageRect.topleft).center)
        Screen.blit(rotated_image, new_rect.topleft)


# ImageComponent::ImageComponent(class GameObject* Owner)
#     : GameComponent(Owner)
# {

# }

# void ImageComponent::OnInit()
# {
# }

# void ImageComponent::OnUpdate()
# {
# }

# void ImageComponent::OnShutdown()
# {
#     if (ImageBitmap)
#     {
#         al_destroy_bitmap(ImageBitmap);
#         ImageBitmap = nullptr;
#     }
# }

# void ImageComponent::OnRender()
# {
#     if (ImageBitmap && bIsVisible)
#     {
#         const GameObject* Owner = GetOwner();
#         al_draw_rotated_bitmap(ImageBitmap, ImageWidth * 0.5f, ImageHeight * 0.5f, Owner->GetPositionX() + GetOffsetX(), Owner->GetPositionY() + GetOffsetY(), Owner->GetRotation(), 0);
#     }
# }

# void ImageComponent::LoadImage(string ImagePath)
# {
#     ImageBitmap = al_load_bitmap(ImagePath.c_str());
#     if (!ImageBitmap)
#     {
#         printf("Couldn't load Image\n");
#     }
#     else
#     {
#         ImageWidth = al_get_bitmap_width(ImageBitmap);
#         ImageHeight = al_get_bitmap_height(ImageBitmap);
#     }
# }

# void ImageComponent::SetVisible(bool bIsNowVisible)
# {
#     bIsVisible = bIsNowVisible;
# }

