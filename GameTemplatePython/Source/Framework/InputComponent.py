import Framework.GameComponent
import pygame

# This component is used by the GameObject to detect if any keys have been pressed or released
class InputComponent(Framework.GameComponent.GameComponent): # It is a child of the GameComponent class
    
    # This is the constructor for the InputComponent. It is called as soon as the InputComponent is created
    def __init__(self, Owner):
        super().__init__(Owner) # This calls the constructor of the base class: 'GameComponent'
        self.Keys = pygame.key.get_pressed() # This stores the current state (pressed or not pressed) of every key on your Keyboard
           
    # These functions are used to query if a Key is currently pressed or released this frame
    def IsKeyPressed(self, KeyCode):
        return self.Keys[KeyCode] == True
    def IsKeyReleased(self, KeyCode):
        return self.Keys[KeyCode] == False
        
    # This stores the current state (pressed or not pressed) of every key on your Keyboard            
    def OnUpdate(self, DeltaTime):
        self.Keys = pygame.key.get_pressed()