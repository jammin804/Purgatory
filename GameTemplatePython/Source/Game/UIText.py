import Framework.GameObject
import Framework.TextComponent
import Framework.MusicComponent

class UIText(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.Position = [100,50]
        self.PlayerScore = Framework.TextComponent.TextComponent(self)
        self.PlayerScore.SetText("Score: 0")
    
    def UpdateScore(self, NewScore):
        self.PlayerScore.SetText("Score: " + str(NewScore))