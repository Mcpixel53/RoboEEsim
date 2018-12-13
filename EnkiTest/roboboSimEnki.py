import pyenki
import random
import math as Math
import numpy as np
from Configuration import Config as conf
import NeuralNetwork as nn
import Genetics as gen
import MyQueue
import threading
import sys, os
import time
from os import path
#Global world properties

#### Debbugs
debugBall = 0
debugRbobo = 0
debugLogic = 0

wW = conf.wWidth
wH = conf.wHeight

WIDTH = conf.environmentWidth
HEIGHT = conf.environmentHeight
maxFitness = np.sqrt(np.power(0 - WIDTH,2)+np.power(0-HEIGHT,2))

OBJ_SIZE = conf.objectiveSize
OBJ_Speed = conf.objectiveSpeed

robotList = []
w = pyenki.World(wW,wH,pyenki.Color(0.5, 0.5, 0.5))
experimentData = {"Iterations": 0, "Individuals": [], "IndividualFitness": [], "MeanFitness": [] , "TopFitness": []}
exitFlag = 0


class Analise(pyenki.Analytics_Module):
	def __init__(self, maxIts):
		super(Analise,self).__init__(maxIts)
		self.integro = 8

class MyBall(pyenki.Bola):
	#Radius = 2
	def __init__(self,pos):
		super(MyBall, self).__init__()
		#self.dir = 1
		#starting pos and angle
		self.pos = pos
		self.angDir = 130
		self.angle = Math.radians(self.angDir)
		self.dir = 1

		print("New Ball At", self.dir, self.angDir)

	def controlStep(self, dt):
		num=random.choice([1.2,3]) # angle multiplier
		grads = random.randrange(35,45,2) # random angle between 35-45 by 2 units
		self.dir = (1 if Math.cos(self.angle)>0 else 0 if Math.cos(self.angle)==0 else -1 ,1 if Math.sin(self.angle)>0 else 0 if Math.sin(self.angle)==0 else -1)#(1 if Math.cos(self.angle)>0 else 0 if Math.cos(self.angle)=0 else -1,1 if Math.sin(self.angle)>0 else 0 if Math.sin(self.angle)=0 else -1)
		if self.collide:
			if (debugBall):
				print("////////////////////////////////")
			coll = self.getWall(wW,wH) #get wich wall caused collision x =1, y = 2, both = 3
			#recovering position before collision //even thought should already be done by engine//
			nextPos = (self.pos[0]-OBJ_Speed*Math.cos(self.angle),self.pos[1]-OBJ_Speed*Math.sin(self.angle))
			#calcular nova direcion & angulo
			nextDir = 0 if (0 in self.dir) else self.dir[0]*self.dir[1] if (coll in (1,3)) else -1 * self.dir[0]*self.dir[1]
			if (debugBall):
				print("nextDir ", nextDir)
			self.angDir = (self.angDir%360)+(nextDir*grads*num) if nextDir != 0 else (self.angDir%360)+(random.choice([1,-1])*grads*num)
			self.angle = Math.radians(self.angDir)
			if (debugBall):
				print("debug self.dir2:",self.dir,"angle: ",self.angDir)
			self.collide=False ## check disable

		else:
			nextPos = (self.pos[0]+OBJ_Speed*Math.cos(self.angle),self.pos[1]+OBJ_Speed*Math.sin(self.angle))

			self.pos = nextPos


class MyRobobo(pyenki.EPuck):

	def __init__(self, pos, id):
		super(MyRobobo, self).__init__()
		self.timeout = 10
		self.id = "rBobo "+str(id)
		self.pos = pos
		self.speedy = conf.roboboSpeed
		self.controlSystem = nn.Neural_Network()
		self.individual = gen.Individual(self.controlSystem.size)
		self.distanceBuffer = MyQueue.MyQueue(conf.distanceBufferSize)
		self.leftSpeed = self.speedy
		self.rightSpeed = self.speedy
		self.setFitnessVar(0)
		self.changeWeights()

	def changeWeights(self):
		self.resetDistanceBuffer()
		self.controlSystem.updateWeights(self.individual.genotype.chromosome)

	def fitnessDistanceOverTimeSpeed(self):
		distance = np.sqrt(np.power((self.pos[0] - objective.pos[0]),2) + np.power((self.pos[1] - objective.pos[1]),2))
		self.distanceBuffer.enqueue(distance)
		fitness = 0
		if self.distanceBuffer.getSize() > 1:
			fitness = (self.distanceBuffer.getTail() - self.distanceBuffer.getHead())
			speed = (conf.roboboSpeed+conf.objectiveSpeed*10)
			fitness = fitness/((self.distanceBuffer.getSize()-1)*speed)
			fitness = (1+fitness)/2
		else:
			fitness = fitness/maxFitness
			speed = 0
		if (debugRbobo and self.id == "rBobo 0"):
			print("debugging fitness distance over time Speed \n")
			print("tail",self.distanceBuffer.getTail(),"head",self.distanceBuffer.getHead())
			print("buffer",self.distanceBuffer.getSize(),"distance: ",distance, " speed ",speed, "fitness: ",fitness)
		return fitness

	def fitnessAlg(self):
		return self.fitnessDistanceOverTimeSpeed()

	def resetDistanceBuffer(self):
		while self.distanceBuffer.isEmpty() != True:
			self.distanceBuffer.dequeue()

	def setFitness(self):
		fitness =  self.fitnessAlg()
		self.setFitnessVar(fitness)
		#print(fitness)
		self.individual.setFitness(fitness)

	def controlStep(self, dt):
		Xrt = objective.pos[0] - self.pos[0]
		Yrt = objective.pos[1] - self.pos[1]

		if Xrt > wW/2:
			Xrt = - (wW - Xrt)
		elif Xrt < - wW/2:
			Xrt = wW + Xrt

		if Yrt > wH/2:
			Yrt = - (wH - Yrt)
		elif Yrt < - wH/2:
			Yrt = wH + Yrt

		beta = np.arctan2(Yrt,Xrt) * 180/np.pi
		alpha = Math.degrees(self.angle)

		delta = beta + alpha

		if delta > 180:
			delta = delta - 360
		elif delta < -180:
			delta = delta + 360

		#print("Pos: %.1f, %.1f"%(self.sprite.pos[0],self.sprite.pos[1]))
		#print("Alpha: ", alpha)
		#print("Beta: ", beta)
		#print("Delta: ", delta)

		output = self.controlSystem.forward(-delta/180)

		#print ("Individual %i Neuronal Network Input: %1f, Output: %2f"%(self.individual.id,delta/180, output))

		incrementRot = output/np.pi*180

		if incrementRot > conf.angleRange:
		    incrementRot = conf.angleRange
		elif incrementRot < -conf.angleRange:
		    incrementRot = -conf.angleRange

		self.angle += Math.radians(incrementRot)
		#incrementRot =  delta

		if (debugRbobo):
			print("ID:",self.id,"speed", self.speed[0],self.speed[1],"rot",incrementRot,"speeds",self.leftSpeed,self.rightSpeed	 )


