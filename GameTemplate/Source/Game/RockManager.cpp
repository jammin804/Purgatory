#include "RockManager.h"
#include "Rock.h"
#include "Framework/Globals.h"
#include "Background.h"

void RockManager::OnInit()
{
	Rocks.reserve(NumberOfEnemiesToSpawn);
}

void RockManager::OnPostInit()
{
	
	
	for (int i = 0; i < NumberOfEnemiesToSpawn; ++i)
	{
		Rock* NewRock = CreateRock();
		SetRandomPosition(*NewRock);
	}
}

void RockManager::OnUpdate(float DeltaTime)
{
    for (auto RockIter = Rocks.begin(); RockIter != Rocks.end();)
    {
        Rock& RockToUpdate = *(*RockIter);
       
        
        if (RockToUpdate.IsDestroyed())
        {
            RockIter = Rocks.erase(RockIter);
            continue;
        }
        ++RockIter;
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
}

Rock* RockManager::CreateRock(int SplitsLeft /*= 2*/)
{
    Rock* NewRock = GameObject::CreateInstance<Rock>();
	int RockTypeRandomizer = rand() % static_cast <int> (EEnemyType::COUNT);
	NewRock->SetParent(GetParent());
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
	if (NumberOfEnemiesInASpace <= 5)
	{
		OffscreenStart = 3;
	}
	if (NumberOfEnemiesInASpace > 5 && NumberOfEnemiesInASpace <= 10)
	{
		OffscreenStart = 1;
	} 
	if (NumberOfEnemiesInASpace > 10 && NumberOfEnemiesInASpace <= 15)
	{
		OffscreenStart = 2;
	}
	else
	{
		OffscreenStart = 0;
	}
    //int OffscreenStart = rand() % 4;

    float StartPosX, StartPosY;
    float StartDirX, StartDirY;
    switch (OffscreenStart)
    {
    case 0:
    {
        StartPosX = -BG->GetBackgroundWidth()*0.5f;
        StartPosY = rand() % Globals::WindowSizeY;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = 0.6f;
        StartDirY = DirectionY * 0.25f;
    }

    break;
    case 1:
    {
        StartPosX = rand() % Globals::WindowSizeX;
        StartPosY = -BG->GetBackgroundHeight()*0.5f;
        float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
        StartDirX = DirectionX * 0.4f;
        StartDirY = 0.4f;
    }
    break;
    case 2:
    {
        StartPosX = Globals::WindowSizeX + BG->GetBackgroundWidth()*0.5f;
        StartPosY = rand() % Globals::WindowSizeY;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = -0.6f;
        StartDirY = DirectionY * 0.25f;
    }
    break;
    case 3:
    {
        StartPosX = rand() % Globals::WindowSizeX;
        StartPosY = Globals::WindowSizeY + BG->GetBackgroundHeight()*0.5f;
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
