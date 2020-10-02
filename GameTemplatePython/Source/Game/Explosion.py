import Framework.GameObject
import Framework.ImageComponent
import Framework.SoundComponent
import pygame
import math

class Explosion(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.MovementSpeed = 150.0
        self.RotationSpeed = 80.0
        self.ExplosionImage = Framework.ImageComponent.ImageComponent(self)
        self.ExplosionImage.LoadImage("Art/Explosion.png")
        self.DestroyedSound = Framework.SoundComponent.SoundComponent(self)
        self.DestroyedSound.LoadSample("Audio/Explosion.wav")
        self.DestroyedSound.Play()
        self.Timer = 0.0
        self.bIsFinished = False
        
    def IsFinished(self):
        if not self.bInitialised:
            return False
        return self.bIsFinished
        
    def OnUpdate(self, DeltaTime):       
        self.Timer += DeltaTime
        if self.Timer > 2.0:
            self.bIsFinished = True