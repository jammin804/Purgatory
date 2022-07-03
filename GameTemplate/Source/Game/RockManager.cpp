#include "RockManager.h"
#include "Rock.h"
#include "Framework/Globals.h"
#include "Background.h"
#include "GameEvent.h"
#include "Framework/EventManager.h"
#include "Framework/EventMessage.h"

void RockManager::OnInit()
{
	Rocks.reserve(NumberOfEnemiesToSpawn);
}

void RockManager::OnPostInit()
{
	if (Player1)
	{
		OnRestart();
	}

}

void RockManager::OnUpdate(float DeltaTime)
{
    bool bEnemyRemoved = false;
    for (auto RockIter = Rocks.begin(); RockIter != Rocks.end();)
    {
        Rock& RockToUpdate = *(*RockIter);
       
        
        if (RockToUpdate.IsDestroyed())
        {
            bEnemyRemoved = true;
            RockIter = Rocks.erase(RockIter);
            continue;
        }
        ++RockIter;
    }
    if (bEnemyRemoved)
    {
        if (Rocks.size() == 0)
        {
            EventManager::BroadcastEvent(GameEvent::AllEnemiesDead);
        }
    }
}

void RockManager::OnRestart()
{
	//Reset the Rockmanager Rock vector
	for (Rock* CurrentRock : Rocks)
	{
		CurrentRock->RequestDestroy();
	}
	Rocks.clear();

	for (int i = 0; i < NumberOfEnemiesToSpawn; ++i)
	{
		Rock* NewRock = CreateRock();
		SetRandomPosition(*NewRock);
	}
}

Rock* RockManager::CreateRock(int SplitsLeft /*= 2*/)
{
    Rock* NewRock = GameObject::CreateInstance<Rock>();
	NewRock->SetEnabled(false);
	int RockTypeRandomizer = rand() % static_cast <int> (EEnemyType::COUNT);
	NewRock->SetParent(GetParent());
	NewRock->SetPlayer(Player1);
	NewRock->SetEnemyType(static_cast <EEnemyType> (RockTypeRandomizer));
    Rocks.push_back(NewRock);
    return NewRock;
}

void RockManager::SetEnabled(bool bEnabled)
{
    __super::SetEnabled(bEnabled);
    for (auto RockIter = Rocks.begin(); RockIter != Rocks.end(); ++RockIter)
    {
        Rock& RockToUpdate = *(*RockIter);
        RockToUpdate.SetEnabled(bEnabled);
    }
}

void RockManager::SetRandomPosition(Rock& RockToPosition)
{
	const Background* BG = static_cast <const Background*> (GetParent());

	if (!BG)
	{
		return;
	}

    ESpawnStart OffscreenStart = ESpawnStart::Left;
	if (NumberOfEnemiesInASpace <= NumberOfEnemiesToSpawn/4)
	{
		OffscreenStart = ESpawnStart::Bottom;
	}
	else if (NumberOfEnemiesInASpace > NumberOfEnemiesToSpawn / 4 && NumberOfEnemiesInASpace <= NumberOfEnemiesToSpawn / 2)
	{
		OffscreenStart = ESpawnStart::Top;
	} 
	else if (NumberOfEnemiesInASpace > NumberOfEnemiesToSpawn / 2 && NumberOfEnemiesInASpace <= (NumberOfEnemiesToSpawn / 4) * 3)
	{
		OffscreenStart = ESpawnStart::Right;
	}

    float StartPosX, StartPosY;
    float StartDirX, StartDirY;

 
    
    int BGWidth = BG->GetBackgroundWidth();
    int BGHeight = BG->GetBackgroundHeight();
    int HalfBGWidth = BG->GetBackgroundWidth() / 2;
    int HalfBGHeight = BG->GetBackgroundHeight() / 2;

    switch (OffscreenStart)
    {
    case ESpawnStart::Left:
    {
        StartPosX = -(Globals::WindowSizeX) - (rand() % (HalfBGWidth-Globals::WindowSizeX));
		StartPosY = (rand() % BGHeight) - HalfBGHeight;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = 0.6f;
        StartDirY = DirectionY * 0.25f;
    }

    break;
    case ESpawnStart::Top:
    {
		StartPosX = (rand() % BGWidth)- HalfBGWidth;
        StartPosY = -(Globals::WindowSizeY) - (rand() % (HalfBGHeight-Globals::WindowSizeY));
        float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
        StartDirX = DirectionX * 0.4f;
        StartDirY = 0.4f;
    }
    break;
    case ESpawnStart::Right:
    {
        StartPosX = Globals::WindowSizeX + (rand() % (HalfBGWidth-Globals::WindowSizeX));
        StartPosY = (rand() % BGHeight) - HalfBGHeight;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = -0.6f;
        StartDirY = DirectionY * 0.25f;
    }
    break;
    case ESpawnStart::Bottom:
    {
        StartPosX = (rand() % BGWidth) - HalfBGWidth;
        StartPosY = Globals::WindowSizeY + (rand() % (HalfBGHeight-Globals::WindowSizeY));
        float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
        StartDirX = DirectionX * 0.4f;
        StartDirY = -0.4f;
    }
    break;
    }
    RockToPosition.SetMovementSpeed(150.0f);
    RockToPosition.SetPosition(StartPosX, StartPosY);
    RockToPosition.SetMovementDirection(StartDirX, StartDirY);

	NumberOfEnemiesInASpace++;
}
