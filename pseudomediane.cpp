//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//int dimx,dimy;
 
FILE *fio, *fir;
 
int main()
{
    unsigned char chi;
 
    int *io, *ir;
    long int k = 3, s = 1, nbg;
    long int i, j, dimx, dimy, taille;
 
    char entree[35], sortie[35], chaine[10];
 
    printf("donner entree sans .pgm\n");
    scanf("%s", entree);
    strcat(entree, ".pgm");
 
    printf("donner sortie sans .pgm\n");
    scanf("%s", sortie);
    strcat(sortie, ".pgm");
 
 
    fio = fopen(entree, "rb");
    fir = fopen(sortie, "wb+");
 
    if (fio != NULL) printf("ouverture du fichier in\n");
    if (fir != NULL) printf("ouverture du fichier out\n");
 
    //if(im!=0) printf("allocation de im\n");
 
    //lecture entete ppm
    fscanf(fio, "%s\n", chaine);
    fprintf(fir, "%s\n", chaine);
 
 
    i = 0;
    while (i<1)
    {
        chi = fgetc(fio);
        // if((int)chi==6)  fputc((unsigned char)5,fr);
        fputc(chi, fir);
        if (chi == '\n') i++;
    }
 
    fscanf(fio, "%ld %ld\n", &dimx, &dimy);
    fprintf(fir, "%ld %ld\n", dimx, dimy);
 
 
    fscanf(fio, "%d\n", &nbg);
    fprintf(fir, "%d\n", nbg);
 
    printf("dimx=%d dimy=%d nbg=%d\n", dimx, dimy, nbg);
 
    io = (int *)malloc(dimx*dimy * sizeof(int));
 
    ir = (int *)malloc(dimx*dimy * sizeof(int));
 
    if (ir == NULL) printf("allocation ir impossible\n");
 
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
 
 
 
    //Traitement
    for (j = 0; j < dimx; j++)
    {
        int iNB = -1;
        int iBN = -1;
        for (i = 0; i < dimy - 1; i++)
        {
            if (io[i*dimx + j] == 0 && io[(i + 1)*dimx + j] == 255)
                iNB = i;
            else if (io[i*dimx + j] == 255 && io[(i + 1)*dimx + j] == 0)
                iBN = i;
 
        }
        if (iBN != -1 && iNB != -1)
            ir[((iNB + iBN) / 2) * dimx + j] = 255;
    }
 
    for (i = 0; i<dimy; i++)
        for (j = 0; j<dimx; j++)
        {
            fputc((unsigned char)ir[i*dimx + j], fir);
 
        }
 
 
    free(io); //...
 
    free(ir);
 
    fclose(fio); fclose(fir);
    return 0;
}