
class MyQueue:

    def __init__(self,maxSize):
        self.queue = []
        self.maxSize = maxSize
        self.head = 0
        self.tail = 0

    def getHead(self):
        return self.queue[self.head]

    def getTail(self):
        return self.queue[self.getSize()-1]

    def getSize(self):
        return len(self.queue)

    def isFull(self):
        return len(self.queue) == self.maxSize

    def isEmpty(self):
        return len(self.queue) == 0

    def enqueue(self,val):
        if self.isFull():
            self.dequeue()
        self.queue.insert(0,val)

    def dequeue(self):
        if self.isEmpty():
            return None
        else:
            return self.queue.pop() # quitar o primeiro elemento en troques do ultimo, non?
