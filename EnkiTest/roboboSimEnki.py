import traceback
import pyenki
import random
import math as Math
import numpy as np
from Configuration import Config as conf
import NeuralNetwork as nn
# import Genetics as gen
import Individuals as ind
import MyQueue
import threading
import sys, os
import time
from os import path


#### Debbugs
debugBall = 0
debugRbobo = 0
debugLogic = 0


#Global world properties
from tarefas.tarefa_chasing import TarefaChasing
from tarefas.tarefa_zones import TarefaZones
from tarefas.tarefa_testing import Testing

wW = conf.wWidth
wH = conf.wHeight
wR = conf.wRadio # for round worlds

# WIDTH = conf.environmentWidth
# HEIGHT = conf.environmentHeight
# maxFitness = np.sqrt(np.power(0 - WIDTH,2)+np.power(0-HEIGHT,2))

#OBJ_SIZE = conf.objectiveSize
#OBJ_Speed = conf.objectiveSpeed

# Squared world with no texture
#w = pyenki.World(wW,wH,pyenki.Color(0.5, 0.5, 0.5))
# round worldd with texture "area" and white background
# w = pyenki.WorldWithTexturedGround(wR, "GroundTextures/area.png", pyenki.Color(1,1, 1))
# round world with texture terra and sky-blue color background
if conf.roundMap:
	w = pyenki.WorldWithTexturedGround(wR, "GroundTextures/tiles.png", pyenki.Color(135/250., 206/250., 235/250.))
else:
	w = pyenki.WorldWithTexturedGround(wW, wH, "GroundTextures/tiles.png", pyenki.Color(135/250., 206/250., 235/250.))

experimentData = {"Iterations": 0, "Individuals": [], "IndividualFitness": [], "MeanFitness": [] , "TopFitness": []}



class Analise(pyenki.Analytics_Module):

	def __init__(self, maxIts, tarefa):
		super(Analise,self).__init__(maxIts)
		# self.integero = 8
		# self.varName = []
		self.robotList = []
		self.varList = {} #dict which contains all the variables wanted to show
		self.Individuals = self.register("Chromosome_str");
		self.Age =  self.register("Age");
		self.Fitness = self.register("Fitness");
		self.stop = False
		self.population = []
		self.objective = None
		self.task = tarefa()
		self.task.init(self)
		self.currentIteration = 0
		# self.exitFlag = 0
		#self.maxFitInd

	def register(self,nome):
		lista = []
		self.varList[nome] = lista
		return lista
		# super(Analise,self).registaer(lep,lop

	def getObjective(self):
		if self.objective:
			return self.objective
		else:
			print("No Objective!!")

	def addRobot(self,robot):
		self.robotList.append(robot)
		self.population.append(robot.individual)
		if (self.task):
			self.task.initRobo(robot, self.objective)
		for nome in self.varList.keys():
 			if(nome[-4:] == "_str"):
				self.varList[nome].append(self.getStringList(robot.id, nome[:-4]))
			else:
				self.varList[nome].append(self.getDoubleList(robot.id, nome))


	def vlAdd(self, nome, robo, value):
		if not self.varList.__contains__(nome):
			print("ERROR ADDING value",value," in ", nome)
			return
		self.varList[nome][robo].append(value)


	def evController(self):
		global w
		#print("initiated EvController")
	#	experimentData['Size'] = conf.populationSize
		veryBest = 0.0
		#time.sleep(conf.startTime)
		diferencial = isinstance(self.robotList[0].individual, ind.DifferentialIndividual)
		#MaxSumQ
		#MaxQ
		try:
			self.currentIteration = w.iterations
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
				if not self.task.specific(i, current, self):
					return
				#Buscar el individuo mas apto
				if current.individual.genotype.fitness > iterationMaxFitness:
					iterationMaxFitness = current.individual.genotype.fitness
					bestFitted = current
				iterationMeanFitness += current.individual.genotype.fitness

				current.individual.checkStatus(self.population)
				current.individual.incrementAge()
				if current.individual.age == 0:
					current.reset()

				self.vlAdd("Fitness", i,current.individual.genotype.fitness)
				#devolver String de cromosomas, de maneira facilmente interpretable pola GUI
				self.vlAdd("Chromosome_str", i, current.individual.genotype.returnChromosomeS())
				self.vlAdd("Age", i,current.individual.age)
				i+=1
			# se non existe non pasa nada

			#Guardar valores Globales de los experimentos
			#if (currentIteration % conf.eachIterationCollection == 0):
			#print(iterationMeanFitness,len(self.robotList))

			# iterationMeanFitness = iterationMeanFitness/len(self.robotList)

		except Exception as e:
			    traceback.print_exc()
				# print("exception")
				# print(e)

	#	experimentData['MeanFitness'] = fitnessList
	#	experimentData['TopFitness'] = maxFitnessList
		#gm.experimentDataToCSVs(conf.experimentName,experimentData)


	def step(self):
	# print("Evolving Step!")
	#		try:
	#	    logicThread = threading._start_new_thread(
		if self.robotList:
			self.evController()
			if not self.stop:
				self.log("*Task: " + str(self.task)+"\n")
				self.log("*Population size: " + str(len(self.robotList))+"\n")
				# print(str(self.robotList[0].controlSystem))
				self.log("*Controller: " + str(self.robotList[0].controlSystem)+"\n")
				self.log("*Individual type: " + str(self.robotList[0].individual)+"\n")
				# self.log("*Parametro cruze : " + str(conf.crueglgabmtrls)+"\n")
				self.log("\n\n")
				self.stop=True

		else:
			if not self.stop:
				print("Population size = 0")
			self.stop=True



