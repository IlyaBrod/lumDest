#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ppmFunctions.hpp"

//michel.chapron1@gmail.com

int main()
{




    /**         IMPORTATION        **/
    unsigned char chi;
 
    FILE *fio, *fir;

    int *io, *ir;
    long int k = 3, s = 1, nbg;
    long int i, j, dimx, dimy, taille;
    char *pch;
 
    char entree[35],redChannel[35], sortie[35], chaine[10];
 
    printf("* Input file (ppm) ");
    scanf("%s", entree);

    //strcat(entree, ".ppm");

    //get red channel
    strcpy(redChannel,entree);
    strcat(redChannel,"_R");
    getChannel(entree,redChannel,1);
    strcat(redChannel, ".pgm");

    printf("* Output file (pgm) ");
    scanf("%s", sortie);
    strcat(sortie, ".pgm");
    
    printf("\tOPENING\t");
    fio = fopen(redChannel, "rb");
    fir = fopen(sortie, "wb+");
 
    if (fio == NULL) printf("Error: <%s> file doesn't exist\n",redChannel);
    if (fir == NULL) printf("Error: Impossible to create output file\n");
    else printf("SUCESS\n");
     
    //lecture entete ppm
    fscanf(fio, "%s\n", chaine);
    fprintf(fir, "%s\n", chaine);

    do
    {
        chi = fgetc(fio);
        fputc(chi, fir);  
    } while(chi != '\n');
 
    fscanf(fio, "%ld %ld\n", &dimx, &dimy);
    fprintf(fir, "%ld %ld\n", dimx, dimy);
    printf("%ld %ld\n", dimx, dimy);
 
    fscanf(fio, "%ld\n", &nbg);
    fprintf(fir, "%ld\n", nbg);
 
    printf("dimx=%ld dimy=%ld nbg=%ld\n", dimx, dimy, nbg);
 
    io = new int[dimx*dimy];
 
    ir = new int[dimx*dimy];

 
    taille = dimx*dimy;
    printf("taille=%ld\n", taille);
 
    //lecture des pixels
    for (i = 0; i<dimy; i++)
        for (j = 0; j<dimx; j++)
        {
            chi = (unsigned char)fgetc(fio);
            io[i*dimx + j] = (int)chi;
            ir[i*dimx + j] = 0;
        }
 
 
    /**         TRAITEMENT        **/
    int seuil = 207; //we are geany, méthode semi-epirique

    // Limittation au seuil
    for (i = 0; i<dimy; i++)
        for (j = 0; j<dimx; j++)
        {
            if(io[i*dimx + j]>seuil)
                ir[i*dimx + j] = 255;
        }

    //Suppression des singletons

    int testeur_singleton;

    for (i = 1; i<dimy-1; i++)
        for (j = 1; j<dimx-1; j++)
        {
            if(ir[i*dimx + j]==255)
             {
              testeur_singleton =   ir[i*dimx + j - 1] + 
                                    ir[i*dimx + j + 1] +
                                    ir[(i-1)*dimx + j] +
                                    ir[(i-1)*dimx + j +1] +
                                    ir[(i-1)*dimx + j -1] +
                                    ir[(i+1)*dimx + j] +
                                    ir[(i-1)*dimx + j - 1] +
                                    ir[(i-1)*dimx + j + 1];

            if (testeur_singleton < 255)
                if(ir[i*dimx + j]==0);
             }//end if
        }


    /**         EXPORCTATION        **/

     for (i = 0; i<dimy; i++)
        for (j = 0; j<dimx; j++)
        {
            fputc((unsigned char)ir[i*dimx + j], fir);
 
        }

    fclose(fio);
    fclose(fir);

}