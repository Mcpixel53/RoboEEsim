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
wR = conf.wRadio # for round worlds

WIDTH = conf.environmentWidth
HEIGHT = conf.environmentHeight
maxFitness = np.sqrt(np.power(0 - WIDTH,2)+np.power(0-HEIGHT,2))

#OBJ_SIZE = conf.objectiveSize
#OBJ_Speed = conf.objectiveSpeed

#w = pyenki.World(wW,wH,pyenki.Color(0.5, 0.5, 0.5))
w = pyenki.WorldWithTexturedGround(wR, "GroundTextures/area.png", pyenki.Color(135/250.,206/250.,235/250.))

experimentData = {"Iterations": 0, "Individuals": [], "IndividualFitness": [], "MeanFitness": [] , "TopFitness": []}



class Analise(pyenki.Analytics_Module):

	def __init__(self, maxIts):
		super(Analise,self).__init__(maxIts)
		# self.integero = 8
		self.robotList = []
		self.varList = {} #dict which contains all the variables wanted to show
		# self.varName = []
		self.Individuals = self.register("Chromosome");
		self.Age =  self.register("Age");
		self.Fitness = self.register("Fitness");
		self.stop = False
		# self.exitFlag = 0
		#self.maxFitInd

	def register(self,nome):
		lista = []
		self.varList[nome] = lista
		return lista
		# super(Analise,self).registaer(lep,lop

	def addRobot(self,robot):
		self.robotList.append(robot)
		for nome in self.varList.keys():
			self.varList[nome].append(self.getDoubleList(robot.id, nome))

	def vlAdd(self, nome, robo, value):
		self.varList[nome][robo].append(value);

	def evController(self):
		global w
		#print("initiated EvController")
	#	experimentData['Size'] = conf.populationSize
		veryBest = 0.0
		#time.sleep(conf.startTime)
		try:
			currentIteration = w.iterations
			#print(running,(w.iterations<conf.maxIterations))
			iterationMeanFitness = 0
			iterationMaxFitness = 0

			i = 0
			for current in self.robotList:
				current.setFitness()
				#Guardar valores Individuales de los experimentos
				#if (currentIteration % conf.eachIterationCollection == 0):
			#self.Individuals.append(current.individual.genotype.chromosome[:])
				#experimentData['IndividualFitness'].append(current.individual.genotype.fitness)

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
					checkMatings(self.robotList,current)

				self.vlAdd("Fitness",i,current.individual.genotype.fitness)
				self.vlAdd("Chromosome",i,current.individual.genotype.fitness)
				self.vlAdd("Age",i,current.individual.age)

				i+=1
			#Guardar valores Globales de los experimentos
			#if (currentIteration % conf.eachIterationCollection == 0):
			#print(iterationMeanFitness,len(self.robotList))

			# iterationMeanFitness = iterationMeanFitness/len(self.robotList)
			self.Fitness.append(iterationMeanFitness/len(self.robotList))

			# self.maxFit.append(iterationMaxFitness)
			# if (currentIteration >= 20):
			# 	if (currentIteration <=50):
			# 		self.testList()
			# 		print(self.meanFitness[0])
			# 	elif (currentIteration <=80):
			# 		self.testList2()
			#bestFittedList.append(bestFitted)


			#Notify right before waiting
			# while currentIteration >= w.iterations:
			# 	time.sleep(0.05)
			# currentIteration = w.iterations
			#experimentData['Iterations'] = currentIteration

		except Exception as e:
			print(e)

	#	experimentData['MeanFitness'] = fitnessList
	#	experimentData['TopFitness'] = maxFitnessList
		#gm.experimentDataToCSVs(conf.experimentName,experimentData)



	def step(self):
		# print("Evolving Step!")
#		try:
#	    logicThread = threading._start_new_thread(
		if self.robotList:
			self.evController()
			self.stop=False

		else:
			if not self.stop:
				print("Population size = 0")
			self.stop=True
''' 	)
		except Exception as e:
			print ("Error: unable to start thread",str(e))
'''

class MyBall(pyenki.Bola):
	#Radius = 2
	def __init__(self,pos):
		super(MyBall, self).__init__()
		#self.dir = 1
		#starting pos and angle
		self.pos = pos
		self.angDir = 130
		self.angle =  Math.radians(self.angDir)
		self.dir = 1
		self.neutralSpeed = conf.objectiveSpeed
		print("New Ball At", self.pos)
		# self.mills = int(round(time.time() * 1000))
		# self.colliss =0

	def controlStep(self, dt):
		num= random.choice([1.2,3]) # angle multiplier
		grads = random.randrange(35,45,2) # random angle between 35-45 by 2 units
		self.dir = (1 if Math.cos(self.angle)>0 else 0 if Math.cos(self.angle)==0 else -1 ,1 if Math.sin(self.angle)>0 else 0 if Math.sin(self.angle)==0 else -1)#(1 if Math.cos(self.angle)>0 else 0 if Math.cos(self.angle)=0 else -1,1 if Math.sin(self.angle)>0 else 0 if Math.sin(self.angle)=0 else -1)
		if self.collide:
			# self.colliss +=1
			# if (int(round(time.time() * 1000)) - self.mills)>=1000:
			#  	print(self.colliss," Collisssss")
			#   	time.sleep(10)
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



