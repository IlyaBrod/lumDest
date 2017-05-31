#ifndef CLASS_TGM
#define CLASS_TGM

#include "pgmFunctions.hpp"

class TGM
{
    protected:
        PgmFunctions* pic;
        std::vector<long int> x;
        std::vector<long int> y;
        std::vector<long int> z;
        float M[12]; 

        void cramer(float lig1[3], float lig2[3],float result[2]);
        void readCSV();

    public:
        TGM(const char* pgmin,const char* pgmout = "TGMout.pgm");
        void open(const char* pgmin,const char* pgmout = "TGMout.pgm");
        void calcule_XYZ();
        ~TGM();
};

#endif