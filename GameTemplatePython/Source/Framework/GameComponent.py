# import other files
import Framework.GameObject

# The GameComponent is the base class for all other components. A GameObject can own multiple GameComponents
class GameComponent(object):
    
    # This is the constructor for the GameComponent. It is called when the GameComponent is created
    # We store the owner which is the GameObject that created this GameComponent
    def __init__(self, Owner): 
        self.Owner = Owner
        self.Owner.RegisterComponent(self) # Registers the component with the GameObject so that the Game Object can update it
        self.Offset = [0,0] # Allows the component to be positioned at an offset from the GameObject's position

    # These are all functions that can be used to build behaviour from children of a GameComponent. Such as ImageComponent
    def OnInit(self):
        pass
    def OnUpdate(self, DeltaTime):
        pass
    def OnRender(self, Screen):
        pass
    def OnShutdown(self):
        pass
    def GetOwner(self):
        return self.Owner

    # These are protected functions. The GameObject is the only user of these functions.
    def _Init_(self):
        self.OnInit()        
    def _Update_(self, DeltaTime):
        self.OnUpdate(DeltaTime)        
    def _Render_(self, Screen):
        self.OnRender(Screen)        
    def _Shutdown_(self):
        self.OnShutdown()
