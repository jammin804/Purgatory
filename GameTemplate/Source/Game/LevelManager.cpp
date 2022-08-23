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
	int	CurrentHeight = 1;
	bool isWallCreatingVert = false;
	float WorldPosX, WorldPosY, Scale;

	for (int i = 0; i < SpawnPositions.size(); i++)
	{
		vector<bool>& RowData = SpawnPositions[i];
		int CurrentWidth = 1;
		bool isWallCreatingHoriz = false;


		for (int j = 0; j < RowData.size(); ++j)
		{
			bool ColumnData = RowData[j];
			if (ColumnData == true)
			{

				if (!isWallCreatingHoriz)
				{
					isWallCreatingHoriz = true;
					CurrentHeight = 1;
					CurrentWidth = 1;

					WorldPosX = j;
					WorldPosY = i;
					Scale = 1;
				}
				else
				{
					CurrentWidth += 1;
					isWallCreatingVert = false;
				}

			}
			else if (isWallCreatingHoriz)
			{
				CreateWall(WorldPosX, WorldPosY, CurrentWidth, CurrentHeight);
				isWallCreatingHoriz = false;
			}
			
		}
		if (isWallCreatingHoriz)
		{
			CreateWall(WorldPosX, WorldPosY, CurrentWidth, CurrentHeight);
			isWallCreatingHoriz = false;
		}
	}
}

Wall* LevelManager::CreateWall(float posX, float posY, int Width, int Height)
{
	if (Walls.size() < MaxWalls)
	{
		Wall* NewWall = GameObject::CreateInstance<Wall>();
		NewWall->SetParent(GetParent());
		Walls.push_back(NewWall);

		//NewWall->SetWorldPosition(posX, posY);

		NewWall->SetWidth(Width);
		NewWall->SetHeight(Height);

		NewWall->SetStartPosX(posX);
		NewWall->SetStartPosY(posY);
		return NewWall;
	}

	return nullptr;
}
