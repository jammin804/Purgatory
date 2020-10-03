import pygame
import Framework.GameComponent

class BoxCollisionComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.bShowDebug = False
        self.HitBox = pygame.Rect([0,0,0,0])
        self.Scale = 1.0
    
    def SetScale(self, NewScale):
        self.Scale = NewScale
        
    def GetScale(self):
        return self.Scale
            
    def ShowDebug(self, bShowDebug):
        self.bShowDebug = bShowDebug
        
    def SetRect(self, NewRect):
        self.HitBox[0] = NewRect[0] + ((1.0 - self.Scale) * NewRect[2] * 0.5)
        self.HitBox[1] = NewRect[1] + ((1.0 - self.Scale) * NewRect[3] * 0.5)
        self.HitBox[2] = NewRect[2] * self.Scale
        self.HitBox[3] = NewRect[3] * self.Scale
        
    def DoesCollide(self, OtherCollisionComponent):
        return self.HitBox.colliderect(OtherCollisionComponent.HitBox)
    
    def OnRender(self, Screen):
        if (not self.bShowDebug):
            return
        pygame.draw.rect(Screen, (255,0,0), self.HitBox,2)

