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
                return true;//found it
            }
        }
        return false;
	};

	for (int i = 0; i < SpawnPositions.size(); i++)
	{
		vector<bool>& RowData = SpawnPositions[i];
		bool isCurrentlyCreatingHorizontalWall = false;
		WallData HorizontalWall;

		auto CreateHorizontalWall = [this, &isCurrentlyCreatingHorizontalWall](const WallData& HorizontalWall)
		{
            CreateWall(HorizontalWall.WorldPosX, HorizontalWall.WorldPosY, HorizontalWall.Length, 1);
            isCurrentlyCreatingHorizontalWall = false;
		};

		for (int j = 0; j < RowData.size(); ++j)
		{
			bool ColumnData = RowData[j];
			if (ColumnData == true)
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

	SetWorldPosition(-45 * 64, -24 * 64);
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
