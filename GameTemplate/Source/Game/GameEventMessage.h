#pragma once
#include "Framework/EString.h"
namespace GameEventMessage
{
	enum IDs
	{
		INVALID = -1,
		EnemyDied,
		EnemyHurt,
		AllEnemiesDead,
		CrossDestroyed,
		PlayerDied,
		PlayerTakeDamage,
		SpawnEnemy
	};

}
