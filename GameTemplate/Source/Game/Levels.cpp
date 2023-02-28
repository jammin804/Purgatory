#include "Levels.h"
#include "Framework/ImageComponent.h"
#include "Game/Player.h"
#include "../GameObjectTypes.h"
#include "GameEventMessage.h"
#include "Framework/EventManager.h"
#include "Framework/EventMessage.h"


void Levels::OnInit()
{
	LevelImage = GameComponent::CreateInstance<ImageComponent>(this);
}

void Levels::OnPostInit()
{
	std::string LevelImagePath = "";

	switch (LevelNum)
	{
	case ELevelNum::First:
	default:
	{
		LevelImagePath = "Art/Level1.png";
		break;
	}

	case ELevelNum::Second:
	{
		LevelImagePath = "Art/Level2.png";
		break;
	}

	}

	if (LevelImage)
	{
		LevelImage->LoadImage(LevelImagePath);
	}
}

void Levels::SetLevelNum(ELevelNum num)
{
	LevelNum = num;
}

ELevelNum Levels::GetLevelNum() const
{
	return LevelNum;
}
