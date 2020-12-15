#pragma once

#include "Framework/GameObject.h"
#include "Player.h"
#include <vector>

using namespace std;


class GameFlow : public GameObject
{
    enum class EState
    {
        Starting = 0,
        InGame,
		Pause, //Added Pause to EState
        Ending
    };

    protected:
        virtual void OnInit() override;
        virtual void OnPostInit() override;
        virtual void OnUpdate(float DeltaTime) override;
        virtual void OnShutdown() override;
		virtual void Restart(bool bShouldResetGame);
		void SetPaused(bool bIsPaused);

    public:
        void SetPlayerIsDead();
        void UpdateLivesLeft(int NewLivesLeft);
        void AddScore(int ScoreToAdd);
        void AddObjectToDisableAtStart(GameObject* ObjectToDisable);
        bool ShouldEndGame() const { return bShouldEndGame; }
		bool ShouldResetGame() const { return bShouldResetGame; }
    private:
        vector<GameObject*> ObjectsToDisableOutsideGame;
        int CurrentScore = 0;
        EState CurrentState = EState::Starting;
        class InputComponent* Input = nullptr;
        float TimeRemaining = 120.0f;
        class UIText* GameUI = nullptr;
        bool bReturnPressed = false;
        bool bShouldEndGame = false;
		bool bShouldPauseGame = false; /* adding bool or pausing and resuming game */
		bool bShouldResumeGame = false;
		bool bShouldResetGame = false;
		//class Player* player = nullptr;
};

