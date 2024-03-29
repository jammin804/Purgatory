#include "LevelManager.h"
#include "Framework/EventMessage.h"
#include "GameEventMessage.h"
#include "Framework/EventManager.h"
#include "Framework/EventMessage.h"
#include "Wall.h"
#include "Enemy.h"
#include "GameGlobals.h"



void LevelManager::OnInit()
{
	ReadLevelImage(LevelImage);

	AddEventListener(GameEventMessage::AllEnemiesDead);
}

void LevelManager::ReadLevelImage(string LevelImagePath)
{
	LevelData = GameFramework::Get().GetBitmapManager().FindOrAddBitmap(LevelImagePath);
	if (LevelData)
	{
		ALLEGRO_BITMAP* BitMapData = LevelData->ImageBitmap;
		if (BitMapData)
		{
			al_lock_bitmap(BitMapData, al_get_bitmap_format(BitMapData), ALLEGRO_LOCK_READONLY);

			SpawnPositions.clear();
			SpawnPositions.resize(LevelData->ImageHeight);
			for (int i = 0; i < SpawnPositions.size(); i++)
			{
				vector<SpawnType>& RowData = SpawnPositions[i];
				RowData.resize(LevelData->ImageWidth);

				for (int j = 0; j < RowData.size(); ++j)
				{
					ALLEGRO_COLOR Color = al_get_pixel(BitMapData, j, i);
					//RowData[j] = Color.r > 0 ? SpawnType::Empty : SpawnType::Wall;
					//Checking the color white first then check it if it has any red if so classify it as an enemy
					if (Color.r == 0.0f && Color.g == 0.0f && Color.b == 0.0f)
					{
						RowData[j] = SpawnType::Wall;
					}
					else if (Color.r >= 0.9f && Color.g <= 0.1f && Color.b <= 0.1f)
					{
 						RowData[j] = SpawnType::Enemy;
					}

				}
			}

		}
	}
}

void LevelManager::OnPostInit()
{
	PopulateWorld();
}

void LevelManager::UnloadWorld()
{
	for (auto WallIter = Walls.begin(); WallIter != Walls.end(); ++WallIter)
	{
		(*WallIter)->RequestDestroy();
	}
	Walls.clear();

	EventManager::BroadcastEvent(GameEventMessage::DespawnEnemy);
}



void LevelManager::PopulateWorld()
{
	struct WallData
	{
		int WorldPosX;
		int WorldPosY;
		int Length = 1;
		bool bIsVerticalWall = false;
	};

	vector<WallData> VerticalWalls;

	auto ExtendVerticalWall = [](vector<WallData>& VerticalWalls, int CurrentX, int CurrentY)->bool
	{
		for (WallData& VerticalWall : VerticalWalls)
		{
			if (VerticalWall.WorldPosX == CurrentX && VerticalWall.WorldPosY + VerticalWall.Length == CurrentY)
			{
				VerticalWall.Length++;
				return true;
			}
		}
		return false;
	};

	for (int i = 0; i < SpawnPositions.size(); i++)
	{
		vector<SpawnType>& RowData = SpawnPositions[i];
		bool isCurrentlyCreatingHorizontalWall = false;
		WallData HorizontalWall;

		auto CreateHorizontalWall = [this, &isCurrentlyCreatingHorizontalWall](const WallData& HorizontalWall)
		{
			CreateWall(HorizontalWall.WorldPosX, HorizontalWall.WorldPosY, HorizontalWall.Length, 1);
			isCurrentlyCreatingHorizontalWall = false;
		};

		for (int j = 0; j < RowData.size(); ++j)
		{
			SpawnType ColumnData = RowData[j];
			if (ColumnData == SpawnType::Enemy)
			{
				EventMessage Evt(GameEventMessage::SpawnEnemy);
				EventPayload EnemyPositionX;
				EventPayload EnemyPositionY;
				EnemyPositionX.SetAsInt(j);
				EnemyPositionY.SetAsInt(i);
				Evt.payload.push_back(EnemyPositionX);
				Evt.payload.push_back(EnemyPositionY);
				EventManager::BroadcastEvent(Evt);
			}
			else if (ColumnData == SpawnType::Wall)
			{
				if (isCurrentlyCreatingHorizontalWall)
				{
					HorizontalWall.Length++; // still extending the wall
				}
				else if (!ExtendVerticalWall(VerticalWalls, j, i))
				{
					//creating a new wall
					isCurrentlyCreatingHorizontalWall = true;
					HorizontalWall.Length = 1;
					HorizontalWall.WorldPosX = j;
					HorizontalWall.WorldPosY = i;
					HorizontalWall.bIsVerticalWall = false;
				}
			}
			else if (isCurrentlyCreatingHorizontalWall)
			{
				if (HorizontalWall.Length == 1)
				{
					VerticalWalls.push_back(HorizontalWall);
					isCurrentlyCreatingHorizontalWall = false;
				}
				else
				{
					CreateHorizontalWall(HorizontalWall);
				}
			}



		}
		if (isCurrentlyCreatingHorizontalWall)
		{
			if (HorizontalWall.Length == 1)
			{
				VerticalWalls.push_back(HorizontalWall);
				isCurrentlyCreatingHorizontalWall = false;
			}
			else
			{
				CreateHorizontalWall(HorizontalWall);
			}
		}
	}

	for (WallData& VerticalWall : VerticalWalls)
	{
		CreateWall(VerticalWall.WorldPosX, VerticalWall.WorldPosY, 1, VerticalWall.Length);
	}

	SetWorldPosition(-45 * GameGlobals::WorldScale, -24 * GameGlobals::WorldScale);
}

void LevelManager::SetEnabled(bool bEnabled)
{
	__super::SetEnabled(bEnabled);
	for (auto WallIter = Walls.begin(); WallIter != Walls.end(); ++WallIter)
	{
		Wall& WallToUpdate = *(*WallIter);
		WallToUpdate.SetEnabled(bEnabled);
	}
}


void LevelManager::OnEvent(const EventMessage& Msg)
{
	if (Msg == GameEventMessage::AllEnemiesDead)
	{
 		UnloadWorld();
		ReadLevelImage("Art/Level_2.png");
		PopulateWorld();
	}
}


Wall* LevelManager::CreateWall(float posX, float posY, int Width, int Height)
{
	if (Walls.size() < MaxWalls)
	{
		Wall* NewWall = GameObject::CreateInstance<Wall>();
		NewWall->SetParent(this);
		NewWall->SetEnabled(IsEnabled());
		Walls.push_back(NewWall);

		NewWall->SetWidth(Width);
		NewWall->SetHeight(Height);

		NewWall->SetStartPosX(posX);
		NewWall->SetStartPosY(posY);
		return NewWall;
	}

	return nullptr;
}

void LevelManager::OnShutdown()
{
	RemoveEventListener(GameEventMessage::AllEnemiesDead);
}