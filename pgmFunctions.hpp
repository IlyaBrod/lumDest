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

#ifndef pgmF
#define pgmF

//comment to desactive DEBUG print in all program
//#define DEBUG_PRINT_pgmF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>


/*classe pgm    -> contien 2x l'image
                -> les fonctions de traitements
                -> les fonctions de sauvegarde.

        ordre d'utilisation conseiller :
            seuil
            complete_ligne
            select_bas

*/

class PgmFunctions
{
    protected:
        /*_*pgmInit : used in all traitment-fonctions (the image IN and OUT)
        **_*pgmTemp : used in all traitment-fonctions (the temporary image)
        *******  ++ améloration : only echange the 2 pointer (juste change  ::rcopi)
        **
        **FILE _*fir and *fio needed by open and save
        **_dimx, _dimy, _nbg,_taille : contain dimantion of image : x,y,gray_level_max,x*y
        **
        **_point_extremite_x and --_y are list of extremite's position of any line.
        **
        */
        unsigned char *pgmInit;
        unsigned char *pgmTemp;
        FILE *fir, *fio;
        long int dimx, dimy, nbg,taille;
        std::vector<long int> point_extremite_x;
        std::vector<long int> point_extremite_y;
        

        public:
        /*
        **_point_u and --_v : used to report u and v to a 3D map _x_y_z
        */
        std::vector<long int> point_u;
        std::vector<long int> point_v;


        //stock pgm dans pgmInit
        //file->PgmInit
        //file->out
        /*
        **@param pgmin fichier pgm a traiter
        **@param pgmout fichier pgm dans lequel sera sauvegardé le fichier apres traitements (utile comme memoir tempon)
        */
        void open(const char* pgmin,const char* pgmout);


        //copi pgmInit dans pgmTemp
        //pgmInit->pgmTemp
        void copi(void);
        //copi pgmTemp dans pgmInit
        //pgmTemp->pgmInit


        void rcopi(void);

        //place un pix a 255 si >min sinon 0
        //pgmInit->pgmTemp
        void seuil(unsigned char seuil = 204);
    
    
        //sauvegarde pgmTemp dans le fichier nomé
        //pgmTemp->file
        void save();


        //pgmInit->(pgmTemp,pgmInit)
        //selectionne les point les plus bas sur une colone de pixels (plus utilisé, gardé pour retro-compatibilité)
        void select_bas();
        //selectionne les point les plus haut sur une colone de pixels
        void select_haut();

        //complete les trous  /!\lent
        void complete_ligne(void);

        //filtre passe bas /!\ peut etre tres lent si ordre grand
        // l'ordre 0 ou negatif passe simplement la fonction
        void passe_bas(int ordre = 1);

        //ellimine les pixels isolés
        void pas_isole(void);

        //detecte les points extremité
        //pgmInit -> point extremité x, point extremité y
        void capt_point_extremite(void);

                //DEBUG
        //captures les point extremité sur pgmTemp
        //fx de debuggage. (juste pour verifier que ça marche.) 
                  //DEBUG
        void pgm_point_extremiter(void);

        //complette _point_u et --_v utile pour la 3D
        void pgm_uv_reader(void);

                //DEBUG
        //colorize pixels #Ilya
        //prend un ansien système de parametre
        //gardé pour rétro-compatibilité
        //passe les pts extremités en rouge et autre en blanc
        //sauvegarde dans sortie
                // DEBUG
        void coloration(const char sortie[35]);

        //traçage de lignes #Bresenheim
        void fill_Lines(unsigned int X[2], unsigned int Y[2]);
        //utilise fill_Lines pour chaquepoint extremités
        void trace_Lines();


        void point_un(long int point[2]);


        //accesseur
        unsigned char* get_pgm(void);
        //accesseur (DEBUG)
        unsigned char* get_pgm_tmp(void);

        


        //initialise les pointeurs
        //default : NULL NULL
        PgmFunctions(const char* pgmin,const char* pgmout);
        //sauvegarde les résultat (Iminit)
        //ferme le système : ferme les fichiers en lecture ecriture.
        ~PgmFunctions();

};


#endif