import Framework.GameObject
import Framework.ImageComponent
import Framework.InputComponent
import Framework.SoundComponent
import Framework.BoxCollisionComponent
import pygame
import math

class Rock(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.MovementSpeed = 150.0
        self.RotationSpeed = 80.0
        self.RockImage = Framework.ImageComponent.ImageComponent(self)
        self.RockImage.LoadImage("Art/Rock.png")
        self.Collision = Framework.BoxCollisionComponent.BoxCollisionComponent(self)
        self.Collision.SetScale(0.5)
        self.Collision.SetRect(self.RockImage.GetImageRect())
        
    def OnUpdate(self, DeltaTime):       
        self.Rotation += self.RotationSpeed * DeltaTime
        MovementDirection = [0.3, 0.1]
        MovementDirection[0] *= self.MovementSpeed * DeltaTime
        MovementDirection[1] *= self.MovementSpeed * DeltaTime
        self.Position[0] += MovementDirection[0]
        self.Position[1] += MovementDirection[1]
        self.Collision.SetRect(self.RockImage.GetImageRect())