def checkMatings(pRobotList,pCurrent):

    for candidate in pRobotList:
        if candidate.individual.id != pCurrent.individual.id:
            pCurrent.individual.updateMaxFitness(candidate.individual.genotype.fitness)
            if candidate.individual.matingOperator.isMating:
                pCurrent.individual.mate(candidate.individual.genotype)
                candidate.individual.mate(pCurrent.individual.genotype)



def updateLogic():

	global exitFlag, robotList, w

	experimentData['Size'] = conf.populationSize
	fitnessList = []
	maxFitnessList = []
	bestFittedList = []
	veryBest = 0.0
	running = True
	#currentIteration = 0
	#time.sleep(conf.startTime)
	try:
		currentIteration = w.iterations
		#print(running,(w.iterations<conf.maxIterations))
		while (running and currentIteration < conf.maxIterations):
			iterationMeanFitness = 0
			iterationMaxFitness = 0
			bestFitted = None

			if exitFlag:
			    running = False

			#time.sleep(conf.sleepTest)
			#if currentIteration >= conf.fastForwardToIterarion:
			#    time.sleep(conf.algorithmSleep)

			#objective.update()

			for current in robotList:
				current.setFitness()
				#Guardar valores Individuales de los experimentos
				#if (currentIteration % conf.eachIterationCollection == 0):
				experimentData['Individuals'].append(current.individual.genotype.chromosome[:])
				experimentData['IndividualFitness'].append(current.individual.genotype.fitness)

				#Buscar el individuo mas apto
				if current.individual.genotype.fitness > iterationMaxFitness:
				    iterationMaxFitness = current.individual.genotype.fitness
				    bestFitted = current

				iterationMeanFitness += current.individual.genotype.fitness

				current.individual.incrementAge()
				current.individual.checkStatus()
				if current.individual.age == 0:
				    current.changeWeights()
				if current.individual.matingOperator.isMating:
				    checkMatings(robotList,current)

			#Guardar valores Globales de los experimentos
			#if (currentIteration % conf.eachIterationCollection == 0):
			#print(iterationMeanFitness,len(robotList))
			iterationMeanFitness = iterationMeanFitness/len(robotList)
			fitnessList.append(iterationMeanFitness)
			maxFitnessList.append(iterationMaxFitness)
			bestFittedList.append(bestFitted)
			#print(currentIteration)
			if (iterationMaxFitness>veryBest):
				 veryBest=iterationMaxFitness

			#Notify right before waiting
			anl.notifyBestQuality(w.iterations, float(veryBest))
			anl.notifyAVGQuality(w.iterations, float(iterationMeanFitness))
			while currentIteration >= w.iterations:
				time.sleep(0.05)
			currentIteration = w.iterations
			experimentData['Iterations'] = currentIteration

	except Exception as e:
	    print(e)

	experimentData['MeanFitness'] = fitnessList
	experimentData['TopFitness'] = maxFitnessList
	#gm.experimentDataToCSVs(conf.experimentName,experimentData)
	exitFlag = True
	#print("Experiment Dta: " , experimentData)
	#print("UEAH",veryBest)

ball = MyBall((50.0,5.0))
objective = ball
#w.steps = 100
anl = Analise(conf.maxIterations)
for i in range(conf.populationSize):
	robobo = MyRobobo((i*10,5*10),i)
	w.addObject(robobo)
	robotList.append(robobo)

w.addObject(ball)
#//runInviewer(Enki::World self, camPos, camAltitude, camYaw, camPitch, wallsHeight)

#if __name__ == '__main__':
try:
    logicThread = threading._start_new_thread( updateLogic, () )
except Exception as e:
	print ("Error: unable to start thread",str(e))

pyenki.EnkiViewer.runSimulation(w, anl, (wW/2,wH/2),wH*1.05, 0, Math.radians(-89.9), 10)

#experimentData['Iterations'] = w.iterations
