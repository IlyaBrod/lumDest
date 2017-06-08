"""
  This file is part of LumDest.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LumDest is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LumDest.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2017 Brodoline Ilya & Pichon Hugot

"""

from os import listdir
from os.path import isfile, join


def csvToObj(inputDir,outputName):
    
    fileList = []
    onlyfiles = [f for f in listdir(inputDir) if isfile(join(inputDir, f))]
    output = open(outputName,'w')
    output.write("#Scanner3D by Brodoline Ilya & Pichon Hugot\n")
    output.write("o Scan\n")


    vertexList = []

    indice = 1

    for index in range(0,len(onlyfiles)):
        print(str(index*100/len(onlyfiles))+"%")


        titlePass = False
        fichier = open(inputDir+"XYZ"+str(index)+".csv",'r')
        lines = fichier.readlines()

        for line in lines:
            #save index for face creation
            vertexList.append(indice)
            indice+=1
            ##

            v1=""
            v2=""
            v3=""   
            idx=0  

            if(titlePass==False):
                    titlePass=True
                    continue

            for charac in line:
                if(charac==";" or charac=="\n"):
                    idx+=1
                elif(idx==0):
                    v1+=charac
                elif(idx==1):
                    v2+=charac
                elif(idx==2):
                    v3+=charac
            output.write("v "+v1+" "+v2+" "+v3+"\n")
        fichier.close()
        fileList.append(vertexList)
        vertexList = []

    output.write("s off\n")
    for el in range(0,len(fileList)-1):
        vertexList1 = fileList[el]
        vertexList2 = fileList[el+1]
        dim = min(len(vertexList1),len(vertexList2))
        for j in range(0,dim-1):
            output.write("f ")
            output.write(str(vertexList2[j]))
            output.write(" "+str(vertexList1[j]))
            output.write(" "+str(vertexList1[j+1]))
            output.write(" "+str(vertexList2[j+1]))
            output.write("\n")

    output.close()
    print("100%")
    
    
