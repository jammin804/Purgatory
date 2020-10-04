import Framework.GameComponent
import pygame

# This component allows us to play Music from the GameObject
class MusicComponent(Framework.GameComponent.GameComponent): # It is a child of the GameComponent class
    
    # This is the constructor for the MusicComponent. It is called as soon as the MusicComponent is created
    def __init__(self, Owner):
        super().__init__(Owner) # This calls the constructor of the base class: 'GameComponent'
        self.bIsLooped = True # This can be used to determine if the music loops or not. Generally we want Music to loop
        self.bIsPlaying = False # This is used to know if the music is playing right now or not
    
    # Make sure to turn off the music when the GameObject shuts down
    def OnShutdown(self):
        self.Stop()
    
    # This function is used to load the sound file that we want. 
    # It takes a path on the computer to load the sound file from
    # We can use it to load .wav files for example
    def LoadSample(self, SamplePath):
        pygame.mixer.music.load(SamplePath)
    
    # Used to play the music
    def Play(self):
        pygame.mixer.music.play(-1 if self.bIsLooped else 0)
        self.bIsPlaying = True          
    
    # Used to stop playing the music
    def Stop(self):
        pygame.mixer.music.stop()
        self.bIsPlaying = False
    
    # Allows us to set if the music should loop
    def SetLooped(self, bIsLooping):
        self.bIsLooped = bIsLooping
    
    # Allows us to set the volume of the music
    def SetVolume(self, NewVolume):
        pygame.mixer.music.set_volume(NewVolume)
    
    # Allows us to query if the music is currently playing
    def IsPlaying(self):
        return self.bIsPlaying  
