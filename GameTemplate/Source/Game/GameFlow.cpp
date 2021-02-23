#include "GameFlow.h"
#include "Framework/InputComponent.h"
#include "UIText.h"
#include "Player.h"
#include "GUI.h"
#include "Shop.h"

void GameFlow::OnInit()
{
    Input = GameComponent::CreateInstance<InputComponent>(this);
    GameUIText = GameObject::CreateInstance<UIText>();
	GameShop = GameObject::CreateInstance<Shop>();
}

void GameFlow::OnPostInit()
{
    if (GameUIText)
    {
		GameUIText->SetWelcomeToTheGame();
    }

	if (GameShop)
	{
		GameShop->SetEnabled(false);
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
                if (GameUIText)
                {
                    GameUIText->SetInGame();
                    GameUIText->UpdateTimeRemaining((int)TimeRemaining / 60, (int)TimeRemaining % 60);
                    GameUIText->UpdateLivesLeft(2);
                    GameUIText->UpdateScore(0);
                }
            }
        }
        break;
    case EState::InGame:
        TimeRemaining -= DeltaTime;
        if (GameUIText)
        {
            GameUIText->UpdateTimeRemaining((int)TimeRemaining / 60, (int)TimeRemaining% 60);
        }
		if (GameUI)
		{
			
			GameUI->SetFearPercentage(TimeRemaining / MAX_TIME);
		}
        if (TimeRemaining <= 0.0f)
        {
            CurrentState = EState::Shopping;
            for (GameObject* Object : GameFlowGameObjects)
            {
				if (Object)
				{
					Object->SetEnabled(false);
				}
            }
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
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_1))
			{
				if (player && player->GetNumberOfCoins() >= GameShop->GetShopItems()[0].ItemCost1)
				{
					player->UpgradeWeaponLevel();
				}
			}
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_2))
			{
			}
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_3))
			{
			}
			if (Input->IsKeyJustPressed(ALLEGRO_KEY_ENTER))
			{
				Restart(true);
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
}

void GameFlow::Restart(bool bShouldResetGame)
{
	CurrentState = EState::Starting;
	GameShop->SetEnabled(false);
	for (GameObject* Object : GameFlowGameObjects)
	{
		Object->OnRestart();
	}
	TimeRemaining = MAX_TIME;
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
		if (GameUIText)
		{
			GameUIText->SetGamePaused();
		}

	}
	else 
	{
		CurrentState = EState::InGame;
		for (GameObject* Object : GameFlowGameObjects)
		{
			Object->SetEnabled(true);
		}
		if (GameUIText)
		{
			GameUIText->SetInGame();
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
    if (GameUIText)
    {
        GameUIText->SetGameOver(CurrentScore);
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
