#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <thread>
#include <cstdlib>

#include "ppmFunctions.hpp"
#include "pgmFunctions.hpp"
#include "tgm.hpp"

//michel.chapron1@gmail.com

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
