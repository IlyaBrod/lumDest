#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "ppmFunctions.hpp"
#include "pgmFunctions.hpp"

//michel.chapron1@gmail.com

int main()
{

    PgmFunctions test("./laser_R.pgm","./test_out.pgm");
    test.seuil(204);
    test.select_bas();
    return 0;
}
