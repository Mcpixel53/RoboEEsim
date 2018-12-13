import pyenki
import random
import math as Math
from Configuration import Config as conf
import NeuralNetwork as nn

#Global world properties

wL = 200
wH = 100



w = pyenki.World(wL,wH,pyenki.Color(0.5, 0.5, 0.5))
w.steps = 100

#//runInviewer(Enki::World self, camPos, camAltitude, camYaw, camPitch, wallsHeight)
w.runInViewer((wL/2,wH/2),wH*1.05, 0, Math.radians(-89.9), 10)
