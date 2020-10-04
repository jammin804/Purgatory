# Importing other files
import pygame # pygame is our game library
import Framework.GameComponent # the base class of all components

# This class represents a bounding box that covers our objects and is used to detect collisions between GameObjects
class BoxCollisionComponent(Framework.GameComponent.GameComponent): # It is a child of the GameComponent class
    
    # This is the constructor for the BoxCollisionComponent. It is called as soon as the BoxCollisionComponent is created
    def __init__(self, Owner):
        super().__init__(Owner) # This calls the constructor of the base class: 'GameComponent'
        self.bShowDebug = False # Used to show us where our collision box is by drawing a red rectangle where it is
        self.CollisionBox = pygame.Rect([0,0,0,0]) # The rectangle that represents our collision box
        self.Scale = 1.0 # We can use this scale to make the collision box smaller/bigger than the image
    
    def SetScale(self, NewScale):
        self.Scale = NewScale
        
    def GetScale(self):
        return self.Scale
        
    # We use this function to make sure that the collision box is following the object it is surrounding
    def SetRect(self, NewRect):
        self.CollisionBox[0] = NewRect[0] + ((1.0 - self.Scale) * NewRect[2] * 0.5)
        self.CollisionBox[1] = NewRect[1] + ((1.0 - self.Scale) * NewRect[3] * 0.5)
        self.CollisionBox[2] = NewRect[2] * self.Scale
        self.CollisionBox[3] = NewRect[3] * self.Scale
    
    # We use this to detect if two collision components have hit one another
    def DoesCollide(self, OtherCollisionComponent):
        return self.CollisionBox.colliderect(OtherCollisionComponent.CollisionBox)
    
    # If we are using debug we draw a red box to show where the rectangle is
    def OnRender(self, Screen):
        if (not self.bShowDebug):
            return
        pygame.draw.rect(Screen, (255,0,0), self.CollisionBox,2)

