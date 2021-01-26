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
        BG->SetImage("Art/background_base.png");
        BG->SetMusic("Audio/Music.wav");
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
    }

	if (UI)
	{
		/*Player Health*/
		UI->SetLayerImage("Art/healthbar_layer.png");
		UI->SetLifeImage("Art/healthbar.png");
		UI->SetBorderImage("Art/healthbar_border.png");
		UI->SetPosition(30.0f, 48.0f);
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


	if (RockMgr)
	{
		for (Rock* CurrentRock : RockMgr->GetRocks())
		{
			if (CurrentRock->IsDestroyed())
			{
				continue;
			}

			if (!Player1->IsInvulnerable() && Player1->IsEnabled())
			{
				if (Player1->GetCollision()->DoesCollide(CurrentRock->GetCollision()))
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

					CreateExplosion(CurrentRock->GetWorldPositionX(), CurrentRock->GetWorldPositionY());
					CurrentRock->EnemyHit();
					CurrentCross->RequestDestroy();

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
					}
				}
			}
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
