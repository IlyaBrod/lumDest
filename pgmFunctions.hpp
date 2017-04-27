#ifndef pgmF
#define pgmF

//comment to desactive DEBUG print in all program
#define DEBUG_PRINT_pgmF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#

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
    private:
        unsigned char *pgmInit;
        unsigned char *pgmTemp;
        FILE *fir, *fio;
        long int dimx, dimy, nbg,taille;
    public:
        //stock pgm dans pgmInit
        //file->PgmInit
        //file->out
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
        //ne garde que le pixpgmel le plus bas d'une colone' 
        //pgmInit->pgmTemp
        void select_bas();
        void select_haut();
        //complete les trous  -----lent
        void complete_ligne(void);
        //filtre passe bas
        void passe_bas(int ordre = 1);

        void pas_isole(void);

        //initialise les pointeurs
        //def : NULL NULL
        PgmFunctions(const char* pgmin,const char* pgmout);
        ~PgmFunctions();

};


#endif