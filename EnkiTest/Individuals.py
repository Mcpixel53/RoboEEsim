from Genetics import *

class Individual:
    pass


class DifferentialIndividual:

    individualID = 0
    F = 0.5     #(coeficiente de diferencias)
    CR = 0.5    #crossover Rate (percentage genes change)
        # self.fitness = 0.0
    # self.parentFitness = 0.0
    def __init__(self, pDimensions):
            DifferentialIndividual.individualID += 1
            self.id = DifferentialIndividual.individualID
            self.maxPrivateFitness = 0
            self.maturity = maturity
            self.parent = Genotype(pDimensions)
            # self.maxLifetime = maxLifetime
            self.child = self.parent.create_new() #copy genotype
            self.genotype = self.parent # genotype is the active genotype
            self.replacementOperator = DifferentialEvolutionOperator(pbest, populationSize, conf.affinity, conf.F, conf.CR)
            self.matingAndReplaceProbability = matingAndReplaceProbability         #???Diffecm rential replacement probability
            self.age = 0


    def setParentAsActive(self):
        self.genotype = self.parent
        

    def replaceWithChild(self):
        # self.parent = self.genotype.fitness
        self.parent = self.genotype
        self.genotype = self.child
        # self.genotype = self.child.fitness
        # self.genotype = self.child.create_new()
        # print(" child ",self.child.chromosome," self ",self.genotype.chromosome)
        self.replacementOperator.replace = False
        self.age = 0


    def setFitness(self, pFitness):
        self.genotype.fitness = pFitness
        if (self.genotype.fitness > self.maxPrivateFitness):
            self.maxPrivateFitness = self.genotype.fitness


    def checkStatus(self,population):
        self.checkReplacement(population)


    def checkReplacement(self, population):
        if self.age == self.maturity:
            if self.genotype.fitness < self.parent.fitness:
                # CHILD NOT BETTER, PARENT ACTIVE
                self.setParentAsActive()
        elif self.age > self.maturity:
            if (np.random.random()  <= self.matingAndReplaceProbability or self.age >= maxLifetime):
                self.replacementOperator.replace = True
        if (self.replacementOperator.replace == True):
            sortedPopulation = sorted(population, reverse=True)
            # print(population[0].genotype.chromosome)
            self.replacementOperator.currentToPBest1Bin(sortedPopulation, self)
            self.replaceWithChild()

    def incrementAge(self):
        self.age += 1


    def genotypic_distance(self, other):
        dist = 0.0
        for i in range(len(self.genotype.chromosome)):
            dist += (self.genotype.chromosome[i] - other.genotype.chromosome[i])*(self.genotype.chromosome[i] - other.genotype.chromosome[i])
        dist = sqrt(dist)
        return dist


    def __lt__ (self, other):
        return self.genotype.fitness < other.genotype.fitness

    def __gt__ (self, other):
        return other.__lt__(self)

    def __eq__ (self, other):
        return self.genotype.fitness == other.genotype.fitness

    def __ne__ (self, other):
        return not self.__eq__(other)

    def __str__ (self):
        return "differential"


