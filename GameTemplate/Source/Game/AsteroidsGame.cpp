#include "AsteroidsGame.h"

#include "Background.h"
#include "Explosion.h"
#include "Framework/BoxCollisionComponent.h"
#include "GameFlow.h"
#include "Cross.h"
#include "Player.h"
#include "Rock.h"
#include "RockManager.h"
#include "UIText.h"
#include <sstream>

void AsteroidsGame::OnInit()
{
    GFlow = GameObject::CreateInstance<GameFlow>();
    BG = GameObject::CreateInstance<Background>();
    Player1 = GameObject::CreateInstance<Player>();
    RockMgr = GameObject::CreateInstance<RockManager>();
}

void AsteroidsGame::OnPostInit()
{
    if (BG)
    {
        BG->SetImage("Art/Background.png");
        BG->SetMusic("Audio/Music.wav");
        BG->SetPosition(638.0f, 360.0f);
    }

    if (Player1)
    {
        Player1->SetAvatarImage("Art/Ship.png");
        Player1->SetThrustersImage("Art/Thrusters.png");
        Player1->SetThrustersSound("Audio/Thruster.wav");
        Player1->SetPosition(638.0f, 360.0f);
    }

    if (GFlow)
    {
        GFlow->AddObjectToDisableAtStart(Player1);
        GFlow->AddObjectToDisableAtStart(RockMgr);
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
                CreateExplosion(Player1->GetPositionX(), Player1->GetPositionY());
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

        for (Cross* CurrentLaser : Player1->GetLasers())
        {
            if (CurrentRock->GetCollision()->DoesCollide(CurrentLaser->GetCollision()))
            {
                GFlow->AddScore(5 * (CurrentRock->GetSplitsLeft() + 1));
                CreateExplosion(CurrentRock->GetPositionX(), CurrentRock->GetPositionY(), 
                    (CurrentRock->GetSplitsLeft() + 1) * 0.33f);
                CurrentRock->RequestSplit();
                CurrentLaser->RequestDestroy();
            }
        }
    }
}
