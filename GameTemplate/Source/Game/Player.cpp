#include "Player.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"

void Player::OnInit()
{
    PlayerAvatarThrusters = new ImageComponent(this);
    PlayerAvatar = new ImageComponent(this);
    InputComp = new InputComponent(this);
    ThrusterSound = new SoundComponent(this);
    ThrusterSound->SetLooped(true);
    ThrusterSound->SetVolume(0.3f);
}

void Player::OnUpdate()
{
    if (InputComp->IsKeyPressed(ALLEGRO_KEY_UP) || InputComp->IsKeyPressed(ALLEGRO_KEY_W))
    {
        float DirectionY = cos(GetRotation()) * PlayerMovementSpeed;
        float DirectionX = sin(GetRotation()) * PlayerMovementSpeed;

        SetPos(GetPosX() + DirectionX, GetPosY() - DirectionY);

        PlayerAvatarThrusters->SetVisible(true);
        if (!ThrusterSound->IsPlaying())
        {
            ThrusterSound->Play();
        }
    }
    else
    {
        PlayerAvatarThrusters->SetVisible(false);
        if (ThrusterSound->IsPlaying())
        {
            ThrusterSound->Stop();
        }
    }
    
    if (InputComp->IsKeyPressed(ALLEGRO_KEY_LEFT) || InputComp->IsKeyPressed(ALLEGRO_KEY_A))
    {
        SetRotation(GetRotation() - RotationSpeed);
    }
    else if (InputComp->IsKeyPressed(ALLEGRO_KEY_RIGHT) || InputComp->IsKeyPressed(ALLEGRO_KEY_D))
    {
        SetRotation(GetRotation() + RotationSpeed);
    }
}

void Player::OnShutdown()
{
    delete PlayerAvatarThrusters;
    PlayerAvatarThrusters = nullptr;

    delete PlayerAvatar;
    PlayerAvatar = nullptr;

    delete InputComp;
    InputComp = nullptr;

    delete ThrusterSound;
    ThrusterSound = nullptr;
}

void Player::SetAvatarImage(string ImagePath)
{
    if (PlayerAvatar)
    {
        PlayerAvatar->LoadImage(ImagePath);
    }
}

void Player::SetThrustersImage(string ImagePath)
{
    if (PlayerAvatarThrusters)
    {
        PlayerAvatarThrusters->LoadImage(ImagePath);
    }
}

void Player::SetThrustersSound(string SoundPath)
{
    if (ThrusterSound)
    {
        ThrusterSound->LoadSample(SoundPath);
    }
}
