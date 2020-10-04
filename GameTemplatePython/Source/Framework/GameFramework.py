# Import other files
import pygame # pygame is the main library of functionality to make python games
import Globals

ColorBlue = 0, 0, 100 # specify the color of blue for a background

# This is the GameFramework class. It is used to run the entire game. It controls all GameObjects and maintains their lifetime
class GameFramework(object):

    # This is the constructor for the GameFramework class. It is called when the GameFramework is first created
    def __init__(self, ScreenSize, TargetFPS):
        self.ScreenSize = ScreenSize # Here we capture the window size for use inside our class
        self.TargetFPS = TargetFPS # Here we capture the maximum number of frames we will run the game at
        self.GameOver = False # This variable is used to determine when the game has finished
        self.GameObjects = [] # This is used to store a list of all game objects currently in the game

    # This is used to register the GameObject with the Framework so it can be updated and displayed by the game
    def RegisterGameObject(self, NewGameObject):
        self.GameObjects.append(NewGameObject)
        
    # This is used to unregister the GameObject when it is destroyed
    def UnregisterGameObject(self, GameObjectToUnregister):
        for GameObject in self.GameObjects:
            if GameObject == GameObjectToUnregister:
                GameObject._Shutdown_() # Here we call shutdown on the GameObject which allows us to shutdown any components
                self.GameObjects.remove(GameObject) # Remove the GameObject from the list of GameObjects we are updating
                break # break means "leave the loop" we can leave the loop since we found the object we were looking for
        
    
    # Here we set the title of the Window that we run the game in
    def SetTitle(self, NewTitle):
        pygame.display.set_caption(NewTitle) 
        
    # This is used to setup the font we will be using for all our TextComponents
    def SetGameFont(self, FontPath, FontSize):
        Globals.DefaultFont = pygame.font.Font(Globals.path_to_font + "/" + FontPath, FontSize)
    
    # These functions are used by the child class of the GameFramework. The child class represents the actual game we are making
    def OnInit(self): # Called at the start
        pass
    def OnPostInit(self): # Called after everything has been initialised at the start
        pass
    def OnUpdate(self, DeltaTime): # Called every frame. DeltaTime tells us how many seconds have passed since the Update last triggered
        pass
    def OnShutdown(self): # Called when the game is over and the game closes
        pass
    
    def GetTimeElapsed(self): # This calculation converts the DeltaTime from milliseconds to seconds
        return self.FPSClock.get_time() * 0.001
    
    # Called at the start
    def Init(self):
        pygame.init() # This is intialisation of the pygame engine
        pygame.mixer.pre_init(frequency=44100, size=-16, channels=1, buffer=512) # here we are setting up the sound drivers
        pygame.mixer.init() # This is setting up the pygame sound engine
        self.FPSClock = pygame.time.Clock() # this clock is used to determine how long its been between each frame displayed of our game
        self.Screen = pygame.display.set_mode(self.ScreenSize) # this represents the Window that the game is displayed in
        
        self.OnInit() # Here we let the child class (the real game) know that it can now be initialised
        self.OnPostInit() # Here we let the child class (the real game) know that everything is now initalised

        return True # We let the main class know that Initialisation was successful

    # This function is used to ensure that we can control the order that GameObjects are 'Drawn' on the screen
    def GameObjectRenderSort(self, GameObject): 
        return GameObject.RenderDepth # The higher the RenderDepth the later it will be 'Drawn' (Will be on top)

    # This function is our main update loop for the game
    def Update(self):
        # First we check if the game is finished. We want to close the game if its finished
        if (self.GameOver):
            return False # This will close the game
        
        # Here we detect if the player closed the window with the 'X' in the top corner
        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                return False # This will close the game
            
        # Here we go through every GameObject in case anything new was added this frame
        # New GameObjects could be added at any time. So first we make sure to initalise them
        for GameObject in self.GameObjects:
            if not GameObject.bInitialised:
                GameObject._Init_()

        # After ALL New GameObjects are Initialised we let each of them know that they're all initalised
        for GameObject in self.GameObjects:
            if not GameObject.bInitialised:                
                GameObject._PostInit_()
        
        #Here we let the child of the GameFramework (The real game) know that it can update anything
        self.OnUpdate(self.GetTimeElapsed())
        
        #Next we Update all enabled GameObjects
        for GameObject in self.GameObjects:
            if GameObject.bEnabled:
                GameObject._Update_(self.GetTimeElapsed())
        
        # This clears the screen so that we can Render(Draw) on a blank screen with everything that updated
        self.Screen.fill(ColorBlue)
        
        # This goes through and draws all GameObjects that are enabled and sorts them by their RenderDepth variable
        for GameObject in sorted(self.GameObjects, key=self.GameObjectRenderSort):
            if GameObject.bEnabled:
                GameObject._Render_(self.Screen)
        
        # This sends the updated image to your graphics card/screen
        pygame.display.update()
        
        # Here we request that the next update happen as fast as our TargetFPS specifies 
        # It may run slower depending on the speed of your computer
        # This will just ask it not to run any faster than the TargetFPS
        self.FPSClock.tick(self.TargetFPS)

        # Return True means the game should keep updating (i.e. It's not finished)
        return True
    
    # This is called when the game closes. It shutsdown all the GameObjects
    def Shutdown(self):
        self.OnShutdown()
        for GameObject in self.GameObjects:
            GameObject._Shutdown_()