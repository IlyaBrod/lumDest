#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "ppmFunctions.hpp"
#include "pgmFunctions.hpp"

//michel.chapron1@gmail.com

int main(int argc, char *argv[])
{
    if (argc <= 2)
        { printf ("completez l'apele du programe avec \"./pgm_source ./pgm_cible\"\n");
            exit(1);}

    printf("%s\n%s\n",argv[1],argv[2]);
    PgmFunctions test(argv[1],argv[2]);
    test.seuil();
    test.complete_ligne();
    test.select_bas();
    test.passe_bas(30);
    return 0;
}
