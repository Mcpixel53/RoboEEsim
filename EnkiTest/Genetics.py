# Imports
import numpy as np
import Configuration as cnf
# Config Variables


# Mutation
geneMax = cnf.Config.geneMax
geneMin = cnf.Config.geneMin

mutationRate = cnf.Config.mutationRate
mutationAmplitude = geneMax * 0.05
mutationPercent = cnf.Config.mutationPercent

superMutationProbability = cnf.Config.superMutationProbability
geneVariability = cnf.Config.geneVariability


# Mating
cm = cnf.Config.cm
maxTournament = cnf.Config.maxTournament
maturity = cnf.Config.maturity  # Funcion Matematica = 1
maxLifetime = cnf.Config.maxLifetime  # Funcion Matematica 10
maxMatings = cnf.Config.maxMatings

preference = cnf.Config.preference

# Crossover
percentOfGenes = cnf.Config.percentOfGenes
alpha = cnf.Config.alpha

matingSeason = 0.20 * maxLifetime

# Global Variables


# Classes

class Genotype:

    def __init__(self, pDimensions):

        self.chromosome = [None for j in range(pDimensions)]
        self.fitness = 0.0


class RecombinationOperators:

    def __init__(self, pReplacer, pMater, pPreference, pGeneVariability, pAlpha, pPercentOfGenes, pMutationRate, pSuperMutationProb, pMutationPercent, pMutationAmplitude):
        self.replacer = pReplacer
        self.mater = pMater

        self.preference = pPreference
        self.geneVariability = pGeneVariability

        self.alpha = pAlpha
        self.percentOfGenes = pPercentOfGenes

        self.mutationRate = pMutationRate
        self.superMutationProbability = pSuperMutationProb
        self.mutationPercent = pMutationPercent
        self.mutationAmplitude = pMutationAmplitude

    def selectMatings(self):
        matesGenotype = self.mater.listOfMates
        bestMateIndex = 0
        matesMaxFitness = -np.finfo(float).max
        for i in range(len(matesGenotype)):
            if matesMaxFitness < matesGenotype[i].fitness:
                bestMateIndex = i
                matesMaxFitness = matesGenotype[i].fitness
        return matesGenotype[bestMateIndex]

    def startMating(self, pOwnGenotype):
        self.mate(pOwnGenotype, self.selectMatings())

    def mate(self, pReceiver, pOther):
        if(np.random.uniform(0.0, 1.0) < self.mutationRate):
            self.mutationMating(pReceiver, pOther)
        else:
            self.crossoverMating(pReceiver, pOther)

    def mutationMating(self, pReceiver, pOther):
        newGenotype = Genotype(len(pReceiver.chromosome))
        if np.random.uniform(0.0, 1.0) < self.preference:
            newGenotype.chromosome = self.mutate(pReceiver.chromosome)
            estimatedFitness = pReceiver.fitness
        # mutation over Other
        else:
            newGenotype.chromosome = self.mutate(pOther.chromosome)
            estimatedFitness = pOther.fitness

        newGenotype.fitness = estimatedFitness*0.5
        self.replacer.embryoGenotype = newGenotype

    def crossoverMating(self, pReceiver, pOther):
        newGenotype = Genotype(len(pReceiver.chromosome))
        newGenotype.chromosome = self.crossover(
            pReceiver.chromosome, pOther.chromosome)

        newGenotype.fitness = (pReceiver.fitness + pOther.fitness) * 0.5
        self.replacer.embryoGenotype = newGenotype

    def crossover(self, pReceiverChromosome, pOtherChromosome):
        size = len(pReceiverChromosome)

        newChromosome = [None for i in range(size)]

        for i in range(size):
            if np.random.uniform(0.0, 1.0) < self.percentOfGenes:
                newChromosome[i] = self.BLXCrossover(
                    pReceiverChromosome[i], pOtherChromosome[i])
            else:
                if (np.random.uniform(0.0, 1.0) < 0.5):
                    newChromosome[i] = pReceiverChromosome[i]
                else:
                    newChromosome[i] = pOtherChromosome[i]
        return newChromosome

    def BLXCrossover(self, pReceiverGene, pOtherGene):
        dist = np.abs(pReceiverGene - pOtherGene)
        minimum = np.minimum(pReceiverGene, pOtherGene)
        maximum = np.maximum(pReceiverGene, pOtherGene)

        dif = maximum + alpha*dist - (minimum - alpha*dist)
        return self.checkBoundaries(minimum - alpha*dist + np.random.uniform(0, 1)*dif)

    def checkBoundaries(self, gene):
        if gene > geneMax:
            return geneMax
        elif gene < geneMin:
            return geneMin
        return gene

    def mutateGene(self, gene):
        superMut = np.random.uniform(0.0, 1.0)
        if superMut < self.superMutationProbability:
            print("WHAT")
            print("Valor aletorio ", superMut)
            print("Prob Supermutation ", self.superMutationProbability)
            #return randomGene()
        else:
            return self.checkBoundaries(gene + (np.random.uniform(0.0, 1.0) - 0.5)*self.mutationAmplitude)

    def mutate(self, pChromosome):
        mutated = pChromosome
        for i in range(len(mutated)):
            if np.random.uniform(0, 1) < mutationPercent:
                mutated[i] = self.mutateGene(pChromosome[i])
        return mutated


