import pygame
import Globals
import Framework.GameComponent

class TextComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.TextString = ""
        self.TextObject = None
        self.bIsVisible = True
      
    def SetVisible(self, bIsNowVisible):
        self.bIsVisible = bIsNowVisible

    def IsVisible(self):
        return self.bIsVisible         
        
    def SetText(self, Text):
        self.TextString = Text
        white = (255, 255, 255) 
        self.TextObject = Globals.DefaultFont.render(self.TextString, True, white, None) 
        self.TextObjectRect = self.TextObject.get_rect()  
    
    def OnUpdate(self, DeltaTime):
        for axis in range(0, 2):
            self.TextObjectRect[axis] = int(self.Owner.Position[axis] + self.Offset[axis])
    
    def OnRender(self, Screen):
        if (not self.bIsVisible):
            return
        Screen.blit(self.TextObject, self.TextObjectRect)
        