# Imports
import numpy as np
from Configuration import Config as conf
# Config Variables


# Mutation
geneMax = conf.geneMax
geneMin = conf.geneMin

mutationRate = conf.mutationRate
mutationAmplitude = geneMax * 0.05
mutationPercent = conf.mutationPercent

superMutationProbability = conf.superMutationProbability
geneVariability = conf.geneVariability
matingAndReplaceProbability = conf.matingAndReplaceProbability

# Mating
cm = conf.cm
# maxTournament = conf.tournamentSize
maturity = conf.maturity  # Funcion Matematica = 1
maxLifetime = conf.maxLifetime  # Funcion Matematica 10
# maxMatings = conf.maxMatings

preference = conf.preference

# Crossover
percentOfGenes = conf.crossoverPortion
alpha = conf.alpha
matingSeason = 0.20 * maxLifetime
populationSize = conf.populationSize
pbest = conf.pbest

# Global Variables


# Classes

class Genotype:
    def __init__(self, pDimensions):
        self.size = pDimensions
        self.chromosome = self.generateRandomChromosome(self.size)
        self.fitness = 0.0

    def create_new(self, chrom = None):
        chrom = chrom or self.chromosome
        newGenotyppe = Genotype(len(chrom))
        newGenotyppe.chromosome = list(chrom) #list copy
        newGenotyppe.fitness = self.fitness
        return newGenotyppe

    def returnChromosomeD(self):
        ch = 0
        for i in self.chromosome:
            ch+=i
            ch*=10
        return ch

    def returnChromosomeS(self):
        return " ".join(str('%+.2f') %elem for elem in self.chromosome).replace(".",",")

    def generateRandomChromosome(self, pDimensions):
        newChromosome = [None for j in range(pDimensions)]
        for i in range(len(newChromosome)):
            newChromosome[i] = self.randomGene()
        return newChromosome


    def randomGene(self):
        return np.random.uniform(geneMin, geneMax)

#############
##OPERATORS##
################################################################################

class CanonicalGeneticOperators:

    def __init__(self, mutation_amplitude, mutation_portion, crossover_portion, crossover_margin):
        self.mutation_amplitude = mutation_amplitude
        self.mutation_portion = mutation_portion
        self.crossover_portion = crossover_portion
        self.crossover_margin = crossover_margin


    def mutate(self, genotype, amplitude):
        mutated = genotype.create_new()
        for i in range(len(mutated.chromosome)):
            if np.random.random() < self.mutation_portion:
                mutated.chromosome[i] = self.check_boundaries(genotype.chromosome[i] + (np.random.random() - 0.5)*amplitude)

        #print("Distancia genotipica al mutado ", self.distancia_genotipica(mutated, genotype))
        return mutated

    def crossover(self, receiver_genome, other_genome):
        sibling = receiver_genome.create_new()
        for i in range(len(sibling.chromosome)):
            if np.random.random() < self.crossover_portion:
                sibling.chromosome[i] = self.blx_crossover(receiver_genome.chromosome[i], other_genome.chromosome[i])
            elif np.random.random() < 0.5:
                sibling.chromosome[i] = receiver_genome.chromosome[i]
            else:
                sibling.chromosome[i] = other_genome.chromosome[i]
        return sibling

    def blx_crossover(self, a, b):
        alpha = self.crossover_margin
        dist = abs(a - b)
        minimum = min(a, b)
        maximum = max(a, b)
        dif = maximum + alpha*dist - (minimum - alpha*dist)
        return self.check_boundaries(minimum - alpha*dist + np.random.random()*dif)

    def check_boundaries(self, gen):
        if gen > 1.0:
            return 1.0
        elif gen < 0.0:
            return 0.0
        else:
            return gen

    def distancia_genotipica(self, uno, otro):
        suma = 0.0
        for i in range(len(uno)):
            suma += (uno[i] - otro[i])*(uno[i] - otro[i])
        return math.sqrt(suma)


