#include <cstdlib>
#include "pgmFunctions.hpp"

void PgmFunctions::open(const char* pgmin,const char* pgmout)
{
    char chi;
    char chaine[100];
    long int i = 0;
    
    if ((fio = fopen(pgmin, "rb"))==NULL)
        printf ("\n\rOPEN : ERREUR : FILE doesn't exist");
    else printf("\n\rOPEN : SUCCESS\n");
    
    if ((fir = fopen(pgmout, "wb+"))==NULL)
        printf ("n\rOPEN : ERREUR : FILE cannot be created");
    else printf ("\n\rOPEN : SUCCESS again\n");

    
    fscanf(fio, "%s\n", chaine);//ligne 1 (p5)
    fprintf(fir, "%s\n", chaine);    
    do                          //ligne 2
    {
        chi = fgetc(fio);
        fputc(chi, fir);
 
    } while(chi != '\n');      //fin ligne 2
    
    fscanf(fio, "%ld %ld\n", &dimx, &dimy); //ligne 3
    fprintf(fir, "%ld %ld\n", dimx, dimy);
    
    fscanf(fio, "%ld\n", &nbg);//ligne 4
    fprintf(fir, "%ld\n", nbg);
    taille = dimx*dimy;
    

    pgmInit = new unsigned char[taille];
    
    for (i = 0; i<taille; i++)
    {
                //printf(" %d ",chi);
               pgmInit[i] = (unsigned char)fgetc(fio);
    }
    pgmTemp = new unsigned char[taille];
    copi();
}


void PgmFunctions::copi(void)
{
    long int i;
    for (i=0; i < taille; i++)
        pgmTemp[i] = pgmInit[i];
}


void PgmFunctions::rcopi(void)
{
    long int i;
    for (i=0; i < taille; i++)
        pgmInit[i] = pgmTemp[i];
}

void PgmFunctions::seuil(unsigned char seuil)
{
    long int i,j;
    for (i = 0; i<dimy; i++)
        for (j = 0; j<dimx; j++)
        {
            if(pgmInit[i*dimx + j]>seuil)
                pgmTemp[i*dimx + j] = 255;
            else 
                pgmTemp[i*dimx + j] = 0;
        }
    rcopi();
}


void PgmFunctions::save()
{
    long int i,j;
        for (i = 0; i<dimy; i++)
        for (j = 0; j<dimx; j++)
        {
            fputc((unsigned char)pgmTemp[i*dimx + j], fir);
 
        }
}

void PgmFunctions::select_bas()
{
        long int i,j;
        bool ok;
        for (i = 0; i<dimx; i++)
        {
            ok = true;
        for (j = 0; j<dimy; j++)
        {
            if (ok)
                {if (pgmTemp[taille -(i + j*dimx) - 1]==255)
                ok = false;}//end ok
            else pgmTemp[taille -(i + j*dimx) - 1]=0;//not ok
        }//j
        }//i

        rcopi();
}





PgmFunctions::PgmFunctions(const char* pgmin,const char* pgmout)
{
    pgmInit = NULL;
    pgmTemp = NULL;
    fir = NULL;
    fio = NULL;
    open(pgmin,pgmout);
}

PgmFunctions::~PgmFunctions()
{
    save();
    if (fio == NULL)
        printf ("fio not open\n");
    else
    fclose(fio);

    if (fir == NULL)
        printf ("fir not open\n");
    else
    fclose(fir);

    if (pgmInit == NULL)
        printf ("init not open\n");
    else
    free(pgmInit);
    if (pgmTemp == NULL)
        printf ("pgmTemp not open\n");
    else
    free(pgmTemp);
}