from MyBuffer import Buffer
from Configuration import Config as conf
import Tarefa
width = 0 if conf.roundMap else conf.wWidth

class TarefaZones(Tarefa.Tarefa):

    def __init__(self):
        #Config specific
        # Tarefa.__init__(self)
        pass

    def init(self, anl):
        conf.inputSize = 5
        conf.hiddenSize = 5
        conf.outputSize = 1

        anl.coefZona = anl.register("Zone Sharing Coef")
        anl.coefPunish = anl.register("Punish Sharing Coef")
        anl.coef_reparto_zona = 0

    def initRobo(self, current, objective = None):  ## args
        ### if isinstance(algo): initOtherKindofRobot(current)
        current.fitnessFunc = fitness_coefzona
        current.buffer = Buffer(conf.distanceBufferSize)
        current.task_control = roboboZones_controlStep
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

    def initOtherKindofRobot():
        pass

    def specific(self, i, current, anl):
        current.buffer.add(current.pos[0], current.pos[1], width)
        # print("deque",current.buffer.deque)
        update_coeficiente_reparto_and_ir_floor(current, anl.coef_reparto_zona)
        anl.vlAdd("Punish Sharing Coef", i, current.coeficiente_penalizacion_reparto)
        ### adding at last
        if i==conf.populationSize-1:
			anl.vlAdd("Zone Sharing Coef", 0, anl.coef_reparto_zona)

    def __str__(self):
         return "Task Zones " + ("raw" if  conf.fitness_sin_zonas else "double zone" if conf.fitness_dos_zonas else "active zone")

################################################################################
def normalizarIR(valor):
    if ( valor > 11):
         return 1
    else:
        return 0

def checkCastigo(input):
    if min(input) < 1:
        return 15
    return 0

def roboboZones_controlStep(self):

    inputController = []
    irSensors = self.proximitySensorDistances
    inputController.append(normalizarIR(irSensors[6])) #front-L
    inputController.append(normalizarIR(irSensors[7])) #front-front-L
    inputController.append(normalizarIR(irSensors[0])) #front-front-R
    inputController.append(normalizarIR(irSensors[1])) #front-R

    if (self.castigo < 1):
        self.castigo = checkCastigo(irSensors)
    else:
        self.castigo -=1
        (self.leftSpeed, self.rightSpeed) = (0,0)
        # if (self.id=="rBobo 1"):
        #     print("Senss ", inputController)
        return

    inputController.append(self.zona_actual)

    # # alpha = 1/cos(15.*M_PI/180.)
    V = conf.roboboSpeed #	100
    output = self.controlSystem.forward(inputController)
    discrepancia = output * V * 2 -V
    if (self.id=="rBobo 0"):
        print(inputController)
    # (self.leftSpeed, self.rightSpeed) = output*V
    (self.leftSpeed, self.rightSpeed) = (V-discrepancia[0], V+discrepancia[0])


################################################################################


def update_coeficiente_reparto_and_ir_floor(self, coef_reparto_zona):

       if self.pos[0] < width * 0.5:
           self.contador_pasos_en_zona_izda_en_vida_paraesterobot += 1.0
           if self.zona_actual == 1:
               coef_reparto_zona += 1/conf.populationSize
               if coef_reparto_zona>1:
                   coef_reparto_zona = 1
               # self.environment.robots_zona_derecha -= 1
               # self.environment.robots_zona_izquierda += 1
               self.zona_actual = 0
           coeficiente_reparto_mi_zona = coef_reparto_zona
       else:
           self.contador_pasos_en_zona_dcha_en_vida_paraesterobot += 1.0
           if self.zona_actual == 0:
               coef_reparto_zona -= 1/conf.populationSize
               if coef_reparto_zona<0:
                   coef_reparto_zona = 0
               # self.environment.robots_zona_derecha += 1
               # self.environment.robots_zona_izquierda -= 1
               self.zona_actual = 1
           coeficiente_reparto_mi_zona = 1 - coef_reparto_zona

       if coeficiente_reparto_mi_zona > 0.5:
           self.coeficiente_penalizacion_reparto = 1 - ((coeficiente_reparto_mi_zona - 0.5)/0.5)**0.5
       else:
           self.coeficiente_penalizacion_reparto = 1.0
       # self.porcentaje_pasos_en_vida_ZI = self.contador_pasos_en_zona_izda_en_vida_paraesterobot / self.age


def fitness_coefzona(self):

        distancia_recorrida = self.buffer.get_distancia_recorrida(self.pos[0], self.pos[1], self.Speed, 0.5)
        if (self.id=="rBobo 0"):
            print(distancia_recorrida, self.leftSpeed, self.rightSpeed)
        #coeficiente_zona_continuo = self.buffer.get_coeficiente_zona_continuo(self.x, self.y, config.width, self)
        coeficiente_por_pasos_en_vida = self.buffer.get_coeficiente_zona_por_pasos_en_vida(self.pos[0], self.pos[1], width, self)
        '''if self.x > width *0.5:
            if self.gen_de_zona > 0:
                coeficiente_zona_por_genotipo = 1.0
            else:
                coeficiente_zona_por_genotipo = 0.0
        else:
            if self.gen_de_zona > 0:
                coeficiente_zona_por_genotipo = 0.0
            else:
                coeficiente_zona_por_genotipo= 1.0
        '''
        if conf.fitness_sin_zonas:
            privateFitness = distancia_recorrida

        elif conf.fitness_dos_zonas:
            privateFitness =  distancia_recorrida * coeficiente_por_pasos_en_vida #*self.coeficiente_penalizacion_reparto

        elif conf.fitness_dos_zonas_una_activa:
            if self.x > width *0.5:
                privateFitness = distancia_recorrida
            else:
                privateFitness = 0.0
        # print(privateFitness, coeficiente_por_pasos_en_vida)
        return privateFitness
