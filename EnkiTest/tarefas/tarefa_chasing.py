from MyQueue import MyQueue
from Configuration import Config as conf
import numpy as np
import math as Math
import random
import time
import traceback
import pyenki
from Tarefa import Tarefa

wW = conf.wWidth
wH = conf.wHeight
wR = conf.wRadio

class TarefaChasing(Tarefa):

    def __init__(self):
        #Config specific
        pass


    def init(self, anl):
        anl.objective = MyBall((0,0), conf.objectiveSize, (0.9,0.9,0))
        pass

    def initRobo(self, current, objective):
        current.fitnessFunc = fitnessDistanceOverTimeSpeed
        current.objective = objective
        current.buffer = MyQueue(conf.distanceBufferSize)
        current.task_control = roboboChasing_controlStep
        current.reset()
    def specific(self, i, current, anl):
        pass

    def initobjective(self):
        pass

    def __str__(self):
         return "Task Chasing"

################################################################################
debugBall = False
class MyBall(pyenki.Bola):
	#Radius = 2
	def __init__(self,pos, size = 3, col = (0.9, 0.9, 0)):
		(r,g,b) = col
		super(MyBall, self).__init__(size, pyenki.Color(r,g,b))
		#self.dir = 1
		#starting pos and angle
		self.id = self.setId("Bola")
		self.pos = pos
		self.angDir = 130
		self.Speed = 0.114 * conf.objectiveSpeed #holds real speed (u/s)
		self.angle =  Math.radians(self.angDir)
		self.dir = 1
		self.neutralSpeed = conf.objectiveSpeed # holds physics speed
		print("New Ball At", self.pos)
		self.mills = int(round(time.time() * 1000))
		print(self.pos)
		# self.colliss =0

	def controlStep(self, dt):
		num= random.choice([1.2,3]) # angle multiplier
		grads = random.randrange(35,45,2) # random angle between 35-45 by 2 units
		self.dir = (1 if Math.cos(self.angle)>0 else 0 if Math.cos(self.angle)==0 else -1 ,1 if Math.sin(self.angle)>0 else 0 if Math.sin(self.angle)==0 else -1)#(1 if Math.cos(self.angle)>0 else 0 if Math.cos(self.angle)=0 else -1,1 if Math.sin(self.angle)>0 else 0 if Math.sin(self.angle)=0 else -1)
		# if (int(round(time.time() * 1000)) - self.mills)>=1000:
		# 	print(self.colliss,self.pos)
		# 	time.sleep(10)
		# return
		if self.collide:
			# self.colliss +=1
			if (debugBall):
				print("////////////////////////////////")
			coll = self.getWall(wW,wH) #get wich wall caused collision x =1, y = 2, both = 3
			#recovering position before collision //even thought should already be done by engine//
			#nextPos = (self.pos[0]-OBJ_Speed*Math.cos(self.angle),self.pos[1]-OBJ_Speed*Math.sin(self.angle))
			#calcular nova direcion & angulo
			nextDir = 0 if (0 in self.dir) else self.dir[0]*self.dir[1] if (coll in (1,3)) else -1 * self.dir[0]*self.dir[1]
			if (debugBall):
				print("nextDir ", nextDir)
			self.angDir = (self.angDir%360)+(nextDir*grads*num) if nextDir != 0 else (self.angDir%360)+(random.choice([1,-1])*grads*num)
			self.angle = Math.radians(self.angDir+180)
			if (debugBall):
				print("debug speed:",self.speed,"angle: ",self.angle)
			self.collide=False ## check disable
		#else:
			#nextPos = (self.pos[0]+OBJ_Speed*Math.cos(self.angle),self.pos[1]+OBJ_Speed*Math.sin(self.angle))
		if (debugBall):
			print("debug speed:",self.speed,"angle: ",self.angle)

################################################################################
def roboboChasing_controlStep(self):
    Xrt = self.objective.pos[0] - self.pos[0]
    Yrt = self.objective.pos[1] - self.pos[1]

    w1 = wR if conf.roundMap else wW
    w2 = wR if conf.roundMap else wH

    if Xrt > w1/2:
    	Xrt = - (w1 - Xrt)
    elif Xrt < - w1/2:
    	Xrt = w1 + Xrt

    if Yrt > w2/2:
    	Yrt = - (w2 - Yrt)
    elif Yrt < - w2/2:
    	Yrt = w2 + Yrt
    beta = np.arctan2(Yrt,Xrt) * 180/np.pi
    alpha = Math.degrees(self.angle)

    delta = beta - alpha

    if delta > 180:
    	delta = delta - 360
    elif delta < -180:
    	delta = delta + 360
    # print("Pos: %.1f, %.1f"%(self.sprite.pos[0],self.sprite.pos[1]))
    #print("Alpha: ", alpha)
    #print("Beta: ", beta)
    #print("Delta: ", delta)

    V = conf.roboboSpeed #	100
    discrepancia = self.controlSystem.forward([delta])*V*2 -V
    (self.leftSpeed,self.rightSpeed) = (V-discrepancia[0], V+discrepancia[0])
################################################################################

WIDTH = conf.wWidth
HEIGHT = conf.wHeight
maxFitness = np.sqrt(np.power(0 - WIDTH,2)+np.power(0-HEIGHT,2)) if conf.roundMap else conf.wRadio

def fitnessDistanceOverTimeSpeed(self):
    distance = np.sqrt(np.power((self.pos[0] - self.objective.pos[0]),2) + np.power((self.pos[1] - self.objective.pos[1]),2))
    self.buffer.enqueue(distance)
    fitness = 0
    if self.buffer.getSize() > 1:
        fitness = (self.buffer.getTail() - self.buffer.getHead())
        speed = (self.Speed + self.objective.Speed)
        fitness = fitness/((self.buffer.getSize()-1)*speed)
        fitness = (1+fitness)/2

    return fitness


def fitnesSpeed(self): #100,100
    difer = 1-(abs(100-self.leftSpeed)/100 + abs(100-self.rightSpeed)/100)
    print ("Calidade: "+ str(1-difer))
    return (difer)


def fitness(self):
    ## para implementar en task_chasing
    return self.buffer.get_distancia_recorrida(self.x, self.y, self.speed, 0.5)

    # if self.zona_actual_esterobot == 0:
    #     fitness = self.buffer.get_fitness(self.sensor_distancia_recorrida, \
    #         self.ir_values_normalized, self.zona_actual_esterobot, self.environment.robots_zona_izquierda)
    # else:
    #     fitness = self.buffer.get_fitness(self.sensor_distancia_recorrida, \
    #         self.ir_values_normalized, self.zona_actual_esterobot, self.environment.robots_zona_derecha)
    # return fitness
