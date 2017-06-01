#include <cstdlib>
#include <math.h>
#include "pgmFunctions.hpp"

void PgmFunctions::open(const char* pgmin,const char* pgmout)
{
    char chi;
    char chaine[100];
    long int i = 0;
    
    if ((fio = fopen(pgmin, "rb"))==NULL)
        {printf ("ComputingError : File %s doesn't exist\n",pgmin);
        exit(EXIT_FAILURE);}
    #ifdef DEBUG_PRINT_pgmF
    else printf("\n\rOPEN : SUCCESS\n");
    #endif //DEBUG_PRINT_pgmF
    if ((fir = fopen(pgmout, "wb+"))==NULL)
        printf ("ComputingError : File %s cannot be created\n",pgmout);
    #ifdef DEBUG_PRINT_pgmF
    else printf ("\n\rOPEN : SUCCESS again\n");
    #endif //DEBUG_PRINT_pgmF
    
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
    #ifdef DEBUG_PRINT_pgmF
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
        #ifdef DEBUG_PRINT_pgmF
        printf ("save : SUCCESS\n");
        #endif //DEBUG_PRINT_pgmF
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
        #ifdef DEBUG_PRINT_pgmF
        printf("selection 1 pix / ligne : SUCCESS\n");
        #endif //DEBUG_PRINT_pgmF
}


void PgmFunctions::select_haut()
{
        long int i,j;
        bool ok;
        for (i = 0; i<dimx; i++)
        {
            ok = true;
        for (j = 0; j<dimy; j++)
        {
            if (ok)
                {if (pgmInit[i + j*dimx]==255)
                ok = false;}//end ok
            else pgmTemp[i + j*dimx]=0;//not ok
        }//j
        }//i

        rcopi();
        #ifdef DEBUG_PRINT_pgmF
        printf("selection H 1 pix / ligne : SUCCESS\n");
        #endif //DEBUG_PRINT_pgmF
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
        #ifdef DEBUG_PRINT_pgmF
        printf ("line completion : SUCCESS\n");
        #endif //DEBUG_PRINT_pgmF

}

void PgmFunctions::passe_bas(int ordre)
{
    #ifdef DEBUG_PRINT_pgmF
    printf("passe bas ordre : %d\n",ordre);
    #endif //DEBUG_PRINT_pgmF
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
        #ifdef DEBUG_PRINT_pgmF
        printf("passe_bas : SUCCESS\n");
        #endif //DEBUG_PRINT_pgmF
        ordre--;
    }while (ordre>0);
}


 void PgmFunctions::pas_isole(void)
 {
     long int i,j,k;
     bool ok;
 char Mx[8]={1,1,0,-1,-1,-1,0,1};
 char My[8]={0,-1,-1,-1,0,1,1,1};
     for (i = 1; i<dimx-1; i++)
        for (j = 1; j<dimy-1; j++)
        {
             ok = false;
            //fputc((unsigned char)pgmTemp[j*dimx + i], fir);
            if (pgmInit[j*dimx + i] != 0)
                for (k=0;k<8;k++)
                    if ((pgmInit[(j+My[k])*dimx + i + Mx[k]]) != 0)
                        ok = true;
            if (ok)
                pgmTemp[j*dimx + i]= 255;
            else 
                pgmTemp[j*dimx + i]= 0;
        }
        rcopi();
        #ifdef DEBUG_PRINT_pgmF
        printf("supretion des points solitaire : SUCCESS\n");
        #endif //DEBUG_PRINT_pgmF
 }


void PgmFunctions::capt_point_extremite(void)
{
    long int i,j,k;
    
     char voisin;
 char Mx[8]={1,1,0,-1,-1,-1,0,1};
 char My[8]={0,-1,-1,-1,0,1,1,1};
     for (i = 1; i<dimx-1; i++)
        for (j = 1; j<dimy-1; j++)
        {
             voisin = 0;
            //fputc((unsigned char)pgmTemp[j*dimx + i], fir);
            if (pgmInit[j*dimx + i] != 0)
                for (k=0;k<8;k++)
                    if ((pgmInit[(j+My[k])*dimx + i + Mx[k]]) != 0)
                        voisin++;
            if (voisin == 1)
            {
                point_extremite_x.push_back(i);
                point_extremite_y.push_back(j);
            }
        }
        #ifdef DEBUG_PRINT_pgmF
        printf("recolte des points extrémités : SUCCESS\n");
        #endif //DEBUG_PRINT_pgmF
}

