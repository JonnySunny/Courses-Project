## CSCI 1133
## ZHONGYI SUN
## DATE 10/13
## Homework 4

#-------------------A----------------------------
def ct(symbol): #A helper funtion to convert digits to numbers
    if(symbol == "I"):
        return 1
    if(symbol == "V"):
        return 5
    if(symbol == "X"):
        return 10
    if(symbol == "L"):
        return 50
    if(symbol == "C"):
        return 100
    if(symbol == "D"):
        return 500
    if(symbol == "M"):
        return 1000

def romanNumbers(r):
    #r = str(input("Enter: "))
    counter = 0
    for i in range(len(r)):
        if( r[i] !="I" and r[i] !="V" and r[i] !="X" and r[i] !="L" and r[i] !="C" and r[i] !="D" and r[i] !="M"):
            return 0
        if (counter < 3):
            if(r[i]=="I"):  
                counter += 1
            if( r[i]=="X"):
                counter += 1
            if( r[i]=="C"):
                counter += 1
            if( r[i]=="M"):
                counter += 1
        if(counter > 3):
            return False
    
    else:
        total = ct(r[0])
        i = 1
        if(len(r)==1):
            total = ct(r[0])
        else:
            while i < len(r):
                if(ct(r[i-1])<ct(r[i])):
                    total += ct(r[i]) - 2*ct(r[i-1])
                else:
                    total += ct(r[i])       
                i+=1
        return total
 
#-------------------B----------------------------
def r1Encode(listNum):
    i = 0
    compresslist = []
    
    while i < len(listNum):
        counter = 1
        m = i+1
        n = listNum[i]
        #print(n)
        #print(listNum[1])
        compresslist += [n]
        while m<len(listNum):
            if(listNum[i] == listNum[m]):
                counter += 1
            else:
                break
            m+=1
        i += counter
        compresslist += [counter]
    return compresslist

def encodeTest():
    a = [1,2,3,5,5,5,5,5,5,6,8,8,1,1,1,5,5,12,13,14,14]
    print(r1Encode(a))

#--------------C-------------------------
b =[1, 1, 2, 1, 3, 1, 5, 6, 6, 1, 8, 2, 1, 3, 5, 2, 12, 1, 13, 1, 14, 2] 
def reDecode(listNum):
    i = 0
    list1 = []
    for i in range(0,len(listNum),2):
        number = listNum[i]
        times = listNum[i+1]
        m = 0
        while m < times:
            list1 += [number]
            m+=1
        i += 1
    return list1

reDecode(b)
