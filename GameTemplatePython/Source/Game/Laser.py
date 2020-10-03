import Framework.GameObject
import Framework.ImageComponent
import Framework.BoxCollisionComponent
import Framework.SoundComponent
import pygame
import math

class Laser(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.LaserSpeed = 500.0
        self.LaserImage = Framework.ImageComponent.ImageComponent(self)
        self.LaserImage.LoadImage("Art/Laser.png")
        self.Collision = Framework.BoxCollisionComponent.BoxCollisionComponent(self)
        self.Collision.SetRect(self.LaserImage.GetImageRect())
        self.LaserSound = Framework.SoundComponent.SoundComponent(self)
        self.LaserSound.LoadSample("Audio/Laser.wav")
        self.LaserSound.SetVolume(0.1)
        self.LaserSound.Play()
        self.LifeTimer = 0.0
        
    def OnPostInit(self):
        self.Position[0] -= self.LaserImage.GetImageRect()[2] * 0.5
        self.Position[1] -= self.LaserImage.GetImageRect()[3] * 0.5
        DirectionX = math.sin(math.radians(self.Rotation))
        DirectionY = math.cos(math.radians(self.Rotation)) 
        self.Position[0] += DirectionX * 30 
        self.Position[1] += -DirectionY * 30
        
    def OnUpdate(self, DeltaTime):        
        DirectionX = math.sin(math.radians(self.Rotation)) * self.LaserSpeed
        DirectionY = math.cos(math.radians(self.Rotation)) * self.LaserSpeed 
        self.Position[0] += (DirectionX * DeltaTime)
        self.Position[1] += -(DirectionY * DeltaTime)
        self.Collision.SetRect(self.LaserImage.GetImageRect())
        self.LifeTimer += DeltaTime
        if (self.LifeTimer > 5.0):
            self.Destroy()