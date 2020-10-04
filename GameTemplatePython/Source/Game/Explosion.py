import Framework.GameObject
import Framework.ImageComponent
import Framework.SoundComponent
import pygame
import math
import Globals

# This GameObject represents an explosion in our game
class Explosion(Framework.GameObject.GameObject):
    
    # This is the constructor for the Explosion. It is called when the Explosion is created
    def __init__(self):
        super().__init__()
        self.Scale = 1.0 # We set the scale immediately as we often need to scale it when we create it
    
    def OnInit(self):
        # Setup the Explosion Image
        self.ExplosionImage = Framework.ImageComponent.ImageComponent(self)
        self.ExplosionImage.LoadImage(Globals.path_to_art + "/Explosion.png")
        self.ExplosionImage.Scale = self.Scale
        
        # Setup the Explosion Sound
        self.DestroyedSound = Framework.SoundComponent.SoundComponent(self)
        self.DestroyedSound.LoadSample(Globals.path_to_audio + "/Explosion.wav")
        self.DestroyedSound.Play()
        self.DestroyedSound.SetVolume(0.4)
        
        # This timer is used to determine how long we show the explosion on the screen for
        self.Timer = 0.0
        
    # Here we remove the explosion after two seconds
    def OnUpdate(self, DeltaTime):       
        self.Timer += DeltaTime
        if self.Timer > 2.0:
            self.Destroy()