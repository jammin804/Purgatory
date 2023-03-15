#include "EnemyManager.h"
#include "Enemy.h"
#include "Framework/Globals.h"
#include "Background.h"
#include "GameEventMessage.h"
#include "Framework/EventManager.h"
#include "Framework/EventMessage.h"
#include "Game/GameGlobals.h"

void EnemyManager::OnInit()
{
	Enemies.reserve(NumberOfEnemiesToSpawn);
	AddEventListener(GameEventMessage::SpawnEnemy);
	AddEventListener(GameEventMessage::DespawnEnemy);
}

void EnemyManager::OnPostInit()
{
	
	SetWorldPosition(-45 * GameGlobals::WorldScale, -24 * GameGlobals::WorldScale);
}

void EnemyManager::OnUpdate(float DeltaTime)
{
    bool bEnemyRemoved = false;
    for (auto EnemyIter = Enemies.begin(); EnemyIter != Enemies.end();)
    {
        Enemy& EnemyToUpdate = *(*EnemyIter);
       
        
        if (EnemyToUpdate.IsDestroyed())
        {
            bEnemyRemoved = true;
            EnemyIter = Enemies.erase(EnemyIter);
            continue;
        }
        ++EnemyIter;
    }
    if (bEnemyRemoved)
    {
        if (Enemies.size() == 0)
        {
             EventManager::BroadcastEvent(GameEventMessage::AllEnemiesDead);
        }
    }
}

void EnemyManager::OnRestart()
{
	ClearEnemy();

}

void EnemyManager::OnEvent(const EventMessage& Msg)
{
	if (Msg == GameEventMessage::SpawnEnemy)
	{
		Enemy* NewEnemy = CreateEnemy();
		NewEnemy->SetPosition(Msg.payload[0].GetAsFloat() * GameGlobals::WorldScale, Msg.payload[1].GetAsFloat() * GameGlobals::WorldScale);
	}
	
	if (Msg == GameEventMessage::DespawnEnemy)
	{
		ClearEnemy();
	}
}

Enemy* EnemyManager::CreateEnemy()
{
    Enemy* NewEnemy = GameObject::CreateInstance<Enemy>();
	NewEnemy->SetEnabled(false);
	int EnemyTypeRandomizer = rand() % static_cast <int> (EEnemyType::COUNT);
	NewEnemy->SetParent(this);
	NewEnemy->SetPlayer(Player1);
	NewEnemy->SetEnemyType(static_cast <EEnemyType> (EnemyTypeRandomizer));
    Enemies.push_back(NewEnemy);
    return NewEnemy;
}

void EnemyManager::ClearEnemy()
{
	for (Enemy* CurrentEnemy : Enemies)
	{
		CurrentEnemy->RequestDestroy();
	}
	Enemies.clear();

}

void EnemyManager::SetEnabled(bool bEnabled)
{
    __super::SetEnabled(bEnabled);
    for (auto EnemyIter = Enemies.begin(); EnemyIter != Enemies.end(); ++EnemyIter)
    {
        Enemy& EnemyToUpdate = *(*EnemyIter);
        EnemyToUpdate.SetEnabled(bEnabled);
    }
}

