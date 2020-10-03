#pragma once

import Game.AsteroidsGame
import pygame
import os
import sys

bundle_dir = getattr(sys, '_MEIPASS', os.path.abspath(os.path.dirname(__file__)))
path_to_art = os.path.abspath(os.path.join(bundle_dir, 'Art'))
path_to_audio = os.path.abspath(os.path.join(bundle_dir, 'Audio'))
path_to_font = os.path.abspath(os.path.join(bundle_dir, 'Font'))
# path_to_art = 'Art'
# path_to_audio = 'Audio'
# path_to_font = 'Font'

ScreenSize = [1280,720]
TargetFPS = 120
MyGameFramework = Game.AsteroidsGame.Asteroids(ScreenSize, TargetFPS)
DefaultFont = None
