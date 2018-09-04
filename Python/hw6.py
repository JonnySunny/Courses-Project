##CSci1133
##Zhongyi Sun
##Date 10/27



##--A

def count(char, text):
    global times
    if(len(text)==1):
        if(char == text[0]):
            return 1
        else:
            return 0
    if(len(text)>1):
        if(text[0] == char):
            return 1+count(char, text[1:])
        else:
            return count(char, text[1:])




##--B
def isEqual(list1, list2):
    if(len(list1)!= len(list2)):
        return False
    if(len(list1)==1 and len(list2)==1):
        if(list1[0] == list2[0]):
            return True
        else:
            return False
##    if(len(list1) > 1 and len(list2) > 1):
##        if(list1[-1]==list2[-1]):
##            
##            return isEqual(list1[:-1],list2[:-1])
##        else:
##            return False

    if(len(list1) > 1 and len(list2) > 1):
        if(list1[0]==list2[0]):
            return isEqual(list1[1:],list2[1:])
        else:
            return False


##--C
look_up = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
def convertBase(n, base):
    
    if(n // base > 0):
        if(base > 10):
            if(n%base>9):
                return convertBase(n//base, base)+look_up[n%base -10]
            else:
                return convertBase(n//base, base)+str(n%base)
        else:
            return convertBase(n//base, base)+str(n%base)
    if(n // base == 0):
        if(n%base > 9):
            return look_up[n%base -10]
        else:
            return str(n%base)
    

    
    