class CanonicalMating:

    def __init__(self, mutation_amplitude, mutation_portion, crossover_portion, crossover_margin):
        self.operators = CanonicalGeneticOperators(mutation_amplitude, mutation_portion, crossover_portion, crossover_margin)
        self.preference = 0.5
        self.pMating = conf.pMating
        self.contadorCruce = 0
        self.contadorMutation = 0
        self.mutationRate = conf.mutationRate
        self.mutation_amplitude = mutation_amplitude


    def mutation(self, receiver, other):
        self.contadorMutation += 1
        selected = None
        if np.random.random() < self.preference:
            selected = receiver
        else:
            selected = other
        # the operator gives a copy
        selected.embryo = self.operators.mutate(selected.genotype, self.mutation_amplitude)
        selected.embryo.fitness = selected.genotype.fitness * 0.5


    def mutate_embryo(self, genotype):
        self.contadorMutation += 1
        # this operator gives a copy
        return self.operators.mutate(genotype, self.mutation_amplitude*0.1)


    def crossover(self, receiver, other):
        self.contadorCruce += 1
        # the operator gives a copy
        receiver.embryo = self.operators.crossover(receiver.genotype, other.genotype)
        receiver.embryo.fitness = (receiver.genotype.fitness + other.genotype.fitness) *0.5


class CanonicalReplacement:


    def __init__(self,maxLifetime,cm,maturity):
        # self.maturity_time = maturity_time
        self.maxLifetime = maxLifetime
        self.cm = cm
        self.lifespan = self.maxLifetime - maturity


    def replacementProb(self, individual):
        if individual.maximumPrivateFitness - individual.minimumPrivateFitness == 0:
            replaceProb = 1.0
        else:
            fitnessNorm = (individual.genotype.fitness - individual.minimumPrivateFitness)/(individual.maximumPrivateFitness - individual.minimumPrivateFitness)
            if fitnessNorm < 2.0/3.0:
                expectedLifetimeCoeff = fitnessNorm*self.cm*3.0/2.0
            else:
                expectedLifetimeCoeff = self.cm + (fitnessNorm - 2.0/3.0)*3*(1 - self.cm)
            if expectedLifetimeCoeff > 0:
                replaceProb = 1.0 / (self.lifespan*expectedLifetimeCoeff)
            else:
                replaceProb = 1.0

        if replaceProb < 0:
            replaceProb = 0.0
        elif replaceProb > 1:
            replaceProb = 1.0

        return replaceProb


