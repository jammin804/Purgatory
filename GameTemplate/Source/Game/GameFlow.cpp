#include "GameFlow.h"
#include "Framework/InputComponent.h"
#include "UIText.h"

void GameFlow::OnInit()
{
    Input = GameComponent::CreateInstance<InputComponent>(this);
    GameUI = GameObject::CreateInstance<UIText>();
}

void GameFlow::OnPostInit()
{
    if (GameUI)
    {
        GameUI->SetWelcomeToTheGame();
    }

    for (GameObject* Object : ObjectsToDisableOutsideGame)
    {
        Object->SetEnabled(false);
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
                for (GameObject* Object : ObjectsToDisableOutsideGame)
                {
                    Object->SetEnabled(true);
                }
                if (GameUI)
                {
                    GameUI->SetInGame();
                    GameUI->UpdateTimeRemaining((int)TimeRemaining / 60, (int)TimeRemaining % 60);
                    GameUI->UpdateLivesLeft(2);
                    GameUI->UpdateScore(0);
                }
            }
        }
        break;
    case EState::InGame:
        TimeRemaining -= DeltaTime;
        if (GameUI)
        {
            GameUI->UpdateTimeRemaining((int)TimeRemaining / 60, (int)TimeRemaining% 60);
        }
        if (TimeRemaining <= 0.0f)
        {
            CurrentState = EState::Ending;
            for (GameObject* Object : ObjectsToDisableOutsideGame)
            {
                Object->SetEnabled(false);
            }
            if (GameUI)
            {
                GameUI->SetYouSurvived(CurrentScore);
            }
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

    case EState::Ending:
        if (Input)
        {
            if (Input->IsKeyPressed(ALLEGRO_KEY_ENTER))
            {
                bReturnPressed = true;
            }
            if (bReturnPressed && Input->IsKeyReleased(ALLEGRO_KEY_ENTER))
            {
                bShouldEndGame = true;
            }
        }
        break;
    }
}

void GameFlow::OnShutdown()
{
}

void GameFlow::SetPaused(bool bIsPaused)
{
	if (bIsPaused)
	{
		CurrentState = EState::Pause;
		for (GameObject* Object : ObjectsToDisableOutsideGame)
		{
			Object->SetEnabled(false);
		}

	}
	else 
	{
		CurrentState = EState::InGame;
		for (GameObject* Object : ObjectsToDisableOutsideGame)
		{
			Object->SetEnabled(true);
		}

	}

}

void GameFlow::SetPlayerIsDead()
{
    CurrentState = EState::Ending;
    for (GameObject* Object : ObjectsToDisableOutsideGame)
    {
        //Object->SetEnabled(false);
    }
    if (GameUI)
    {
        GameUI->SetGameOver(CurrentScore);
    }
}

void GameFlow::UpdateLivesLeft(int NewLivesLeft)
{
    if (GameUI)
    {
        GameUI->UpdateLivesLeft(NewLivesLeft);
    }
}

void GameFlow::AddScore(int ScoreToAdd)
{
    CurrentScore += ScoreToAdd;
    if (GameUI)
    {
        GameUI->UpdateScore(CurrentScore);
    }
}

void GameFlow::AddObjectToDisableAtStart(GameObject* ObjectToDisable)
{
    ObjectsToDisableOutsideGame.push_back(ObjectToDisable);
}
