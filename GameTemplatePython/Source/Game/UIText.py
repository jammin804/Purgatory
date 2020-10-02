import Framework.GameObject
import Framework.TextComponent
import Framework.MusicComponent

class UIText(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.Position = [200,100]
        self.PlayerScore = Framework.TextComponent.TextComponent(self)
        self.PlayerScore.SetText("Score: 0")