#CSCI1133
#Zhongyi Sun
#Homework2
#Date 09/28


import turtle
import math
#--A
def orbit():
    turtle.showturtle()
    turtle.shape('circle')# change the shape of turle
    turtle.dot(40, "yellow")
    #BigCircle x^2 + y^2 = 150^2
    turtle.penup()
    turtle.goto(150,0)
    turtle.pencolor("blue")
    i =  1
    while (i < 1081):# 360* 3 = 1080
        turtle.goto(150* math.cos(math.radians(i)), 150 * math.sin(math.radians(i)))
        i += 1
           

                      
#--B
def compound(startingAmount, targetAmount, interestRate):#All of these are float type.
    sumAmount = startingAmount
    year = 0 # You dont get the interst before you deposit your money to the bank.
    while(sumAmount < targetAmount):
        year = year + 1
        sumAmount = sumAmount + (sumAmount*interestRate)#sumAmount*interestRate means the total interst which you already get.
        
    return year
    

#--C

def perfect(perfect_number):
    i = 2.00
    sum_divisor = 1
    if (perfect_number == 1):# 1 is not a perfect number.
        return False
    else:
        while(i < perfect_number):# Here Divisors don't include itself, so we need "<", not "<="
            if(perfect_number % i == 0):# if it = 0, i is the divisor of this nunmber.
                sum_divisor = sum_divisor+ perfect_number/i #start 1, for every number has 1 as divisor.
                i = i + 1
            else:
                sum_divisor = sum_divisor# if it != 0, just i =i+1. Restart the while looop.
                i = i + 1
    if(sum_divisor == perfect_number):
        return True
    else:
        return False
def perfectList(upperlimit):
    i = 1
    while(i <= upperlimit): #how many numbers are between 1 and upperlimit
        if(perfect(i)): # when it's true, out put the number 
            print(i)
        i = i+1
        
