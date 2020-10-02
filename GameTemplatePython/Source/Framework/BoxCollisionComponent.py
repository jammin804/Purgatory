import pygame
import Framework.GameComponent

class BoxCollisionComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.bShowDebug = True
        self.HitBox = [0,0,0,0]
            
    def ShowDebug(self, bShowDebug):
        self.bShowDebug = bShowDebug
        
    def SetRect(self, NewRect):
        self.HitBox = NewRect
        
    def DoesCollide(self, OtherCollisionComponent):
        return self.HitBox.colliderect(OtherCollisionComponent.HitBox)
    
    def OnRender(self, Screen):
        if (not self.bShowDebug):
            return
        pygame.draw.rect(Screen, (255,0,0), self.HitBox,2)

