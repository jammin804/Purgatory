#include "AsteroidsGame.h"

#include "Background.h"
#include "Explosion.h"
#include "Framework/BoxCollisionComponent.h"
#include "GameFlow.h"
#include "Laser.h"
#include "Player.h"
#include "Rock.h"
#include "RockManager.h"
#include "UIText.h"
#include <sstream>

void AsteroidsGame::OnInit()
{
    {
        BG = new Background();
    }
    {
        Player1 = new Player();
    }
    RockMgr = new RockManager();
    GFlow = new GameFlow();
}

void AsteroidsGame::OnPostInit()
{
    if (BG)
    {
        BG->SetImage("Art/Background.png");
        //BG->SetMusic("Audio/Music.wav");
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
    Explosion* NewExplosion = new Explosion();
    NewExplosion->SetPosition(PositionX, PositionY);
    NewExplosion->SetExplosionScale(ExplosionScale);
    Explosions.push_back(NewExplosion);
}

void AsteroidsGame::OnUpdate(float DeltaTime)
{   
    if (GFlow->ShouldEndGame())
    {
        return;
    }

    for (auto ExplosionIter = Explosions.begin(); ExplosionIter != Explosions.end();)
    {
        Explosion* CurrentExplosion = (*ExplosionIter);
        if (CurrentExplosion->IsDestroyed())
        {
            ExplosionIter = Explosions.erase(ExplosionIter);
            delete CurrentExplosion;
            continue;
        }
        ++ExplosionIter;
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

        for (Laser* CurrentLaser : Player1->GetLasers())
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
