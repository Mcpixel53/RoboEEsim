import numpy as np
import Configuration as cnf


##Internal Functions:
k = 0.5 #0.5

def sigmoid(x):
    return 1 / (1 + np.exp(-k*x))

def nonlin(x,deriv=False):
    if(deriv==True):
        return x*(1-x)
    return 1/(1+np.exp(-k*x))

def tanh(x):
    return np.tanh(x)

def ReLU(x):
    return x * (x > 0)

#########################################################
class MLPNeuralNetwork:

    def __init__(self):
        self.input = cnf.Config.inputSize
        self.hidden = cnf.Config.hiddenSize
        self.output = cnf.Config.outputSize
        self.wi = (2.0*np.random.rand(self.input+1, self.hidden)-1.0)*1.0
        self.wo = (2.0*np.random.rand(self.hidden+1, self.output)-1.0)*1.0
        self.size = self.wi.size + self.wo.size


    def forward(self, input):
        if len(input) != self.input:
            raise ValueError('Wrong number of inputs')

        input_with_bias = np.append(input, 1.0)
        activations = ReLU(np.dot(input_with_bias, self.wi))
        activations_with_bias = np.append(activations, 1.0)
        out = sigmoid(np.dot(activations_with_bias,self.wo))
        return out

    def updateWeights(self, Genes):
        new_weights = np.asarray(Genes, dtype=np.float32)
        if len(new_weights) != self.size:
            return
            # raise ValueError('Wrong number of parameters')
        weights = (2.0 * new_weights - 1.0) *5.0
        self.wi = np.reshape(weights[:self.wi.size], (self.input+1, self.hidden))
        self.wo = np.reshape(weights[self.wi.size:], (self.hidden+1, self.output))


    def updateWeights2(self, Genes):
        sizeW1 = np.prod(self.wi.shape)
        flatW1 = Genes[:sizeW1]
        flatW2 = Genes[sizeW1:]

        self.wi = np.reshape(flatW1, self.wi.shape)
        self.wo = np.reshape(flatW2, self.wo.shape)

    def __str__ (self):
        return "MPL Neural Network. " + str(self.inputSize) +" input layers, "\
        + str(self.hiddenSize) + " hidden layers, "  + str(self.outputSize) + " output layers."

#########################################################

class Neural_Network(object):

  def __init__(self):

    #parameters
    self.inputSize = cnf.Config.inputSize
    self.outputSize = cnf.Config.outputSize
    self.hiddenSize = cnf.Config.hiddenSize

    #Weights

    self.W1 = np.random.uniform(low = cnf.Config.minWeight , high =cnf.Config.maxWeight, size = (self.inputSize,self.hiddenSize))
    self.W2 = np.random.uniform(low = cnf.Config.minWeight , high =cnf.Config.maxWeight, size = (self.hiddenSize,self.outputSize))

    self.size = np.prod(self.W1.shape)+np.prod(self.W2.shape)

  def forward(self,X):
    self.z = np.dot(X, self.W1)

    o = np.dot(self.z,self.W2)

    return o

  def updateWeights(self, Genes):
    sizeW1 = np.prod(self.W1.shape)
    flatW1 = Genes[:sizeW1]
    flatW2 = Genes[sizeW1:]

    self.W1 = np.reshape(flatW1,self.W1.shape)
    self.W2 = np.reshape(flatW2,self.W2.shape)

  def __str__ (self):
      return "Generic Neural Network. " + str(self.inputSize) +" input layers, "\
      + str(self.hiddenSize) + " hidden layers, "  + str(self.outputSize) + " output layers."



class sigNeural_Network(object):


  def __init__(self):
    #parameters
    self.inputSize = cnf.Config.inputSize
    self.outputSize = cnf.Config.outputSize
    self.hiddenSize = cnf.Config.hiddenSize

    #seed
    np.random.seed(1)
    #Weights
    self.W1 = np.random.uniform(low = cnf.Config.minWeight , high =cnf.Config.maxWeight, size = (self.inputSize,self.hiddenSize))
    self.W2 = np.random.uniform(low = cnf.Config.minWeight , high =cnf.Config.maxWeight, size = (self.hiddenSize,self.outputSize))

    self.size = np.prod(self.W1.shape)+np.prod(self.W2.shape)


  def forward(self,X):
    try:
        hL = nonlin(np.dot(X,self.W1))
        o = nonlin(np.dot(hL,self.W2))
    except Exception as e:
        print("Error with the neural controller!",e)
    return o

  def updateWeights(self, Genes):
    sizeW1 = np.prod(self.W1.shape)
    flatW1 = Genes[:sizeW1]
    flatW2 = Genes[sizeW1:]

    self.W1 = np.reshape(flatW1,self.W1.shape)
    self.W2 = np.reshape(flatW2,self.W2.shape)

  def __str__ (self):
      return "Sigmoid Neural Network. k=" + str(k) +" "+ str(self.inputSize) \
      + " input layers, " + str(self.hiddenSize) + " hidden layers, "  + str(self.outputSize) + " output layers."
