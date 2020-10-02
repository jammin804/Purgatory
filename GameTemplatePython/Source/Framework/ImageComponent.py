import pygame
import Framework.GameComponent

class ImageComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.bIsVisible = True

    def LoadImage(self, ImagePath):
        self.Image = pygame.image.load(ImagePath)
        self.OriginalImage = self.Image
        self.ImageRect = self.Image.get_rect()
        
    def SetVisible(self, bIsNowVisible):
        self.bIsVisible = bIsNowVisible
    
    def GetImageRect(self):
        return self.ImageRect
            
    def OnRender(self, Screen):
        if (not self.bIsVisible):
            return
        for axis in range(0, 2):
            self.ImageRect[axis] = int(self.Owner.Position[axis])
        rotated_image = pygame.transform.rotate(self.OriginalImage, -self.Owner.Rotation)
        new_rect = rotated_image.get_rect(center = self.OriginalImage.get_rect(topleft = self.ImageRect.topleft).center)
        Screen.blit(rotated_image, new_rect.topleft)