void EnemyManager::SetRandomPosition(Enemy& EnemyToPosition) //Should this be removed since we have control of enemy spawn?
{
	const Background* BG = static_cast <const Background*> (GetParent());

	if (!BG)
	{
		return;
	}

    ESpawnStart OffscreenStart = ESpawnStart::LeftCenter;
	if (NumberOfEnemiesInASpace <= NumberOfEnemiesToSpawn/8)
	{
		OffscreenStart = ESpawnStart::TopLeft;
	}
	else if (NumberOfEnemiesInASpace > NumberOfEnemiesToSpawn / 8 && NumberOfEnemiesInASpace <= NumberOfEnemiesToSpawn / 4)
	{
		OffscreenStart = ESpawnStart::TopCenter;
	} 
	else if (NumberOfEnemiesInASpace > NumberOfEnemiesToSpawn / 4 && NumberOfEnemiesInASpace <= (NumberOfEnemiesToSpawn / 6) * 2)
	{
		OffscreenStart = ESpawnStart::TopRight;
	}
	else if (NumberOfEnemiesInASpace > ((NumberOfEnemiesToSpawn / 6) * 2) && NumberOfEnemiesInASpace <= NumberOfEnemiesToSpawn / 2)
	{
		OffscreenStart = ESpawnStart::RightCenter;
	}
	else if (NumberOfEnemiesInASpace > NumberOfEnemiesToSpawn / 2 && NumberOfEnemiesInASpace <= (NumberOfEnemiesToSpawn / 3) * 2)
	{
		OffscreenStart = ESpawnStart::BottomRight;
	}
	else if (NumberOfEnemiesInASpace > ((NumberOfEnemiesToSpawn / 3) * 2) && NumberOfEnemiesInASpace <= (NumberOfEnemiesToSpawn / 4) * 3)
	{
		OffscreenStart = ESpawnStart::BottomCenter;
	}
	else if (NumberOfEnemiesInASpace > (NumberOfEnemiesToSpawn / 4) * 3 && NumberOfEnemiesInASpace <= (NumberOfEnemiesToSpawn / 7) * 6)
	{
		OffscreenStart = ESpawnStart::BottomLeft;
	}

    float StartPosX, StartPosY;
    float StartDirX, StartDirY;

 
    
    int BGWidth = BG->GetBackgroundWidth();
    int BGHeight = BG->GetBackgroundHeight();
    int HalfBGWidth = BG->GetBackgroundWidth() / 2;
    int HalfBGHeight = BG->GetBackgroundHeight() / 2;

    switch (OffscreenStart)
    {
    case ESpawnStart::LeftCenter:
    {
        StartPosX = -(Globals::WindowSizeX) - (rand() % (HalfBGWidth-Globals::WindowSizeX));
		StartPosY = (rand() % BGHeight) - HalfBGHeight;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = 0.6f;
        StartDirY = DirectionY * 0.25f;
    }

    break;
    case ESpawnStart::TopLeft:
	{
		StartPosX = -(Globals::WindowSizeX)-(rand() % (HalfBGWidth - Globals::WindowSizeX));
		StartPosY = (rand() % BGHeight) - HalfBGHeight;
		float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
		StartDirX = 0.6f;
		StartDirY = DirectionY * 0.25f;
	}

	break;
    case ESpawnStart::TopCenter:
    {
		StartPosX = (rand() % BGWidth)- HalfBGWidth;
        StartPosY = -(Globals::WindowSizeY) - (rand() % (HalfBGHeight-Globals::WindowSizeY));
        float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
        StartDirX = DirectionX * 0.4f;
        StartDirY = 0.4f;
    }
    break;
	case ESpawnStart::TopRight:
	{
		StartPosX = (rand() % BGWidth) - HalfBGWidth;
		StartPosY = -(Globals::WindowSizeY)-(rand() % (HalfBGHeight - Globals::WindowSizeY));
		float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
		StartDirX = DirectionX * 0.4f;
		StartDirY = 0.4f;
	}
	break;
    case ESpawnStart::RightCenter:
    {
        StartPosX = Globals::WindowSizeX + (rand() % (HalfBGWidth-Globals::WindowSizeX));
        StartPosY = (rand() % BGHeight) - HalfBGHeight;
        float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
        StartDirX = -0.6f;
        StartDirY = DirectionY * 0.25f;
    }
    break;
	case ESpawnStart::BottomRight:
	{
		StartPosX = Globals::WindowSizeX + (rand() % (HalfBGWidth - Globals::WindowSizeX));
		StartPosY = (rand() % BGHeight) - HalfBGHeight;
		float DirectionY = 1.0f - (StartPosY / (Globals::WindowSizeY * 0.5f));
		StartDirX = -0.6f;
		StartDirY = DirectionY * 0.25f;
	}
	break;
    case ESpawnStart::BottomCenter:
    {
        StartPosX = (rand() % BGWidth) - HalfBGWidth;
        StartPosY = Globals::WindowSizeY + (rand() % (HalfBGHeight-Globals::WindowSizeY));
        float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
        StartDirX = DirectionX * 0.4f;
        StartDirY = -0.4f;
    }
    break;
	case ESpawnStart::BottomLeft:
	{
		StartPosX = (rand() % BGWidth) - HalfBGWidth;
		StartPosY = Globals::WindowSizeY + (rand() % (HalfBGHeight - Globals::WindowSizeY));
		float DirectionX = 1.0f - (StartPosX / (Globals::WindowSizeX * 0.5f));
		StartDirX = DirectionX * 0.4f;
		StartDirY = -0.4f;
	}
	break;
    }
    EnemyToPosition.SetMovementSpeed(150.0f);
    EnemyToPosition.SetPosition(StartPosX, StartPosY);
    EnemyToPosition.SetMovementDirection(StartDirX, StartDirY);

	NumberOfEnemiesInASpace++;
}

void EnemyManager::OnShutdown()
{
	RemoveEventListener(GameEventMessage::SpawnEnemy);
	RemoveEventListener(GameEventMessage::DespawnEnemy);
}
