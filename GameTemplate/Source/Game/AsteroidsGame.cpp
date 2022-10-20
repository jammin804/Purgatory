#include "AsteroidsGame.h"

#include "Game/Background.h"
#include "Framework/BoxCollisionComponent.h"
#include "Game/GameFlow.h"
#include "Game/UserInterface/UIHUD.h" 
#include "Game/Cross.h"
#include "Game/Player.h"
#include "Game/EnemyManager.h"
#include "Game/UserInterface/UIText.h"
#include <sstream>
#include "Game/CoinManager.h"
#include "Game/ExplosionManager.h"
#include "Game/Sfx.h"
#include "Game/LevelManager.h"

void AsteroidsGame::OnInit()
{

    GFlow = GameObject::CreateInstance<GameFlow>();
    BG = GameObject::CreateInstance<Background>();
	Player1 = GameObject::CreateInstance<Player>();
	LevelMgr = GameObject::CreateInstance<LevelManager>();
    EnemyMgr = GameObject::CreateInstance<EnemyManager>();
	CoinMgr = GameObject::CreateInstance<CoinManager>();
	ExplodeMgr = GameObject::CreateInstance<ExplosionManager>();
	UI = GameObject::CreateInstance<UIHUD>();
}

void AsteroidsGame::OnPostInit()
{
    if (BG)
    {
        BG->SetImage("Art/background_with_tiles.png");
        BG->SetMusic("Audio/Horror.mp3");
		
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
        GFlow->AddObjectToDisableAtStart(EnemyMgr);
		GFlow->AddObjectToDisableAtStart(UI);
		GFlow->SetRenderDepth(50);
		GFlow->SetGUI(UI);
		if (Player1)
		{
			GFlow->SetPlayer(Player1);
		}

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

	if (EnemyMgr)
	{
		if (BG)
		{
			EnemyMgr->SetParent(BG);
		}
		if (Player1)
		{
			EnemyMgr->SetPlayer(Player1);
		}
	}

	if (CoinMgr)
	{
		if (BG)
		{
			CoinMgr->SetParent(BG);
		}
	}

	if (ExplodeMgr)
	{
		if (BG)
		{
			ExplodeMgr->SetParent(BG);
		}
	}

	if (LevelMgr)
	{
		if (BG)
		{
			LevelMgr->SetParent(BG);
		}
	}
}