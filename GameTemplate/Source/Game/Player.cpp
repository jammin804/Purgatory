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
             //bRespawning = true;
			 bInvulnerable = true;
         }
         return;
    }

    if (bInvulnerable)//bRespawning)
    {
        PlayerAvatarImageComponent->SetVisible(!PlayerAvatarImageComponent->IsVisible());
        RespawnTimer += DeltaTime;
        if (RespawnTimer > RespawningTime)
        {
            //bRespawning = false;
            bInvulnerable = false;
            PlayerAvatarImageComponent->SetVisible(true);
        }
    }
    
	float DirectionX = 0.0f;
	float DirectionY = 0.0f;
	if (InputComp->IsKeyPressed(ALLEGRO_KEY_UP) || InputComp->IsKeyPressed(ALLEGRO_KEY_W))
	{
		DirectionY -= PlayerMovementSpeed * DeltaTime;
	}
	if (InputComp->IsKeyPressed(ALLEGRO_KEY_DOWN) || InputComp->IsKeyPressed(ALLEGRO_KEY_S))
	{
		DirectionY += PlayerMovementSpeed * DeltaTime;
	}
    if (InputComp->IsKeyPressed(ALLEGRO_KEY_LEFT) || InputComp->IsKeyPressed(ALLEGRO_KEY_A))
    {
		DirectionX -= PlayerMovementSpeed * DeltaTime;
    }
    if (InputComp->IsKeyPressed(ALLEGRO_KEY_RIGHT) || InputComp->IsKeyPressed(ALLEGRO_KEY_D))
    {
		DirectionX += PlayerMovementSpeed * DeltaTime;
    }
	SetPosition(GetPositionX() + DirectionX, GetPositionY() + DirectionY);
	//Update Sprite
	
	if (DirectionY < 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P_Back.png");
	}
	if (DirectionY > 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P.png");
	}
	if (DirectionX > 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P_Side.png");
		PlayerAvatarImageComponent->SetScaleX(-1.0f);
	}
	if (DirectionX < 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P_Side.png");
		PlayerAvatarImageComponent->SetScaleX(1.0f);
	}


	if (!bInvulnerable && InputComp->IsKeyPressed(ALLEGRO_KEY_SPACE))
	{
		if (bCanMakeLaser)
		{
			CreateCross(DirectionX, DirectionY);
			bCanMakeLaser = false;
		}
	}

	if (InputComp->IsKeyReleased(ALLEGRO_KEY_SPACE))
	{
		bCanMakeLaser = true;
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

    /*if (PlayerAvatarImageComponent)
    {
        PlayerAvatarImageComponent->SetVisible(false);
    }*/

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

void Player::CreateCross(float DirX, float DirY)
{
	Cross* NewCross = GameObject::CreateInstance<Cross>();

	//float DirectionY = 0.0f;//cos(GetRotation());
	//float DirectionX = 1.0f;//sin(GetRotation());
    NewCross->SetPosition(GetPositionX() + (DirX * 30.0f),  GetPositionY() + (-DirY * 30.0f));
	//NewCross->SetPosition(GetPositionX(), GetPositionY());
	NewCross->SetInitialDirection(DirX, DirY);
    Crosses.push_back(NewCross);
}

bool Player::IsInvulnerable() const
{
    return bInvulnerable;
}