class DifferentialEvolutionOperator:

    def __init__(self, pbest, populationSize, affinity, F, CR):
        self.F = F     #(coeficiente de diferencias)
        self.CR = CR    #crossover Rate (percentage genes change)
        self.pbest = pbest
        self.populationSize = populationSize
        self.pBestRange = int(self.pbest * self.populationSize)
        self.replace = False
        self.affinity = affinity                                                #???

    def currentToPBest1Bin(self, sortedPopulation, current):
        if self.affinity:
            # get best affine
            best = self.get_best_affine(sortedPopulation, current)
            (index1, index2) = self.getTwoRandomIndex(sortedPopulation, current)
            randomIndividual1 = sortedPopulation[index1]
            randomIndividual2 = sortedPopulation[index2]
        else:
            indexCurrent = sortedPopulation.index(current)
            indexBest = np.random.randint(0, self.pBestRange)
            best = sortedPopulation[indexBest]
            (index1, index2) = self.getTwoRandomIndex(len(sortedPopulation), indexBest, indexCurrent)
            randomIndividual1 = sortedPopulation[index1]
            randomIndividual2 = sortedPopulation[index2]

        randomVariable = np.random.randint(0, current.genotype.size-1)          #???

        for i in range(current.genotype.size):
            if np.random.random() < self.CR or i == randomVariable:
                current.child.chromosome[i] = current.genotype.chromosome[i] + self.F*(best.genotype.chromosome[i] - current.genotype.chromosome[i]) + \
                    self.F*(randomIndividual1.genotype.chromosome[i] - randomIndividual2.genotype.chromosome[i])
            else:
                current.child.chromosome[i] = current.genotype.chromosome[i]
            # check boundaries
            if current.child.chromosome[i] <  geneMin:
                current.child.chromosome[i] =  geneMin
            elif current.child.chromosome[i] >  geneMax:
                current.child.chromosome[i] =  geneMax

    def get_two_random_affines(self, population, current):

        sample = 10
        muestra = np.random.sample(range(0, self.populationSize), sample)
        comparado = None
        distancias = []
        distanciaAIndice = {}

        dist = 0.0

        for indice in muestra:
            comparado = population[indice]
            dist = current.genotypic_distance(comparado)
            distancias.append(dist)
            distanciaAIndice[dist] = indice

        distancias = sorted(distancias)

        d10 = distancias[sample-1]
        umbral_dist = 2*d10/10.0

        max_dist=0
        current_dist=0
        max_index= 0

        for index in range(len(distancias) - 1):
            current_dist = abs(distancias[index+1] - distancias[index])
            if current_dist > max_dist:
                max_dist = current_dist
                max_index = index

        indice_corte = 0
        if max_dist > umbral_dist:
            indice_corte = max_index
        else:
            indice_corte = sample

        if indice_corte < 2:
            indice_corte = 2

        if indice_corte >= 2:
            r1 = random.randint(0, indice_corte-1)
            r2 = (r1 + random.randint(0, indice_corte-2)) % indice_corte

            dist_de_r1 = distancias[r1]
            dist_de_r2 = distancias[r2]
            indice1 = distanciaAIndice[dist_de_r1]
            indice2 = distanciaAIndice[dist_de_r2]
            return (indice1, indice2)

    def get_best_affine(self, population, current):
        muestras = 30
        distancias = []
        population_size = len(population)
        for i in range(muestras):
            r1 = random.randint(0, population_size -1)
            r2 = random.randint(0, population_size - 1)
            distancias.append(population[r1].genotypic_distance(population[r2]))

        distancias = sorted(distancias)
        d30 = distancias[muestras-1]
        umbral = 2*d30/30.0

        current_dist = 0
        max_dist = 0
        max_index = 0
        indice_a_distancia = {}

        for index in range(len(distancias) - 1):
            current_dist = abs(distancias[index+1] - distancias[index])
            if current_dist > max_dist:
                max_dist = current_dist
                max_index = index
            indice_a_distancia[index] = current_dist

        distancia_corte = 0

        if max_dist > umbral:
            distancia_corte = distancias[max_index]
        else:
            distancia_corte = distancias[muestras-1]

        #afines
        #si no hay ninguno el mas afin
        best_affine = None
        min_distance_of_best = 99999.99
        dist = 0.0
        index_min = 0
        one_affine = False
        for i in range(self.pbestRange):
            dist = population[i].genotypic_distance(current)
            if dist < distancia_corte and not one_affine:
                one_affine = True
                best_affine = population[i]
            if dist < min_distance_of_best:
                min_distance_of_best = dist
                index_min = i
        if best_affine is None:
            best_affine = population[index_min]
        return best_affine


    def getTwoRandomIndex(self, range, index1, index2):
        r1 = np.random.randint(0, range-1)
        r2 = np.random.randint(0, range-1)

        while r1 == index1 or r2 == index2 or r1 == r2:
            r1 = np.random.randint(0, range-1)
            r2 = np.random.randint(0, range-1)

        return (r1, r2)


################################################################################

