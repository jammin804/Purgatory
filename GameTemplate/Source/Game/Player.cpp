#include "Player.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Cross.h"

void Player::OnInit()
{
    PlayerAvatarThrustersImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
    PlayerAvatarThrustersImageComponent->SetVisible(false);
    PlayerAvatarImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
    InputComp = GameComponent::CreateInstance<InputComponent>(this);
    ThrusterSoundComponent = GameComponent::CreateInstance<SoundComponent>(this);
    ThrusterSoundComponent->SetLooped(true);
    ThrusterSoundComponent->SetVolume(0.3f);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);

    Crosses.reserve(200);
    //Collision->SetScale(0.5f);
}

void Player::OnUpdate(float DeltaTime)
{
    if (Crosses.size() > 0)
    {
        for (auto Iter = Crosses.begin(); Iter != Crosses.end();)
        {
            if ((*Iter)->IsDestroyed())
            {
                Iter = Crosses.erase(Iter);
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
            CreateCross(); 
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

    if (HealthLeft > 0)
    {
        bExploding = true;
        HealthLeft--;
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

void Player::CreateCross()
{
	Cross* NewCross = GameObject::CreateInstance<Cross>();
    float DirectionY = cos(GetRotation());
    float DirectionX = sin(GetRotation());
    NewCross->SetPosition(GetPositionX() + (DirectionX * 30.0f),  GetPositionY() - (DirectionY * 30.0f));
	NewCross->SetInitialDirection(DirectionX, DirectionY);
    Crosses.push_back(NewCross);
}

bool Player::IsInvulnerable() const
{
    return bInvulnerable;
}
