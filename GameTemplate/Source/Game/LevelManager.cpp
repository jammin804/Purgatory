#include "LevelManager.h"
#include "Framework/EventMessage.h"
#include "GameEvent.h"
#include "Framework/EventManager.h"
#include "Wall.h"



void LevelManager::OnInit()
{
	LevelData = GameFramework::Get().GetBitmapManager().FindOrAddBitmap("Art/Level.png");
	if (LevelData)
	{
		ALLEGRO_BITMAP* BitMapData = LevelData->ImageBitmap;
		if (BitMapData)
		{
			al_lock_bitmap(BitMapData, al_get_bitmap_format(BitMapData), ALLEGRO_LOCK_READONLY);
			
			SpawnPositions.resize(LevelData->ImageHeight);
			for (int i = 0; i < SpawnPositions.size(); i++)
			{
				vector<bool>& RowData = SpawnPositions[i];
				RowData.resize(LevelData->ImageWidth);

				for (int j = 0; j < RowData.size(); ++j)
				{
					ALLEGRO_COLOR Color = al_get_pixel(BitMapData, i, j);
					RowData[j] = Color.r > 0 ? false : true;
				}
			}

		}
	}
}

void LevelManager::OnPostInit()
{
	for (int i = 0; i < SpawnPositions.size(); i++)
	{
		vector<bool>& RowData = SpawnPositions[i];

		for (int j = 0; j < RowData.size(); ++j)
		{
			bool ColumnData = RowData[j];
			if (ColumnData == true)
			{
				EventMessage Evt(GameEvent::EnemyHurt);
				//EventPayload WorldPosX, WorldPosY, Scale;

				float WorldPosX, WorldPosY, Scale;

				//TODO: Build the wall. Parent it to the level manager add it to a vector in the level manager of wall pointers
				//TODO: Set world position multiple by a scale

				WorldPosX = i*15;
				WorldPosY = j*15;
				Scale = 1;

				CreateWall(WorldPosX, WorldPosY);

				/*Evt.payload.push_back(WorldPosX);
				Evt.payload.push_back(WorldPosY);
				Evt.payload.push_back(Scale);
				EventManager::BroadcastEvent(Evt);*/
			}
			
		}
	}
}

Wall* LevelManager::CreateWall(float posX, float posY)
{
	if (Walls.size() < MaxWalls)
	{
		Wall* NewWall = GameObject::CreateInstance<Wall>();
		NewWall->SetParent(GetParent());
		Walls.push_back(NewWall);
		NewWall->SetWorldPosition(posX, posY);
		return NewWall;
	}

	return nullptr;
}
