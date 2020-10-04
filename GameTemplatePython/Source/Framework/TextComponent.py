import pygame
import Globals
import Framework.GameComponent

# This component allows us to display Text on a GameObject
class TextComponent(Framework.GameComponent.GameComponent):  # It is a child of the GameComponent class
    
    # This is the constructor for the TextComponent. It is called as soon as the TextComponent is created
    def __init__(self, Owner):
        super().__init__(Owner) # This calls the constructor of the base class: 'GameComponent'
        self.TextString = "" # These are the words that we want to display on screen
        self.TextObject = None # This is the object that represent the the text that we draw on screen
        self.bIsVisible = True # This is used to turn the display of the text on and off
      
    # These are accessors for turning the text visible/invisible
    def SetVisible(self, bIsNowVisible):
        self.bIsVisible = bIsNowVisible
    def IsVisible(self):
        return self.bIsVisible         
    
    # This allows us to change the words that the TextComponent displays
    def SetText(self, Text):
        self.TextString = Text
        white = (255, 255, 255) 
        self.TextObject = Globals.DefaultFont.render(self.TextString, True, white, None) 
        self.TextObjectRect = self.TextObject.get_rect()  
    
    # Here we make sure the Text always follows the position of the GameObject
    def OnUpdate(self, DeltaTime):
        for axis in range(0, 2):
            self.TextObjectRect[axis] = int(self.Owner.Position[axis] + self.Offset[axis])
    
    # This is where we draw the text on screen. If it's not visible, we don't draw it
    def OnRender(self, Screen):
        if (not self.bIsVisible):
            return
        Screen.blit(self.TextObject, self.TextObjectRect)
        