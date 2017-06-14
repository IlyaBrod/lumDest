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

#ifndef CLASS_TGM
#define CLASS_TGM

#include "pgmFunctions.hpp"

class TGM
{
    protected:
        PgmFunctions* pic;

        //_x _y _z :                                        \
            contienent la position 3D des points de l'image

        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> z;
        float M[12]; 

        //Resolution du système de Cramer, result[0] = X, result[1] = Y
        void cramer(double lig1[3], double lig2[3],double result[2]);
        //importation d'un fichier CVS dans la matrice M de calibration
        void readCSV();

    public:
        TGM(const char* pgmin,const char* pgmout = "TGMout.pgm");
        void open(const char* pgmin,const char* pgmout = "TGMout.pgm");
        void calcule_XYZ();


        //export of values
        void saveXYZ(const char* outputName="XYZ.cvs");
        ~TGM();
};

#endif

/*        _
        |\_,,____
        ( o__o \/
        / (..) \
       (_ )--( _)
       / ""--"" \
,===,=| |-,,,,-| |==,==
|d  |  WW   |  WW   |
|s  |   |   |   |   |
*/

