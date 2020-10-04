#importing other files
import Game.Player
import Game.RockManager
import Game.Explosion
import Game.Background
import Game.GameFlow
import Framework.GameFramework
import copy

# This class represents our actual Game! This is where we decide what our Asteroids game really is.
class Asteroids(Framework.GameFramework.GameFramework): # We are a child of the GameFramework class
    
    # This is the constructor for the Asteroids class. It is called as soon as the Asteroids class is created
    # We need to specify the ScreenSize and TargetFPS when we create it because the base class requires it
    def __init__(self, ScreenSize, TargetFPS): 
        super().__init__(ScreenSize, TargetFPS)
    
    # This is called immediately after the Asteroids Class is created
    # Here we set up the initial 'Contents' of our game. Think of it like a recipe. 
    # These are the 'things' we want in our game
    def OnInit(self):
        self.SetTitle("Asteroids Game") # Set The Title Of Our Games Window
        self.SetGameFont("arial.ttf", 32) # Set up the Font we want to use
        self.BG = Game.Background.Background() # We want a background in our game
        self.Player1 = Game.Player.Player() # We want a player in our game
        self.RockManager = Game.RockManager.RockManager() # We want a way to create lots of Rocks!
        self.GameFlow = Game.GameFlow.GameFlow() # We want a way to determine when the game starts, if it has been won/lost
        self.GameFlow.ObjectsToDisableAtStart.append(self.Player1) # We tell the GameFlow not to start these GameObjects until the game starts fully!
        self.GameFlow.ObjectsToDisableAtStart.append(self.RockManager) # We tell the GameFlow not to start these GameObjects until the game starts fully!
    
    # Here we update our Asteroid Game every frame 
    def OnUpdate(self, DeltaTime):         
        if self.GameFlow.bEndGame: # If the GameFlow says the game is finished then we let the GameFramework know we're finished!
            self.GameOver = True
            return
        
        # Here we are detecting what to do when Rocks collide with things in our game
        for Rock in self.RockManager.Rocks: # We go through every rock
            # if the Rock wasn't already destroyed and the player isn't currently invulnerable we check for collision
            if not self.Player1.bInvulnerable and Rock is not None: 
                # This checks if the player has collided with this rock
                if self.Player1.Collision.DoesCollide(Rock.Collision):
                    # If we collide we want to Explode the player! So we create an Explosion at the player's position
                    Explosion = Game.Explosion.Explosion()
                    Explosion.Position = self.Player1.Position
                    # Then we check to see if this was the last life of the player. If it was tell the GameFlow the player has died :(
                    if (self.Player1.HandleDeath()):
                        self.GameFlow.SetPlayerDied()
                    else:
                        # Otherwise we will update the GameFlow with the new number of lives so it can update the UI
                        self.GameFlow.UpdateLivesLeft(self.Player1.LivesLeft)
            
            # So for each Rock we also check if any of the player's laser beams have hit one of the rocks            
            for Laser in self.Player1.Lasers: 
                if Rock.Collision.DoesCollide(Laser.Collision): # Did the laser beam hit the rock?
                    self.GameFlow.AddScore(5 * (Rock.SplitsLeft + 1)) # Add score based on the size of the rock
                    # Create an explosion where we hit the rock!
                    Explosion = Game.Explosion.Explosion() 
                    Explosion.Position = copy.copy(Rock.Position)
                    Explosion.Scale = Rock.RockImage.Scale # Create an appropriate sized explosion based on the size of the rock hit
                    
                    # Does the Rock split or is it small enough to Destroy?
                    if (Rock.SplitsLeft == 0):
                        Rock.Destroy()
                    else:
                        Rock.bNeedsSplit = True # We let the RockManager know it needs to split this rock into two pieces!
                    Laser.Destroy() # We destroy the laser beam as it was used up in the explosion with the rock!
                    break
