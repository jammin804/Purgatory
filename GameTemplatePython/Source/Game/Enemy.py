#include "Enemy.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"

void Enemy::OnInit()
{
    EnemyAvatarThrustersImageComponent = new ImageComponent(this);
    EnemyAvatarThrustersImageComponent->SetVisible(false);
    EnemyAvatarImageComponent = new ImageComponent(this);
    ThrusterSoundComponent = new SoundComponent(this);
    ThrusterSoundComponent->SetLooped(true);
    ThrusterSoundComponent->SetVolume(0.3f);
}

void Enemy::OnUpdate()
{
}

void Enemy::OnShutdown()
{
    delete EnemyAvatarThrustersImageComponent;
    EnemyAvatarThrustersImageComponent = nullptr;

    delete EnemyAvatarImageComponent;
    EnemyAvatarImageComponent = nullptr;

    delete ThrusterSoundComponent;
    ThrusterSoundComponent = nullptr;
}

void Enemy::SetAvatarImage(string ImagePath)
{
    if (EnemyAvatarImageComponent)
    {
        EnemyAvatarImageComponent->LoadImage(ImagePath);
    }
}

void Enemy::SetThrustersImage(string ImagePath)
{
    if (EnemyAvatarThrustersImageComponent)
    {
        EnemyAvatarThrustersImageComponent->LoadImage(ImagePath);
    }
}

void Enemy::SetThrustersSound(string SoundPath)
{
    if (ThrusterSoundComponent)
    {
        ThrusterSoundComponent->LoadSample(SoundPath);
    }
}
