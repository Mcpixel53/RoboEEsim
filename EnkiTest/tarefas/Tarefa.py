from abc import abstractmethod

class Tarefa:

    def __init__(self):
        print("parent")


    def init(self, anl):
        print("parent 2")

    @abstractmethod
    def init():
        pass
