import Framework.GameObject
import Framework.InputComponent
import Game.UIText
import pygame

class GameFlow(Framework.GameObject.GameObject):
    
    def __init__(self):
        super().__init__()
        self.ObjectsToDisableAtStart = []
        
    def OnInit(self):
        self.CurrentScore = 0
        self.bStarting = True
        self.bInGame = False
        self.Input = Framework.InputComponent.InputComponent(self)
        self.TimeRemaining = 180.0
        self.UI = Game.UIText.UIText()          
        self.ReturnPressed = False
        self.bEndGame = False
        
        
    def OnPostInit(self):
        self.UI.SetWelcomeToTheGame()
        
    def SetPlayerDied(self):
        self.UI.SetGameOver(self.CurrentScore)
        self.bInGame = False
    
    def UpdateLivesLeft(self, NewLivesLeft):
        self.UI.UpdateLivesLeft(NewLivesLeft)        
        
    def AddScore(self, ScoreToAdd):
        self.CurrentScore += ScoreToAdd
        self.UI.UpdateScore(self.CurrentScore)
        
    def OnUpdate(self, DeltaTime):
        if self.bStarting == True:
            for GameObject in self.ObjectsToDisableAtStart:
                GameObject.bEnabled = False
            
            if self.Input.IsKeyPressed(pygame.K_RETURN):
                self.ReturnPressed = True
            if self.ReturnPressed and self.Input.IsKeyReleased(pygame.K_RETURN):
                self.ReturnPressed = False
                self.bStarting = False
                self.bInGame = True
                for GameObject in self.ObjectsToDisableAtStart:
                    GameObject.bEnabled = True
                self.UI.SetInGame()
        elif self.bInGame == True:
            self.TimeRemaining -= DeltaTime
            self.UI.UpdateTimeRemaining(int(self.TimeRemaining / 60), int(self.TimeRemaining) % 60)
            if self.TimeRemaining <= 0.0 :
                self.bInGame = False
                self.UI.SetYouSurvived(self.CurrentScore)
            pass
        else:
            if self.Input.IsKeyPressed(pygame.K_RETURN):
                self.ReturnPressed = True
            if self.ReturnPressed and self.Input.IsKeyReleased(pygame.K_RETURN):
                self.ReturnPressed = False
                self.bEndGame = True