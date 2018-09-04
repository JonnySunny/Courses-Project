## Homework1 
## CSCI1133 
## Author: ZHONGYI SUN
## Date: 09/16/2016
## Time:12:05-
import turtle
##----------------A------------------
def windchill(temp, wind): # temp is ambientemperature in degrees Fahrenheit; wind is wind velocity in Miles per hour
    windchill_temperature = 35.74 + 0.6215*temp - 35.75*(wind**0.16) + 0.4275*temp*(wind**0.16)
    return windchill_temperature
##print(windchill(-15,20))

##----------------B------------------
def computeWC():
    temp = float(input("Please enter a temperature in degress Fahrenheit: "))
    wind = float(input("Please enter a wind velocity(MPH): "))
    print("The windchill is:",windchill(temp,wind))
computeWC()

##----------------C------------------
def draw_star():
    
    turtle.showturtle()
    length_eachside = turtle.numinput("Please enter a number to the blank", "length of eachside")

    
    turtle.left(36)
    turtle.forward(length_eachside)

    turtle.left(144)
    turtle.forward(length_eachside)

    turtle.left(144)
    turtle.forward(length_eachside)

    turtle.left(144)
    turtle.forward(length_eachside)

    turtle.left(144)
    turtle.forward(length_eachside)

draw_star()
