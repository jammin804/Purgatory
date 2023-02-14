#include "GameFlow.h"
#include "Framework/EventManager.h"
#include "Framework/EventMessage.h"
#include "Framework/InputComponent.h"
#include "Game/GameEventMessage.h"
#include "Game/Player.h"
#include "Game/UserInterface/UIEndGameMessage.h"
#include "Game/UserInterface/UIHUD.h"
#include "Game/UserInterface/UIShop.h"
#include "Game/UserInterface/UIText.h"
#include "Game/UserInterface/UIWelcomeMessage.h"
#include "Game/UserInterface/UIPause.h"

const float GameFlow::COURAGE_LOSS_SPEED = 0.5f;
const float GameFlow::MAX_COURAGE = 10.0f;

void GameFlow::OnInit()
{
    Input = GameComponent::CreateInstance<InputComponent>(this);
    GameUIText = GameObject::CreateInstance<UIText>();
	WelcomeMessageText = GameObject::CreateInstance<UIWelcomeMessage>();
	GameShop = GameObject::CreateInstance<UIShop>();

	AddEventListener(GameEventMessage::EnemyDied);
	AddEventListener(GameEventMessage::PlayerDied);
	AddEventListener(GameEventMessage::PlayerTakeDamage);
	AddEventListener(GameEventMessage::AllEnemiesDead);
}

void GameFlow::OnPostInit()
{


	if (GameShop)
	{
		GameShop->SetEnabled(false);
		GameShop->SetPlayer(player);
	}


    for (GameObject* Object : GameFlowGameObjects)
    {
		if (Object)
		{
			Object->SetEnabled(false);
		}
    }
}

void GameFlow::OnUpdate(float DeltaTime)
{
    switch (CurrentState)
    {
    case EState::Starting:
        if (Input)
        {
            if (Input->IsKeyPressed(ALLEGRO_KEY_ENTER))
            {
                bReturnPressed = true;
            }
            if (bReturnPressed && Input->IsKeyReleased(ALLEGRO_KEY_ENTER))
            {
                CurrentState = EState::InGame;
                for (GameObject* Object : GameFlowGameObjects)
                {

					if (Object)
					{
						Object->SetEnabled(true);
					}

                }
				if (WelcomeMessageText)
				{
					WelcomeMessageText->RequestDestroy();
					WelcomeMessageText = nullptr;
				}

				
                if (GameUIText)
                {
                    //GameUIText->SetInGame();
                    GameUIText->UpdateLivesLeft(2);
                    GameUIText->UpdateScore(0);
                }
            }
        }
        break;
    case EState::InGame:
        CourageRemaining -= (DeltaTime * COURAGE_LOSS_SPEED);
		if (GameUI)
		{
			
			GameUI->SetFearPercentage(1.0f-(CourageRemaining / MAX_COURAGE));
		}
        if (CourageRemaining <= 0.0f )
        {
			SetShopPause(true);
           
			GameShop->UpdateCoinShopText();
			GameShop->SetEnabled(true);
        }
		if (Input)
		{
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_ESCAPE))
			{
				SetPaused(true);
			}
		}
        break;
	case EState::Pause:
		if (Input)
		{
			
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_ESCAPE))
			{
				SetPaused(false);
			}
		}
		break;
	case EState::Shopping:
		if (Input)
		{
			UpdateShop();
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_ENTER))
			{
				SetShopPause(false);
				CourageRemaining = MAX_COURAGE;
			}
		}
		break;
    case EState::Ending:
        if (Input)
		{
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_ENTER))
			{
				Restart(true);
			}
        }
        break;
    }
}

void GameFlow::OnShutdown()
{
	RemoveEventListener(GameEventMessage::EnemyDied);
	RemoveEventListener(GameEventMessage::PlayerDied);
	RemoveEventListener(GameEventMessage::PlayerTakeDamage);
	RemoveEventListener(GameEventMessage::AllEnemiesDead);
}

void GameFlow::Restart(bool bShouldResetGame)
{
	CurrentState = EState::Starting;
	GameShop->SetEnabled(false);
	for (GameObject* Object : GameFlowGameObjects)
	{
		Object->OnRestart();
		
	}
	if (EndGameMessageText)
	{
		EndGameMessageText->RequestDestroy();
		EndGameMessageText = nullptr;
	}

	CourageRemaining = MAX_COURAGE;
}

void GameFlow::OnEvent(const EventMessage& Msg)
{
	if (Msg == GameEventMessage::EnemyDied)
	{
		AddTime();
	}
	else if(Msg == GameEventMessage::PlayerTakeDamage)
	{
		if (Msg.payload.size() < 1)
		{
			return;
		}

		UpdateLivesLeft(Msg.payload[0].GetAsInt());
	}
	else if (Msg == GameEventMessage::PlayerDied)
	{
		SetPlayerIsDead();
	}
	else if (Msg == GameEventMessage::AllEnemiesDead)
	{
		SetAllDead();
	}
}

