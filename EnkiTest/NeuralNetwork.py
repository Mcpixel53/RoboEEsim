import numpy as np
import Configuration as cnf

class Neural_Network(object):

  def __init__(self):

    #parameters
    self.inputSize = cnf.Config.inputSize
    self.outputSize = cnf.Config.outputSize
    self.hiddenSize = cnf.Config.hidden_LayerSize

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
