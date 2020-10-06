#include "Player.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Laser.h"

void Player::OnInit()
{
    PlayerAvatarThrustersImageComponent = new ImageComponent(this);
    PlayerAvatarThrustersImageComponent->SetVisible(false);
    PlayerAvatarImageComponent = new ImageComponent(this);
    InputComp = new InputComponent(this);
    ThrusterSoundComponent = new SoundComponent(this);
    ThrusterSoundComponent->SetLooped(true);
    ThrusterSoundComponent->SetVolume(0.3f);
    Collision = new BoxCollisionComponent(this);

    Lasers.reserve(200);
    //Collision->SetScale(0.5f);
}

void Player::OnUpdate(float DeltaTime)
{
    if (Lasers.size() > 0)
    {
        for (auto Iter = Lasers.begin(); Iter != Lasers.end();)
        {
            if ((*Iter)->IsDestroyed())
            {
                Iter = Lasers.erase(Iter);
                continue;
            }
            ++Iter;
        }
    }

    if (bExploding)
    {
         ExplodeTimer += DeltaTime;
         if (ExplodeTimer > ExplodingTime)
         {
             bExploding = false;
             bRespawning = true;
         }
         return;
    }

    if (bRespawning)
    {
        PlayerAvatarImageComponent->SetVisible(!PlayerAvatarImageComponent->IsVisible());
        RespawnTimer += DeltaTime;
        if (RespawnTimer > RespawningTime)
        {
            bRespawning = false;
            bInvulnerable = false;
            PlayerAvatarImageComponent->SetVisible(true);
        }
    }
    

    if (InputComp->IsKeyPressed(ALLEGRO_KEY_UP) || InputComp->IsKeyPressed(ALLEGRO_KEY_W))
    {
        // Move the player forward in the direction he's facing
        {
            float DirectionY = cos(GetRotation()) * PlayerMovementSpeed * DeltaTime;
            float DirectionX = sin(GetRotation()) * PlayerMovementSpeed * DeltaTime;

            SetPosition(GetPositionX() + DirectionX, GetPositionY() - DirectionY);
        }

        if (!bRespawning && !ThrusterSoundComponent->IsPlaying())
        {
            PlayerAvatarThrustersImageComponent->SetVisible(true);
            ThrusterSoundComponent->Play();
        }
    }
    else
    {
        if (ThrusterSoundComponent->IsPlaying())
        {
            PlayerAvatarThrustersImageComponent->SetVisible(false);
            ThrusterSoundComponent->Stop();
        }
    }

    if (!bRespawning && InputComp->IsKeyPressed(ALLEGRO_KEY_SPACE))
    {
        if (bCanMakeLaser)
        {
            CreateLaser(); 
            bCanMakeLaser = false;
        }
    }
    
    if (InputComp->IsKeyReleased(ALLEGRO_KEY_SPACE))
    {
        bCanMakeLaser = true;
    }
    
    if (InputComp->IsKeyPressed(ALLEGRO_KEY_LEFT) || InputComp->IsKeyPressed(ALLEGRO_KEY_A))
    {
        SetRotation(GetRotation() - RotationSpeed * DeltaTime);
    }
    else if (InputComp->IsKeyPressed(ALLEGRO_KEY_RIGHT) || InputComp->IsKeyPressed(ALLEGRO_KEY_D))
    {
        SetRotation(GetRotation() + RotationSpeed * DeltaTime);
    }
}

void Player::OnShutdown()
{
    delete PlayerAvatarThrustersImageComponent;
    PlayerAvatarThrustersImageComponent = nullptr;

    delete PlayerAvatarImageComponent;
    PlayerAvatarImageComponent = nullptr;

    delete InputComp;
    InputComp = nullptr;

    delete ThrusterSoundComponent;
    ThrusterSoundComponent = nullptr;
}

void Player::SetAvatarImage(string ImagePath)
{
    if (PlayerAvatarImageComponent)
    {
        PlayerAvatarImageComponent->LoadImage(ImagePath);
    }
}

void Player::SetThrustersImage(string ImagePath)
{
    if (PlayerAvatarThrustersImageComponent)
    {
        PlayerAvatarThrustersImageComponent->LoadImage(ImagePath);
    }
}

void Player::SetThrustersSound(string SoundPath)
{
    if (ThrusterSoundComponent)
    {
        ThrusterSoundComponent->LoadSample(SoundPath);
    }
}

bool Player::HandleDeath()
{
    if (ThrusterSoundComponent && ThrusterSoundComponent->IsPlaying())
    {
        PlayerAvatarThrustersImageComponent->SetVisible(false);
        ThrusterSoundComponent->Stop();
    }

    if (PlayerAvatarImageComponent)
    {
        PlayerAvatarImageComponent->SetVisible(false);
    }

    if (LivesLeft > 0)
    {
        bExploding = true;
        LivesLeft--;
        bInvulnerable = true;
        ExplodeTimer = 0.0f;
        RespawnTimer = 0.0f;
        return false;
    }
    else
    {
        SetEnabled(false);
        return true;
    }
}

void Player::CreateLaser()
{
    Laser* NewLaser = new Laser();
    float DirectionY = cos(GetRotation());
    float DirectionX = sin(GetRotation());
    NewLaser->SetPosition(GetPositionX() + (DirectionX * 30.0f),  GetPositionY() - (DirectionY * 30.0f));
    NewLaser->SetRotation(GetRotation());
    Lasers.push_back(NewLaser);
}

bool Player::IsInvulnerable() const
{
    return bInvulnerable;
}
