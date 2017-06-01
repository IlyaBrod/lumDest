#ifndef CLASS_TGM
#define CLASS_TGM

#include "pgmFunctions.hpp"

class TGM
{
    protected:
        PgmFunctions* pic;
        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> z;
        float M[12]; 

        //Resolution du système de Cramer, result[0] = X, result[1] = Y
        void cramer(double lig1[3], double lig2[3],double result[2]);
        //importation d'un fichier CVS dans la matrice M de calibration
        void readCSV();

        //exporc of values
        void saveXYZ(const char* outputName="XYZ.cvs");
    public:
        TGM(const char* pgmin,const char* pgmout = "TGMout.pgm");
        void open(const char* pgmin,const char* pgmout = "TGMout.pgm");
        void calcule_XYZ();
        ~TGM();
};

#endif