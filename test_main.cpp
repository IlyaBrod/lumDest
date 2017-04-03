#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "ppmFunctions.hpp"
#include "pgmFunctions.hpp"

//michel.chapron1@gmail.com

int main()
{
    printf ("main first step\n");

    PgmFunctions test("./laser_R.pgm","./test_out.pgm");
    
    return 0;
}
