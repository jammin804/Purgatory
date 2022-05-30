#include "AsteroidsGame.h"

#include "Game/Background.h"
#include "Game/Explosion.h"
#include "Framework/BoxCollisionComponent.h"
#include "Game/GameFlow.h"
#include "Game/GUI.h" 
#include "Game/Cross.h"
#include "Game/Player.h"
#include "Game/Rock.h"
#include "Game/RockManager.h"
#include "Game/UIText.h"
#include <sstream>
#include "Game/Coin.h"
#include "Game/CoinManager.h"
#include "Game/Sfx.h"

void AsteroidsGame::OnInit()
{
    GFlow = GameObject::CreateInstance<GameFlow>();
    BG = GameObject::CreateInstance<Background>();
	UI = GameObject::CreateInstance<GUI>();
    Player1 = GameObject::CreateInstance<Player>();
    RockMgr = GameObject::CreateInstance<RockManager>();
	CoinMgr = GameObject::CreateInstance<CoinManager>();
}

void AsteroidsGame::OnPostInit()
{
    if (BG)
    {
        BG->SetImage("Art/background_with_tiles.png");
        BG->SetMusic("Audio/Horror.mp3");
		//BG->SetWallVImage("Art/backgroundWall_V.png");
    }

    if (Player1)
    {
        Player1->SetAvatarImage("Art/Player_P_Back.png");
        Player1->SetPosition(638.0f, 360.0f);
		Player1->SetRenderDepth(10);
		if (BG) 
		{
			Player1->SetBackground(BG);
		}
    }

    if (GFlow)
    {
        GFlow->AddObjectToDisableAtStart(Player1);
        GFlow->AddObjectToDisableAtStart(RockMgr);
		GFlow->AddObjectToDisableAtStart(UI);
		GFlow->SetRenderDepth(50);
		GFlow->SetGUI(UI);
		if (Player1)
		{
			GFlow->SetPlayer(Player1);
		}

		
		/*if (GFlow->GameState() != GameFlow::EState::InGame)
		{
			return;
		}*/ //GameFlow::EState::InGame throwing error
    }

	if (UI)
	{
		/*Player Health*/
		UI->SetLayerImage("Art/healthbar_layer.png");
		UI->SetLifeImage("Art/healthbar.png");
		UI->SetBorderImage("Art/healthbar_border.png");

		UI->SetPosition(50.0f, 48.0f);
		/*Player Fear*/
		UI->SetFearLayerImage("Art/healthbar_layer.png");
		UI->SetFearImage("Art/fear.png");
		UI->SetFearBorderImage("Art/healthbar_border.png");
		UI->SetCoinImage("Art/Coins.png");
		UI->SetPlayer(Player1);
		UI->SetRenderDepth(100);
	}

	if (RockMgr)
	{
		if (BG)
		{
			RockMgr->SetParent(BG);
		}
		if (Player1)
		{
			RockMgr->SetPlayer(Player1);
		}
	}

	if (CoinMgr)
	{
		if (BG)
		{
			CoinMgr->SetParent(BG);
		}
	}
}

void AsteroidsGame::CreateExplosion(float PositionX, float PositionY, float ExplosionScale /*= 1.0f*/)
{
    Explosion* NewExplosion = GameObject::CreateInstance<Explosion>();
	if (BG)
	{
		NewExplosion->SetParent(BG);
	}
    NewExplosion->SetWorldPosition(PositionX, PositionY);
    NewExplosion->SetExplosionScale(ExplosionScale);
}

void AsteroidsGame::OnUpdate(float DeltaTime)
{   
    /*if (GFlow->ShouldEndGame()) Replacing with the reset functionality 
    {        
        SetGameOver();
        return;
    }*/

	if (GFlow->GameState() != GameFlow::EState::InGame) //Scoping issue
	{
		return;
	}

	if (RockMgr)
	{
		int NumberOfExistingEnemies = 0;
		for (Rock* CurrentRock : RockMgr->GetRocks())
		{
			if (CurrentRock->IsDestroyed())
			{
				continue;
			}
			NumberOfExistingEnemies++;

			/*for (const Rock* OtherRock : RockMgr->GetRocks())
			{
				if (CurrentRock->IsDestroyed() || CurrentRock == OtherRock)
				{
					continue;
				}
				
				

				if (CurrentRock->GetCollision()->DoesCollide(OtherRock->GetCollision()))
				{
					float DirectionFromEnemyToEnemyX = CurrentRock->GetWorldPositionX() - OtherRock->GetWorldPositionX();
					float DirectionFromEnemyToEnemyY = CurrentRock->GetWorldPositionY() - OtherRock->GetWorldPositionY();
					float DirectionFromEnemyToEnemySize = sqrt(pow(DirectionFromEnemyToEnemyX, 2) + pow(DirectionFromEnemyToEnemyY, 2));

					if (DirectionFromEnemyToEnemySize != 0.0f)
					{
						DirectionFromEnemyToEnemyX /= DirectionFromEnemyToEnemySize;
						DirectionFromEnemyToEnemyY /= DirectionFromEnemyToEnemySize;

						CurrentRock->SetPosition(CurrentRock->GetPositionX() + (DirectionFromEnemyToEnemyX * 2.0f), CurrentRock->GetPositionY() + (DirectionFromEnemyToEnemyY * 2.0f));
					}

				}
			}*/

			if (!Player1->IsInvulnerable() && Player1->IsEnabled())
			{
				if ((Player1->GetCollision()->DoesCollide(CurrentRock->GetCollision())) && (CurrentRock->GetState() != EState::Flee))
				{
					//CreateExplosion(Player1->GetPositionX(), Player1->GetPositionY());
					if (Player1->HandleDeath())
					{
						GFlow->SetPlayerIsDead();
					}
					else
					{
						GFlow->UpdateLivesLeft(Player1->GetLivesLeft());
					}
				}
			}

			for (Cross* CurrentCross : Player1->GetCross())
			{
				if (CurrentRock->GetCollision()->DoesCollide(CurrentCross->GetCollision()))
				{
					float ExplosionScale = 1.0f;
					if (CurrentRock->GetEnemyType() == EEnemyType::Demon)
					{
						ExplosionScale = 1.8f;
					}
					else if(CurrentRock->GetEnemyType() == EEnemyType::Bat)
					{
						ExplosionScale = 0.5f;
					}
					else 
					{
						ExplosionScale = 2.2f;
					}

					CreateExplosion(CurrentRock->GetWorldPositionX(), CurrentRock->GetWorldPositionY(), ExplosionScale);
					//CurrentRock->TakeDamage();
					

					if (CurrentRock->GetEnemyLivesLeft() < 0.0f)
					{
						if (CoinMgr)
						{
							int NumberOfCoinsToSpawn = rand() % 4;
							for (int i = 0; i < NumberOfCoinsToSpawn; i++)
							{
								CoinMgr->CreateCoin(CurrentRock->GetWorldPositionX(), CurrentRock->GetWorldPositionY());
							}
						}
						if (GFlow)
						{
							GFlow->AddTime();
						}
					}
				}
			}
		}
		if (NumberOfExistingEnemies == 0)
		{
			GFlow->SetAllDead();
		}
	}

	
	if (CoinMgr)
	{
		for (Coin* CurrentCoin : CoinMgr->GetCoins()) 
		{

			if (!Player1->IsInvulnerable() && Player1->IsEnabled())
			{
				if (Player1->GetCollision()->DoesCollide(CurrentCoin->GetCollision()) && !CurrentCoin->IsDestroyed())
				{
					CurrentCoin->CoinCollision();
					Player1->CollectCoin();
				}
			}

		}

	}
}
