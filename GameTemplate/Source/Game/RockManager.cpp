#include "RockManager.h"
#include "Rock.h"
#include "Framework/Globals.h"

void RockManager::OnInit()
{
        Rocks.reserve(100);
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

    TimeSinceSpawn += DeltaTime;
    if (TimeSinceSpawn > SpawnTimer)
    {
        SpawnTimer *= 0.979f;
        TimeSinceSpawn = 0.0f;
        Rock* NewRock = CreateRock();
        SetRandomPosition(*NewRock);
    }
}

void RockManager::OnRestart()
{
	//Reset the Rockmanager Rock vector
	Rocks.clear();
	
	//Set the Position for the rocks to start

	//Reset SpawnTimer?
}

Rock* RockManager::CreateRock(int SplitsLeft /*= 2*/)
{
    Rock* NewRock = GameObject::CreateInstance<Rock>();
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
    int OffscreenStart = rand() % 4;

    float StartPosX, StartPosY;
    float StartDirX, StartDirY;
    switch (OffscreenStart)
    {
    case 0:
    {
        StartPosX = -100.0f;
        StartPosY = rand() % Globals::WindowSizeY;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = 0.6f;
        StartDirY = DirectionY * 0.25f;
    }

    break;
    case 1:
    {
        StartPosX = rand() % Globals::WindowSizeX;
        StartPosY = -100.0f;
        float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
        StartDirX = DirectionX * 0.4f;
        StartDirY = 0.4f;
    }
    break;
    case 2:
    {
        StartPosX = Globals::WindowSizeX + 100.0f;
        StartPosY = rand() % Globals::WindowSizeY;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = -0.6f;
        StartDirY = DirectionY * 0.25f;
    }
    break;
    case 3:
    {
        StartPosX = rand() % Globals::WindowSizeX;
        StartPosY = Globals::WindowSizeY + 100.0f;
        float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
        StartDirX = DirectionX * 0.4f;
        StartDirY = -0.4f;
    }
    break;
    }
    RockToPosition.SetMovementSpeed(150.0f);
    RockToPosition.SetPosition(StartPosX, StartPosY);
    RockToPosition.SetMovementDirection(StartDirX, StartDirY);
}
