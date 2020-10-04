import Framework.GameObject
import Framework.InputComponent
import Game.UIText
import pygame

# This GameObject represents the flow of our game to determine when it starts/ends. Keeping track of the time remaining, the score of the player and displaying it in UI
class GameFlow(Framework.GameObject.GameObject):
    
    # This is the constructor of the GameFlow. It is called as soon as we create the GameFlow GameObject
    def __init__(self):
        super().__init__()
        self.ObjectsToDisableAtStart = [] # This is a list of GameObjects we want to disable until the game starts
        
    def OnInit(self):
        self.CurrentScore = 0 # This is the current score of the player
        self.bStarting = True # This is the state of the game
        self.bInGame = False # This is the state of the game
        self.Input = Framework.InputComponent.InputComponent(self) # This component is used to determine when we have pressed the return key
        self.TimeRemaining = 120.0 # This is the time remaining for the game. Right now the game ends in 2 minutes (120 seconds)
        self.UI = Game.UIText.UIText() # This is the Game UI GameObject. It tells the player the time remaining, the current score and how many lives the player has left
        self.ReturnPressed = False # This makes sure we have both a pressed and released state of the return key before we action it
        self.bEndGame = False # This is used to tell the game framework we have ended the game
        
    # This is called after initialisation. here we display the welcome message to the player
    def OnPostInit(self):
        self.UI.SetWelcomeToTheGame()
    
    # This is used to setup the display when the player dies. I.e. we show a game over screen
    def SetPlayerDied(self):
        self.UI.SetGameOver(self.CurrentScore)
        self.bInGame = False
    
    # Here we update the games ui with the number of lives left from the player
    def UpdateLivesLeft(self, NewLivesLeft):
        self.UI.UpdateLivesLeft(NewLivesLeft)        
        
    # Here we update the games ui when the player increases their score
    def AddScore(self, ScoreToAdd):
        self.CurrentScore += ScoreToAdd
        self.UI.UpdateScore(self.CurrentScore)
        
    # Here we update the game flow based on the current state of the game
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