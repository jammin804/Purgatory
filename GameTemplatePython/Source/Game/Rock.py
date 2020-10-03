import Framework.GameObject
import Framework.ImageComponent
import Framework.BoxCollisionComponent
import pygame
import math
import Globals

class Rock(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.bNeedsSplit = False
        self.RotationSpeed = 80.0
        self.RockImage = Framework.ImageComponent.ImageComponent(self)
        self.RockImage.LoadImage(Globals.path_to_art + "/Rock.png")
        self.RockImage.Scale = (self.SplitsLeft + 1) * 0.33
        self.Collision = Framework.BoxCollisionComponent.BoxCollisionComponent(self)
        self.Collision.SetScale((self.SplitsLeft + 1) * 0.16)
        self.Collision.SetRect(self.RockImage.GetImageRect())
        self.MaxLifeTime = 30.0
        self.LifeTimer = 0.0
        
    def OnUpdate(self, DeltaTime):       
        self.Rotation += self.RotationSpeed * DeltaTime
        self.Position[0] += self.MovementDirection[0] * self.MovementSpeed * DeltaTime
        self.Position[1] += self.MovementDirection[1] * self.MovementSpeed * DeltaTime
        self.Collision.SetRect(self.RockImage.GetImageRect())
        self.LifeTimer += DeltaTime
        if self.LifeTimer > self.MaxLifeTime:
            self.Destroy()
        
        
    def Split(self):
        self.SplitsLeft -= 1
        self.MovementSpeed *= 1.2
        self.bNeedsSplit = False
        self.RockImage.Scale = (self.SplitsLeft + 1) * 0.33
        self.Collision.SetScale((self.SplitsLeft + 1) * 0.16)
        CurrentMoveDirectionX = self.MovementDirection[0]
        self.MovementDirection[0] = self.MovementDirection[1]
        self.MovementDirection[1] = CurrentMoveDirectionX
        