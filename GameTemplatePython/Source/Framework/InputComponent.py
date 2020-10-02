import Framework.GameComponent
import pygame

class InputComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.Keys = pygame.key.get_pressed()
        
        
    def IsKeyPressed(self, KeyCode):
        return self.Keys[KeyCode] == True
    
    def IsKeyReleased(self, KeyCode):
        return self.Keys[KeyCode] == False
        
    def OnUpdate(self, DeltaTime):
        self.Keys = pygame.key.get_pressed()