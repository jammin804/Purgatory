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

void AsteroidsGame::OnInit()
{
    GFlow = GameObject::CreateInstance<GameFlow>();
    BG = GameObject::CreateInstance<Background>();
	UI = GameObject::CreateInstance<GUI>();
    Player1 = GameObject::CreateInstance<Player>();
    RockMgr = GameObject::CreateInstance<RockManager>();
}

void AsteroidsGame::OnPostInit()
{
    if (BG)
    {
        BG->SetImage("Art/Background_N.png");
        BG->SetMusic("Audio/Music.wav");
        BG->SetPosition(638.0f, 360.0f);
    }

    if (Player1)
    {
        Player1->SetAvatarImage("Art/Player_P_Back.png");
        //Player1->SetThrustersImage("Art/Thrusters.png");
        Player1->SetThrustersSound("Audio/Thruster.wav");
        Player1->SetPosition(638.0f, 360.0f);
    }

    if (GFlow)
    {
        GFlow->AddObjectToDisableAtStart(Player1);
        GFlow->AddObjectToDisableAtStart(RockMgr);
		GFlow->AddObjectToDisableAtStart(UI);
    }

	if (UI)
	{
		UI->SetLifeImage("Art/healthbar.png");
		UI->SetBorderImage("Art/healthbar_border.png");
		UI->SetPosition(30.0f, 48.0f);
		UI->SetFearImage("Art/fear.png");
		UI->SetFearBorderImage("Art/healthbar_border.png");
		UI->SetPlayer(Player1);
	}
}

void AsteroidsGame::CreateExplosion(float PositionX, float PositionY, float ExplosionScale /*= 1.0f*/)
{
    Explosion* NewExplosion = GameObject::CreateInstance<Explosion>();
    NewExplosion->SetPosition(PositionX, PositionY);
    NewExplosion->SetExplosionScale(ExplosionScale);
}

void AsteroidsGame::OnUpdate(float DeltaTime)
{   
    if (GFlow->ShouldEndGame())
    {        
        SetGameOver();
        return;
    }

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
                GFlow->AddScore(5 * (CurrentRock->GetSplitsLeft() + 1));
                CreateExplosion(CurrentRock->GetPositionX(), CurrentRock->GetPositionY(), 
                    (CurrentRock->GetSplitsLeft() + 1) * 0.33f);
                CurrentRock->RequestSplit();
                CurrentCross->RequestDestroy();
            }
        }
    }
}
