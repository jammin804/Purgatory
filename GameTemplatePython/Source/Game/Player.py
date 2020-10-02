import Framework.GameObject
import Framework.ImageComponent
import Framework.InputComponent
import pygame
import math

class Player(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.PlayerMovementSpeed = 150.0
        self.RotationSpeed = 60.0
        self.Position = [1280*0.5, 720*0.5]
        self.PlayerAvatar = Framework.ImageComponent.ImageComponent(self)
        self.PlayerAvatar.LoadImage("Art/Ship.png")
    #         ImageComponent* PlayerAvatarThrustersImageComponent = nullptr;
        self.InputComponent = Framework.InputComponent.InputComponent(self)
    # SoundComponent* ThrusterSoundComponent = nullptr;
    
    def OnUpdate(self, DeltaTime):
        if self.InputComponent.IsKeyPressed(pygame.K_UP) or self.InputComponent.IsKeyPressed(pygame.K_w):
        # Move the player forward in the direction he's facing
            DirectionY = math.cos(math.radians(self.Rotation)) * self.PlayerMovementSpeed 
            DirectionX = math.sin(math.radians(self.Rotation)) * self.PlayerMovementSpeed
            self.Position[0] += (DirectionX * DeltaTime)
            self.Position[1] += -(DirectionY * DeltaTime)

    #     if (!ThrusterSoundComponent->IsPlaying())
    #     {
    #         PlayerAvatarThrustersImageComponent->SetVisible(true);
    #         ThrusterSoundComponent->Play();
    #     }
    # }
    # else
    # {
    #     if (ThrusterSoundComponent->IsPlaying())
    #     {
    #         PlayerAvatarThrustersImageComponent->SetVisible(false);
    #         ThrusterSoundComponent->Stop();
    #     }
    # }
    
        if self.InputComponent.IsKeyPressed(pygame.K_LEFT) or self.InputComponent.IsKeyPressed(pygame.K_a):
            self.Rotation -= self.RotationSpeed * DeltaTime
        elif self.InputComponent.IsKeyPressed(pygame.K_RIGHT) or self.InputComponent.IsKeyPressed(pygame.K_d):
            self.Rotation += self.RotationSpeed * DeltaTime