# class RecombinationOperators:
#
#     def __init__(self, pReplacer, pMater, pPreference, pGeneVariability, pAlpha, pPercentOfGenes, pMutationRate, pSuperMutationProb, pMutationPercent, pMutationAmplitude):
#         self.replacer = pReplacer
#         self.mater = pMater
#
#         self.preference = pPreference
#         self.geneVariability = pGeneVariability
#
#         self.alpha = pAlpha
#         self.percentOfGenes = pPercentOfGenes
#
#         self.mutationRate = pMutationRate
#         self.superMutationProbability = pSuperMutationProb
#         self.mutationPercent = pMutationPercent
#         self.mutationAmplitude = pMutationAmplitude
#
#     def selectMatings(self):
#         matesGenotype = self.mater.listOfMates
#         bestMateIndex = 0
#         matesMaxFitness = -np.finfo(float).max
#         for i in range(len(matesGenotype)):
#             if matesMaxFitness < matesGenotype[i].fitness:
#                 bestMateIndex = i
#                 matesMaxFitness = matesGenotype[i].fitness
#         return matesGenotype[bestMateIndex]
#
#     def startMating(self, pOwnGenotype):
#         self.mate(pOwnGenotype, self.selectMatings())
#
#     def mate(self, pReceiver, pOther):
#         if(np.random.uniform(0.0, 1.0) < self.mutationRate):
#             self.mutationMating(pReceiver, pOther)
#         else:
#             self.crossoverMating(pReceiver, pOther)
#
#     def mutationMating(self, pReceiver, pOther):
#         newGenotype = Genotype(len(pReceiver.chromosome))
#         if np.random.uniform(0.0, 1.0) < self.preference:
#             newGenotype.chromosome = self.mutate(pReceiver.chromosome)
#             estimatedFitness = pReceiver.fitness
#         # mutation over Other
#         else:
#             newGenotype.chromosome = self.mutate(pOther.chromosome)
#             estimatedFitness = pOther.fitness
#
#         newGenotype.fitness = estimatedFitness*0.5
#         self.replacer.embryoGenotype = newGenotype
#
#     def crossoverMating(self, pReceiver, pOther):
#         newGenotype = Genotype(len(pReceiver.chromosome))
#         newGenotype.chromosome = self.crossover(
#             pReceiver.chromosome, pOther.chromosome)
#
#         newGenotype.fitness = (pReceiver.fitness + pOther.fitness) * 0.5
#         self.replacer.embryoGenotype = newGenotype
#
#     def crossover(self, pReceiverChromosome, pOtherChromosome):
#         size = len(pReceiverChromosome)
#
#         newChromosome = [None for i in range(size)]
#
#         for i in range(size):
#             if np.random.uniform(0.0, 1.0) < self.percentOfGenes:
#                 newChromosome[i] = self.BLXCrossover(
#                     pReceiverChromosome[i], pOtherChromosome[i])
#             else:
#                 if (np.random.uniform(0.0, 1.0) < 0.5):
#                     newChromosome[i] = pReceiverChromosome[i]
#                 else:
#                     newChromosome[i] = pOtherChromosome[i]
#         return newChromosome
#
#     def BLXCrossover(self, pReceiverGene, pOtherGene):
#         dist = np.abs(pReceiverGene - pOtherGene)
#         minimum = np.minimum(pReceiverGene, pOtherGene)
#         maximum = np.maximum(pReceiverGene, pOtherGene)
#
#         dif = maximum + alpha*dist - (minimum - alpha*dist)
#         return self.checkBoundaries(minimum - alpha*dist + np.random.uniform(0, 1)*dif)
#
#     def checkBoundaries(self, gene):
#         if gene > geneMax:
#             return geneMax
#         elif gene < geneMin:
#             return geneMin
#         return gene
#
#     def mutateGene(self, gene):
#         superMut = np.random.uniform(0.0, 1.0)
#         if superMut < self.superMutationProbability:
#             print("WHAT")
#             print("Valor aletorio ", superMut)
#             print("Prob Supermutation ", self.superMutationProbability)
#             #return randomGene()
#         else:
#             return self.checkBoundaries(gene + (np.random.uniform(0.0, 1.0) - 0.5)*self.mutationAmplitude)
#
#     def mutate(self, pChromosome):
#         mutated = pChromosome
#         for i in range(len(mutated)):
#             if np.random.uniform(0, 1) < mutationPercent:
#                 mutated[i] = self.mutateGene(pChromosome[i])
#         return mutated
#

#
#
# class MatingOperators:
#
#     def __init__(self, pPendingMatings, pMaxTournament, pMaxLifeTime):
#         self.pendingMatings = pPendingMatings
#         self.matesAllowed = pPendingMatings
#         self.isMating = False
#         self.listOfMates = []
#
#         self.maxTournament = pMaxTournament
#         self.maximunMatingProbability = pMaxTournament/pMaxLifeTime
#         self.matingProbability = pMaxTournament/pMaxLifeTime
#         #print(pMaxTournament,pMaxLifeTime,self.matingProbability)
#
#     def checkMating(self):
#         if self.isMating:
#             pass
#         else:
#             if np.random.uniform(0, 1) < self.matingProbability:
#                 self.isMating = True
#
#     def addMate(self, pGenotype):
#         self.listOfMates.append(pGenotype)
#         self.pendingMatings -= 1
#
#     def resetMatingStatus(self):
#         self.pendingMatings = self.matesAllowed
#         self.isMating = False
#         self.listOfMates = []
#
#         self.matingProbability = self.maximunMatingProbability
