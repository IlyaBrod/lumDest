from WavefrontOBJ import*
from subprocess import call
from os.path import isfile, join

onlyfiles = [f for f in listdir("./Images/Color") if isfile(join("./Images/Color", f))]

countLeft = len(onlyfiles)
index = 0
while (countLeft-index>0):
    
    print("File "+str(index))
    call(["./LumDest", "./Images/Color/laser"+str(index)+".ppm","./Images/Gray/laser"+str(index)+".pgm","./Output/XYZ"+str(index)+".csv"])
    index+=1

print("Converting...")
csvToObj("./Output/","./Output/Object/Scan.obj")
print("DONE")