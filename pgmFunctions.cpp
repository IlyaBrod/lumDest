#include <cstdlib>
#include "pgmFunctions.hpp"

void PgmFunctions::open(const char* pgmin,const char* pgmout)
{
    char chi;
    char chaine[100];
    long int i = 0;
    
    if ((fio = fopen(pgmin, "rb"))==NULL)
        printf ("\n\rOPEN : ERREUR : FILE doesn't exist");
    #ifdef DEBUG_PRINT
    else printf("\n\rOPEN : SUCCESS\n");
    #endif //DEBUG_PRINT
    if ((fir = fopen(pgmout, "wb+"))==NULL)
        printf ("n\rOPEN : ERREUR : FILE cannot be created");
    #ifdef DEBUG_PRINT
    else printf ("\n\rOPEN : SUCCESS again\n");
    #endif //DEBUG_PRINT
    
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
    #ifdef DEBUG_PRINT
    printf("seuil : %d : SUCCESS\n", seuil);
    #endif
}


void PgmFunctions::save()
{
    long int i,j;
        for (i = 0; i<dimy; i++)
        for (j = 0; j<dimx; j++)
        {
            fputc((unsigned char)pgmTemp[i*dimx + j], fir);
 
        }
        #ifdef DEBUG_PRINT
        printf ("save : SUCCESS\n");
        #endif //DEBUG_PRINT
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
                {if (pgmInit[taille -(i + j*dimx) - 1]==255)
                ok = false;}//end ok
            else pgmTemp[taille -(i + j*dimx) - 1]=0;//not ok
        }//j
        }//i

        rcopi();
        #ifdef DEBUG_PRINT
        printf("selection 1 pix / ligne : SUCCESS\n");
        #endif //DEBUG_PRINT
}


void PgmFunctions::complete_ligne(void)
{
    //completion par la gauche
    /* teste : {X 0+ 1- 1-
    **          1+0+ 1- 1-   
    **          X 0+ 1- 1-}
    ** +(et) -ou
    */
        long int i,j;
    for (i = 0; i<dimx-3; i++)//pas les 3 dernières
        {
        for (j = 1; j<dimy-1; j++)//pas la première ni la dernière
        {
                if (pgmInit[i + j*dimx]!=0)
                {
                    if ( (pgmInit[i+1 + j*dimx]==0) && (pgmInit[i+1 + (j+1)*dimx]==0) && (pgmInit[i +1 + (j-1)*dimx]==0) )
                    {
                        if ( ((pgmInit[i+2 + j*dimx]!=0) || (pgmInit[i+2 + (j+1)*dimx]!=0) || (pgmInit[i +2 + (j-1)*dimx]!=0))
                            || (pgmInit[i+3 + j*dimx]!=0) || (pgmInit[i+3 + (j+1)*dimx]!=0) || (pgmInit[i +3 + (j-1)*dimx]!=0) )
                            {
                            pgmTemp[i+1 + j*dimx] = 255;
                }}}
        }//j
        }//i
        rcopi();
        #ifdef DEBUG_PRINT
        printf ("line completion : SUCCESS\n");
        #endif //DEBUG_PRINT

}

void PgmFunctions::passe_bas(int ordre)
{
    #ifdef DEBUG_PRINT
    printf("passe bas ordre : %d\n",ordre);
    #endif //DEBUG_PRINT
      long int i,j,score,nb_pts;
    //mise a 0 de temps nessessaire
    do {
    for (i = 0; i<dimx; i++)
        for (j = 0; j<dimy; j++)
            pgmTemp[i + j*dimx]=0;
   
    //matrix : {{0.3}c {0.3}c {0.3}c}
    for (i = 1; i<dimx-1; i++)
        {
            score = 0;
            nb_pts =0;
        for (j = 0; j<dimy; j++)//pas la première ni la dernière
        {
            //(pgmInit[i + j*dimx]!=0)
            if (pgmInit[i -1 + j*dimx]!=0)
                {score += j;
                 nb_pts+=1; }
            if (pgmInit[i + j*dimx]!=0)
                {score += j;
                 nb_pts+=1; }
            if (pgmInit[i + 1 + j*dimx]!=0)
                {score += j;
                 nb_pts+=1; }
        }//j
        if (nb_pts != 0)
            pgmTemp[i + dimx*(score/nb_pts)] = 255;

        }//i
        rcopi();
        #ifdef DEBUG_PRINT
        printf("passe_bas : SUCCESS\n");
        #endif //DEBUG_PRINT
        ordre--;
    }while (ordre>0);
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