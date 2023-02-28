#pragma once

#include "Framework/GameObject.h"
#include "Player.h"

class BoxCollisionComponent;
class Player;
enum class ELevelNum : int
{
	First = 0,
	Second,
	COUNT
};

class Levels : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;

public:
	void SetLevelNum(ELevelNum num);
	ELevelNum GetLevelNum() const; // Trying to access to the enemy types in AsteroidsGame.cpp to change explosion scale


private:

	class ImageComponent* LevelImage = nullptr;

	bool bNeedsSwitch = false; // bool for switching
	ELevelNum LevelNum = ELevelNum::First;

};