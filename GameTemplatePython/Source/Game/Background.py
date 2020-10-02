import Framework.GameObject
import Framework.ImageComponent
import Framework.MusicComponent

class Background(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.BackgroundImage = Framework.ImageComponent.ImageComponent(self)
        self.BackgroundImage.LoadImage("Art/Background.png")
        self.BGMusic = Framework.MusicComponent.MusicComponent(self)
        self.BGMusic.SetLooped(True)
        self.BGMusic.LoadSample("Audio/Music.wav")
        self.BGMusic.Play()