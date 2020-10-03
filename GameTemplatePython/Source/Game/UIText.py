import Framework.GameObject
import Framework.TextComponent
import Framework.MusicComponent
import Globals

class UIText(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.Position = [0,50]
        self.PlayerScore = Framework.TextComponent.TextComponent(self)
        self.PlayerScore.SetText("Score: 0")
        self.PlayerScore.Offset[0] = 100 
        
        self.LivesLeft = Framework.TextComponent.TextComponent(self)
        self.LivesLeft.SetText("Lives Left: 3")
        self.LivesLeft.Offset[0] = Globals.ScreenSize[0] * 0.5 - 50
        
        self.TimeRemaining = Framework.TextComponent.TextComponent(self)
        self.TimeRemaining.SetText("Time Left: 0")
        self.TimeRemaining.Offset[0] = Globals.ScreenSize[0] - 300
        
        self.MainText = Framework.TextComponent.TextComponent(self)
        self.MainText.SetText("GAME OVER")
        self.MainText.Offset[0] = Globals.ScreenSize[0] * 0.5 - 100
        self.MainText.Offset[1] = Globals.ScreenSize[1] * 0.5 - 150
        self.MainText.SetVisible(False)
        
        self.FinalScore = Framework.TextComponent.TextComponent(self)
        self.FinalScore.SetText("Final Score: ")
        self.FinalScore.Offset[0] = Globals.ScreenSize[0] * 0.5 - 100
        self.FinalScore.Offset[1] = Globals.ScreenSize[1] * 0.5 - 100
        self.FinalScore.SetVisible(False)
        
        self.PressEnterToQuit = Framework.TextComponent.TextComponent(self)
        self.PressEnterToQuit.SetText("Press Enter To Quit")
        self.PressEnterToQuit.Offset[0] = Globals.ScreenSize[0] * 0.5 - 100
        self.PressEnterToQuit.Offset[1] = Globals.ScreenSize[1] * 0.5 - 50
        self.PressEnterToQuit.SetVisible(False)
        
        self.RenderDepth = 10.0
    
    def SetWelcomeToTheGame(self):
        self.PlayerScore.SetVisible(False)
        self.LivesLeft.SetVisible(False)
        self.TimeRemaining.SetVisible(False)
        self.FinalScore.SetVisible(True)
        self.MainText.SetVisible(True)
        self.MainText.SetText("Welcome To Asteroids! Press Enter To Start")
        self.MainText.Offset[0] = Globals.ScreenSize[0] * 0.5 - 300
        self.FinalScore.SetText("Use the ""Arrow Keys"" to move and the ""Space"" button to fire lasers")
        self.FinalScore.Offset[0] = Globals.ScreenSize[0] * 0.5 - 450
        
    def SetInGame(self):
        self.PlayerScore.SetVisible(True)
        self.LivesLeft.SetVisible(True)
        self.TimeRemaining.SetVisible(True)
        self.MainText.SetVisible(False)
        self.FinalScore.SetVisible(False)
    
    def SetGameOver(self, FinalScore):
        self.PlayerScore.SetVisible(False)
        self.LivesLeft.SetVisible(False)
        self.TimeRemaining.SetVisible(False)
        self.MainText.SetVisible(True)
        self.MainText.Offset[0] = Globals.ScreenSize[0] * 0.5 - 100
        self.MainText.SetText("GAME OVER")
        self.FinalScore.SetVisible(True)
        self.FinalScore.SetText("Final Score: " + str(FinalScore))
        self.FinalScore.Offset[0] = Globals.ScreenSize[0] * 0.5 - 100
        self.PressEnterToQuit.SetVisible(True)
        
    def SetYouSurvived(self, FinalScore):
        self.PlayerScore.SetVisible(False)
        self.LivesLeft.SetVisible(False)
        self.TimeRemaining.SetVisible(False)
        self.MainText.SetVisible(True)
        self.MainText.Offset[0] = Globals.ScreenSize[0] * 0.5 - 100
        self.MainText.SetText("YOU SURVIVED!")
        self.FinalScore.SetVisible(True)
        self.FinalScore.SetText("Final Score: " + str(FinalScore))
        self.FinalScore.Offset[0] = Globals.ScreenSize[0] * 0.5 - 100
        self.PressEnterToQuit.SetVisible(True)
    
    def UpdateScore(self, NewScore):
        self.PlayerScore.SetText("Score: " + str(NewScore))
        
    def UpdateLivesLeft(self, NewLivesLeft):
        self.LivesLeft.SetText("Lives Left: " + str(NewLivesLeft))
        
    def UpdateTimeRemaining(self, NewTimeMins, NewTimeSeconds):
        if NewTimeMins > 0:
            self.TimeRemaining.SetText("Time Left: " + str(NewTimeMins) + ":" + ("0" if NewTimeSeconds < 10 else "") + str(NewTimeSeconds))
        else:
            self.TimeRemaining.SetText("Time Left: "+ str(NewTimeSeconds) + "s")