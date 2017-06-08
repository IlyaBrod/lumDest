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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2017 Brodoline Ilya & Pichon Hugot

"""

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