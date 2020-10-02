import Framework.GameObject
import Framework.ImageComponent

class Player(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.PlayerAvatar = Framework.ImageComponent.ImageComponent(self)
        self.PlayerAvatar.LoadImage("Art/Ship.png")
    #         ImageComponent* PlayerAvatarThrustersImageComponent = nullptr;
    # InputComponent* InputComp = nullptr;
    # SoundComponent* ThrusterSoundComponent = nullptr;
    
    def OnUpdate(self):
        #check input
        pass

# protected:
#     virtual void OnInit() override;
#     virtual void OnUpdate() override;
#     virtual void OnShutdown() override;

# public:
#     void SetAvatarImage(string ImagePath);
#     void SetThrustersImage(string ImagePath);
#     void SetThrustersSound(string SoundPath);
# private:
#     ImageComponent* PlayerAvatarImageComponent = nullptr;


#     float PlayerMovementSpeed = 10.0f;
#     float RotationSpeed = 0.2f;
# };


# void Player::OnInit()
# {
#     PlayerAvatarThrustersImageComponent = new ImageComponent(this);
#     PlayerAvatarThrustersImageComponent->SetVisible(false);
#     PlayerAvatarImageComponent = new ImageComponent(this);
#     InputComp = new InputComponent(this);
#     ThrusterSoundComponent = new SoundComponent(this);
#     ThrusterSoundComponent->SetLooped(true);
#     ThrusterSoundComponent->SetVolume(0.3f);
# }

# void Player::OnUpdate()
# {
#     if (InputComp->IsKeyPressed(ALLEGRO_KEY_UP) || InputComp->IsKeyPressed(ALLEGRO_KEY_W))
#     {
#         // Move the player forward in the direction he's facing
#         {
#             float DirectionY = cos(GetRotation()) * PlayerMovementSpeed;
#             float DirectionX = sin(GetRotation()) * PlayerMovementSpeed;

#             SetPosition(GetPositionX() + DirectionX, GetPositionY() - DirectionY);
#         }

#         if (!ThrusterSoundComponent->IsPlaying())
#         {
#             PlayerAvatarThrustersImageComponent->SetVisible(true);
#             ThrusterSoundComponent->Play();
#         }
#     }
#     else
#     {
#         if (ThrusterSoundComponent->IsPlaying())
#         {
#             PlayerAvatarThrustersImageComponent->SetVisible(false);
#             ThrusterSoundComponent->Stop();
#         }
#     }
    
#     if (InputComp->IsKeyPressed(ALLEGRO_KEY_LEFT) || InputComp->IsKeyPressed(ALLEGRO_KEY_A))
#     {
#         SetRotation(GetRotation() - RotationSpeed);
#     }
#     else if (InputComp->IsKeyPressed(ALLEGRO_KEY_RIGHT) || InputComp->IsKeyPressed(ALLEGRO_KEY_D))
#     {
#         SetRotation(GetRotation() + RotationSpeed);
#     }
# }

# void Player::OnShutdown()
# {
#     delete PlayerAvatarThrustersImageComponent;
#     PlayerAvatarThrustersImageComponent = nullptr;

#     delete PlayerAvatarImageComponent;
#     PlayerAvatarImageComponent = nullptr;

#     delete InputComp;
#     InputComp = nullptr;

#     delete ThrusterSoundComponent;
#     ThrusterSoundComponent = nullptr;
# }

# void Player::SetAvatarImage(string ImagePath)
# {
#     if (PlayerAvatarImageComponent)
#     {
#         PlayerAvatarImageComponent->LoadImage(ImagePath);
#     }
# }

# void Player::SetThrustersImage(string ImagePath)
# {
#     if (PlayerAvatarThrustersImageComponent)
#     {
#         PlayerAvatarThrustersImageComponent->LoadImage(ImagePath);
#     }
# }

# void Player::SetThrustersSound(string SoundPath)
# {
#     if (ThrusterSoundComponent)
#     {
#         ThrusterSoundComponent->LoadSample(SoundPath);
#     }
# }
