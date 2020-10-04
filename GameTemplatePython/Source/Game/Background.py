import Framework.GameObject
import Framework.ImageComponent
import Framework.MusicComponent
import Globals

# This GameObject represents the background of the game
class Background(Framework.GameObject.GameObject):
    
    # Here we define what our background is made up of
    def OnInit(self):
        # We want a background image
        self.BackgroundImage = Framework.ImageComponent.ImageComponent(self)
        self.BackgroundImage.LoadImage(Globals.path_to_art + "/Background.png")
        self.BackgroundImage.Scale = 1.1
        # We want some background music
        self.BGMusic = Framework.MusicComponent.MusicComponent(self)
        self.BGMusic.LoadSample(Globals.path_to_audio + "/Music.wav")
        self.BGMusic.Play()