# TODO: ToDo subclass Individual
class CanonicalIndividual:

    individualID = 0

    def __init__(self, pDimensions):
        CanonicalIndividual.individualID += 1
        self.id = CanonicalIndividual.individualID
        self.genotype = Genotype(pDimensions)
        self.embryo = self.genotype.create_new()
        self.age = 0
        self.pendingMatings = 0
        self.maximumPrivateFitness = 0.0
        self.minimumPrivateFitness = 0.0
        # self.maxLifetime = maxLifetime
        self.maturity = maturity
        self.matingOperator = CanonicalMating(conf.mutationAmplitude, conf.mutationPortion, conf.crossoverPortion, conf.crossoverMargin)
        self.replacementOperator = CanonicalReplacement(maxLifetime, cm, maturity)
        # self.recombinationOperator = RecombinationOperators(self.replacementOperator, self.matingOperator, preference,
                                                            # geneVariability, alpha, percentOfGenes, mutationRate, superMutationProbability, mutationPercent, mutationAmplitude)
        # self.genotype.chromosome = self.generateRandomChromosome()

    # @property
    # def privateFitness(self):
    #     return self.genotype.fitness
    #
    # @privateFitness.setter
    # def privateFitness(self, value):
    #     self.genotype.fitness = value
    #     if self.genotype.fitness < 0.0:
    #         self.genotype.fitness = 0.0
    #     if self.genotype.fitness > self.maximumPrivateFitness:
    #         self.maximumPrivateFitness = self.genotype.fitness
    #     elif self._privateFitness < self.minimumPrivateFitness:
    #         self.minimumPrivateFitness = self.genotype.fitness

    def setFitness(self, value):
        self.genotype.fitness = value
        if self.genotype.fitness < 0.0:
            self.genotype.fitness = 0.0
        if self.genotype.fitness > self.maximumPrivateFitness:
            self.maximumPrivateFitness = self.genotype.fitness
        elif self.genotype.fitness < self.minimumPrivateFitness:
            self.minimumPrivateFitness = self.genotype.fitness


    def updateFitnessLimits(self, maximum_of_other, minimum_of_other):
        if maximum_of_other > self.maximumPrivateFitness:
            self.maximumPrivateFitness = maximum_of_other
        if minimum_of_other < self.minimumPrivateFitness:
            self.minimumPrivateFitness = minimum_of_other

    def checkReplacement(self):
        if self.age > self.maturity:
            replacement_prob = self.replacementOperator.replacementProb(self)
            if self.age >= maxLifetime or np.random.random() < replacement_prob:
                self.generateEmbryo()
                self.genotype = self.embryo
                self.pendingMatings = 0
                self.age = 0

    def checkStatus(self, population):
        self.checkMatings(population)
        self.checkReplacement()

    def generateEmbryo(self):
        self.embryo  =  self.matingOperator.mutate_embryo(self.genotype.create_new())
        # self.embryo.fitness = self.genotype.fitness


    def incrementAge(self):
        self.age += 1

    def checkMatings(self, population):
		if np.random.random() < self.matingOperator.pMating:
		    self.pendingMatings += 1
		if self.pendingMatings > 0:
		    selected = self.select_candidate(self.look_for_candidates(population))
		    if selected is not None and selected.genotype.fitness > self.embryo.fitness:
		        if np.random.random() < self.matingOperator.mutationRate:
		            self.matingOperator.mutation(self, selected)
		        else:
		            self.matingOperator.crossover(self, selected)
		        self.pendingMatings -= 1
			# 	for candidate in pRobotList:
	        # if candidate.individual.id != pCurrent.individual.id:
	        #     pCurrent.individual.updateMaxFitness(candidate.individual.genotype.fitness)
	        #     if candidate.individual.matingOperator.isMating:
	        #         pCurrent.individual.mate(candidate.individual.genotype)
	        #         candidate.individual.mate(pCurrent.individual.genotype)

    def look_for_candidates(self, population):
		candidates = []
		for candidate in population:
		    if candidate is not self:
		        candidate.updateFitnessLimits(
				self.maximumPrivateFitness, self.minimumPrivateFitness)         #???
		        if candidate.pendingMatings > 0:
		            candidates.append(candidate)
		return candidates


    def select_candidate(self, population):
	    max_candidate_private_fitness = -9999.9
	    best_candidate = None
	    for possible_candidate in population:
	        possible_candidate.pendingMatings -= 1
	        if possible_candidate.genotype.fitness > max_candidate_private_fitness:
	            max_candidate_private_fitness = possible_candidate.genotype.fitness
	            best_candidate = possible_candidate
	    return best_candidate

    def __lt__ (self, other):
        return self.genotype.fitness < other.genotype.fitness


    def __gt__ (self, other):
        return other.__lt__(self)


    def __eq__ (self, other):
        return self.genotype.fitness == other.genotype.fitness


    def __ne__ (self, other):
        return not self.__eq__(other)

    def __str__ (self):
        return "cannonical"

# def calculateGenotypicDistance(self, pGenotype):                            ###?
#     pass
#
#
# def rastriginGene():
#     return np.random.uniform(-5.12, 5.12)
#
#
# def similarityGene():
#     return np.random.uniform(0.0, 1.0)