void GameFlow::SetPaused(bool bIsPaused)
{
	if (bIsPaused)
	{
		CurrentState = EState::Pause;
		for (GameObject* Object : GameFlowGameObjects)
		{
			Object->SetEnabled(false);
		}
		

		if (PauseText == nullptr)
		{
			PauseText = GameObject::CreateInstance<UIPause>();
		}

	}
	else 
	{
		CurrentState = EState::InGame;
		for (GameObject* Object : GameFlowGameObjects)
		{
			Object->SetEnabled(true);
		}

		if (PauseText)
		{
			PauseText->RequestDestroy();
			PauseText = nullptr;
		}
	}

}

void GameFlow::SetShopPause(bool bIsInShop)
{
	if (GameShop == nullptr)
	{
		return;
	}

	GameShop->SetEnabled(bIsInShop);

	if (bIsInShop)
	{
		CurrentState = EState::Shopping;
		for (GameObject* Object : GameFlowGameObjects)
		{
			Object->SetEnabled(false);
		}
		GameShop->UpdateCoinShopText();

	}
	else
	{
		CurrentState = EState::InGame;
		for (GameObject* Object : GameFlowGameObjects)
		{
			Object->SetEnabled(true);
		}


	}
}

void GameFlow::UpdateShop()
{
	if (GameShop == nullptr)
	{
		return;
	}

	if (Input->IsKeyJustPressed(ALLEGRO_KEY_1))
	{
		const ShopItem& WeaponUpgrade = GameShop->GetShopItems()[0];
		if (WeaponUpgrade.NumberBought <= 2)
		{
			int UpgradeCost = WeaponUpgrade.NumberBought == 0 ? WeaponUpgrade.ItemCost1 : WeaponUpgrade.ItemCost2;
			if (player && player->GetNumberOfCoins() >= UpgradeCost)
			{
				player->SpendCoins(UpgradeCost);
				GameShop->UpdateCoinShopText();
				player->UpgradeWeaponLevel();
				GameShop->UpgradeWeaponLevel(WeaponUpgrade);
			}
		}

	}
	if (Input->IsKeyJustPressed(ALLEGRO_KEY_2))
	{
		const ShopItem& SpeedUpgrade = GameShop->GetShopItems()[1];
		if (SpeedUpgrade.NumberBought <= 2)
		{
			int UpgradeCost = SpeedUpgrade.NumberBought == 0 ? SpeedUpgrade.ItemCost1 : SpeedUpgrade.ItemCost2;
			if (player && player->GetNumberOfCoins() >= UpgradeCost)
			{
				player->SpendCoins(UpgradeCost);
				GameShop->UpdateCoinShopText();
				player->UpgradeSpeedLevel();
				GameShop->UpgradeSpeedLevel(SpeedUpgrade); // This will switch out the image, description and cost. Also, increase Numberbrought
			}
		}
	}
	if (Input->IsKeyJustPressed(ALLEGRO_KEY_3))
	{
		const ShopItem& HealthUpgrade = GameShop->GetShopItems()[2];
		if (HealthUpgrade.NumberBought <= 2)
		{
			int UpgradeCost = HealthUpgrade.NumberBought == 0 ? HealthUpgrade.ItemCost1 : HealthUpgrade.ItemCost2;
			if (player && player->GetNumberOfCoins() >= UpgradeCost)
			{
				player->SpendCoins(UpgradeCost);
				GameShop->UpdateCoinShopText();
				player->UpgradeHealthLevel();
				GameShop->UpgradeHealthLevel(HealthUpgrade); // This will switch out the image, description and cost. Also, increase Numberbrought
			}
		}
	}
}

void GameFlow::SetPlayerIsDead()
{
    CurrentState = EState::Ending;
    for (GameObject* Object : GameFlowGameObjects)
    {
        Object->SetEnabled(false);
    }

	if (EndGameMessageText == nullptr)
	{
		EndGameMessageText = GameObject::CreateInstance<UIEndGameMessage>();
	}
	

}

void GameFlow::UpdateLivesLeft(int NewLivesLeft)
{
    if (GameUIText)
    {
        GameUIText->UpdateLivesLeft(NewLivesLeft);
    }
}

void GameFlow::AddScore(int ScoreToAdd)
{
    CurrentScore += ScoreToAdd;
    if (GameUIText)
    {
        GameUIText->UpdateScore(CurrentScore);
    }
}

void GameFlow::AddObjectToDisableAtStart(GameObject* ObjectToDisable)
{
    GameFlowGameObjects.push_back(ObjectToDisable);
}

void GameFlow::SetAllDead()
{
	CourageRemaining = 0;
}

void GameFlow::AddTime()
{
	CourageRemaining = min(CourageRemaining + 5.0f, MAX_COURAGE);
}


