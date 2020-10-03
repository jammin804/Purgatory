import Framework.GameObject
import Framework.ImageComponent
import Framework.MusicComponent
import Globals

class Background(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.BackgroundImage = Framework.ImageComponent.ImageComponent(self)
        self.BackgroundImage.LoadImage(Globals.path_to_art + "/Background.png")
        self.BackgroundImage.Scale = 1.1
        self.BGMusic = Framework.MusicComponent.MusicComponent(self)
        self.BGMusic.SetLooped(True)
        self.BGMusic.LoadSample(Globals.path_to_audio + "/Music.wav")
        self.BGMusic.Play()