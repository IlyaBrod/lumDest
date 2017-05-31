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
    if (argc <= 2)
        { printf ("completez l'apele du programe avec \"./pgm_source ./pgm_cible\"\n");
            exit(1);}

    printf("%s\n%s\n",argv[1],argv[2]);

    TGM worker(argv[1],argv[2]);

    worker.calcule_XYZ();

    return 0;
}
