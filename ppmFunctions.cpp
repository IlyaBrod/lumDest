#include "ppmFunctions.hpp"
#define ppmR 1
#define ppmG 2
#define ppmB 3


void getChannel(char entree[35],char sortie[35],int channel)
{
    /**         IMPORTATION        **/
    unsigned char chi;
 
    FILE *fio, *fir;

    long int nbg;
    long int i, j, dimx, dimy, taille;
    char entreeP[35],sortieP[35];
    strcpy(entreeP,entree);
    strcpy(sortieP,sortie);
    char chaine[10];
 
    printf("%s %d\n","* Extract color channel",channel);
    strcat(entreeP, ".ppm");
    strcat(sortieP, ".pgm");
    printf("\t%s%s \n\t%s%s\n","Input : ",entreeP,"Output : ",sortieP);
 
    printf("\t%s","OPENING\t");
    fio = fopen(entreeP, "rb");
    fir = fopen(sortieP, "wb+");
 
    if (fio == NULL) printf("Error: Input file doesn't exist\n");
    else if (fir == NULL) printf("Error: Impossible to create output file\n");
    else printf("%s\n","SUCESS");

    //Creation d'entête
    fscanf(fio, "%s\n", chaine);
    fprintf(fir, "%s\n", "P5");
    do
    {
        chi = fgetc(fio);
        fputc(chi, fir);  
    } while(chi != '\n');
 
    fscanf(fio, "%ld %ld\n", &dimx, &dimy);
    fprintf(fir, "%ld %ld\n", dimx, dimy);
 
    fscanf(fio, "%ld\n", &nbg);
    fprintf(fir, "%ld\n", nbg);
 
    printf("\tFormat : dimx=%ld dimy=%ld nbg=%ld\n", dimx, dimy, nbg);

    taille = dimx*dimy;
    
    //lecture des pixels
    for (i = 0; i<taille; i++)
    {
        for(j=0;j<3;j++)
            {
                chi = (unsigned char)fgetc(fio);
                //printf(" %d ",chi);
                if(j==channel-1)
                fputc(chi, fir); 
            }
    }

    fclose(fio);
    fclose(fir);
}