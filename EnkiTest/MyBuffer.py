import collections
import math
import numpy

class Buffer:

    def __init__(self, size):
        self.max_size = size
        self.deque = collections.deque([], size)
        self.penalizacionzona = 0

    def add(self, x, y, width):
        if x > 0.5 * width:
            self.deque.append((x, y, 1.0))
        else:
            self.deque.append((x, y, 0.0))

    def get_distancia(self):
        # print(len(self.deque[0]))
        (x1, y1, z1) = self.deque[0]
        if len(self.deque) > 1:
            (x2, y2, z2) = self.deque[1]
        else:
            (x2,y2) = (x1,y1)
        return math.sqrt((x2-x1)**2  + (y2-y1)**2)

    def get_distancia_recorrida(self, x, y, mySpeed, coeficente_correccion_length):
        head, tail = ( 0,0)
        if len(self.deque) > 1:
            head, tail = self.deque[0], self.deque[-1]
            distx = tail[0] - head[0]
            disty = tail[1] - head[1]
            distancia = math.sqrt(distx*distx + disty*disty)/(len(self.deque)*mySpeed)*(len(self.deque)/float(self.max_size))**coeficente_correccion_length  ##coef castigo traxectoria curta
        else:
            distancia = 0.0

        # print(head, tail, distancia, len(self.deque))
        # codigo para penalizacion con genzona
        '''coef = 0.5

        if (genzona > 0.5 and x > width*coef) or (genzona < 0.5 and x < width*coef):
            self.penalizacionzona += 1
        else:
            self.penalizacionzona = 0
        distancia = distancia * max(self.max_size - self.penalizacionzona, 0)/self.max_size
        '''
        # fin codigo penalizacion con genzona
        return distancia


    def get_coeficiente_zona_continuo(self, x, y, width, robot):

        sumacoefzona_d = 0.0
        for valor in self.deque:
            sumacoefzona_d += valor[2]

        coef_derecha = 2*(sumacoefzona_d - 0.5*len(self.deque))/len(self.deque)
        coef_izquierda = -coef_derecha


        if x > width*0.5:
            return max(0, coef_derecha)**2
        else:
            return max(0, coef_izquierda)**2


    def get_coeficiente_zona_por_pasos_en_vida(self, x, y, width, robot):

        if robot.contador_pasos_en_zona_izda_en_vida_paraesterobot > \
            robot.contador_pasos_en_zona_dcha_en_vida_paraesterobot:
            robot.variable_especie = 0
            if x > width *0.5:
                return 0
            else:
                return 1
        else:
            robot.variable_especie = 1
            if x > width*0.5:
                return 1
            else:
                return 0


    # es la distancia entre el primero y el ultimo
    def get_fitness(self, distanciaRecorrida, ir_values_normalized, mizona, robotsenmizona):

        '''maximo = numpy.amax(ir_values_normalized)
        if distanciaRecorrida > 0:
            return 1 -  maximo
        else:
            return 0 '''
        if robotsenmizona > 20:
            return distanciaRecorrida*(1 - ((robotsenmizona - 20)/20)**0.5 )
        else:
            return distanciaRecorrida

    def reset(self):
        self.penalizacionzona = 0
        self.deque.clear()
