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
 
    //printf("\t%s%s \n\t%s%s\n","Input : ",entreeP,"Output : ",sortieP);
 
    //printf("\t%s","OPENING\t");
    fio = fopen(entreeP, "rb");
    fir = fopen(sortieP, "wb+");
 
    if (fio == NULL) printf("ExtractChannelError: Input %s file doesn't exist\n",entreeP);
    else if (fir == NULL) printf("ExtractChannelError: Impossible to create output %s file\n",sortieP);
    //else printf("%s\n","SUCESS");

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
 
    //printf("\tFormat : dimx=%ld dimy=%ld nbg=%ld\n", dimx, dimy, nbg);

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