class ReplacementOperators:

    def __init__(self):
        self.embryoGenotype = None
        self.maxLifetime = maxLifetime
        self.cm = cm
        self.maxMinusMaturity = self.maxLifetime - maturity

    def replacementProb(self, pGenotype, pMaxPrivateFitness):
        maxFitness = pMaxPrivateFitness

        if (maxFitness < 0.00000001):
            maxFitness = 0.00000001

        fitnessNorm = pGenotype.fitness/maxFitness

        if fitnessNorm < 2.0*maxFitness/3.0:
            slope = fitnessNorm * self.cm * maxFitness * 3.0/2.0

        else:
            slope = self.cm + (fitnessNorm - 2.0 *
                               maxFitness/3.0)*3*(1 - self.cm)

        return 1.0 / (self.maxMinusMaturity*slope)


class MatingOperators:

    def __init__(self, pPendingMatings, pMaxTournament, pMaxLifeTime):
        self.pendingMatings = pPendingMatings
        self.matesAllowed = pPendingMatings
        self.isMating = False
        self.listOfMates = []

        self.maxTournament = pMaxTournament
        self.maximunMatingProbability = pMaxTournament/pMaxLifeTime
        self.matingProbability = pMaxTournament/pMaxLifeTime
        #print(pMaxTournament,pMaxLifeTime,self.matingProbability)

    def checkMating(self):
        if self.isMating:
            pass
        else:
            if np.random.uniform(0, 1) < self.matingProbability:
                self.isMating = True

    def addMate(self, pGenotype):
        self.listOfMates.append(pGenotype)
        self.pendingMatings -= 1

    def resetMatingStatus(self):
        self.pendingMatings = self.matesAllowed
        self.isMating = False
        self.listOfMates = []

        self.matingProbability = self.maximunMatingProbability


class Individual:

    individualID = 0

    def __init__(self, pDimensions):
        self.genotype = Genotype(pDimensions)
        self.id = Individual.individualID + 1
        Individual.individualID += 1
        self.maxPrivateFitness = 0
        self.age = 0
        self.maxAge = maxLifetime
        self.maturity = maturity
        self.matingOperator = MatingOperators(
            maxMatings, maxTournament, maxLifetime)
        self.replacementOperator = ReplacementOperators()
        self.recombinationOperator = RecombinationOperators(self.replacementOperator, self.matingOperator, preference,
                                                            geneVariability, alpha, percentOfGenes, mutationRate, superMutationProbability, mutationPercent, mutationAmplitude)
        self.genotype.chromosome = self.generateRandomChromosome()
        self.generateEmbryo()

    def setFitness(self, pFitness):
        self.genotype.fitness = pFitness
        if (self.genotype.fitness > self.maxPrivateFitness):
            self.maxPrivateFitness = self.genotype.fitness

    def checkStatus(self):
        self.matingOperator.checkMating()
        self.checkReplacement()

    def checkReplacement(self):
        if self.age > self.maturity:
            if self.age >= maxLifetime or np.random.uniform(0.0, 1.0) < self.replacementOperator.replacementProb(self.genotype, self.maxPrivateFitness):
                tempfitness = self.genotype.fitness
                self.genotype = self.replacementOperator.embryoGenotype
                self.genotype.fitness = tempfitness * 0.5
                self.age = 0
                self.generateEmbryo()
                self.matingOperator.resetMatingStatus()
                # self.genotype.chromosome = self.recombinationOperator.mutate(self.replacementOperator.embryoGenotype.chromosome) #Mutacion no es necesaria
                #self.genotype.fitness = tempfitness*0.5

    def mate(self, pMateGenotype):
        if pMateGenotype.fitness > self.replacementOperator.embryoGenotype.fitness:
            self.matingOperator.addMate(pMateGenotype)

            if pMateGenotype.fitness > self.maxPrivateFitness:
                self.maxPrivateFitness = pMateGenotype.fitness

            if self.matingOperator.pendingMatings == 0:
                self.startMating()

    def startMating(self):
        if len(self.matingOperator.listOfMates) > 1:
            self.recombinationOperator.startMating(self.genotype)
            self.matingOperator.resetMatingStatus()

    def generateRandomChromosome(self):
        newChromosome = [None for j in range(len(self.genotype.chromosome))]
        for i in range(len(newChromosome)):
            newChromosome[i] = randomGene()

        return newChromosome

    def generateEmbryo(self):
        newGenotype = Genotype(len(self.genotype.chromosome))
        newGenotype.chromosome = self.genotype.chromosome[:]
        newGenotype.chromosome = self.recombinationOperator.mutate(
            newGenotype.chromosome)
        self.replacementOperator.embryoGenotype = newGenotype

    def incrementAge(self):
        self.age += 1

    def updateMaxFitness(self,pFitness):
        if pFitness > self.maxPrivateFitness:
            self.maxPrivateFitness = pFitness

    def calculateGenotypicDistance(self, pGenotype):
        pass


def rastriginGene():
    return np.random.uniform(-5.12, 5.12)


def similarityGene():
    return np.random.uniform(0.0, 1.0)


def randomGene():
    return np.random.uniform(geneMin,geneMax)


def main():
    pass
