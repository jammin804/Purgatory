import Framework.GameObject
import Framework.ImageComponent
import Framework.InputComponent
import Framework.SoundComponent
import Framework.BoxCollisionComponent
import Game.Laser
import pygame
import math
import copy

class Player(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.PlayerMovementSpeed = 150.0
        self.RotationSpeed = 60.0
        self.Position = [1280*0.5, 720*0.5]
        self.PlayerAvatar = Framework.ImageComponent.ImageComponent(self)
        self.PlayerAvatar.LoadImage("Art/Ship.png")
        self.PlayerThruster = Framework.ImageComponent.ImageComponent(self)
        self.PlayerThruster.LoadImage("Art/Thrusters.png")
        self.PlayerThruster.SetVisible(False)
        self.Input = Framework.InputComponent.InputComponent(self)
        self.ThrusterSound = Framework.SoundComponent.SoundComponent(self)
        self.ThrusterSound.SetLooped(True)
        self.ThrusterSound.LoadSample("Audio/Thruster.wav")
        self.ThrusterSound.SetVolume(0.1)
        self.Collision = Framework.BoxCollisionComponent.BoxCollisionComponent(self)
        self.Collision.SetScale(0.5)
        self.Collision.SetRect(self.PlayerAvatar.GetImageRect())
        self.bCanMakeLaser = True
        self.Lasers = []
    
    def CreateLaser(self):
        Laser = Game.Laser.Laser()
        PlayerRect = self.PlayerAvatar.GetImageRect()
        Laser.Position = [PlayerRect[0] + (PlayerRect[2] * 0.5), PlayerRect[1] + (PlayerRect[3] * 0.5)]
        Laser.Rotation = copy.copy(self.Rotation)
        self.Lasers.append(Laser)
    
    def OnUpdate(self, DeltaTime):
        
        for Laser in self.Lasers:
            if (Laser.bIsDestroyed):
                self.Lasers.remove(Laser)
        
        if self.Input.IsKeyPressed(pygame.K_UP) or self.Input.IsKeyPressed(pygame.K_w):
        # Move the player forward in the direction he's facing
            DirectionY = math.cos(math.radians(self.Rotation)) * self.PlayerMovementSpeed 
            DirectionX = math.sin(math.radians(self.Rotation)) * self.PlayerMovementSpeed
            self.Position[0] += (DirectionX * DeltaTime)
            self.Position[1] += -(DirectionY * DeltaTime)

            if not self.ThrusterSound.IsPlaying():
                self.PlayerThruster.SetVisible(True)
                self.ThrusterSound.Play()
        else:
            if self.ThrusterSound.IsPlaying():
                self.PlayerThruster.SetVisible(False)
                self.ThrusterSound.Stop()
        
        if self.Input.IsKeyPressed(pygame.K_SPACE):
            if self.bCanMakeLaser:
                self.CreateLaser()
            self.bCanMakeLaser = False
        elif self.Input.IsKeyReleased(pygame.K_SPACE):
            self.bCanMakeLaser = True
        
        if self.Input.IsKeyPressed(pygame.K_LEFT) or self.Input.IsKeyPressed(pygame.K_a):
            self.Rotation -= self.RotationSpeed * DeltaTime
        elif self.Input.IsKeyPressed(pygame.K_RIGHT) or self.Input.IsKeyPressed(pygame.K_d):
            self.Rotation += self.RotationSpeed * DeltaTime
            
        self.Collision.SetRect(self.PlayerAvatar.GetImageRect())