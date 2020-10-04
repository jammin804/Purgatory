# Import other files
import pygame
import Framework.GameComponent
import copy

# This Component is used to allow us to draw image files on screen
class ImageComponent(Framework.GameComponent.GameComponent): # It is a child of the GameComponent class
    
    # This is the constructor for the ImageComponent. It is called as soon as the ImageComponent is created
    def __init__(self, Owner):
        super().__init__(Owner) # This calls the constructor of the base class: 'GameComponent'
        self.bIsVisible = True # Allows us to turn the image on and off
        self.Scale = 1.0 # Allows us to resize the image

    # This function is used to load the image file that we want. 
    # It takes a path on the computer to load the image file from
    # We can use it to load .png files for example
    def LoadImage(self, ImagePath):
        self.Image = pygame.image.load(ImagePath)
        self.ImageRect = self.Image.get_rect()
        self.OriginalRect = copy.copy(self.ImageRect)
        self.OnUpdate(0.0)
    
    # Accessor methods for visibility
    def SetVisible(self, bIsNowVisible):
        self.bIsVisible = bIsNowVisible
    def IsVisible(self):
        return self.bIsVisible        
    
    # Accessor for the Rectangle that represents the position of the Image
    def GetImageRect(self):
        return self.ImageRect
    
    # Every update we make sure that the image follows the GameObject's Position alongside any Offset specified as part of the component
    def OnUpdate(self, DeltaTime):
        for axis in range(0, 2):
            self.ImageRect[axis] = int(self.Owner.Position[axis] + self.Offset[axis])
    
    # This method is used to Draw the image. It makes sure it is scaled and rotated too.        
    def OnRender(self, Screen):
        if (not self.bIsVisible): # If it's not visible don't draw it
            return
        RotatedAndScaledImage = pygame.transform.rotozoom(self.Image, -self.Owner.Rotation, self.Scale) # rotozoom is rotation and scale
        new_rect = RotatedAndScaledImage.get_rect(center = self.Image.get_rect(topleft = self.ImageRect.topleft).center) # We make sure to rotate from the center
        Screen.blit(RotatedAndScaledImage, new_rect.topleft) # This draws the Image on the Screen

