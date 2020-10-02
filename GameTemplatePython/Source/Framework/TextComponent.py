import pygame
import Globals
import Framework.GameComponent

class TextComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.TextString = ""
        self.TextObject = None
        
        
    def SetText(self, Text):
        self.TextString = Text
        white = (255, 255, 255) 
        self.TextObject = Globals.DefaultFont.render(self.TextString, True, white, None) 
        self.TextObjectRect = self.TextObject.get_rect()  
    
    def OnUpdate(self, DeltaTime):
        self.TextObjectRect.center = self.Owner.Position
    
    def OnRender(self, Screen):
        Screen.blit(self.TextObject, self.TextObjectRect)
        