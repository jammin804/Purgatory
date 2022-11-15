#pragma once

#include "Framework/GameObject.h"
#include <vector>

class UIHUD;
class UIShop;
class Player;
class UIText;
class InputComponent;
class UIWelcomeMessage;
class UIEndGameMessage;
class UIPause;

using namespace std;


class GameFlow : public GameObject
{
public:
    enum class EState
    {
        Starting = 0,
        InGame,
		Pause,
		Shopping,
        Ending
    };


    protected:
        virtual void OnInit() override;
        virtual void OnPostInit() override;
        virtual void OnUpdate(float DeltaTime) override;
        virtual void OnShutdown() override;
		virtual void Restart(bool bShouldResetGame);
        virtual void OnEvent(const EventMessage& Msg);
		void SetPaused(bool bIsPaused);
        void SetShopPause(bool bIsInShop);

		void UpdateShop();

public:
        void SetPlayerIsDead();
        void UpdateLivesLeft(int NewLivesLeft);
        void AddScore(int ScoreToAdd);
        void AddObjectToDisableAtStart(GameObject* ObjectToDisable);
        bool ShouldEndGame() const { return bShouldEndGame; }
		bool ShouldResetGame() const { return bShouldResetGame; }
		void SetGUI(UIHUD* GameUIRef) { GameUI = GameUIRef; }
		void SetPlayer(Player* NewPlayer) { player = NewPlayer; }
		EState GameState() {return CurrentState;}
		void SetAllDead();
		void AddTime();
    private:
        vector<GameObject*> GameFlowGameObjects;
        int CurrentScore = 0;
        EState CurrentState = EState::Starting;
		const float MAX_TIME = 10.0f;
        float TimeRemaining = MAX_TIME;
		int FearTimer;
        InputComponent* Input = nullptr;
        UIText* GameUIText = nullptr;
		UIShop* GameShop = nullptr;
        UIHUD* GameUI = nullptr;
        UIWelcomeMessage* WelcomeMessageText = nullptr;
        UIEndGameMessage* EndGameMessageText = nullptr;
        UIPause* PauseText = nullptr;
		Player* player = nullptr;
        bool bReturnPressed = false;
        bool bShouldEndGame = false;
		bool bShouldPauseGame = false;
		bool bShouldResumeGame = false;
		bool bShouldResetGame = false;
};

