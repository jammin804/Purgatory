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
	float PosX = BG->GetPositionX();
	float PosY = BG->GetPositionY();

	//Add a while loop to check to see if the player + 32 px is near the edge of the world.		
	if (InputComp->IsKeyPressed(ALLEGRO_KEY_UP) || InputComp->IsKeyPressed(ALLEGRO_KEY_W))
	{
		DirectionY -= PlayerVerticalMovementSpeed * DeltaTime;
		LookingDirectionY = 1;
		LookingDirectionX = 0;
	}

	if (InputComp->IsKeyPressed(ALLEGRO_KEY_DOWN) || InputComp->IsKeyPressed(ALLEGRO_KEY_S))
	{
		DirectionY += PlayerVerticalMovementSpeed * DeltaTime;
		LookingDirectionY = -1;
		LookingDirectionX = 0;
	}

	if (InputComp->IsKeyPressed(ALLEGRO_KEY_LEFT) || InputComp->IsKeyPressed(ALLEGRO_KEY_A))
	{
		DirectionX -= PlayerHorizontalMovementSpeed * DeltaTime;
		LookingDirectionX = -1;
		LookingDirectionY = 0;
	}

	if (InputComp->IsKeyPressed(ALLEGRO_KEY_RIGHT) || InputComp->IsKeyPressed(ALLEGRO_KEY_D))
	{
		DirectionX += PlayerHorizontalMovementSpeed * DeltaTime;
		LookingDirectionX = 1;
		LookingDirectionY = 0;
	}
	float DesiredPostionX = PosX - DirectionX;
	float DesiredPostionY = PosY - DirectionY;

	if (DesiredPostionY > BG->GetBackgroundHeight()*0.5f ||
		DesiredPostionY < -BG->GetBackgroundHeight()*0.5f)
	{
		DesiredPostionY = PosY;
	}
	if (DesiredPostionX > BG->GetBackgroundWidth()*0.5f ||
		DesiredPostionX < -BG->GetBackgroundWidth()*0.5f)
	{
		DesiredPostionX = PosX;
	}



    

	/*Is just key pressed for looking direction - code below*/
	
	if (BG)
	{
		BG->SetPosition(DesiredPostionX, DesiredPostionY);
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
			//ShootSpread();
			//ShootOrbital();
			ShootBase();

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

void Player::ShootBase()
{
	CreateCross(LookingDirectionX, LookingDirectionY);
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
