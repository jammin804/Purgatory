#import other files
import Globals

# This class represents the overall entity of something in the game like a player/enemy/text 
# Something that has a position/transform
class GameObject(object):    
    
    # This is the constructor of the GameObject. It is called as soon as the GameObject is created
    def __init__(self):
        Globals.MyGameFramework.RegisterGameObject(self) # We register with the Framework so it can tell us when to update each frame
        self.Position = [0.0,0.0] # This is the position of the GameObject on screen
        self.Rotation = 0.0 # This is the rotation of the GameObject on screen
        self.GameComponents = [] # This is a list holding all the connected components to our GameObject such as Image/Input/Sound
        self.bEnabled = True # This is used to hide/show our GameObject at any time
        self.bInitialised = False # This is used to tell us if the GameObject has been initialised by the Framework yet
        self.bIsDestroyed = False # This is used to know that the GameObject has been destroyed
        self.RenderDepth = 0.0 # Higher values will be rendered(drawn) on top of GameObjects with smaller values
    
    # This is used when we want to destroy our GameObject during the game
    def Destroy(self):
        Globals.MyGameFramework.UnregisterGameObject(self)
        self.bIsDestroyed = True
  
    # These functions are used by the child classes (such as player) when they want to do something during a stage of their lifecycle
    def OnInit(self):
        pass
    def OnPostInit(self):
        pass
    def OnUpdate(self, DeltaTime):
        pass
    def OnShutdown(self):
        pass

    # These functions are only called by the Framework when it is an appropriate stage in their lifecycle
    def _Init_(self):
        self.OnInit() # We usually create any GameComponents in this function
        for Component in self.GameComponents: # After the GameObject is initalised we initialise any components it created
            Component._Init_()
    def _PostInit_(self):
        self.OnPostInit() # Called to let the GameObject know he can now setup his components as they have been initalised
        self.bInitialised = True # This is used to let the Framework know that is initialised and we don't need to initialise it again
    def _Update_(self, DeltaTime):
        if not self.bInitialised: # We make sure we don't update the GameObject until it has been initialised
            return
        self.OnUpdate(DeltaTime) # Called every frame to allow the Child class (The real GameObject like Player) to Update
        for Component in self.GameComponents:
            Component._Update_(DeltaTime) # After the GameObject updates we update all its attached components   
    def _Render_(self, Screen):
        for Component in self.GameComponents:
            Component._Render_(Screen) # Only components render(draw). So we go through and render them all  
    def _Shutdown_(self): # Called after the GameObject is destroyed
        for Component in self.GameComponents:
            Component._Shutdown_()
            self.GameComponents.remove(Component)
        self.OnShutdown()
       
    # This is used by GameComponents to register themselves with the GameObject so they will get initialised/updated/shutdown by the GameObject
    def RegisterComponent(self, NewComponent): 
        self.GameComponents.append(NewComponent)
