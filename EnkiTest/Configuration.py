
class Config:

    #World
    roundMap = True
    wHeight = 250
    wWidth = 350
    wRadio = 150

    #[General]
    maturity = 20  # Funcion Matematica = 1              maturityTime = 1
    maxLifetime = 200.0  # Funcion Matematica 10         maxLifetime = 100.0
    best = "Fitness"
    graphicInterface = False
    logging = False
    tournamentSize = 10                     ###maxTournament

    #Genes
    geneMax = 1.0
    geneMin = -1.0
    dimensions = 2

    # canonical
    cm = 0.01                                         ### Cm = 0.2
    pMating = tournamentSize/maxLifetime
    crossoverPortion = 1 # era 0.6
    mutationPortion = 0.75 # era 0.25
    mutationRate = 0.2
    mutationAmplitude = 0.05 # 0.5 o 0.1 pruebas gathering 0.05
    crossoverMargin = 0.05


    #Differential
    affinity = False
    F = 0.5     #(coeficiente de diferencias)
    CR = 0.5    #crossover Rate (percentage genes change)
    pbest = 0.15                                        #porcentaxe mellores no differential
    matingAndReplaceProbability = 0.01

    #Mating
    maxMatings = 10
    preference = 0.5

    #Mutation
    superMutationProbability = 0.0
    geneVariability = 0.01
    mutationAmplitude = geneMax * 0.10
    mutationPercent = 0.25

    #CrossOver
    alpha = 0.50
    percentOfGenes = 0.6                                # ???
    fixedTags = 0
    #Neuronal Network
    maxWeight = 1.0
    minWeight = -1.0

    inputSize = 1
    hiddenSize = 3
    outputSize = 1

    #Zones
    fitness_sin_zonas = False
    fitness_dos_zonas = True
    fitness_dos_zonas_una_activa = False

    #Simulation

    environmentWidth = 1000
    environmentHeight = 600

    roboboSpeed = 100
    # roboboSize = 30

    populationSize =                            20   ### populationSize = 40
    sleepTest = 0
    maxIterations = 100000

    angleRange = 50

    fitnessBarOn = True

    fitnessBarWidth = 50
    fitnessBarHeight = 20

    objectiveSize = 3.5
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
