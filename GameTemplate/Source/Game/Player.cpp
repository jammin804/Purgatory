#include "Player.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/SoundComponent.h"
#include "Framework/BoxCollisionComponent.h"
#include "Cross.h"
#include "Background.h"
#include "GameEvent.h"
#include "Framework/EventManager.h"
#include "Enemy.h"
#include "../GameObjectTypes.h"
#include "Framework/EventMessage.h"
#include <iostream>

const float Player::BASE_MOVEMENT_SPEED = 400.0f;

void Player::OnInit()
{
	SetType(GOT_Player);
    PlayerAvatarThrustersImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
    PlayerAvatarThrustersImageComponent->SetVisible(false);
    PlayerAvatarImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
    InputComp = GameComponent::CreateInstance<InputComponent>(this);
	CoinSoundComponentPickup = GameComponent::CreateInstance<SoundComponent>(this);
    Collision = GameComponent::CreateInstance<BoxCollisionComponent>(this);
	AddEventListener(GameEvent::CrossDestroyed);

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

	UpdateRespawn(DeltaTime);

	UpdateMovement(DeltaTime);

	UpdateWeapon();

	UpdateSprite();

}

void Player::UpdateWeapon()
{
	if (!bInvulnerable && InputComp->IsKeyPressed(ALLEGRO_KEY_SPACE))
	{
		if (bCanMakeLaser)
		{


			if (WeaponLevel == 0)
			{
				ShootBase();
			}
			else if (WeaponLevel == 1)
			{
				ShootSpread();
			}
			else
			{
				ShootOrbital();
			}


			bCanMakeLaser = false;


		}
	}

	if (InputComp->IsKeyReleased(ALLEGRO_KEY_SPACE))
	{
		bCanMakeLaser = true;
	}
}

void Player::UpdateSprite()
{
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
}

void Player::UpdateMovement(float DeltaTime)
{

	float DirectionX = 0.0f;
	float DirectionY = 0.0f;


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

	if (BG)
	{
		PreviousPosX = BG->GetPositionX();
		PreviousPosY = BG->GetPositionY();

		float NewPosX = PreviousPosX - DirectionX;
		float NewPosY = PreviousPosY - DirectionY;

		BG->SetPosition(NewPosX, NewPosY);
	}
}

void Player::UpdateRespawn(float DeltaTime)
{
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
}

void Player::OnShutdown()
{
	RemoveEventListener(GameEvent::CrossDestroyed);
}

void Player::OnCollision(GameObject* Other)
{

	if (!IsInvulnerable() && IsEnabled())
	{
		if (Other->GetType() == static_cast<int>(GOT_Enemy))
		{
			const Enemy* enemy = static_cast<const Enemy*>(Other);
			if (enemy->GetState() != EState::Flee)
			{
				//CreateExplosion(Player1->GetPositionX(), Player1->GetPositionY());
				if (HandleDeath())
				{
					EventManager::BroadcastEvent(GameEvent::PlayerDied);
				}
				else
				{
					EventMessage Evt(GameEvent::PlayerTakeDamage);
					EventPayload HPLeft;
					HPLeft.SetAsInt(HealthLeft);
					Evt.payload.push_back(HPLeft);
					EventManager::BroadcastEvent(Evt);
				}
			}
		}
		else if (Other->GetType() == static_cast<int>(GOT_Coin))
		{
			CollectCoin();
		}
	}

}

void Player::OnEvent(const EventMessage& Msg)
{
	if (Msg == GameEvent::CrossDestroyed)
	{
		for (auto Iter = Crosses.begin(); Iter != Crosses.end();)
		{
			if ((*Iter)->IsDestroyed())
			{
				Iter = Crosses.erase(Iter);
			}
			else
			{
				++Iter;
			}

		}
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

	//Checks if health was upgraded
	if (HealthLevel == 0)
	{
		MaxLife = BASE_LIFE;
	}
	else if (HealthLevel == 1)
	{
		MaxLife = BASE_LIFE + 5;
	}
	else
	{
		MaxLife = BASE_LIFE + 10;
	}

	SetLivesLeft(MaxLife);
	
	BG->SetPosition(0.0f, 0.0f);


	if (SpeedLevel == 0)
	{
		PlayerVerticalMovementSpeed = BASE_MOVEMENT_SPEED;
		PlayerHorizontalMovementSpeed = BASE_MOVEMENT_SPEED;
	}
	else if (SpeedLevel == 1)
	{
		PlayerVerticalMovementSpeed = BASE_MOVEMENT_SPEED * 1.5f;
		PlayerHorizontalMovementSpeed = BASE_MOVEMENT_SPEED * 1.5f;
	}
	else
	{
		PlayerVerticalMovementSpeed = BASE_MOVEMENT_SPEED * 2.0f;
		PlayerHorizontalMovementSpeed = BASE_MOVEMENT_SPEED * 2.0f;
	}


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

void Player::RewindPosition()
{
	if (BG)
	{
		BG->SetPosition(PreviousPosX, PreviousPosY);
	}
}
