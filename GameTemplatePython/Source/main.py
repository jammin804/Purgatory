import Game.AsteroidsGame as AsteroidsGame

MyGame = AsteroidsGame.Asteroids()

def Main(): 
    if (MyGame.Init() == False):
        return
    
    while (MyGame.Update()):
        continue
    
    MyGame.Shutdown()
    
Main()