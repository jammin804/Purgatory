import Framework.GameComponent
import pygame

# This component allows us to play Sound from the GameObject
class SoundComponent(Framework.GameComponent.GameComponent): # It is a child of the GameComponent class
    
    # This is the constructor for the SoundComponent. It is called as soon as the SoundComponent is created
    def __init__(self, Owner):
        super().__init__(Owner) # This calls the constructor of the base class: 'GameComponent'
        self.bIsLooped = False # This can be used to determine if the sound loops or not
        self.bIsPlaying = False # This is used to know if the sound is playing right now or not
    
    # Make sure to turn off the sound (if we have one) when the GameObject shuts down
    def OnShutdown(self):
        if (self.AudioSample is not None):
            self.Stop()
    
    # This function is used to load the sound file that we want. 
    # It takes a path on the computer to load the sound file from
    # We can use it to load .wav files for example
    def LoadSample(self, SamplePath):
        self.AudioSample = pygame.mixer.Sound(SamplePath)
    
    # Used to play the sound
    def Play(self):
        self.AudioSample.play(-1 if self.bIsLooped else 0)
        self.bIsPlaying = True
    
    # Used to stop playing the sound
    def Stop(self):
        self.AudioSample.stop()
        self.bIsPlaying = False
    
    # Allows us to set if the sound should loop
    def SetLooped(self, bIsLooping):
        self.bIsLooped = bIsLooping
    
    # Allows us to set the volume of the sound
    def SetVolume(self, NewVolume):
        self.AudioSample.set_volume(NewVolume)
    
    # Allows us to query if the sound is currently playing
    def IsPlaying(self):
        return self.bIsPlaying 
