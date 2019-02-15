
class Config:

    #World
    wHeight = 250
    wWidth = 350
    wRadio = 150

    #[General]
    maturity = 20  # Funcion Matematica = 1
    maxLifetime = 200.0  # Funcion Matematica 10
    best = "Fitness"
    #Genes
    geneMax = 1.0
    geneMin = -1.0

    dimensions = 2

    #Mating
    maxTournament = 10
    maxMatings = 10
    preference = 0.5

    #Replacement
    cm = 0.01

    #Mutation
    superMutationProbability = 0.0
    geneVariability = 0.01
    mutationRate = 1.0
    mutationAmplitude = geneMax * 0.10
    mutationPercent = 0.25

    #CrossOver
    alpha = 0.50
    percentOfGenes = 0.60

    #Neuronal Network
    maxWeight = 1.0
    minWeight = -1.0

    inputSize = 1
    hidden_LayerSize = 2
    outputSize = 1

    #Simulation

    environmentWidth = 1000
    environmentHeight = 600

    roboboSpeed = 40
    roboboSize = 30

    populationSize = 20
    sleepTest = 0
    maxIterations = 100000

    angleRange = 50

    fitnessBarOn = True

    fitnessBarWidth = 50
    fitnessBarHeight = 20

    objectiveSize = 10
    objectiveSpeed = 100

    distanceBufferSize = 40

    fastForwardToIterarion = 1
    eachIterationCollection = 1

    startTime = 5

    algorithmSleep = 0.05

    #Data Saving
    startSavingNetworkOnIteration = 1000
    individualIDNetworkData = 1
    experimentName = "Find Objective Fitness DistanceOverTimeSpeed2"
