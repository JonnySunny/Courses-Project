#CSci1133
#Zhongyi Sun
#Date 10/06

import turtle
import math

#---------------------A-------------------------------
def orbit():
    turtle.showturtle()
    turtle_moon = turtle.Turtle()#get a "moon"
    turtle_moon.shape("circle")
    turtle_moon.color("green")
    turtle.shape('circle')# change the shape of turle
    turtle.dot(40, "yellow")
    turtle.penup()
    turtle.goto(150,0)
    turtle_moon.penup()
    turtle_moon.goto(230,0)
    turtle.color("blue")
    
    i = 0
    while(i<360):# Assume the plane turns around one circle.
        n = 0
        turtle.goto(150* math.cos(math.radians(i)), 150 * math.sin(math.radians(i)))
        
        while (n < 360):#The moon turns first, so we need a nested while loop.
            turtle_moon.goto(150* math.cos(math.radians(i)) + 80* math.cos(math.radians(n)), 150 * math.sin(math.radians(i))+80*math.sin(math.radians(n)))
            n += 5
        i += 2


#-----------------B-------------------------------
def ptrip(a,b,c):
    if (max(a,b,c)==a   and  b**2+c**2==a**2 ):
        return True
    elif (max(a,b,c)==b and  a**2+c**2==b**2 ):
        return True
    elif (max(a,b,c)==c and  b**2+a**2==c**2 ):
        return True
    else:
        return False
def findtriples():
    a = 1
    m = 1 #how many times have tried
    value = int(input("Enter an upper bound > 10: "))
    if(value <= 10):
        while(m < 3):
            print("Input error! Must be > 10")
            m += 1
            value = int(input("Enter an upper bound > 10: "))
        if(m ==3):
            print("Input error! Must be > 10")#if times of trying is greater than 3, Stop 
    else:
        while(a <= value):
            b = 2
            while(b < a):
                c = 3
                while(c < b):
                    if(ptrip(a,b,c)):
                        print("(",c,b,a,")")
                    c+=1
                b+=1
            a+=1
        
                
        
