/*
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

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstdlib>

#include "ppmFunctions.hpp"
#include "pgmFunctions.hpp"
#include "tgm.hpp"


/* MAIN_ ARGV
** argv(1) : ppm file in
** argv(2) : pgm file out
** argv(3) : csv file out
*/
int main(int argc, char *argv[])
{

    printf("\t Extracting RED channel\n");
    getChannel(argv[1],argv[2],1);

    printf("\t Computing values\n");

    TGM worker(argv[2],"temp.pgm");
    worker.calcule_XYZ();
    worker.saveXYZ(argv[3]);

    printf("DONE\n");

    return 0;
}
