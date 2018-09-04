#CSci1133
#Zhongyi Sun

def reverseAssoc(myfriend):
    reverse = {}
    key_list_myfriend = list(myfriend.values()) #reverse the keys and values
    value_list_myfriend = list(myfriend.keys()) #same as above
    for n in range(0,len(key_list_myfriend)):
##        print(n,"  ",key_list_myfriend[n]," ",value_list_myfriend[n])
        reverse[str(key_list_myfriend[n])] = value_list_myfriend[n]
    return reverse


def getNumber():
    # use loops to make a ditionary called ans
    ans ={}
    for n in range(10):
        ans[str(n)]=str(n)
    for m in "abcdefghijklmnopqrstuvwxyz":
        if(m == 'a' or m == 'b' or m == 'c'):  
            ans[m]='2'
        if(m == 'd' or m == 'e' or m == 'f'):  
            ans[m]='3'
        if(m == 'g' or m == 'h' or m == 'i'):  
            ans[m]='4'
        if(m == 'j' or m == 'k' or m == 'l'):  
            ans[m]='5'
        if(m == 'm' or m == 'n' or m == 'o'):  
            ans[m]='6'
        if(m == 'p' or m == 'q' or m == 'r' or  m == 's'):  
            ans[m]='7'
        if(m == 't' or m == 'u' or m == 'v'):  
            ans[m]='8'
        if(m == 'w' or m == 'x' or m == 'y' or  m == 'z'):  
            ans[m]='9'
    print("If you enter nothing, the process will be terminated") # if enter ''. stop!
    number = input("Enter a telephone number: ").lower() #transfer string into lowercase, for the letters in the dictionary are lowercase letters.
    
    
    while(number != ''):
          ans1 = ''
          counter = 0
          for letter in number:
              if(letter in ans):
                  ans1 += ans[letter]
                  counter += 1
##                  if(counter == 3 or counter ==6):
##                      ans1 += '-'
          if(counter != 10  and counter != 7):
##              print(counter)      
              print("Invalid Number!")
          elif(counter == 10):
              print("Numeric telephone number is: ",ans1[0:3],'-',ans1[3:6],'-',ans1[6:])
          else:
              print("Numeric telephone number is: ",ans1[0:3],'-',ans1[3:7])
          number = input("Enter a telephone number: ").lower()
                    
