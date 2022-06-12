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