class MyRobobo(pyenki.EPuck):

	def __init__(self, pos, id):
		super(MyRobobo, self).__init__()
		# self.timeout = 10
		self.id = self.setId("rBobo "+str(id))
		self.pos = pos # tuple: pos[0] = x, pos[1] = y
		# self.speed is reserved by the engine
		self.Speed = 0.0471 * conf.roboboSpeed #holds real speed (u/s)
		self.leftSpeed = conf.roboboSpeed # holds physics speed (left)
		self.rightSpeed = conf.roboboSpeed # holds physics speed (right)

		# self.individual = ind.DifferentialIndividual(self.controlSystem.size) ##
		self.controlSystem = nn.sigNeural_Network() #Neural_Network
		# self.controlSystem = nn.MLPNeuralNetwork() #Neural_Network
		self.individual = ind.DifferentialIndividual(self.controlSystem.size) ##
		# self.individual = ind.CanonicalIndividual(self.controlSystem.size) ##

		self.fitnessFunc = None
		self.buffer = None
		self.task_control = None
		# self.reset() 	### Robot reseted in the task

		# self.mills = int(round(time.time() * 1000))
		# print("POS",self.pos)


	def reset(self):
		if (not self.buffer):
			print("NOT BUFFER SPECIFIED IN", self.id)
			return
		self.buffer.reset()
		self.controlSystem.updateWeights(self.individual.genotype.chromosome)
		# print(self.testParam)

	def setFitness(self):
		if (not self.fitnessFunc):
			print("NOT BUFFER SPECIFIED IN", self.id)
			return
		fitness =  self.fitnessFunc(self)
		#setFitness en Qt
		self.setFitnessVar(fitness)
		#setFitness en individual
		self.individual.setFitness(fitness)

	def controlStep(self, dt):
		if (not self.task_control):
			print("NOT TASK_CONTROL SPECIFIED IN", self.id)
			return
		self.task_control(self)

		# if (int(round(time.time() * 1000)) - self.mills)>=1000:
		# 	time.sleep(4)
		# 	print("POS",self.pos,int(round(time.time() * 1000)))
		# return

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
			print("ID:",self.id,"speed", self.pos[0],self.speed[1],"rot",incrementRot,"speeds",self.leftSpeed,self.rightSpeed	 )





#w.steps = 100
# task = ()
anl = Analise(conf.maxIterations, TarefaZones)
# anl = Analise(conf.maxIterations, TarefaChasing)
# anl = Analise(conf.maxIterations, Testing)
objective = anl.getObjective()
if objective:
	w.addObject(objective)

random.seed(0)
for i in range(conf.populationSize):
	robobo = MyRobobo((random.randrange(-wR/2,wR/2,2),random.randrange(-wR/2,wR/2,2)),i)
	w.addObject(robobo)
	anl.addRobot(robobo)



# for a in range (-13,16):
# 	w.addItem("recta", ((a-1)* 10,0), 5000)
# for eh in range(0,10):
# 	w.addItem("cruz",(random.randrange(-wR/2,wR/2,2),random.randrange(-wR/2,wR/2,2)), 100000)
#
# w.addItem("recta",(a,0), 1000)
# anl.evolve()
	#//runSimulation(Enki::World, AnalyticsModule, camPos, camAltitude, camYaw, camPitch, wallsHeight)
#pyenki.EnkiViewer.runSimulation(w, anl, (wW/2,wH/2),wH*1.05, 0, Math.radians(-89.9), 10)
pyenki.EnkiViewer.runSimulation(w, anl, 10)

#experimentData['Iterations'] = w.iterations
