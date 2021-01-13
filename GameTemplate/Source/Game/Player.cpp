#include "Player.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Cross.h"
#include "Background.h"

void Player::OnInit()
{
    PlayerAvatarThrustersImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
    PlayerAvatarThrustersImageComponent->SetVisible(false);
    PlayerAvatarImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
    InputComp = GameComponent::CreateInstance<InputComponent>(this);
	CoinSoundComponentPickup = GameComponent::CreateInstance<SoundComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);

    Crosses.reserve(200);
}

void Player::OnPostInit()
{
	if (CoinSoundComponentPickup)
	{
		CoinSoundComponentPickup->SetVolume(1.0f);
		CoinSoundComponentPickup->LoadSample("Audio/Pickup.wav");
	}
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

    if (bInvulnerable)
    {
        PlayerAvatarImageComponent->SetVisible(!PlayerAvatarImageComponent->IsVisible());
        RespawnTimer += DeltaTime;
        if (RespawnTimer > RespawningTime)
        {
            bInvulnerable = false;
            PlayerAvatarImageComponent->SetVisible(true);
        }
    }
    
	float DirectionX = 0.0f;
	float DirectionY = 0.0f;
	if (InputComp->IsKeyPressed(ALLEGRO_KEY_UP) || InputComp->IsKeyPressed(ALLEGRO_KEY_W))
	{
		DirectionY -= PlayerMovementSpeed * DeltaTime;
		LookingDirectionY = 1;
		LookingDirectionX = 0;
	}
	if (InputComp->IsKeyPressed(ALLEGRO_KEY_DOWN) || InputComp->IsKeyPressed(ALLEGRO_KEY_S))
	{
		DirectionY += PlayerMovementSpeed * DeltaTime;
		LookingDirectionY = -1;
		LookingDirectionX = 0;
	}
    if (InputComp->IsKeyPressed(ALLEGRO_KEY_LEFT) || InputComp->IsKeyPressed(ALLEGRO_KEY_A))
    {
		DirectionX -= PlayerMovementSpeed * DeltaTime;
		LookingDirectionX = -1;
		LookingDirectionY = 0;
    }
    if (InputComp->IsKeyPressed(ALLEGRO_KEY_RIGHT) || InputComp->IsKeyPressed(ALLEGRO_KEY_D))
    {
		DirectionX += PlayerMovementSpeed * DeltaTime;
		LookingDirectionX = 1;
		LookingDirectionY = 0;
    }

	/*Is just key pressed for looking direction - code below*/
	
	if (BG)
	{
		BG->SetPosition(BG->GetPositionX() - DirectionX, BG->GetPositionY() - DirectionY);
	}
	//Update Sprite
	
	if (LookingDirectionY > 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P_Back.png");
	}
	if (LookingDirectionY < 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P.png");
	}
	if (LookingDirectionX > 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P_Side.png");
		PlayerAvatarImageComponent->SetScaleX(-1.0f);
	}
	if (LookingDirectionX < 0)
	{
		PlayerAvatarImageComponent->LoadImage("Art/Player_P_Side.png");
		PlayerAvatarImageComponent->SetScaleX(1.0f);
	}


	if (!bInvulnerable && InputComp->IsKeyPressed(ALLEGRO_KEY_SPACE))
	{
		if (bCanMakeLaser)
		{
			/*int NumberOfCrossesToSpawn = 3;
			int TimeSinceLastCross = 100;*/
			/*for (int i = 0; i < NumberOfCrossesToSpawn; i++) for 3 shot burst
			{
				 
					CreateCross(LookingDirectionX, LookingDirectionY);
					// Need to space the bullets out based on time
			}*/

			/*CreateCross(LookingDirectionX, LookingDirectionY -= 15);
			CreateCross(LookingDirectionX, LookingDirectionY += 15);
			CreateCross(LookingDirectionX, LookingDirectionY += 15); */
			//ShootSpread();
			ShootOrbital();
			//CreateCross(LookingDirectionX, LookingDirectionY);

			/* Shoots behind the player and in the front
			CreateCross(LookingDirectionX, LookingDirectionY * 0 + sin(30));
				CreateCross(LookingDirectionX, LookingDirectionY);
				CreateCross(LookingDirectionX, LookingDirectionY * 0 - sin(30));*/
			bCanMakeLaser = false;


		}
	}

	if (InputComp->IsKeyReleased(ALLEGRO_KEY_SPACE))
	{
		bCanMakeLaser = true;
	}
}

void Player::ShootSpread()
{
	if (LookingDirectionY == 0)
	{
		CreateCross(LookingDirectionX, LookingDirectionY + sin(SpreadAmount));
		CreateCross(LookingDirectionX, LookingDirectionY);
		CreateCross(LookingDirectionX, LookingDirectionY - sin(SpreadAmount));
	}
	else
	{
		CreateCross(LookingDirectionX + sin(SpreadAmount), LookingDirectionY);
		CreateCross(LookingDirectionX, LookingDirectionY);
		CreateCross(LookingDirectionX - sin(SpreadAmount), LookingDirectionY);
	}
}

void Player::ShootOrbital()
{
	Cross* NewCross = GameObject::CreateInstance<Cross>();

	NewCross->SetParent(this);

	NewCross->SetWorldPosition(GetWorldPositionX() + (LookingDirectionX * 30.0f), GetWorldPositionY() + (-LookingDirectionY * 30.0f));

	NewCross->SetOrbital(true);

	Crosses.push_back(NewCross);
}

void Player::OnRestart()
{
	SetPosition(638.0f, 360.0f);
	SetLivesLeft(MAX_LIFE);
	//SetFearLeft(MAX_FEAR); //Need to call Max Fear to Gameflow
}

void Player::SetAvatarImage(string ImagePath)
{
    if (PlayerAvatarImageComponent)
    {
        PlayerAvatarImageComponent->LoadImage(ImagePath);
    }
}



bool Player::HandleDeath()
{

    /*if (PlayerAvatarImageComponent)
    {
        PlayerAvatarImageComponent->SetVisible(false);
    }*/

    if (HealthLeft > 0)
    {
        HealthLeft--;
        bInvulnerable = true;
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
	if (BG)
	{
		NewCross->SetParent(BG);
	}

    NewCross->SetWorldPosition(GetWorldPositionX() + (DirX * 30.0f),  GetWorldPositionY() + (-DirY * 30.0f));

	NewCross->SetInitialDirection(DirX, DirY);
    Crosses.push_back(NewCross);
}

bool Player::IsInvulnerable() const
{
    return bInvulnerable;
}

void Player::CollectCoin()
{
	NumberOfCoins++;

	if (CoinSoundComponentPickup)
	{
		CoinSoundComponentPickup->Play();
	}
}
