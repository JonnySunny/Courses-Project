##CSci 1133
##Zhongyi Sun
##


from time import time
import random
##----------------------A-------------------
class Bug():
    def __init__(self,pos = 0, dire = 1 ): #initialize the position -0, and direction -right
        self.pos = pos
        self.dire = dire
    def move(self):
        if(self.pos>0):
            if(self.dire == 1):
                self.pos += 1
            else:
                self.pos -= 1

    def turn(self):
        self.dire = -self.dire

    def display(self):
        
        for num in range(self.pos):
            print('.',end = "")
        if(self.dire == 1):
            print('>')
        if(self.dire == -1):
            print('<')

def testA():
    a = Bug(10)
    a.move()
    a.display()
    a.turn()
    a.display()
    for i in range(13):
        a.move()
        a.display()


##-----------------B------------------------------
class Stopwatch():
    def __init__(self,  startTime = time(), endTime = time()):
        self.__startTime = startTime
        print("Start Time "+str(self.__startTime))
        self.__endTime = endTime
        print("End Time "+str(self.__endTime))
    def getStartTime(self):
        return self.__startTime
    def getEndTime(self):
        return self.__endTime
    def start(self):
        self.__startTime = time()
    def stop(self):
        self.__endTime = time()
    def elapsedTime(self):
        print("Start Time2 "+str(self.__startTime))
        print("End Time2 "+str(self.__endTime))
        return float(self.__endTime - self.__startTime)

def testB():
    
    randomlist = []
    for i in range(10000):
        randomlist.append(random.randrange(0,10000))
    a = Stopwatch()
    a.start()
    randomlist.sort()
    a.stop()
    print(a.elapsedTime())
