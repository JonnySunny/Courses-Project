#SCci 1133
#Zhongyi Sun



from os import path
def main():
    opened = False
    writted = False
    i = 0
    while not opened:
       
        if(i < 3):
            try:
                filename = input("Enter the source filename: ")
                file = open(filename,"r")
                opened  = True
                output_filename = input("Enter the output filename: ")
                
                if(path.isfile(output_filename)):
                    output_file = open(output_filename,"w")
                    a = input("File exists... overwrite? (y/n): ").lower()    
                    if(a == "y"):
                        airport_name = input("Enter airport symbol: ")
                        name = airport_name.upper()
                        for line in file:
                            line1 = line.split(",")
                            if(name == line1[2] or name == line1[4]):
                                #print(line.strip())
                                output_file.write(line.strip())
                                output_file.write("\n")
                        writted = True
                        output_file.close()
                    else:
                        opened = True
                else:
                    output_file = open(output_filename,"w")
                    airport_name = input("Enter airport symbol: ")
                    name = airport_name.upper()
                    for line in file:
                        line1 = line.split(",")
                        if(name == line1[2] or name == line1[4]):
                            #print(line.strip())
                            output_file.write(line.strip())
                            output_file.write("\n")
                    writted = True
                    output_file.close()
                    file.close()
            except FileNotFoundError:
                print("File not found")  
                i += 1
                #print(i)
        else:
            opened = True

    if writted:
        print("Finished")
                

            
