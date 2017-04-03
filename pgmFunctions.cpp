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
        printf("%c",chi); 
    } while(chi != '\n');      //fin ligne 2
    
    fscanf(fio, "%ld %ld\n", &dimx, &dimy); //ligne 3
    fprintf(fir, "%ld %ld\n", dimx, dimy);
    
    fscanf(fio, "%ld\n", &nbg);//ligne 4
    fprintf(fir, "%ld\n", nbg);
    taille = dimx*dimy;
    

    pgmInit = new char[taille];
    strcpy(pgmInit,"");
    for (i = 0; i<taille; i++)
    {
                //printf(" %d ",chi);
               pgmInit[i] = (unsigned char)fgetc(fio);
    }
    pgmTemp = new char[taille];
    strcpy(pgmTemp,pgmInit);
}



PgmFunctions::PgmFunctions(const char* pgmin,const char* pgmout)
{
    pgmInit = NULL;
    pgmTemp = NULL;
    fir = NULL;
    fio = NULL;
    printf("Pgmfunctions init 1");
    open(pgmin,pgmout);
}

PgmFunctions::~PgmFunctions()
{
    if (fio == NULL)
        printf ("\nfio not open\n");
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