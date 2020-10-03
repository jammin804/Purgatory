import pygame
import Framework.GameComponent
import copy

class ImageComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.bIsVisible = True
        self.Scale = 1.0

    def LoadImage(self, ImagePath):
        self.Image = pygame.image.load(ImagePath)
        self.ImageRect = self.Image.get_rect()
        self.OriginalRect = copy.copy(self.ImageRect)
        self.OnUpdate(0.0)
        
    def SetVisible(self, bIsNowVisible):
        self.bIsVisible = bIsNowVisible

    def IsVisible(self):
        return self.bIsVisible        
    
    def GetImageRect(self):
        return self.ImageRect
    
    def OnUpdate(self, DeltaTime):
        for axis in range(0, 2):
            self.ImageRect[axis] = int(self.Owner.Position[axis] + self.Offset[axis])
            
    def OnRender(self, Screen):
        if (not self.bIsVisible):
            return
        rotated_image = pygame.transform.rotozoom(self.Image, -self.Owner.Rotation, self.Scale)
        new_rect = rotated_image.get_rect(center = self.Image.get_rect(topleft = self.ImageRect.topleft).center)
        Screen.blit(rotated_image, new_rect.topleft)