class MyRobobo(pyenki.EPuck):

	def __init__(self, pos, id):
		super(MyRobobo, self).__init__()
		self.timeout = 10
		self.id = self.setId("rBobo "+str(id))
		self.pos = pos
		# self.speed is reserved by the engine
		self.Speed = conf.roboboSpeed
		self.controlSystem = nn.sigNeural_Network() #Neural_Network
		self.individual = gen.Individual(self.controlSystem.size)
		self.distanceBuffer = MyQueue.MyQueue(conf.distanceBufferSize)
		self.leftSpeed = self.Speed
		self.rightSpeed = self.Speed
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
			speed = (30 + conf.objectiveSpeed*0.3)#(conf.roboboSpeed+conf.objectiveSpeed)
			fitness = fitness/((self.distanceBuffer.getSize()-1)*speed)
			fitness = (1+fitness)/2
		else:
			fitness = fitness/maxFitness
			speed = 0
		if (debugRbobo and self.id == "rBobo 0"):
			print("debugging fitness distance over time Speed \n")
			print("tail",self.distanceBuffer.getTail(),"head",self.distanceBuffer.getHead())
			print("buffer",self.distanceBuffer.getSize(),"distance: ",distance, " speed ",speed, "fitness: ",fitness)
			#print()
		return fitness


	def fitnesSpeed(self): #100,100
		difer =1-(abs(100-self.leftSpeed)/100 + abs(100-self.rightSpeed)/100)
		print ("Calidade: "+ str(1-difer))
		return (difer)

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

		delta = beta - alpha

		if delta > 180:
			delta = delta - 360
		elif delta < -180:
			delta = delta + 360

		#print("Pos: %.1f, %.1f"%(self.sprite.pos[0],self.sprite.pos[1]))
		#print("Alpha: ", alpha)
		#print("Beta: ", beta)
		#print("Delta: ", delta)

		V = 100
		discrepancia = self.controlSystem.forward([delta])*V*2 -V
		(self.leftSpeed,self.rightSpeed) = (V-discrepancia[0], V+discrepancia[0])
		# print (self.leftSpeed,self.rightSpeed, "Outpt", discrepancia)
		#output = self.controlSystem.forward(-delta/180)
		#(self.leftSpeed,self.rightSpeed) = self.controlSystem.forward((leftSpeed, rightSpeed, -delta/180))
		#print ("Individual %i Neuronal Network Input: %1f, Output: %2f"%(self.individual.id,delta/180, output))
		'''
		incrementRot = output/np.pi*180

		if incrementRot > conf.angleRange:
		    incrementRot = conf.angleRange
		elif incrementRot < -conf.angleRange:
		    incrementRot = -conf.angleRange

		self.angle += Math.radians(incrementRot)
		#incrementRot =  delta
		'''
		if (debugRbobo):
			print("ID:",self.id,"speed", self.speed[0],self.speed[1],"rot",incrementRot,"speeds",self.leftSpeed,self.rightSpeed	 )


def checkMatings(pRobotList,pCurrent):

    for candidate in pRobotList:
        if candidate.individual.id != pCurrent.individual.id:
            pCurrent.individual.updateMaxFitness(candidate.individual.genotype.fitness)
            if candidate.individual.matingOperator.isMating:
                pCurrent.individual.mate(candidate.individual.genotype)
                candidate.individual.mate(pCurrent.individual.genotype)

ball = MyBall((0,0))
objective = ball
#w.steps = 100
anl = Analise(conf.maxIterations)

for i in range(conf.populationSize):
	robobo = MyRobobo((random.randrange(-wR/2,wR/2,2),random.randrange(-wR/2,wR/2,2)),i)
	w.addObject(robobo)
	anl.addRobot(robobo)

w.addObject(ball)

for a in range (-13,16):
	w.addItem("recta", ((a-1)* 10,0), 5000)
for eh in range(0,10):
	w.addItem("prisma",(random.randrange(-wR/2,wR/2,2),random.randrange(-wR/2,wR/2,2)), -1)

# w.addItem("recta",(a,0), 1000)
# anl.evolve()
	#//runSimulation(Enki::World, AnalyticsModule, camPos, camAltitude, camYaw, camPitch, wallsHeight)
#pyenki.EnkiViewer.runSimulation(w, anl, (wW/2,wH/2),wH*1.05, 0, Math.radians(-89.9), 10)
pyenki.EnkiViewer.runSimulation(w, anl, 10)

#experimentData['Iterations'] = w.iterations
