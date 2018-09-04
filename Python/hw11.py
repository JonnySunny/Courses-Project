##CSCI1133
##Zhongyi Sun

class Vehicle():
    def __init__(self,make="",model="",year=0,mileage=0,price=0):
        self.__Make  = make
        self.__Model = model
        self.__Year  = year
        self.__Mileage = mileage
        self.__Price = price
    def setMake(self,make):
        self.__Make = make
    def setModel(self, model):
        self.__Model = model
    def setYear(self, year):
        self.__Year = year
    def setMileage(self, mileage):
        self.__Mileage = mileage
    def setPrice(self, price):
        self.__Price = price
    def getMake(self):
        return self.__Make
    def getModel(self):
        return self.__Model
    def getYear(self):
        return self.__Year
    def getMileage(self):
        return self.__Mileage
    def getPrice(self):
        return self.__Price
    def Display(self):
        print("Make: "+self.__Make)
        print("Year: "+str(self.__Year))
        print("Model: "+self.__Model)
        print("Mileage: "+str(self.__Mileage))
        print("Price: "+str(self.__Price))

    
class Car(Vehicle):
    def __init__(self,make="",model="",year=0,mileage=0,price=0,doors = 0):
        super().__init__(make,model,year,mileage)
        self.__Doors = doors
    def setDoors(self, doors):
        self.__Doors = doors
    def getDoors(self):
        return self.__Doors
    def Display(self):
        print("Inventory unit: Car")
        super().Display()
        print("Number of doors: "+str(self.__Doors))
        
class Truck(Vehicle):
    def __init__(self,make="",model="",year=0,mileage=0,price=0,drivetype = 0):
        super().__init__(make,model,year,mileage)
        self.__Drivetype = drivetype
    def setDrivetype(self, Drivetype):
        self.__Drivetype = Drivetype
    def getDrivetype(self):
        return self.__Drivetype
    def Display(self):
        print("Inventory unit: Truck")
        super().Display()
        print("Drive type: "+str(self.__Drivetype))
        
class SUV(Vehicle):
    def __init__(self,make="",model="",year=0,mileage=0,price=0,passengers= 0):
        super().__init__(make,model,year,mileage)
        self.__Passengers_number = passengers
    def setPassengersCapacity(self, PassengersNumber):
        self.__Passengers_number = PassengersNumber
    def getPassengersCapacity(self):
        return self.__Passengers_number
    def Display(self):
        print("Inventory unit: SUV")
        super().Display()
        print("Passenger Capacity: "+str(self.__Passengers_number))

class Inventory():
    def __init__(self):
        self.vehiclelist = []
    def addVehicle(self,vehicle):
        self.vehiclelist.append(vehicle)
    def Display(self):
        if(len(self.vehiclelist) == 1):
           for each in self.vehiclelist:
            each.Display()
        else:
            for each in self.vehiclelist:
                each.Display()
                print()
                print()            

def main():
    inventory = Inventory()
    type_car = input("Enter type of vehicle or Enter done if you finish it : ").lower()    
    while(not(type_car == "car") and not(type_car == "truck") and not(type_car == "suv") and (not type_car == "done")):
        print("opps! Input incorrectly, try again!")
        type_car = input("Enter type of vehicle or Enter done if you finish it : ").lower()
        print()
    while(not(type_car == "done")):
        make = input("Please enter the Make : ")
        model = input("Please enter the Model : ")
        year = input("Please enter the Year: ")
        mileage = input("Please enter the Mileage: ")
        price = input("Please enter the Price : ")
        if(type_car == "car"):
            newCar = Car()
            newCar.setMake(make)
            newCar.setModel(model)
            newCar.setYear(year)
            newCar.setMileage(mileage)
            newCar.setPrice(price)
            newCar.setDoors(input("Please enter the number of doors(2 or 4) of this car: "))
            inventory.addVehicle(newCar)
        if(type_car == "truck"):
            newTruck = Truck()
            newTruck.setMake(make)
            newTruck.setModel(model)
            newTruck.setYear(year)
            newTruck.setMileage(mileage)
            newTruck.setPrice(price)
            newTruck.setDrivetype(input("Please enter the Drivetype(2-whieel or 4-wheel drive) of this Truck: "))
            inventory.addVehicle(newTruck)
        if(type_car == "suv"):
            newSUV = SUV()
            newSUV.setMake(make)
            newSUV.setModel(model)
            newSUV.setYear(year)
            newSUV.setMileage(mileage)
            newSUV.setPrice(price)
            newSUV.setPassengersCapacity(input("Please enter PassengersCapacity of this SUV: "))
            inventory.addVehicle(newSUV)
        print("you've added this vehicle to the inventory.")
        print()
        type_car = input("Enter type of vehicle or Enter done if you finish it : ").lower()
        while(not(type_car == "car") and not(type_car == "truck") and not(type_car == "suv") and (not type_car == "done")):
            print("opps! Input incorrectly, try again!")
            type_car = input("Enter type of vehicle or Enter done if you finish it : ").lower()
            print()
    inventory.Display()  
        
