
import Tarefa
from Configuration import Config as conf
import time
import random
from MyBuffer import Buffer
from tarefas.tarefa_zones import *
import numpy as np

class Testing(Tarefa.Tarefa):
    roboPos = 0
    millis = time.time()
    times = 0
    round = 0
    count = 0
    speedCount = 0
    speed = 0

    def init(self,anl):
        conf.inputSize = 1
        conf.hiddenSize = 2
        conf.outputSize = 1
        anl.coefZona = anl.register("Zone Sharing Coef")
        anl.coefPunish = anl.register("Punish Sharing Coef")
        anl.coef_reparto_zona = 0
        #print out config?
        pass
    def specific(self, i, current, anl):
        if len(anl.robotList) <2:
            print("NOT ENOUGH ROBOTS TO PERFORM TESTSSS!!!")
            quit(-1)
        current.buffer.add(current.pos[0], current.pos[1], width)
        # print("deque",current.buffer.deque)
        update_coeficiente_reparto_and_ir_floor(current, anl.coef_reparto_zona)
        return 0

    def initRobo(self, current, objective = None):  ## args
        current.task_control = testing_controlStep
        current.buffer = Buffer(2)
        # current.fitnessFunc = noFitness
        current.fitnessFunc = maxfitness#fitness_coefzona
        current.testTemp = False
        current.testIR = False
        current.testStraight = False
        (current.leftSpeed, current.rightSpeed) = (0,0)
        ###############
        current.contador_pasos_en_zona_izda_en_vida_paraesterobot = 0
        current.contador_pasos_en_zona_dcha_en_vida_paraesterobot = 0
        current.variable_especie = 0
        current.zona_actual = 0
        current.coeficiente_penalizacion_reparto = 0
        current.castigo = 0
        # current.porcentaje_pasos_en_vida_ZI
        ###############
        current.reset()

    def initobjective(self):
        pass

    def __str__(self):
        return "Debug & Test"

def noFitness(self):
    return 0

def maxfitness(self):
    suma = np.sum(self.individual.genotype.chromosome)/len(self.individual.genotype.chromosome)
    # print(suma, self.individual.genotype.chromosome)
    return suma if (suma < 1 and suma > 0) else 0


def testing_controlStep(self):
    irSensors = self.proximitySensorDistances
    return
    if (self.id=="rBobo 0"):
        print(irSensors)

    if (self.testTemp):
        # (self.leftSpeed, self.rightSpeed) = (45,60)
        # roboboZones_controlStep(self)
        if (self.id=="rBobo 0"):
            if len(self.buffer.deque)>1:
                try:
                    temp = self.buffer.get_distancia()
                    Testing.speed += temp
                    # print(temp)
                    Testing.times += 1
                except Exception as e:
                    print("Error with the neural controller!",e)

            if (round(1000*(time.time() - Testing.millis ))>=10000):
                Testing.speedCount += Testing.speed/Testing.times
                print("Iter" + str(Testing.round), Testing.count + Testing.times, Testing.speed/Testing.times)
                Testing.count += Testing.times
                Testing.round += 1
                Testing.times = 0
                Testing.millis = time.time()
                Testing.speed = 0
        if(Testing.round >=6):
            print("Iteracions por 10s", Testing.speedCount/Testing.round)
            print("Velocidade por iteracion", Testing.speedCount/Testing.round)
            Testing.times = 0
            Testing.round = 0
            Testing.count = 0
            self.testTemp = False

            # self.testIR  = True
    elif (self.testIR):
        # if (True)
        (self.leftSpeed, self.rightSpeed) = (0,0)
        if (self.id=="rBobo 1" or self.id=="rBobo 0"):
            (self.pos[0],self.pos[1]) = ((self.id[6])*4, (self.id[7])*4)
            (self.leftSpeed, self.rightSpeed) = (-80 , 0)

        else:
            (self.pos[0],self.pos[1]) = (random.random()*1000,random.random()*1000)


        # self.testIR  = True