void PgmFunctions::pgm_point_extremiter(void)
{
    long int i,j;
    //mise a 0 de tmp
        for (i = 0; i<dimx; i++)
        for (j = 0; j<dimy; j++)
            pgmTemp[i + j*dimx]=0;
        
        for (i= 0;i < point_extremite_x.size();i++)
            pgmTemp[point_extremite_x[i]+(point_extremite_y[i]*dimx)]= 255;

        
}

void PgmFunctions::pgm_uv_reader(void)
{
    for (long int i = 0; i<dimx-1; i++)
        for (long int j = 0; j<dimy-1; j++)
        {
            if (pgmInit[i + j*dimx]>0)
                {
                    point_u.push_back(i);
                    point_v.push_back(j);
                }
        }
}


unsigned char* PgmFunctions::get_pgm(void)
{
    return pgmInit;
}
unsigned char* PgmFunctions::get_pgm_tmp(void)
{
    return pgmTemp;
}

PgmFunctions::PgmFunctions(const char* pgmin,const char* pgmout)
{
    pgmInit = NULL;
    pgmTemp = NULL;
    fir = NULL;
    fio = NULL;
    open(pgmin,pgmout);
}

void PgmFunctions::point_un(long int point[2])
{
    point[0] = point_extremite_x[0];
    point[1] = point_extremite_y[0];
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


void PgmFunctions::coloration(const char sortie[35])
{
    FILE *fir;

    unsigned char* to_color = get_pgm_tmp();
    unsigned char* color = get_pgm();
    unsigned char chi,chi_p;

    //Create output
    char sortieP[35];
    strcpy(sortieP,sortie);
    strcat(sortieP, ".ppm");
    fir = fopen(sortieP, "wb+");
    if (fir == NULL) printf("ColorationError: Impossible to create output file\n");
    fprintf(fir, "%s\n", "P6");
    fprintf(fir, "%s\n", "#SpreadLove");
    fprintf(fir, "%ld %ld\n", dimx,dimy);
    fprintf(fir, "%s\n","255");

    for (long int i = 0; i<dimx*dimy; i++)
    {
        chi_p = to_color[i];
        chi = color[i];

        if(chi==0)
        {
            fputc(0, fir);
            fputc(0, fir);
            fputc(0, fir);
        }
        else if(chi_p!=0)
        {
            fputc(255,fir);
            fputc(0,fir);
            fputc(0,fir);
        }
        else
        {
            fputc(255, fir);
            fputc(255, fir);
            fputc(255, fir);
        }
    }

}

void PgmFunctions::fill_Lines(unsigned int X[2], unsigned int Y[2])
{
    copi();
    unsigned int deltax = abs(X[1]-X[0]);
    unsigned int deltay = abs(Y[1]-Y[0]);
    float error =0;
    float deltaerr = (float)deltay/deltax;

    int y=Y[0];
    for(int x=X[0];x<X[1];x++)
    {
        pgmTemp[dimx*y+x] = 255;
        error=error+deltaerr;
        
        
        while(error>0.5)
        {
            if (Y[0] < Y[1])
                y++;
            else
                y--;
            pgmTemp[dimx*y+x] = 255;
            error = error -1.0;
        }
        
    }
    rcopi();
}




void PgmFunctions::trace_Lines()
{
    int taille = point_extremite_x.size();
    //point_extremite_y
    unsigned int x[2];
    unsigned int y[2];
    for(int i=1;i<taille-1;i+=2)
    {
        x[0] = point_extremite_x[i];
        x[1] = point_extremite_x[i+1];
        y[0] = point_extremite_y[i];
        y[1] = point_extremite_y[i+1];
        fill_Lines(x,y);

    }
    

}