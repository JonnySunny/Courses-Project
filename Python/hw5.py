#CSci1133
#Zhongyi Sun
#Date 10/20




import math

def shortestDist(list):
    min_value = math.sqrt((list[0][0]-list[1][0])**2+(list[0][1]-list[1][1])**2)
    for i in range(len(list)):
        for m in range(i+1,len(list)):
            result = math.sqrt((list[i][0]-list[m][0])**2+(list[i][1]-list[m][1])**2)
            if(min_value > result):
                min_value = result
    return min_value
def unitTest():
    a = [[45, -99], [24, 83], [-48, -68], [-97, 99],
        [-8, -77], [-2, 50], [44, 41], [-48, -58], 
        [-1, 53], [14, 86], [31, 94], [12, -91], 
        [33, 50], [82, 72], [83, -90], [10, 78], 
        [7, -22], [90, -88], [-21, 5], [6, 23]]
    print(shortestDist(a))


    
#--B

def gameState(list):
    empty_list = ''
    value_rows = ""
    value_columns = ""
    value_diagonal1 = ""
    value_diagonal2 = ""
    #check each row
    for n in range(len(list)):
        value_rows=''
        for m in range(len(list)):
            if(list[n][m] != ''):
                value_rows += list[n][m]
            if(value_rows == 3*list[n][m]):
                if(list[n][m] == 'X'):
                    return 'X'
                if(list[n][m] == 'O'):
                    return 'O'
    #check each column
    for n in range(len(list)):
        value_columns =''
        for m in range(len(list)):
            if(list[m][n] != ''):
                value_columns += list[m][n]
            if(value_columns == 3*list[m][n]):
                if(list[m][n] == 'X'):
                    return 'X'
                if(list[m][n] == 'O'):
                    return 'O'
    #check diagonal
    for n in range(len(list)):
        for m in range(len(list)):
            if(n == m and list[n][m] != ''):
                value_diagonal1 += list[n][m]
            if(value_diagonal1 == 3*list[n][m]):
                if(list[n][m] == 'X'):
                    return 'X'
                if(list[n][m] == 'O'):
                    return 'O'
    #check diagonal
    for n in range(len(list)):
        for m in range(len(list)):
            if(abs(n-m)==2 and n == m and list[n][m] != ''):
                value_diagonal2 += list[n][m]
            if(value_diagonal2 == 3*list[n][m]):
                if(list[n][m] == 'X'):    
                    return 'X'
                if(list[n][m] == 'O'):             
                    return 'O'
    #check if not finish
    for n in range(len(list)):
        for m in range(len(list)):
            if(list[n][m] == empty_list):            
                return ''
    #check if it is empty
    for n in range(len(list)):
        for m in range(len(list)):
            if(list[n][m] != empty_list):               
                return 'D'
    

def testTTT():
    A = [['X','','O'],['X','O',''],['X','','O']]
    B = [['O','','X'],['X','O',''],['X','','O']]
    C = [['O','X','O'],['X','X','O'],['X','O','X']]
    D = [['','X','O'],['X','O',''],['X','','O']]

    if(gameState(A) == 'X'):
        print ('X wins')
    if(gameState(B)== 'O'):
        print ('O wins')
    if(gameState(C)=='D'):
        print ('Draw')
    if(gameState(D)==""):
        print ('No Win, No Draw')
    
