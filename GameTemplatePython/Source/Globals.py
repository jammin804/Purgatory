# Importing Other Files
import Game.PongGame
import pygame
import os
import sys

### Data paths here are used for deploying to an executable file (.exe)
# bundle_dir = getattr(sys, '_MEIPASS', os.path.abspath(os.path.dirname(__file__)))
# path_to_art = os.path.abspath(os.path.join(bundle_dir, 'Art'))
# path_to_audio = os.path.abspath(os.path.join(bundle_dir, 'Audio'))
# path_to_font = os.path.abspath(os.path.join(bundle_dir, 'Font'))

### Data paths here are for local build (building inside visual studio code)
path_to_art = 'Art'
path_to_audio = 'Audio'
path_to_font = 'Font'

# Size of the window that the game runs in
ScreenSize = [1280,720]

# The max frame rate we will try to run the game at
TargetFPS = 120

# The game we are making is the asteroids game
MyGameFramework = Game.PongGame.PongGame(ScreenSize, TargetFPS)

# Font we use for all TextComponents
DefaultFont = None
